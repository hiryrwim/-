#include "shawindow.h"
#include "ui_shawindow.h"

SHAWindow::SHAWindow(QWidget *parent, QWidget *menu) :
    QWidget(parent),
    ui(new Ui::SHAWindow),
    mainMenu(menu) // Сохраняем главное меню
{
    ui->setupUi(this);
}

SHAWindow::~SHAWindow()
{
    delete ui;
}

// Кнопка 1: Просто вычислить хеш SHA-512
void SHAWindow::on_calcButton_clicked()
{
    QString input = ui->inputEdit->text();
    if (input.isEmpty()) {
        ui->resultEdit->setText("Ошибка: Введите текст для хеширования!");
        return;
    }

    // Вызываем твой алгоритм
    std::string result = SHA512::hash(input.toStdString());

    // Выводим результат
    ui->resultEdit->setText(QString::fromStdString(result));
}

// Кнопка 2: Проверить, соответствует ли текст какому-то хешу
void SHAWindow::on_checkButton_clicked()
{
    QString input = ui->inputEdit->text();
    QString hashToCompare = ui->hashCompareEdit->text().trimmed();

    if (input.isEmpty() || hashToCompare.isEmpty()) {
        ui->resultEdit->setText("Ошибка: Для проверки заполните «Текст» и «Хеш для сравнения»!");
        return;
    }

    // Хешируем текущий ввод пользователя
    std::string currentHash = SHA512::hash(input.toStdString());

    // Сравниваем строки (приводим к нижнему регистру на всякий случай)
    QString qCurrent = QString::fromStdString(currentHash).toLower();
    QString qCompare = hashToCompare.toLower();

    if (qCurrent == qCompare) {
        ui->resultEdit->setText("✅ СОВПАДЕНИЕ! Этот текст соответствует предоставленному хешу.");
    } else {
        ui->resultEdit->setText("❌ НЕ СОВПАДАЕТ!\n\n"
                                "Хеш твоего текста:\n" + qCurrent + "\n\n"
                                "Ожидаемый хеш:\n" + qCompare);
    }
}

// Автоматически срабатывает, когда пользователь закрывает окно (на крестик)
void SHAWindow::closeEvent(QCloseEvent *event)
{
    if (mainMenu) {
        mainMenu->show(); // Показываем главное меню (UserWindow) обратно
    }
    event->accept(); // Разрешаем закрытие окна
}