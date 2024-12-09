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
                std::set<std::tuple<double,int,int>> antinodesDistance;
                std::set<std::tuple<int,int>> antinodesAux;
                if(antennas.at(i) != antena2) {
                    std::tuple<int,int> A = antennas.at(i);
                    std::tuple<int,int> B = antena2;
                    double xDiff = std::get<0>(B) - std::get<0>(A);
                    double yDiff = std::get<1>(B) - std::get<1>(A);
                    double m =  yDiff / xDiff;
                    double c = std::get<1>(B) - m * std::get<0>(B);
                    for(int x=0;x<map.size();x++) {
                        double y = m*x + c;
                        if(y >= 0 && y<map.size() && std::fmod(y,1) == 0 && map.at(x).at(y) != antennasList.first) {
                            //if(map.at(x).at(y) == '.') map.at(x).at(y) = '#';
                            double distanceAB = distancePoints(A,std::make_tuple(x,y));
                            double distanceBA = distancePoints(B,std::make_tuple(x,y));
                            if(distancePoints(A,B) == distanceAB || distancePoints(A,B) == distanceBA) {
                                antinodesTotal.emplace(x,y);
                            }
                            antinodesDistance.emplace(distanceAB+distanceBA,x,y);
                        }
                    }
                    for(auto antinode : antinodesDistance) {
                        int x;
                        int y;
                        double distance;
                        std::tie(distance,x,y) = antinode;
                        std::cout << "- " << antennasList.first << " - (" << x << ", " << y << ") - " << distance << std::endl;
                    }
                    auto itr = antinodesDistance.begin();
                    for(int count = 0;count<2 && itr != antinodesDistance.end();count++) {
                        int x;
                        int y;
                        double distance;
                        std::tie(distance,x,y) = *itr;
                        //antinodesTotal.emplace(x,y);
                        antinodesAux.emplace(x,y);
                        if(std::next(itr,1) != antinodesDistance.end()) {
                            int x2;
                            int y2;
                            double distance2;
                            std::tie(distance2,x2,y2) = *std::next(itr,1);
                            if(distance == distance2) {
                                //antinodesTotal.emplace(x2,y2);
                                antinodesAux.emplace(x2,y2);
                                break;
                            }
                        }
                    }
                    printMap(map, antinodesAux);
                }
            }
        }
    }
    printMap(map, antinodesTotal);
    std::cout << "Antinodes of a: " << antinodesTotal.size();
}
