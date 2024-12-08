//
// Created by Juanma on 06/12/2024.
//

#include "Day6.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

struct Guard {
public:
    int x;
    int y;
    char direction;
};

void Day6::printMaze(std::vector<std::vector<char>> &map) {
    std::cout << "                  " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "                  " << std::endl;
    for(int i=0;i<map.size();i++) {
        std::cout << std::string(map.at(i).begin(),map.at(i).end()) << std::endl;
    }
}

bool Day6::checkOutOfMap(std::vector<std::vector<char>> &map, int x, int y) {
    return x < 0 || x >= map.size()
        || y < 0 || y >= map.at(0).size();
}

bool Day6::checkOutOfMap(std::vector<std::vector<char>> &map, Guard &guard) {
    switch (guard.direction) {
        case '^':
            return checkOutOfMap(map, guard.x-1,guard.y);
        case 'v':
            return checkOutOfMap(map, guard.x+1,guard.y);
        case '<':
            return checkOutOfMap(map, guard.x,guard.y-1);
        case '>':
            return checkOutOfMap(map, guard.x,guard.y+1);
    }
    return false;
}

void Day6::moveGuard(std::vector<std::vector<char>> &map, Guard &guard,std::set<std::tuple<int,int>> &setPositions) {
    switch (guard.direction) {
        case '^':
            if(!checkOutOfMap(map, guard.x - 1, guard.y)) {
                guard.x = guard.x - 1;
                //map.at(guard.x).at(guard.y) = 'X';
                setPositions.emplace(guard.x,guard.y);
            }
            break;
        case 'v':
            if(!checkOutOfMap(map, guard.x + 1, guard.y)) {
                guard.x = guard.x + 1;
                //map.at(guard.x).at(guard.y) = 'X';
                setPositions.emplace(guard.x,guard.y);
            }
            break;
        case '<':
            if(!checkOutOfMap(map, guard.x,guard.y-1)) {
                guard.y = guard.y - 1;
                //map.at(guard.x).at(guard.y) = 'X';
                setPositions.emplace(guard.x,guard.y);
            }
            break;
        case '>':
            if(!checkOutOfMap(map, guard.x,guard.y+1)) {
                guard.y = guard.y + 1;
                //map.at(guard.x).at(guard.y) = 'X';
                setPositions.emplace(guard.x,guard.y);
            }
            break;
    }
}

void Day6::moveGuard2(std::vector<std::vector<char>> &map, Guard &guard, bool turn, std::multiset<std::tuple<int,int>> &turnPositionsSet, bool &loop) {
    switch (guard.direction) {
        case '^':
            if(!checkOutOfMap(map, guard.x - 1, guard.y)) {
                if(turn) {
                    map.at(guard.x).at(guard.y) = '+';
                    turnPositionsSet.insert(std::make_tuple(guard.x,guard.y));
                }
                guard.x = guard.x - 1;
                if(map.at(guard.x).at(guard.y) == '.') {
                    map.at(guard.x).at(guard.y) = '|';
                }
                if(map.at(guard.x).at(guard.y) == '-') {
                    map.at(guard.x).at(guard.y) = '+';
                    //turnPositionsSet.insert(std::pair(guard.x,guard.y));
                }
            }
        break;
        case 'v':
            if(!checkOutOfMap(map, guard.x + 1, guard.y)) {
                if(turn) {
                    map.at(guard.x).at(guard.y) = '+';
                    turnPositionsSet.insert(std::make_tuple(guard.x,guard.y));
                }
                guard.x = guard.x + 1;
                if(map.at(guard.x).at(guard.y) == '.') {
                    map.at(guard.x).at(guard.y) = '|';
                }
                if(map.at(guard.x).at(guard.y) == '-') {
                    map.at(guard.x).at(guard.y) = '+';
                    //turnPositionsSet.insert(std::pair(guard.x,guard.y));
                }
            }
        break;
        case '<':
            if(!checkOutOfMap(map, guard.x,guard.y-1)) {
                if(turn) {
                    map.at(guard.x).at(guard.y) = '+';
                    turnPositionsSet.insert(std::make_tuple(guard.x,guard.y));
                }
                guard.y = guard.y - 1;
                if(map.at(guard.x).at(guard.y) == '.') {
                    map.at(guard.x).at(guard.y) = '-';
                }
                if(map.at(guard.x).at(guard.y) == '|') {
                    map.at(guard.x).at(guard.y) = '+';
                    //turnPositionsSet.insert(std::pair(guard.x,guard.y));
                }
            }
        break;
        case '>':
            if(!checkOutOfMap(map, guard.x,guard.y+1)) {
                if(turn) {
                    map.at(guard.x).at(guard.y) = '+';
                    turnPositionsSet.insert(std::make_tuple(guard.x,guard.y));
                }
                guard.y = guard.y + 1;
                if(map.at(guard.x).at(guard.y) == '.') {
                    map.at(guard.x).at(guard.y) = '-';
                }
                if(map.at(guard.x).at(guard.y) == '|') {
                    map.at(guard.x).at(guard.y) = '+';
                    //turnPositionsSet.insert(std::pair(guard.x,guard.y));
                }
            }
        break;
    }
    loop = loop || turnPositionsSet.count(std::tuple(guard.x,guard.y)) > 1;
}

bool Day6::checkCollision(std::vector<std::vector<char>> &map, Guard &guard) {
    switch (guard.direction) {
        case '^':
        if(!checkOutOfMap(map, guard.x-1,guard.y)) {
            return map.at(guard.x-1).at(guard.y) == '#' || map.at(guard.x-1).at(guard.y) == 'O';
        }
        break;
        case 'v':
        if(!checkOutOfMap(map, guard.x+1,guard.y)) {
            return map.at(guard.x+1).at(guard.y) == '#' || map.at(guard.x+1).at(guard.y) == 'O';
        }
        break;
        case '<':
        if(!checkOutOfMap(map, guard.x,guard.y-1)) {
            return map.at(guard.x).at(guard.y-1) == '#' || map.at(guard.x).at(guard.y-1) == 'O';
        }
        break;
        case '>':
        if(!checkOutOfMap(map, guard.x,guard.y+1)) {
            return map.at(guard.x).at(guard.y+1) == '#' || map.at(guard.x).at(guard.y+1) == 'O';
        }
        break;
    }
    return false;
}

void Day6::turn(Guard &guard) {
    switch (guard.direction) {
        case '^':
            guard.direction = '>';
        break;
        case 'v':
            guard.direction = '<';
        break;
        case '<':
            guard.direction = '^';
        break;
        case '>':
            guard.direction = 'v';
        break;
    }
}


void Day6::initializeGuard(std::set<std::tuple<int, int>> &setPositions, std::vector<std::vector<char>> &map, Guard &guard) {
    setPositions.clear();
    for(int i=0;i<map.size();i++) {
        //std::cout << std::string(map.at(i).begin(),map.at(i).end()) << std::endl;
        for(int j=0;j<map.at(i).size();j++) {
            if(map.at(i).at(j) == '^'
               || map.at(i).at(j) == 'v'
               || map.at(i).at(j) == '<'
               || map.at(i).at(j) == '>')
            {
                guard = Guard(i,j,map.at(i).at(j));
                //map.at(i).at(j) = 'X';
                setPositions.emplace(guard.x,guard.y);
            }
        }
    }
}

void Day6::setStartingPosition(std::pair<int,int> &startingPosition, Guard &guard) {
    startingPosition.first = guard.x;
    startingPosition.second = guard.y;
}

void Day6::resetMap(std::vector<std::vector<char>> &map,std::pair<int,int> &startingPosition) {
    for(int i=0;i<map.size();i++) {
        for(int j=0;j<map.at(i).size();j++) {
            if(map.at(i).at(j) == '+' || map.at(i).at(j) == '-' || map.at(i).at(j) == '|') {
                map.at(i).at(j) = '.';
            }
        }
    }
    map.at(startingPosition.first).at(startingPosition.second) = '^';
}

void Day6::execute() {
    std::set<std::tuple<int,int>> setPositions;
    std::ifstream inFile;

    inFile.open(R"(C:\Users\Juanma\Downloads\input_day_6.txt)");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    std::string line;
    std::vector<std::vector<char>> map;
    while (std::getline(inFile, line)) {
        map.emplace_back(line.begin(), line.end());
    }
    inFile.close();

    Guard guard;

    std::pair<int,int> startingPosition;
    initializeGuard(setPositions, map, guard);
    setStartingPosition(startingPosition, guard);
    //check collision or out of bounds
    //checkCollision(map, guard);
    //move
    //std::cout << '- ' << checkOutOfMap(map,guard) << std::endl;
    while(!checkOutOfMap(map, guard)) {
        if(checkCollision(map,guard)) {
            turn(guard);
            moveGuard(map, guard, setPositions);
        }else {
            moveGuard(map, guard, setPositions);
        }
    }

    std::cout << "Number of guard positions: " << setPositions.size() << std::endl;

    int solutionsCount = 0;
    int combination = 0;

    for(int i=0;i<map.size();i++) {
        for(int j=0;j<map.at(i).size();j++) {
            if(map.at(i).at(j) =='.') {
                bool loop = false;
                bool turnTime = false;
                std::multiset<std::tuple<int,int>> turnPositionsSet;
                initializeGuard(setPositions, map, guard);
                map.at(i).at(j) = 'O';
                int stuckCount = 0;
                while(!checkOutOfMap(map, guard)) {
                    if(checkCollision(map,guard)) {
                        turn(guard);
                        turnTime = true;
                        stuckCount++;
                    }else {
                        moveGuard2(map, guard, turnTime, turnPositionsSet, loop);
                        turnTime = false;
                    }
                    if(loop) {
                        solutionsCount++;
                        break;
                    }
                }
                resetMap(map, startingPosition);
                turnPositionsSet.clear();
                map.at(i).at(j) = '.';
                combination++;
            }
        }
    }
    std::cout << "Number of solutions: " << solutionsCount << std::endl;
}
