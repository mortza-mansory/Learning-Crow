#include "../../include/crow_all.h"
#include "../api/user_api.h"

void routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/register").methods("POST"_method)(user_api::register_user);
    CROW_ROUTE(app, "/users/<int>").methods("GET"_method)([](int user_id) { return user_api::get_user_details(user_id); });
    CROW_ROUTE(app, "/users/<int>").methods("DELETE"_method)([](int user_id) { return user_api::delete_user(user_id); });
    CROW_ROUTE(app, "/users/<int>").methods("PUT"_method)([](crow::request& req, crow::response& res, int user_id) {
        res = user_api::update_user(user_id, req);
    });
}