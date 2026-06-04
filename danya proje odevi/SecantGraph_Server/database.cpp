#include "database.h"

Database* Database::instance = nullptr;

Database::Database()
{
}

Database* Database::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Database();
    }

    return instance;
}

bool Database::registerUser(const QString& login,
                            const QString& password)
{
    if(users.contains(login))
    {
        return false;
    }

    users[login] = password;
    return true;
}

bool Database::loginUser(const QString& login,
                         const QString& password)
{
    if(!users.contains(login))
    {
        return false;
    }

    return users[login] == password;
}