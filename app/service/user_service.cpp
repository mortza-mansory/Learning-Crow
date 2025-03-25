#include <string>
#include <unordered_map>
#include <sqlite3.h>
#include "../../include/crow_all.h"

namespace user_service {

enum class UserRole { Student, Teacher };

struct User {
    std::string username;
    std::string password;
    std::string job;
    UserRole role;
};

sqlite3* open_database(const std::string& db_name) {
    sqlite3* db;
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Cannot open database: " + std::string(sqlite3_errmsg(db)));
    }
    return db;
}

void create_table_if_not_exists(sqlite3* db) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            password TEXT NOT NULL,
            job TEXT NOT NULL,
            role TEXT NOT NULL
        );
    )";
    char* err_msg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
        sqlite3_free(err_msg);
        throw std::runtime_error("Failed to create table: " + std::string(err_msg));
    }
}

crow::response register_user(const std::string& username, const std::string& password, const std::string& job, const std::string& rule) {
    UserRole user_role;

    if (rule == "student") {
        user_role = UserRole::Student;
    } else if (rule == "teacher") {
        user_role = UserRole::Teacher;
    } else {
        return crow::response(400, "Invalid rule. Must be 'student' or 'teacher'.");
    }

    sqlite3* db = open_database("users.db");
    create_table_if_not_exists(db);

    const char* sql = "INSERT INTO users (username, password, job, role) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return crow::response(500, "Failed to prepare statement.");
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, job.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, (user_role == UserRole::Student) ? "student" : "teacher", -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return crow::response(500, "Failed to execute statement.");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return crow::response(201, "User  registered successfully.");
}

crow::response get_user_details(int user_id) {
    sqlite3* db = open_database("users.db");
    create_table_if_not_exists(db);

    const char* sql = "SELECT username, job, role FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return crow::response(500, "Failed to prepare statement.");
    }

    sqlite3_bind_int(stmt, 1, user_id);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return crow::response(404, "User  not found.");
    }

    const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    const char* job = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    const char* role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

    crow::json::wvalue response_json;
    response_json["username"] = username;
    response_json["job"] = job;
    response_json["rule"] = role;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return crow::response(200, response_json);
}

crow::response delete_user(int user_id) {
    sqlite3* db = open_database("users.db");
    create_table_if_not_exists(db);

    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return crow::response(500, "Failed to prepare statement.");
    }

    sqlite3_bind_int(stmt, 1, user_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return crow::response(404, "User  not found.");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return crow::response(200, "User  deleted successfully.");
}

crow::response update_user(int user_id, const std::string& username, const std::string& password, const std::string& job, const std::string& rule) {
    UserRole user_role;

    if (rule == "student") {
        user_role = UserRole::Student;
    } else if (rule == "teacher") {
        user_role = UserRole::Teacher;
    } else {
        return crow::response(400, "Invalid rule. Must be 'student' or 'teacher'.");
    }

    sqlite3* db = open_database("users.db");
    create_table_if_not_exists(db);

    const char* sql = "UPDATE users SET username = ?, password = ?, job = ?, role = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return crow::response(500, "Failed to prepare statement.");
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, job.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, (user_role == UserRole::Student) ? "student" : "teacher", -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, user_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return crow::response(404, "User  not found.");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return crow::response(200, "User  updated successfully.");
}

}  // namespace user_service