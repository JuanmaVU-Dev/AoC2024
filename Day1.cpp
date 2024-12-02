//
// Created by Juanma on 02/12/2024.
//

#include "Day1.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

Day1::Day1() = default;

Day1::~Day1() = default;

void Day1::execute() {
    std::ifstream inFile;

    inFile.open("C:\\Users\\Juanma\\Downloads\\input.txt");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    int x;
    int i=0;
    int sum = 0;
    int similarityScore = 0;

    std::vector<int> lista1;
    std::vector<int> lista2;
    std::multiset<int> set2;

    while (inFile >> x) {
        if(i%2 == 0) {
            lista1.push_back(x);
        }else {
            lista2.push_back(x);
            set2.insert(x);
        }
        i++;
    }

    inFile.close();

    std::sort(lista1.begin(),lista1.end());
    std::sort(lista2.begin(),lista2.end());

    int similarity;
    for(i=0;i<lista1.size();i++) {
        sum += abs(lista1.at(i) - lista2.at(i));
        similarity = lista1.at(i)*set2.count(lista1.at(i));
        similarityScore += similarity;
    }

    std::cout << sum << std::endl;
    std::cout << similarityScore << std::endl;
}
