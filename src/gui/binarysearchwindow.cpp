#include "binarysearchwindow.h"
#include "ui_binarysearchwindow.h"
#include <QStringList>
#include <algorithm>

BinarySearchWindow::BinarySearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BinarySearchWindow)
{
    ui->setupUi(this);
}

BinarySearchWindow::~BinarySearchWindow()
{
    delete ui;
}

void BinarySearchWindow::on_searchButton_clicked()
{
    ui->resultEdit->clear();

    QString arrayText = ui->arrayEdit->text().trimmed();
    QString targetText = ui->targetEdit->text().trimmed();

    if (arrayText.isEmpty() || targetText.isEmpty()) {
        ui->resultEdit->setText("Ошибка: Заполните все поля ввода!");
        return;
    }

    // Парсим строку с числами в вектор
    QStringList tokens = arrayText.split(' ', Qt::SkipEmptyParts);
    std::vector<int> arr;
    for (const QString& token : tokens) {
        bool ok;
        int num = token.toInt(&ok);
        if (!ok) {
            ui->resultEdit->setText("Ошибка: В массиве должны быть только целые числа!");
            return;
        }
        arr.push_back(num);
    }

    // Проверяем ввод на валидность для бинарного поиска (массив должен быть отсортирован)
    if (!std::is_sorted(arr.begin(), arr.end())) {
        ui->resultEdit->setText("Внимание: Массив не отсортирован по возрастанию!\n"
                                "Бинарный поиск работает только с упорядоченными данными.\n"
                                "Пожалуйста, отсортируйте массив перед вводом.");
        return;
    }

    bool targetOk;
    int target = targetText.toInt(&targetOk);
    if (!targetOk) {
        ui->resultEdit->setText("Ошибка: Искомый элемент должен быть целым числом!");
        return;
    }

    // Вызываем твой собственный алгоритм бинарного поиска
    int index = BinarySearch::search(arr, target);

    // Формируем красивый вывод результата
    QString output;
    output += "Размер массива: " + QString::number(arr.size()) + "\n";
    output += "Искомое значение: " + QString::number(target) + "\n\n";

    if (index != -1) {
        output += "УСПЕХ! Элемент найден.\n";
        output += "Индекс элемента в массиве (начиная с 0): " + QString::number(index);
    } else {
        output += "Элемент не найден в данном массиве (Метод вернул -1).";
    }

    ui->resultEdit->setText(output);
}