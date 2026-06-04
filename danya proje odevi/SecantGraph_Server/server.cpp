#include "server.h"
#include "database.h"

#include <QDebug>

Server::Server(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection,
            this, &Server::newClientConnection);

    if(server->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server started on port 1234";
    }
    else
    {
        qDebug() << "Server error";
    }
}

void Server::newClientConnection()
{
    QTcpSocket *clientSocket =
        server->nextPendingConnection();

    clients.append(clientSocket);

    qDebug() << "New client connected";
    qDebug() << "Total clients:" << clients.size();

    connect(clientSocket,
            &QTcpSocket::readyRead,
            this,
            &Server::readClientData);

    connect(clientSocket,
            &QTcpSocket::disconnected,
            this,
            &Server::clientDisconnected);
}

void Server::readClientData()
{
    QTcpSocket *clientSocket =
        qobject_cast<QTcpSocket*>(sender());

    if(!clientSocket)
        return;

    QString request =
        QString::fromUtf8(clientSocket->readAll()).trimmed();

    qDebug() << "Request:" << request;

    QStringList parts = request.split(" ");

    if(parts.size() < 3)
    {
        clientSocket->write("ERROR\n");
        return;
    }

    QString command = parts[0];
    QString login = parts[1];
    QString password = parts[2];

    Database *db = Database::getInstance();

    if(command == "REGISTER")
    {
        if(db->registerUser(login, password))
        {
            clientSocket->write("REGISTER_OK\n");
        }
        else
        {
            clientSocket->write("REGISTER_ERROR\n");
        }
    }
    else if(command == "LOGIN")
    {
        if(db->loginUser(login, password))
        {
            clientSocket->write("LOGIN_OK\n");
        }
        else
        {
            clientSocket->write("LOGIN_ERROR\n");
        }
    }
}

void Server::clientDisconnected()
{
    QTcpSocket *clientSocket =
        qobject_cast<QTcpSocket*>(sender());

    clients.removeAll(clientSocket);

    qDebug() << "Client disconnected";
    qDebug() << "Total clients:" << clients.size();

    clientSocket->deleteLater();
}