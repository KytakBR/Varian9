#include "transport.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>

// Вспомогательные функции для работы с временем
Time parseTime(const std::string& str) {
    Time t{};
    std::stringstream ss(str);
    char sep;
    ss >> t.hour >> sep >> t.minute;
    return t;
}

std::string formatTime(const Time& t) {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << t.hour << ":"
        << std::setw(2) << std::setfill('0') << t.minute;
    return oss.str();
}

bool loadFromFile(const std::string& filename, std::vector<Transport>& transports) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << "\n";
        return false;
    }

    transports.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Transport t;
        std::string timeStr;
        std::string arrow;
        iss >> t.id >> t.type >> t.price >> timeStr >> t.stops >> t.from >> arrow >> t.to;
        t.time = parseTime(timeStr);
        transports.push_back(t);
    }

    std::cout << "Данные загружены из файла " << filename << "\n";
    return true;
}

bool saveToFile(const std::string& filename, const std::vector<Transport>& transports) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << "\n";
        return false;
    }

    for (const auto& t : transports) {
        file << t.id << " " << t.type << " " << t.price << " " << formatTime(t.time)
             << " " << t.stops << " " << t.from << " -> " << t.to << "\n";
    }

    std::cout << "Данные сохранены в файл " << filename << "\n";
    return true;
}

void displayAll(const std::vector<Transport>& transports) {
    std::cout << "ID    | Тип       | Цена  | Время | Ост-ки | Маршрут\n";
    std::cout << "--------------------------------------------------------------\n";
    for (const auto& t : transports) {
        std::cout << std::setw(5) << t.id << " | "
                  << std::setw(10) << t.type << " | "
                  << std::setw(6) << t.price << " | "
                  << formatTime(t.time) << " | "
                  << std::setw(6) << t.stops << " | "
                  << t.from << " -> " << t.to << "\n";
    }
}

void addRecord(std::vector<Transport>& transports) {
    Transport t;
    std::string timeStr;
    std::cout << "Введите ID, тип, цену, время (HH:MM), кол-во остановок, откуда и куда: ";
    std::cin >> t.id >> t.type >> t.price >> timeStr >> t.stops >> t.from >> t.to;
    t.time = parseTime(timeStr);
    transports.push_back(t);
    std::cout << "Запись добавлена.\n";
}

void deleteRecord(std::vector<Transport>& transports) {
    int id;
    std::cout << "Введите ID записи для удаления: ";
    std::cin >> id;
    auto it = std::remove_if(transports.begin(), transports.end(), [id](const Transport& t) {
        return t.id == id;
    });
    if (it != transports.end()) {
        transports.erase(it, transports.end());
        std::cout << "Запись удалена.\n";
    } else {
        std::cout << "Запись не найдена.\n";
    }
}

void sortRecords(std::vector<Transport>& transports) {
    std::sort(transports.begin(), transports.end(), [](const Transport& a, const Transport& b) {
        return a.price < b.price;
    });
    std::cout << "Сортировка завершена.\n";
}

void findMinStopsForPairs(const std::vector<Transport>& transports) {
    std::map<std::pair<std::string, std::string>, Transport> best;
    for (const auto& t : transports) {
        auto key = std::make_pair(t.from, t.to);
        if (!best.count(key) || t.stops < best[key].stops) {
            best[key] = t;
        }
    }

    std::cout << "Минимальные остановки для каждой пары маршрутов:\n";
    for (const auto& [key, t] : best) {
        std::cout << t.from << " -> " << t.to << ": ID " << t.id << ", остановок: " << t.stops << "\n";
    }
}

void filterByTime(const std::vector<Transport>& transports) {
    int maxMinutes;
    std::cout << "Введите максимальное время в пути (в минутах): ";
    std::cin >> maxMinutes;

    std::ofstream file("filtered.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла filtered.txt\n";
        return;
    }

    for (const auto& t : transports) {
        int minutes = t.time.hour * 60 + t.time.minute;
        if (minutes <= maxMinutes) {
            file << t.id << " " << t.type << " " << t.price << " " << formatTime(t.time)
                 << " " << t.stops << " " << t.from << " -> " << t.to << "\n";
        }
    }

    std::cout << "Рейсы с временем не более " << maxMinutes << " минут сохранены в filtered.txt\n";
}
