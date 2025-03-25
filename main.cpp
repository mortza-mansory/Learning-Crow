#include "include/crow_all.h"  
#include "app/route/route.cpp" 

int main()
{
    crow::SimpleApp app;  

    routes(app);

    app.port(18080).multithreaded().run();
}