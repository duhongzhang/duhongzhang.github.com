#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        //通用的变化,没想到
        //暴力，列举40个值
        vector<map<int, string>> vmap = {
           {{1,    "I"}, {2,    "II"}, {3,    "III"}, {4,    "IV"},
            {5,    "V"}, {6,    "VI"}, {7,    "VII"}, {8,    "VIII"},
            {9,   "IX"}},

           {{10,   "X"}, {20,   "XX"}, {30,   "XXX"}, {40,   "XL"},
            {50,   "L"}, {60,   "LX"}, {70,   "LXX"}, {80,   "LXXX"},
            {90,   "XC"}},

           {{100,  "C"}, {200,  "CC"}, {300,  "CCC"}, {400,  "CD"},
            {500,  "D"}, {600,  "DC"}, {700,  "DCC"}, {800,  "DCCC"},
            {900,   "CM"}},

           {{1000, "M"}, {2000, "MM"}, {3000, "MMM"}}
        };

        //1.从左向右，还是从右向左：
        //从左向右，先除50，再对50求余数：
        string str;
        int step = 1;
        for (int i = 0; i < 4; i++) {
            step *= 10;
            int pos = num % step;
            str = vmap[i][pos] + str;
            num -= pos;
        }

        return str;
    }
};

int main() {

    Solution s;

    string str = s.intToRoman(1994);

    return 0;
}