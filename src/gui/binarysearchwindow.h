#ifndef BINARYSEARCHWINDOW_H
#define BINARYSEARCHWINDOW_H

#include <QWidget>
#include "algorithms/binary_search.h" // Подключаем твой класс бинарного поиска

QT_BEGIN_NAMESPACE
namespace Ui { class BinarySearchWindow; }
QT_END_NAMESPACE

class BinarySearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BinarySearchWindow(QWidget *parent = nullptr);
    ~BinarySearchWindow();

private slots:
    void on_searchButton_clicked(); // Слот для обработки нажатия кнопки

private:
    Ui::BinarySearchWindow *ui;
};

#endif // BINARYSEARCHWINDOW_H