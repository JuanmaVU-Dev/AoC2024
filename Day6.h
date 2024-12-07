//
// Created by Juanma on 06/12/2024.
//

#ifndef DAY6_H
#define DAY6_H
#include <set>
#include <vector>

struct Guard;

class Day6 {
public:
    static void printMaze(std::vector<std::vector<char>> &map);

    static bool checkOutOfMap(std::vector<std::vector<char>> &map, int x,int y);

    bool static checkOutOfMap(std::vector<std::vector<char>> &map, Guard &guard);

    static void moveGuard(std::vector<std::vector<char>> &map, Guard &guard, std::set<std::tuple<int,int>> &setPositions);

    static bool checkCollision(std::vector<std::vector<char>> &map, Guard &guard);

    static void turn(Guard &guard);

    void static execute();
};

#endif //DAY6_H
