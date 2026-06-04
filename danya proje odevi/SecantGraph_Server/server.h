#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QObject>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);

private:
    QTcpServer *server;

    QList<QTcpSocket*> clients;

private slots:
    void newClientConnection();
    void readClientData();
    void clientDisconnected();
};

#endif // SERVER_H