#ifndef DIJKSTRAWINDOW_H
#define DIJKSTRAWINDOW_H

#include <QWidget>
#include "algorithms/dijkstra.h" // Путь к твоему классу Graph

QT_BEGIN_NAMESPACE
namespace Ui { class DijkstraWindow; }
QT_END_NAMESPACE

class DijkstraWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DijkstraWindow(QWidget *parent = nullptr);
    ~DijkstraWindow();

private slots:
    void on_calculateButton_clicked(); // Слот для обработки нажатия кнопки расчета

private:
    Ui::DijkstraWindow *ui;
};

#endif // DIJKSTRAWINDOW_H