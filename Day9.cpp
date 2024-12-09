//
// Created by Juanma on 11/12/2024.
//

#include "Day9.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string Day9::generateString(const std::string& value, int index) {
    std::string s;
    std::string baseText;
    int number = std::stoi(value);
    if(index%2 == 1) {
        baseText = ".";
    }else {
        baseText = std::to_string(index/2);
    }

    for(int i=0;i<number;i++) {
        s.append(baseText);
    }
    return s;
}

__int64 Day9::generateChecksum(std::vector<std::string> &s2) {
    __int64 checksum = 0;
    for(int i=0;i<s2.size();i++) {
        if(s2.at(i) != ".") {
            std::string substring = s2.at(i);
            checksum += _atoi64(substring.c_str()) * i;
        }
    }
    return checksum;
}

int Day9::searchFreeSpace(const std::vector<std::string> &s, int &initial) {
    for(int i = initial;i<s.size();i++) {
        if(s.at(i) == ".") {
            return i;
        }
    }
    return s.size()-1;
}

void Day9::compact(std::vector<std::string> &s2) {
    int initialIndex = 0;
    for(int i=s2.size()-1;i>=0;i--) {
        if(s2.at(i) != ".") {
            int freeSpaceIndex = searchFreeSpace(s2, initialIndex);
            initialIndex = freeSpaceIndex;
            if(freeSpaceIndex < i) {
                s2.at(freeSpaceIndex) = s2.at(i);
                s2.at(i) = ".";
            }else {
                break;
            }
        }
    }
}

int Day9::searchFreeSpaceWithSize(const std::vector<std::string> &s, int initial,int size) {
    for(int i = initial;i<s.size();i++) {
        if(s.at(i) == ".") {
            return i;
        }
    }
    return s.size()-1;
}

void Day9::compactDefrag(std::vector<std::string> &s2) {
    int initial = 0;
    int size;
    for(int i=s2.size()-1;i>=0;i--) {
        if(s2.at(i) != ".") {
            int freeSpaceIndex = searchFreeSpaceWithSize(s2, initial, size);
            if(freeSpaceIndex < i) {
                s2.at(freeSpaceIndex) = s2.at(i);
                s2.at(i) = ".";
            }else {
                break;
            }
        }
    }
}

void Day9::execute() {
    std::ifstream inFile;

    inFile.open(R"(C:\Users\Juanma\Downloads\input_day_9.txt)");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    std::string s;
    std::string line;
    while (std::getline(inFile, line)) {
        s.append(line);
    }
    inFile.close();

    s = "2333133121414131402";

    std::vector<std::string> s2;
    for(int i=0;i<s.size();i++) {
        __int64 number = _atoi64(s.substr(i,1).c_str());
        for(int j=0;j<number;j++) {
            if(i % 2 == 0) {
                s2.emplace_back(std::to_string(i/2));
            }else {
                s2.emplace_back(".");
            }
        }
    }

    //std::cout << s2 << std::endl;

    compact(s2);

    //compactDefrag(s2);

    //std::cout << s2 << std::endl;
    std::string s3;
    //for(int i=0;i<s2.size();i++) {
        //s3.append(s2.at(i));
    //}

    __int64 checksum = generateChecksum(s2);
    std::cout << "Checksum: " << checksum << std::endl;
}
