# Learning-Crow
CrowCpp is something new i enjoyed know more about it. 

## This Project Structure Can Be Your Starter Project Structure Using CrowCpp. 


- This is not tutorial or something like that, its just a simple learning case for myself how can we create light wighted backends using cpp.
Here is my exprience using CrowCpp on debain with single header lib Crow.


- First of all i need to know if crow can be my next backend lib that i using, so i just created a simple HTTP client app that is just user management on a university that can be manage the users such as username and teacher, and just put it in a database using sqllite and can be register, delete , get all users details and also update a user via id.

- Second if i gonna use it so what structure i should use ? For it, i using a simple structure that i learned on fastapi ( is a greate python backend freamwork ) on app folder we contains api/route/service folders witch provide over endpoits/api's and functionality over the api's.

- Third is reading doc! yup..that takes alot effort , but i guess the great thing about programmers is at lasted they alwats reading doc around :)

- fourth is making codes and learn by examples to exactly what i wanted. And i learned the Crow is the thing i loved the most, its simple and without any additional thing you can make your own light weghted cpp backend without worries! Cus all neccery things is provided by the CrowCpp ! take your time and use my template if you wanna get started faster.


Here is how you can run it yourself:

- First provide packages for building it:
<My source is just ready to use its haivng the crow_all.h single header lib, but i download it from here by any chance:

```
https://sourceforge.net/projects/crow-framework.mirror/
```
Install lib boost its neccery for building via crow:
```
sudo apt-get install libboost-all-dev
```
Then install the libsql its neccery while building my http client app, cus i using sql in my codes:
```
sudo apt-get install libsqlite3-dev
```
- Second RUN IT!

Just run this command.
```
g++ -std=c++11 -o test main.cpp app/route/route.cpp app/api/user_api.cpp app/service/user_service.cpp -lboost_system -lpthread -lsqlite3
```
then test the api's and have fun.


### Dev: mortza mansouri 
### Reach me @dashclss on telegram.
