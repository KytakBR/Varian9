#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
#include <vector>

struct Time {
    int hour;
    int minute;
};

struct Transport {
    int id;
    std::string type;
    double price;
    Time time;
    int stops;
    std::string from;
    std::string to;
};

bool loadFromFile(const std::string& filename, std::vector<Transport>& transports);
bool saveToFile(const std::string& filename, const std::vector<Transport>& transports);
void displayAll(const std::vector<Transport>& transports);
void addRecord(std::vector<Transport>& transports);
void deleteRecord(std::vector<Transport>& transports);
void sortRecords(std::vector<Transport>& transports);
void findMinStopsForPairs(const std::vector<Transport>& transports);
void filterByTime(const std::vector<Transport>& transports);

#endif // TRANSPORT_H
