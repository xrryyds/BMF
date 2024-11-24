#include "IO.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "../include/Node.h"
#include "../include/tree.h"
#include <fstream>
#include <string>
#include <cmath>



void transformStrToData(std::vector<std::string> str, std::vector<std::vector<std::string>> &data)
{
    for (int i = 0; i < str.size(); i++)
    {
        std::string line = str[i];
        std::vector<std::string> row;
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(",")) != std::string::npos)
        {
            token = line.substr(0, pos);
            row.push_back(token);
            line.erase(0, pos + 1);
        }
        data.push_back(row);
    }
}



void findAllOn(long long mask, std::vector<long long> &result)
{
    unsigned long long umask = static_cast<unsigned long long>(mask);
    int pos = 0;
    while (umask > 0)
    {
        if ((umask & 1) == 1)
        {                          // 检查当前位是否为1
            result.push_back(pos); // 因为数组是从0开始的，所以加1
        }
        umask >>= 1; // 将k右移一位，继续检查下一位
        pos++;
    }
}