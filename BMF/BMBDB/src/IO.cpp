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

void initMask(std::string fileName, std::vector<Node> BMBNode, int eventID)
{
    long long buffer;
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "openFileErro:" << fileName << std::endl;
        return;
    }

    for (int i = 0; i < BMBNode.size(); i++)
    {
        buffer = BMBNode[i].getQueryMask(eventID);
        file.write(reinterpret_cast<char *>(&buffer), sizeof(long long));
    }

    if (!file.good())
    {
        std::cerr << "writeErro" << std::endl;
    }

    file.close();
}

void readMask(std::string fileName, int eventID, long long number, std::vector<long long> &result)
{
    long long buffer;
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "openFileErro:" << fileName << std::endl;
        return;
    }
    while (number--)
    {
        if (file.read(reinterpret_cast<char *>(&buffer), sizeof(long long)))
        {
            result.push_back(buffer);
        }
        else
        {
            std::cerr << "readErro" << std::endl;
        }
    }

    file.close();
}


void addAGroupOfData(std::vector<std::vector<std::string>> data, int length)
{
    std::ofstream ofs;
    ofs.open("data.txt", std::ios::out | std::ios::app);
    for (int i = 0; i < data.size(); i++)
    {
        std::string buffer;
        for (int j = 0; j < data[i].size(); j++)
        {
            buffer.append(data[i][j]);
            buffer.append(",");
        }
        int cnt = length - buffer.length();
        while (cnt--)
        {
            buffer.append("*");
        }
        ofs << buffer;
    }
    ofs.close();
}