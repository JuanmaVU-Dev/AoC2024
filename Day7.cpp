//
// Created by Juanma on 08/12/2024.
//

#include "Day7.h"

#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

std::vector<char> Day7::generaPermutacion(int combination,const int &size) {
    std::bitset<64> bitsPermutation = combination;
    std::vector<char> vectorPermutation;
    vectorPermutation.reserve(size-1);
    for(int i=0,j=size-1;i<size;i++,j--) {
        if(j<bitsPermutation.size()) {
            if(bitsPermutation[j]== 0) {
                vectorPermutation.emplace_back('+');
            }
            if(bitsPermutation[j]== 1) {
                vectorPermutation.emplace_back('*');
            }
        }else {
            vectorPermutation.emplace_back('+');
        }
    }
    return vectorPermutation;
}

void Day7::execute() {
    std::vector<__int64> results;
    std::vector<std::vector<__int64>> numbers;
    std::vector<std::vector<char>> operators;

    std::ifstream inFile;

    inFile.open(R"(C:\Users\Juanma\Downloads\input_day_7.txt)");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string result;
        int i = 0;
        while(std::getline(iss, result, ':')) {
            if(i%2 == 0) {
                //std::cout << "resultado: " << result << std::endl;
                results.push_back(_atoi64(result.c_str()));
            }
            else {
                std::istringstream iss2(result);
                std::string number;
                std::vector<__int64> vectorNumbers;
                while(std::getline(iss2, number, ' ')) {
                    if(!number.empty()) {
                        //std::cout << " - numero: " << number << std::endl;
                        vectorNumbers.emplace_back(std::stol(number));
                    }
                }
                numbers.emplace_back(vectorNumbers);
            }
            i++;
        }
    }
    inFile.close();
    __int64 tempResult;
    __int64 countCorrectResults = 0;
    for(int rowIndex=0;rowIndex<results.size();rowIndex++) {
        int combination = 0;
        bool correctResult = false;
        __int64 n = pow(2,numbers.at(rowIndex).size()-1);
        //std::cout << "-------------------------------------------" << n << std::endl;
        while(combination < n && !correctResult){
            tempResult = 0;
            bool first = true;
            //operators.emplace_back();
            auto operatorsPermutation = generaPermutacion(combination,numbers.at(rowIndex).size()-1);
            for(int i=0,j=1;j<numbers.at(rowIndex).size();i++,j++) {
                if(operatorsPermutation.at(i) == '*' && first) {
                    tempResult = numbers.at(rowIndex).at(i) * numbers.at(rowIndex).at(j);
                }
                if(operatorsPermutation.at(i) == '*' && !first) {
                    tempResult *= numbers.at(rowIndex).at(j);
                }
                if(operatorsPermutation.at(i) == '+' && first) {
                    tempResult = numbers.at(rowIndex).at(i) + numbers.at(rowIndex).at(j);
                }
                if(operatorsPermutation.at(i) == '+' && !first) {
                    tempResult += numbers.at(rowIndex).at(j);
                }
                first = false;
                //std::cout << tempResult << std::endl;
            }
            correctResult = correctResult || tempResult == results.at(rowIndex);
            if(tempResult == results.at(rowIndex)) {
                std::cout << "-------------- Correct result: " << tempResult<< std::endl;
                countCorrectResults = countCorrectResults + tempResult;
            }
            //std::cout << "-------------------------------------------" << std::endl;
            combination++;
        }
    }
    std::cout << "-------------- Number of posible ecuations: " << countCorrectResults << std::endl;
}
