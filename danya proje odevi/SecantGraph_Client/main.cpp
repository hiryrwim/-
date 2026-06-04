#include <QCoreApplication>
#include <QTcpSocket>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream input(stdin);
    QTextStream output(stdout);

    QString login;
    QString password;

    output << "Enter login: ";
    output.flush();
    login = input.readLine();

    output << "Enter password: ";
    output.flush();
    password = input.readLine();

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 1234);

    if(socket.waitForConnected(3000))
    {
        qDebug() << "Connected to server";

        QString registerRequest =
            "REGISTER " + login + " " + password + "\n";

        socket.write(registerRequest.toUtf8());
        socket.waitForBytesWritten();

        socket.waitForReadyRead();
        qDebug() << socket.readAll();

        QString loginRequest =
            "LOGIN " + login + " " + password + "\n";

        socket.write(loginRequest.toUtf8());
        socket.waitForBytesWritten();

        socket.waitForReadyRead();
        qDebug() << socket.readAll();

        output << "Client is connected. Press Enter to exit...";
        output.flush();
        input.readLine();
    }
    else
    {
        qDebug() << "Connection error";
    }

    return 0;
}