//
// Created by Juanma on 03/12/2024.
//

#include "Day3.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

void Day3::execute() {

    // Note: Raw string literal R"~()~" removes the need to escape the string
    //std::regex const exp{R"~(don't\(\).*do\(\))~"};
    std::regex const e{R"~(do\(\)|mul\((\d{1,3}),(\d{1,3})\)|don't\(\))~"};

    int multiplication = 0;

    std::ifstream inFile;

    inFile.open("C:\\Users\\Juanma\\Downloads\\input_day_3.txt");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    std::string line;
    std::string s;

    while (std::getline(inFile, line)) {
        s += line;
    }
    inFile.close();

    auto words_begin = std::sregex_iterator(s.begin(), s.end(), e);
    auto words_end = std::sregex_iterator();
    bool enabled = true;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        std::string match_str = match.str();
        if(match_str == "do()") {
            enabled = true;
        }else if(match_str == "don't()") {
            enabled = false;
        }
        else {
            if(enabled) {
                std::cmatch matchGroup;
                std::regex_match(match.str().c_str(), matchGroup, e);

                multiplication += std::stoi(match[1].str()) * std::stoi(match[2].str());
                std::cout << match_str << " - ";
                std::cout << std::stoi(match[1].str()) * std::stoi(match[2].str()) << std::endl;
            }

        }
    }

    std::cout << multiplication << std::endl;
}
