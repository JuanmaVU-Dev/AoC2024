//
// Created by Juanma on 08/12/2024.
//

#include "Day8.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>

void Day8::printMap(std::vector<std::vector<char>> &map) {
    std::cout << "                  " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "                  " << std::endl;
    for(int i=0;i<map.size();i++) {
        std::cout << std::string(map.at(i).begin(),map.at(i).end()) << std::endl;
    }
}

double Day8::distancePoints(const std::tuple<int, int> &point1, const std::tuple<int, int> &point2) {
    return sqrt(pow(std::get<0>(point1) - std::get<0>(point2),2)+pow(std::get<1>(point1) - std::get<1>(point2),2));
}

void Day8::printMap(const std::vector<std::vector<char>> &map, const std::set<std::tuple<int, int>> &set) {
    std::cout << "                  " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "                  " << std::endl;
    for(int i=0;i<map.size();i++) {
        for(int j = 0;j<map.at(i).size();j++) {
            if(set.contains(std::make_tuple(i,j))) {
                std::cout << '#';
            }else {
                std::cout << map.at(i).at(j);
            }
        }
        std::cout << std::endl;
    }
}

bool Day8::checkBounds(const std::tuple<int, int> &point, int size) {
    return std::get<0>(point) >= 0 && std::get<0>(point) < size && std::get<1>(point) >= 0 && std::get<1>(point)<size;
}

void Day8::execute() {
    std::ifstream inFile;

    inFile.open(R"(C:\Users\Juanma\Downloads\input_day_8_test.txt)");

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

    //std::vector<std::tuple<int,int>> antennas;
    std::map<char,std::vector<std::tuple<int,int>>> mapAntennas;

    for(int i=0;i<map.size();i++) {
        for(int j=0;j<map.at(i).size();j++){
            if(map.at(i).at(j) != '#' && map.at(i).at(j) != '.') {
                char frequencyLetter = map.at(i).at(j);
                if(mapAntennas.contains(frequencyLetter)) {
                    mapAntennas[frequencyLetter].emplace_back(std::make_tuple(i,j));
                }else {
                    std::vector<std::tuple<int,int>> antenasTemp;
                    antenasTemp.emplace_back(i,j);
                    mapAntennas.emplace(frequencyLetter,antenasTemp);
                }
            }
        }
    }
    std::set<std::tuple<int,int>> antinodesTotal;
    for(const auto& antennasList : mapAntennas) {
        std::vector<std::tuple<int,int>> antennas = mapAntennas[antennasList.first];
        for(int i=0;i<antennas.size();i++) {
            for(auto antena2 : antennas) {
                //std::set<std::tuple<double,int,int>> antinodesDistance;
                //std::set<std::tuple<int,int>> antinodesAux;
                if(antennas.at(i) != antena2) {
                    std::set<std::tuple<int,int>> antinodesTesting;
                    std::tuple<int,int> A = antennas.at(i);
                    std::tuple<int,int> B = antena2;
                    int xDiff = std::get<0>(B) - std::get<0>(A);
                    int yDiff = std::get<1>(B) - std::get<1>(A);
                    int xa1 = std::get<0>(A) - xDiff;
                    int ya1 = std::get<1>(A) - yDiff;
                    int xa2 = std::get<0>(B) + xDiff;
                    int ya2 = std::get<1>(B) + yDiff;
                    std::tuple<int,int> a1 = std::make_tuple(xa1,ya1);
                    std::tuple<int,int> a2 = std::make_tuple(xa2,ya2);
                    if(checkBounds(a1,map.size())) {
                        if(map.at(xa1).at(ya1)) {
                            antinodesTotal.emplace(a1);
                        }
                    }
                    if(checkBounds(a2,map.size())) {
                        if(map.at(xa2).at(ya2)) {
                            antinodesTotal.emplace(a2);
                        }
                    }
                    //printMap(map, antinodesTesting);
                }
            }
        }
    }
    //printMap(map, antinodesTotal);
    std::cout << "Antinodes of a: " << antinodesTotal.size();
}
