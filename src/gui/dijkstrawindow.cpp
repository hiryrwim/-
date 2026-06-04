#include "dijkstrawindow.h"
#include "ui_dijkstrawindow.h"
#include <QStringList>
#include <limits>

DijkstraWindow::DijkstraWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DijkstraWindow)
{
    ui->setupUi(this);
}

DijkstraWindow::~DijkstraWindow()
{
    delete ui;
}

void DijkstraWindow::on_calculateButton_clicked()
{
    ui->resultEdit->clear();

    bool okV, okS;
    int numVertices = ui->verticesEdit->text().trimmed().toInt(&okV);
    int startVertex = ui->startVertexEdit->text().trimmed().toInt(&okS);

    if (!okV || numVertices <= 0) {
        ui->resultEdit->setText("Ошибка: Некорректное количество вершин!");
        return;
    }
    if (!okS || startVertex < 0 || startVertex >= numVertices) {
        ui->resultEdit->setText("Ошибка: Некорректная стартовая вершина!");
        return;
    }

    // Инициализируем твой класс графа
    Graph graph(numVertices);

    // Читаем ребра построчно
    QString edgesText = ui->edgesEdit->toPlainText();
    QStringList lines = edgesText.split('\n', Qt::SkipEmptyParts);

    int lineNum = 0;
    for (const QString& line : lines) {
        lineNum++;
        QStringList parts = line.trimmed().split(' ', Qt::SkipEmptyParts);
        if (parts.isEmpty()) continue;

        if (parts.size() < 3) {
            ui->resultEdit->setText(QString("Ошибка в строке %1: должно быть 3 значения (откуда куда вес)").number(lineNum));
            return;
        }

        bool okFrom, okTo, okWeight;
        int from = parts[0].toInt(&okFrom);
        int to = parts[1].toInt(&okTo);
        long long weight = parts[2].toLongLong(&okWeight);

        if (!okFrom || !okTo || !okWeight || from < 0 || from >= numVertices || to < 0 || to >= numVertices) {
            ui->resultEdit->setText(QString("Ошибка в строке %1: неверные индексы вершин или вес ребра!").number(lineNum));
            return;
        }

        // Вызываем твой метод добавления ребра
        graph.addEdge(from, to, weight);
    }

    // Запускаем твой алгоритм Дейкстры
    std::vector<long long> distances = graph.shortestPath(startVertex);

    // Выводим результат
    QString output;
    output += "Кратчайшие пути от вершины " + QString::number(startVertex) + ":\n";
    output += "----------------------------------------\n";

    long long INF = std::numeric_limits<long long>::max();

    for (int i = 0; i < numVertices; ++i) {
        output += "До вершины " + QString::number(i) + ": ";
        if (distances[i] == INF) {
            output += "❌ Нет пути (Недостижима)\n";
        } else {
            output += QString::number(distances[i]) + "\n";
        }
    }

    ui->resultEdit->setText(output);
}