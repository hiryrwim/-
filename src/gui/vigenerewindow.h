#ifndef VIGENEREWINDOW_H
#define VIGENEREWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include "crypto/vigenere_cipher.h" // Подключаем твой класс шифрования

QT_BEGIN_NAMESPACE
namespace Ui { class VigenereWindow; }
QT_END_NAMESPACE

class VigenereWindow : public QWidget
{
    Q_OBJECT

public:
    // Конструктор принимает указатель на главное меню
    explicit VigenereWindow(QWidget *parent = nullptr, QWidget *menu = nullptr);
    ~VigenereWindow();

protected:
    // Перехватываем закрытие окна
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();

private:
    Ui::VigenereWindow *ui;
    QWidget *mainMenu; // Указатель для возврата в меню
};

#endif // VIGENEREWINDOW_H