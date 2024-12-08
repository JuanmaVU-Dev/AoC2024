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

    static void moveGuard2(std::vector<std::vector<char>> &map, Guard &guard, bool turn, std::multiset<std::tuple<int, int>> &turnPositionsSet, bool
                           &loop);

    static bool checkCollision(std::vector<std::vector<char>> &map, Guard &guard);

    static void turn(Guard &guard);

    static void initializeGuard(std::set<std::tuple<int, int>> &setPositions, std::vector<std::vector<char>> &map,
                                Guard &guard);

    static void setStartingPosition(std::pair<int, int> &startingPosition, Guard &guard);

    static bool findLoop(int turnPositions, int stuckPositions);

    static void resetMap(std::vector<std::vector<char>> &map, std::pair<int, int> &startingPosition);

    void static execute();
};

#endif //DAY6_H
