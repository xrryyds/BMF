#ifndef IO_H
#define IO_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Node.h"
#include <fstream>
#include <string>
#include <cmath>

void initMask(std::string fileName, std::vector<Node> BMBNode, int eventID);

void readMask(std::string fileName, int eventID, long long number, std::vector<long long> &buffer);

void addAGroupOfData(std::vector<std::vector<std::string>> newData, int length);


#endif // FILE_H