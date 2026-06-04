#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "userwindow.h"

#include <QPushButton>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(
        ui->loginButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            QString login =
                ui->loginEdit->text();

            QString password =
                ui->passwordEdit->text();

            if (login == "student" &&
                password == "2026")
            {
                auto* window =
                    new UserWindow();

                window->show();

                this->close();
            }
            else
            {
                QMessageBox::warning(
                    this,
                    "Authorization Error",
                    "Incorrect username or password"
                );
            }
        }
    );
}

LoginWindow::~LoginWindow()
{
    delete ui;
}