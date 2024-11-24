#ifndef tools
#define tools

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


void transformStrToData(std::vector<std::string> str, std::vector<std::vector<std::string>> &data);

void findAllOn(long long mask, std::vector<long long> &result);

#endif // FILE_H