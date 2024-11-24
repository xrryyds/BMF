#ifndef TREE_H
#define TREE_H

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
/*
vector 需用指针重构
乘法转为位运算
*/

class BMBTree
{
public:
    void Test_addNewData();

    void Test_GenerateTree();
    /*****************************************************/
    BMBTree();

    ~BMBTree();

    void query(int queryID,  std::vector<std::string> &resultData);

    void showParam();

    void showTree();

    void init(long long theNumberOfAllData);

    void updataTree(long long theNumberOfAllData);

private:
    // 全局参数更新
    void saveParam();

    void saveTree();

    void putBitOn(int eventId, long long dataID);

    void putBitOff(int eventId, long long dataID);

    void inintParam();

    void inintTree();

    void readData(std::string fileName, std::vector<long long> result, std::vector<std::string> &resultData);

    bool evenIsOn(std::vector<std::string> data, int eventId); //*D

    void updateDataIntoFile(std::vector<std::vector<std::string>> data);

 

    long long Hybrid_query(int queryID, Node node); //*D

    void updataTreeByAllData(std::vector<std::vector<std::string>> data, long long theNumberOfAllData);

private:
    std::vector<Node> BMBRootNode;
    std::vector<Node> BMBMiddleNode;
    std::vector<Node> BMBLeafNode;
    std::vector<std::string> eventSequence;
    std::vector<std::string> fileSequence;
    std::string dataFileName;
    int theLengthOfEachData;
    long long theNumberOfData;
    long long theNumberOfRoot;
    long long theNumberOfLeaf;
    long long theNumberOfMiddleNode;
    long long theNumberOfNode;
    int theNumberOfEvent;
};

#endif