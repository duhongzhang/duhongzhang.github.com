#pragma once
#include <iostream>
#include <algorithm>
#include <string>
class testString {
    std::string str;
public:
    std::string operator()() const { return str; }
    testString(std::string str) : str(str) {}
    bool isEmpty() { return str.empty(); }
    int str2int() { return std::stoi(str); }
    char& operator [] (int index) { return str[index]; }
    int size() { return str.size(); }
};