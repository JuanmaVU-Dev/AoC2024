//
// Created by Juanma on 08/12/2024.
//

#ifndef DAY7_H
#define DAY7_H
#include <vector>
#include <bits/basic_string.h>
#include <bits/c++config.h>


class Day7 {
public:
    static std::string CHARS;

    static std::string intToBase3(int integer);

    static std::vector<char> generaPermutacion(int combination, const int &size);

    static std::vector<char> generaPermutacion2(int combination, const int &size);

    void static execute();
};



#endif //DAY7_H
