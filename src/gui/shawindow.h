#ifndef SHAWINDOW_H
#define SHAWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include "crypto/sha512.h" // Подключаем твой алгоритм

QT_BEGIN_NAMESPACE
namespace Ui { class SHAWindow; }
QT_END_NAMESPACE

class SHAWindow : public QWidget
{
    Q_OBJECT

public:
    // Конструктор теперь принимает указатель на главное меню (menu)
    explicit SHAWindow(QWidget *parent = nullptr, QWidget *menu = nullptr);
    ~SHAWindow();

protected:
    // Перехватываем событие закрытия окна
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_calcButton_clicked();     // Слот для генерации хеша
    void on_checkButton_clicked();    // Слот для сравнения слова с хешем

private:
    Ui::SHAWindow *ui;
    QWidget *mainMenu; // Переменная для хранения указателя на главное меню
};

#endif // SHAWINDOW_H