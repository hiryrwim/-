#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QMap>

class Database
{
private:
    static Database* instance;

    QMap<QString, QString> users;

    Database();

public:
    static Database* getInstance();

    bool registerUser(const QString& login,
                      const QString& password);

    bool loginUser(const QString& login,
                   const QString& password);
};

#endif // DATABASE_H