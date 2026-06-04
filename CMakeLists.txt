cmake_minimum_required(VERSION 3.16)

project(tema_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к твоей установленной версии Qt6
set(Qt6_DIR "C:/Qt/6.11.1/mingw_64/lib/cmake/Qt6")

# Включаем автоматическую генерацию Qt-файлов (MOC, UIC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Ищем модуль QtWidgets
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Позволяет компилятору искать заголовочные файлы начиная с папки src
include_directories(src)

# Собираем исполняемый файл из ВСЕХ компонентов проекта
add_executable(tema_3
        # Главная точка входа интерфейса (main.cpp убран во избежание конфликта)
        src/main_gui.cpp

        # Графический интерфейс (Окна)
        src/gui/loginwindow.cpp
        src/gui/loginwindow.h
        src/gui/loginwindow.ui
        src/gui/userwindow.cpp
        src/gui/userwindow.h
        src/gui/userwindow.ui

        # Алгоритмы шифрования
        src/crypto/vigenere_cipher.cpp
        src/crypto/vigenere_cipher.h
        src/crypto/sha512.cpp
        src/crypto/sha512.h

        # Алгоритмы поиска и графов
        src/algorithms/binary_search.cpp
        src/algorithms/binary_search.h
        src/algorithms/dijkstra.cpp
        src/algorithms/dijkstra.h
        src/gui/shawindow.cpp
        src/gui/shawindow.h
        src/gui/shawindow.ui
        src/gui/binarysearchwindow.cpp
        src/gui/binarysearchwindow.h
        src/gui/binarysearchwindow.ui
        src/gui/dijkstrawindow.cpp
        src/gui/dijkstrawindow.h
        src/gui/dijkstrawindow.ui
        src/gui/vigenerewindow.cpp
        src/gui/vigenerewindow.h
        src/gui/vigenerewindow.ui
        src/tests/tst_crypto_test.cpp
)
# --- БЛОК ЮНИТ-ТЕСТОВ ---

# Ищем модуль Test в Qt
find_package(Qt6 REQUIRED COMPONENTS Test)

# Создаем отдельный исполняемый файл для тестов
add_executable(qt_unit_tests
        src/tests/tst_crypto_test.cpp
        src/crypto/sha512.cpp
        src/crypto/vigenere_cipher.cpp
        src/algorithms/binary_search.cpp
        src/algorithms/dijkstra.cpp
)

# Включаем автоматическую генерацию мета-кода Qt (MOC) для тестов
set_target_properties(qt_unit_tests PROPERTIES
        AUTOMOC ON
)

# Линкуем библиотеки Qt (нам нужен только Core и Test, так как GUI тут нет)
target_link_libraries(qt_unit_tests PRIVATE
        Qt6::Core
        Qt6::Test
)
# Линкуем библиотеки Qt к нашему проекту
target_link_libraries(tema_3 PRIVATE Qt6::Widgets)