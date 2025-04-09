// Copyright [2025] Mohammed Ayan/ Ansh Patel
#pragma once

#include <string>
#include <vector>
#include <iostream>

class EDistance {
 public:
    EDistance(const std::string& s1, const std::string& s2);

    static int penalty(char a, char b);
    static int min3(int a, int b, int c);

    int optDistance();
    std::string alignment();

    friend std::istream& operator>>(std::istream& in, EDistance& ed);
    friend std::ostream& operator<<(std::ostream& os, const EDistance& ed);

 private:
    std::string str1, str2;
    int n, m;
    std::vector<std::vector<int>> dp;
};