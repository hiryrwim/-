#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTcpSocket *socket;

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

    QPushButton *registerButton;
    QPushButton *loginButton;

    QLabel *statusLabel;

private slots:
    void registerUser();
    void loginUser();
    void readServerResponse();
};

#endif // MAINWINDOW_H