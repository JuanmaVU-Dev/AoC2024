//
// Created by Juanma on 06/12/2024.
//

#include "Day5.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

int Day5::findIndex(std::vector<int> update, int number) {
    for(int i=0;i<update.size();i++) {
        if(update.at(i) == number) return i;
    }
    return -1;
}

void Day5::printUpdate(const std::vector<int>& update) {
    for(int i : update) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
    std::cout << update.size() << std::endl;
}

bool Day5::checkCorrect(const std::vector<int> &update, std::vector<std::pair<int,int>> &mapRules) {
    bool correctUpdate = true;
    //std::cout << "-------------- " << updateCount << std::endl;
    for(auto rule : mapRules) {
        bool correctRule = true;
        auto firstIndex = std::ranges::find(update.begin(),update.end(),rule.first);//findIndex(update, rule.first);
        auto secondIndex = std::ranges::find(update.begin(),update.end(),rule.second);
        //std::cout << rule.first << "|" << rule.second << " index: " << firstIndex << "-" << secondIndex << std::endl;
        if( firstIndex != update.end() && secondIndex != update.end())  {
            if(secondIndex < firstIndex){
                correctRule = false;
            }
        }
        correctUpdate = correctUpdate && correctRule;
    }
    return correctUpdate;
}

void Day5::execute() {
    std::ifstream inFile;

    inFile.open(R"(C:\Users\Juanma\Downloads\input_day_5.txt)");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    std::string line;
    std::vector<std::vector<int>> pages;
    std::vector<std::vector<int>> incorrectUpdates;
    int listPageCount = 0;
    std::vector<std::pair<int,int>>mapRules;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string stringNumero;
        if(line.contains('|')) {
            std::vector<int> rule = std::vector<int>(2);
            rule.clear();
            while(std::getline(iss, stringNumero, '|')) {
                //std::cout << stringNumero << std::endl;
                rule.push_back(std::stoi(stringNumero));
            }
            std::pair rulePair(rule.at(0),rule.at(1));
            rule.clear();
            mapRules.emplace_back(rulePair);
        }
        if(line.contains(',')) {
            pages.emplace_back();
            while(std::getline(iss, stringNumero, ',')) {
                //std::cout << stringNumero << ',';
                pages.at(listPageCount).push_back(std::stoi(stringNumero));
            }
            listPageCount++;
            //std::cout << std::endl;
        }
    }
    inFile.close();

    int updateCount = 1;
    int sumMiddleUpdates = 0;
    for(auto update : pages) {
        bool correctUpdate = true;
        //std::cout << "-------------- " << updateCount << std::endl;
        for(auto rule : mapRules) {
            bool correctRule = true;
            auto firstIndex = std::ranges::find(update.begin(),update.end(),rule.first);//findIndex(update, rule.first);
            auto secondIndex = std::ranges::find(update.begin(),update.end(),rule.second);
            //std::cout << rule.first << "|" << rule.second << " index: " << firstIndex << "-" << secondIndex << std::endl;
            if( firstIndex != update.end() && secondIndex != update.end())  {
                if(secondIndex < firstIndex){
                    correctRule = false;
                    //std::cout << "incorrect update: " << rule.first << "|" << rule.second << std::endl;
                }
            }
            correctUpdate = correctUpdate && correctRule;
        }
        if(correctUpdate) {
            sumMiddleUpdates += update.at(update.size()/2);
            //pages.erase(std::ranges::find(pages.begin(),pages.end(),update));
            //std::cout << "middle value: " << update.size()/2 << std::endl;
        }else {
            incorrectUpdates.emplace_back(update);
        }
        updateCount++;
    }
    std::cout << "Total middle value: " << sumMiddleUpdates << std::endl;

    updateCount = 1;
    sumMiddleUpdates = 0;
    for(auto update : incorrectUpdates) {
        //std::cout << "-------------- " << updateCount << std::endl;
        while(!checkCorrect(update, mapRules)) {
            for(auto rule : mapRules) {
                auto firstIndex = std::ranges::find(update.begin(),update.end(),rule.first);//findIndex(update, rule.first);
                auto secondIndex = std::ranges::find(update.begin(),update.end(),rule.second);
                //std::cout << rule.first << "|" << rule.second << " index: " << firstIndex << "-" << secondIndex << std::endl;
                if( firstIndex != update.end() && secondIndex != update.end())  {
                    if(secondIndex < firstIndex){
                        //std::cout << "incorrect update: " << rule.first << "|" << rule.second << std::endl;
                        update.erase(secondIndex);
                        update.insert(firstIndex,rule.second);
                    }
                }
            }
        }
        // if(!checkCorrect(update, mapRules)) {
        //     std::cout << "incorrect update-------";
        // }
        //printUpdate(update);
        sumMiddleUpdates += update.at(update.size()/2);
    }
    std::cout << "Total middle value 2: " << sumMiddleUpdates << std::endl;
}
