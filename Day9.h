//
// Created by Juanma on 11/12/2024.
//

#ifndef DAY9_H
#define DAY9_H
#include <string>
#include <vector>


class Day9 {
public:
    static std::string generateString(const std::string& value, int index);

    static long long generateChecksum(std::vector<std::string> &s2);

    static int searchFreeSpace(const std::vector<std::string> &s, int &initial);

    static void compact(std::vector<std::string> &s);

    static int searchFreeSpaceWithSize(const std::vector<std::string> &s, int initial, int size);

    static void compactDefrag(std::vector<std::string> &s2);

    void static execute();
};



#endif //DAY9_H
