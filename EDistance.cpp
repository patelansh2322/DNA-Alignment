// Copyright [2025] Mohammed Ayan/ Ansh Patel
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "EDistance.hpp"

EDistance::EDistance(const std::string& s1, const std::string& s2)
        : str1(s1), str2(s2), n(s1.length()), m(s2.length()),
        dp(n + 1, std::vector<int>(m + 1, 0)) {}

int EDistance::penalty(char a, char b) {
        return (a == b) ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
        return std::min(a, std::min(b, c));
}

int EDistance::optDistance() {
        for (int i = 0; i <= n; ++i) dp[i][0] = i * 2;
        for (int j = 0; j <= m; ++j) dp[0][j] = j * 2;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int match = dp[i - 1][j - 1] + penalty(str1[i - 1], str2[j - 1]);
                int insert = dp[i][j - 1] + 2;
                int del = dp[i - 1][j] + 2;
                dp[i][j] = min3(match, insert, del);
            }
        }
        return dp[n][m];
}

std::string EDistance::alignment() {
    std::vector<std::string> result;
    int i = n, j = m;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + penalty(str1[i - 1], str2[j - 1])) {
            result.push_back(std::string(1, str1[i - 1]) + " " + std::string(1, str2[j - 1]) + " "
            + std::to_string(penalty(str1[i - 1], str2[j - 1])));
            --i;
            --j;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 2) {
            result.push_back("- " + std::string(1, str2[j - 1]) + " 2");
            --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 2) {
            result.push_back(std::string(1, str1[i - 1]) + " - 2");
            --i;
        }
    }
    std::reverse(result.begin(), result.end());

    std::string output;
    for (const auto& line : result) {
        output += line + "\n";
    }
    return output;
}

std::istream& operator>>(std::istream& in, EDistance& ed) {
    std::getline(in >> std::ws, ed.str1);
    ed.str1.erase(ed.str1.find_last_not_of(" \n\r\t") + 1);
    std::getline(in >> std::ws, ed.str2);
    ed.str2.erase(ed.str2.find_last_not_of(" \n\r\t") + 1);

    ed.n = ed.str1.length();
    ed.m = ed.str2.length();
    ed.dp = std::vector<std::vector<int>>(ed.n + 1, std::vector<int>(ed.m + 1, 0));

    return in;
}

std::ostream& operator<<(std::ostream& os, const EDistance& ed) {
    os << "String 1: " << ed.str1 << "\n";
    os << "String 2: " << ed.str2 << "\n";
    return os;
}
