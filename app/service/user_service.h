#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <string>
#include "../../include/crow_all.h"

namespace user_service {
    crow::response register_user(const std::string& username, const std::string& password, const std::string& job, const std::string& rule);
    crow::response get_user_details(int user_id);
    crow::response delete_user(int user_id);
    crow::response update_user(int user_id, const std::string& username, const std::string& password, const std::string& job, const std::string& rule);
}

#endif // USER_SERVICE_H