//
// Created by Juanma on 02/12/2024.
//

#include "Day2.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

bool Day2::check(std::vector<int> lista) {
    std::set<int> diferencias;
    bool safe = true;
    for(int j=0;j<lista.size()-1;j++) {
        int diferencia = abs(lista.at(j)-lista.at(j+1));
        int incremento = lista.at(j)-lista.at(j+1);
        diferencias.insert(incremento);
        safe = safe && diferencia > 0 && diferencia < 4 && (*diferencias.rbegin() < 0 || *diferencias.begin() > 0);
    }
    return safe;
}

void Day2::execute() {
    std::ifstream inFile;

    inFile.open("C:\\Users\\Juanma\\Downloads\\input_day_2.txt");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    std::string line;

    int sumaSafes = 0;

    std::vector<std::vector<int>> map;
    std::map<int,int> mapUnsafe;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string stringNumero;
        std::vector<int> lista;
         while(std::getline(iss, stringNumero, ' ')) {
             int numero = std::stoi(stringNumero);
             lista.push_back(numero);
         }
        bool safe = true;
        std::set<int> diferencias;
        for(int i=0;i<lista.size()-1;i++) {
            int diferencia = abs(lista.at(i)-lista.at(i+1));
            int incremento = lista.at(i)-lista.at(i+1);
            diferencias.insert(incremento);
            safe = safe && diferencia > 0 && diferencia < 4 && (*diferencias.rbegin() < 0 || *diferencias.begin() > 0);
        }
        map.push_back(lista);
        if(safe) sumaSafes++;
    }
    inFile.close();

    std::cout << sumaSafes << std::endl;

    int indiceLista = 0;
    std::set<int> setSafe;
    for(auto lista : map) {
        for(int i=0;i<lista.size();i++) {
            int copia = lista.at(i);
            lista.erase(lista.begin()+i);
            if(check(lista)){setSafe.emplace(indiceLista);}
            lista.insert(lista.begin()+i,copia);
        }
        indiceLista++;
    }
    std::cout << setSafe.size() << std::endl;
}
