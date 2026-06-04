#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    socket = new QTcpSocket(this);

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QLabel *titleLabel = new QLabel("Secant Graph Client");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 14, QFont::Bold));

    QLabel *loginLabel = new QLabel("Login:");
    loginEdit = new QLineEdit();
    loginEdit->setPlaceholderText("Enter login");

    QLabel *passwordLabel = new QLabel("Password:");
    passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Enter password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    registerButton = new QPushButton("Register");
    loginButton = new QPushButton("Login");

    registerButton->setEnabled(false);
    loginButton->setEnabled(false);

    statusLabel = new QLabel("Status: connecting to server...");
    statusLabel->setWordWrap(true);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(loginButton);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(loginLabel);
    mainLayout->addWidget(loginEdit);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(statusLabel);

    setCentralWidget(central);
    setWindowTitle("Secant Graph System Client");
    resize(360, 240);

    this->setStyleSheet(
        "QMainWindow { background-color: #202124; }"
        "QLabel { color: white; font-size: 13px; }"
        "QLineEdit { background-color: #2b2c30; color: white; border: 1px solid #555; border-radius: 6px; padding: 6px; }"
        "QPushButton { background-color: #2563eb; color: white; border-radius: 6px; padding: 7px; font-weight: bold; }"
        "QPushButton:hover { background-color: #1d4ed8; }"
        "QPushButton:disabled { background-color: #555; color: #aaa; }"
        );

    socket->connectToHost("127.0.0.1", 1234);

    connect(socket, &QTcpSocket::connected, this, [this]() {
        statusLabel->setText("Status: connected to server");
        registerButton->setEnabled(true);
        loginButton->setEnabled(true);
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [this]() {
        statusLabel->setText("Status: connection error");
        registerButton->setEnabled(false);
        loginButton->setEnabled(false);
    });

    connect(registerButton, &QPushButton::clicked,
            this, &MainWindow::registerUser);

    connect(loginButton, &QPushButton::clicked,
            this, &MainWindow::loginUser);

    connect(socket, &QTcpSocket::readyRead,
            this, &MainWindow::readServerResponse);
}

MainWindow::~MainWindow()
{
}

void MainWindow::registerUser()
{
    if (loginEdit->text().isEmpty() || passwordEdit->text().isEmpty()) {
        statusLabel->setText("Error: login and password are required");
        return;
    }

    QString request =
        "REGISTER " + loginEdit->text() + " " +
        passwordEdit->text() + "\n";

    socket->write(request.toUtf8());
    statusLabel->setText("Sent register request");
}

void MainWindow::loginUser()
{
    if (loginEdit->text().isEmpty() || passwordEdit->text().isEmpty()) {
        statusLabel->setText("Error: login and password are required");
        return;
    }

    QString request =
        "LOGIN " + loginEdit->text() + " " +
        passwordEdit->text() + "\n";

    socket->write(request.toUtf8());
    statusLabel->setText("Sent login request");
}

void MainWindow::readServerResponse()
{
    QString response = QString::fromUtf8(socket->readAll());
    statusLabel->setText("Server response: " + response);
}