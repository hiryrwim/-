#include "vigenerewindow.h"
#include "ui_vigenerewindow.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

VigenereWindow::VigenereWindow(QWidget *parent, QWidget *menu) :
    QWidget(parent),
    ui(new Ui::VigenereWindow),
    mainMenu(menu) // Сохраняем указатель на UserWindow
{
    ui->setupUi(this);

    // Защита от багов: разрешаем ввод только английских букв и пробелов
    QRegularExpression re("[a-zA-Z ]*");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(re, this);

    ui->textEdit->setValidator(validator);
    ui->keyEdit->setValidator(validator);
}

VigenereWindow::~VigenereWindow()
{
    delete ui;
}

// Кнопка: Зашифровать
void VigenereWindow::on_encryptButton_clicked()
{
    std::string text = ui->textEdit->text().toStdString();
    std::string key = ui->keyEdit->text().toStdString();

    if (text.empty() || key.empty()) {
        ui->resultEdit->setText("Ошибка: Поля «Текст» и «Ключ» не должны быть пустыми!");
        return;
    }

    // Вызов твоего алгоритма шифрования
    std::string encrypted = VigenereCipher::encrypt(text, key);
    ui->resultEdit->setText(QString::fromStdString(encrypted));
}

// Кнопка: Расшифровать
void VigenereWindow::on_decryptButton_clicked()
{
    std::string text = ui->textEdit->text().toStdString();
    std::string key = ui->keyEdit->text().toStdString();

    if (text.empty() || key.empty()) {
        ui->resultEdit->setText("Ошибка: Поля «Текст» и «Ключ» не должны быть пустыми!");
        return;
    }

    // Вызов твоего алгоритма расшифрования
    std::string decrypted = VigenereCipher::decrypt(text, key);
    ui->resultEdit->setText(QString::fromStdString(decrypted));
}

// Срабатывает при закрытии окна на крестик
void VigenereWindow::closeEvent(QCloseEvent *event)
{
    if (mainMenu) {
        mainMenu->show(); // Возвращаем главное меню на экран
    }
    event->accept();
}