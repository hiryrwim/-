#include "userwindow.h"
#include "ui_userwindow.h"

// Подключаем заголовочные файлы всех созданных окон
#include "shawindow.h"
#include "binarysearchwindow.h"
#include "dijkstrawindow.h"
#include "vigenerewindow.h"

UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);

    // 1. Кнопка Шифра Виженера
    connect(ui->vigenereButton, &QPushButton::clicked, this, [this]() {
        auto* win = new VigenereWindow();
        win->setAttribute(Qt::WA_DeleteOnClose); // Автоудаление памяти при закрытии окна
        win->show();
    });

    // 2. Кнопка SHA-512
    connect(ui->shaButton, &QPushButton::clicked, this, [this]() {
        auto* win = new SHAWindow();
        win->setAttribute(Qt::WA_DeleteOnClose);
        win->show();
    });

    // 3. Кнопка Бинарного поиска
    connect(ui->binaryButton, &QPushButton::clicked, this, [this]() {
        auto* win = new BinarySearchWindow();
        win->setAttribute(Qt::WA_DeleteOnClose);
        win->show();
    });

    // 4. Кнопка Алгоритма Дейкстры
    connect(ui->dijkstraButton, &QPushButton::clicked, this, [this]() {
        auto* win = new DijkstraWindow();
        win->setAttribute(Qt::WA_DeleteOnClose);
        win->show();
    });
}

UserWindow::~UserWindow()
{
    delete ui;
}