//
// Created by Juanma on 04/12/2024.
//

#include "Day4.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <set>

void Day4::readMatrix(Matrix &matrix) {
    std::ifstream inFile;

    inFile.open(R"(C:\Users\Juanma\Downloads\input_day_4.txt)");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    std::string line;

    while (std::getline(inFile, line)) {
        //std::cout << line << std::endl;
        matrix.value.emplace_back(line.begin(), line.end());
    }
    inFile.close();
}

void Day4::readRows(const Matrix& matrix) {
}

void Day4::readColumns() {
}

void Day4::readDiagonals() {
}

void Day4::countXMASinString(int &sum, std::regex const& e, std::string s) {
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), e);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        sum++;
    }
}

void Day4::execute() {

    Matrix matrix;

    readMatrix(matrix);
    //
    // readRows(matrix);
    // readColumns();
    // readDiagonals();

    //std::cout << matrix.getColumn(0) << std::endl;
    //std::cout << matrix.getDiagonal(0,0) << std::endl;

    int sum = 0;

    std::regex const e{R"~(XMAS)~"};

    std::regex const e2{R"~(M(A)S)~"};

    //Filas
    for(int i=0;i<matrix.value.size();i++) {
        std::string s = matrix.getRow(i);
        countXMASinString(sum, e, s);
        std::reverse(s.begin(),s.end());
        countXMASinString(sum, e, s);
    }
    //Columnas
    for(int i=0;i<matrix.value.at(0).size();i++) {
        std::string s = matrix.getColumn(i);
        countXMASinString(sum, e, s);
        std::reverse(s.begin(),s.end());
        countXMASinString(sum, e, s);
    }
    //Diagonales 1
    for(int i=0;i<matrix.value.at(0).size();i++) {
        std::string s = matrix.getDiagonal(i,0);
        //std::cout << "Diagonal 1: " << s << std::endl;
        countXMASinString(sum, e, s);
        std::reverse(s.begin(),s.end());
        countXMASinString(sum, e, s);
    }
    for(int i=1;i<matrix.value.at(0).size();i++) {
        std::string s = matrix.getDiagonal(0,i);
        //std::cout << "Diagonal 1: " << s << std::endl;
        countXMASinString(sum, e, s);
        std::reverse(s.begin(),s.end());
        countXMASinString(sum, e, s);
    }
    //Diagonales 2
    for(int i=0;i<matrix.value.size();i++) {
        std::string s = matrix.getDiagonal2(0,i);
        //std::cout << "Diagonal 2: " << s << std::endl;
        countXMASinString(sum, e, s);
        std::reverse(s.begin(),s.end());
        countXMASinString(sum, e, s);
    }
    for(int i=1;i<matrix.value.at(0).size();i++) {
        std::string s = matrix.getDiagonal2(i,matrix.value.at(0).size()-1);
        //std::cout << "Diagonal 2: " << s << std::endl;
        countXMASinString(sum, e, s);
        std::reverse(s.begin(),s.end());
        countXMASinString(sum, e, s);
    }
    std::cout << "Total XMAS: " << sum << std::endl;

    //Part 2
    sum = 0;
    for(int i=0;i<matrix.value.size();i++) {
        for(int j=0;j<matrix.value.at(0).size();j++) {
            if(matrix.get(i,j) == 'A') {
                std::multiset<char> set;
                set.insert(matrix.get(i+1,j+1));
                set.insert(matrix.get(i-1,j-1));
                set.insert(matrix.get(i+1,j-1));
                set.insert(matrix.get(i-1,j+1));
                bool case1 = matrix.get(i+1,j+1) == 'M' &&
                             matrix.get(i-1,j-1) == 'M' &&
                             matrix.get(i+1,j-1) == 'S' &&
                             matrix.get(i-1,j+1) == 'S';

                bool case2 = matrix.get(i+1,j+1) == 'S' &&
                             matrix.get(i-1,j-1) == 'S' &&
                             matrix.get(i+1,j-1) == 'M' &&
                             matrix.get(i-1,j+1) == 'M';
                if(!case1 && !case2 && set.count('M') == 2 && set.count('S') == 2) {
                    sum++;
                }
            }
        }
    }
    std::cout << "Total X-MAS 2: " << sum << std::endl;
}

std::string Matrix::getRow(int index) {
    return std::string(value.at(index).begin(),value.at(index).end());
}

std::string Matrix::getColumn(int index) {
    std::string s;
    for(std::vector<char> row : value) {
        char a = row.at(index);
        s += a;
    }
    return s;
}

std::string Matrix::getDiagonal(int hIndex, int vIndex) {
    std::string s;
    for(int i=hIndex,j=vIndex;i<value.size() && j < value.at(i).size();i++,j++) {
        s += value.at(i).at(j);
    }
    return s;
}

std::string Matrix::getDiagonal2(int vIndex, int hIndex) {
    std::string s;
    for(int i=vIndex,j=hIndex;i<value.size() && j >= 0;i++,j--) {
        s += value.at(i).at(j);
    }
    return s;
}

bool Matrix::checkInsideMatrix(int i, int j) {
    return i >= 0 && i<value.size() && j >= 0 && j<value.size();
}

char Matrix::get(int i, int j) {
    if(checkInsideMatrix(i,j)) {
        return value.at(i).at(j);
    }
    return 'X';
}
