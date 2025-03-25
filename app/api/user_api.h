#ifndef USER_API_H
#define USER_API_H

#include "../../include/crow_all.h"

namespace user_api {
    crow::response register_user(const crow::request& req);
    crow::response get_user_details(int user_id);
    crow::response delete_user(int user_id);
    crow::response update_user(int user_id, const crow::request& req);
}

#endif // USER_API_H