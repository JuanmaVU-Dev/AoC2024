//
// Created by Juanma on 06/12/2024.
//

#ifndef DAY5_H
#define DAY5_H
#include <vector>


class Day5 {
public:
    //static std::vector<std::pair<int,int>> mapRules;
    static int findIndex(std::vector<int> update, int number);
    static void printUpdate(const std::vector<int>& update);

    static bool checkCorrect(const std::vector<int> &update,std::vector<std::pair<int,int>> &mapRules);

    void static execute();
};



#endif //DAY5_H
