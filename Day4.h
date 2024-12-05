//
// Created by Juanma on 04/12/2024.
//

#ifndef DAY4_H
#define DAY4_H
#include <iosfwd>
#include <vector>
#include <regex>
#include <set>


class Matrix;

class Day4 {
public:
    void static readMatrix(Matrix &matrix);

    static void readRows(const Matrix& matrix);

    static void readColumns();

    static void readDiagonals();

    static void countXMASinString(int &sum,std::regex const& e, std::string s);

    void static execute();
};

class Matrix {
public:
    std::vector<std::vector<char>> value;
    std::string getRow(int index);
    std::string getColumn(int index);
    std::string getDiagonal(int hIndex, int vIndex);

    std::string getDiagonal2(int hIndex, int vIndex);

    bool checkInsideMatrix(int i, int j);

    char get(int i, int j);
};



#endif //DAY4_H
