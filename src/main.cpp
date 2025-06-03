#include "transport.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Transport> routes;
    std::string filename = "transport.txt";  // ← исправлено имя файла

    int choice;
    do {
        std::cout << "\n1. Загрузить из файла\n2. Сохранить в файл\n3. Показать все\n4. Добавить\n5. Удалить\n6. Сортировать по цене\n7. Минимальные остановки\n8. Фильтр по времени\n0. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                loadFromFile(filename, routes);
                break;
            case 2:
                saveToFile(filename, routes);
                break;
            case 3:
                displayAll(routes);
                break;
            case 4:
                addRecord(routes);
                break;
            case 5:
                deleteRecord(routes);  // ID запрашивается внутри функции
                break;
            case 6:
                sortRecords(routes);
                break;
            case 7:
                findMinStopsForPairs(routes);
                break;
            case 8:
                filterByTime(routes);
                break;
            case 0:
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}
