#include <QtTest>
#include <vector>
#include <string>

// Подключаем твои готовые классы алгоритмов
#include "../crypto/sha512.h"
#include "../crypto/vigenere_cipher.h"
#include "../algorithms/binary_search.h"
#include "../algorithms/dijkstra.h"

class CryptoAndAlgoTest : public QObject
{
    Q_OBJECT

private slots:
    // 1. Тест для SHA-512
    void test_sha512_hash() {
        std::string result = SHA512::hash("hello");

        QVERIFY(!result.empty());
        // ИСПРАВЛЕНО: Просто чистое число 128 без опечаток
        QCOMPARE(result.length(), static_cast<size_t>(128));
    }

    // 2. Тест для Шифра Виженера
    void test_vigenere_cipher() {
        std::string original = "ATTACKATDAWN";
        std::string key = "LEMON";

        std::string encrypted = VigenereCipher::encrypt(original, key);
        QVERIFY(!encrypted.empty());
        QVERIFY(encrypted != original);

        std::string decrypted = VigenereCipher::decrypt(encrypted, key);
        QCOMPARE(decrypted, original);
    }

    // 3. Тест для Бинарного поиска (Метод деления пополам)
    void test_binary_search() {
        std::vector<int> arr = {1, 3, 5, 7, 9, 11, 15};

        int foundIndex = BinarySearch::search(arr, 7);
        QCOMPARE(foundIndex, 3);

        int notFoundIndex = BinarySearch::search(arr, 100);
        QCOMPARE(notFoundIndex, -1);
    }

    // 4. Тест для алгоритма Дейкстры (Кратчайшие пути в графе)
    void test_dijkstra_shortest_path() {
        Graph g(3);
        g.addEdge(0, 1, 5);
        g.addEdge(1, 2, 3);
        g.addEdge(0, 2, 10);

        std::vector<long long> distances = g.shortestPath(0);

        // ИСПРАВЛЕНО: Явное приведение к long long для стабильности QCOMPARE
        QCOMPARE(distances[2], static_cast<long long>(8));
    }
};

QTEST_MAIN(CryptoAndAlgoTest)
#include "tst_crypto_test.moc"