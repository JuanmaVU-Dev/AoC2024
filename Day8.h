//
// Created by Juanma on 08/12/2024.
//

#ifndef DAY8_H
#define DAY8_H
#include <iosfwd>
#include <set>
#include <vector>


class Day8 {
public:
    static void printMap(std::vector<std::vector<char>> &map);

    static double distancePoints(const std::tuple<int, int> & tuple, const std::tuple<int, int> & point2);

    static void printMap(const std::vector<std::vector<char>> & map, const std::set<std::tuple<int, int>> & set);

    static bool checkBounds(const std::tuple<int, int> & a1, int size);

    static void execute();
};



#endif //DAY8_H
