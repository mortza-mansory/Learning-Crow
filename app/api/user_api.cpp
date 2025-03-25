#include <string>
#include "../../include/crow_all.h"
#include "../service/user_service.h"

namespace user_api {

    crow::response register_user(const crow::request& req) {
        auto json = crow::json::load(req.body);
        if (!json) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = json["username"].s();
        std::string password = json["password"].s();
        std::string job = json["job"].s();
        std::string rule = json["rule"].s();

        return user_service::register_user(username, password, job, rule);
    }

    crow::response get_user_details(int user_id) {
        return user_service::get_user_details(user_id);
    }

    crow::response delete_user(int user_id) {
        return user_service::delete_user(user_id);
    }

    crow::response update_user(int user_id, const crow::request& req) {
        auto json = crow::json::load(req.body);
        if (!json) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = json["username"].s();
        std::string password = json["password"].s();
        std::string job = json["job"].s();
        std::string rule = json["rule"].s();

        return user_service::update_user(user_id, username, password, job, rule);
    }

}  // namespace user_api
