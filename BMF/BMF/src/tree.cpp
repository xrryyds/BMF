#include "../include/tree.h"
#include <bitset>
#include "../include/IO.h"
#include "../include/tools.h"
#include <chrono>
using namespace std;
BMBTree::BMBTree()
{
}

BMBTree::~BMBTree()
{
    // 析构函数的实现
}

void BMBTree::init(long long theNumberOfAllData)
{
    inintParam();
    inintTree();
    if (theNumberOfAllData > theNumberOfData)
    {
        auto beforeTime = std::chrono::steady_clock::now();

        updataTree(theNumberOfAllData);
        auto afterTime = std::chrono::steady_clock::now();

        // 毫秒级
        double duration_millsecond = std::chrono::duration<double, std::milli>(afterTime - beforeTime).count();
        std::cout << duration_millsecond << "OOms" << std::endl;
    }
}

void BMBTree::showParam()
{
    std::cout << "theNumberOfData:" << theNumberOfData << std::endl;
    std::cout << "theNumberOfRoot:" << theNumberOfRoot << std::endl;
    std::cout << "theNumberOfMiddleNode:" << theNumberOfMiddleNode << std::endl;
    std::cout << "theNumberOfLeaf:" << theNumberOfLeaf << std::endl;
    std::cout << "theNumberOfNode:" << theNumberOfNode << std::endl;
    std::cout << "theNumberOfEvent:" << theNumberOfEvent << std::endl;
    std::cout << "theLengthOfEachData:" << theLengthOfEachData << std::endl;

    std::cout << "eventList:" << std::endl;
    for (int i = 0; i < theNumberOfEvent; i++)
    {
        std::cout << " **********" << eventSequence[i] << std::endl;
    }

    std::cout << "fileList:" << std::endl;
    for (int i = 0; i < theNumberOfEvent; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << " *********" << fileSequence[i * 3 + j] << std::endl;
        }
    }
}

void BMBTree::showTree()
{
    std::cout << "root:"
              << "\n";
    // for (int e = 1; e < theNumberOfEvent; e++)
    // {
    //     for (int i = 0; i < theNumberOfRoot; i++)
    //     {
    //         std::bitset<sizeof(long long) * 8> bits(BMBRootNode[i].getQueryMask(e));
    //         std::cout << bits.to_string() << " ";
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << "middleNode:"
    //           << "\n";
    // for (int e = 0; e < theNumberOfEvent; e++)
    // {
    //     for (int i = 0; i < theNumberOfMiddleNode; i++)
    //     {
    //         std::bitset<sizeof(long long) * 8> bits(BMBMiddleNode[i].getQueryMask(e));
    //         std::cout << bits.to_string() << " ";
    //     }
    //     std::cout << "\n";
    // }

    std::cout << "leafNode:"
              << "\n";
    for (int e = 1; e < theNumberOfEvent; e++)
    {

        std::bitset<sizeof(long long) * 8> bits(BMBLeafNode[theNumberOfLeaf - 1].getQueryMask(e));
        std::cout << bits.to_string() << " ";

        std::cout << "\n";
    }
}

// 全局参数更新
void BMBTree::saveParam()
{
    std::ofstream ofs;
    ofs.open("param.txt", std::ios::out);
    if (ofs.is_open())
    {
        ofs << theNumberOfData << "\n";
        ofs << theNumberOfEvent << "\n";
        ofs << theLengthOfEachData << "\n";
        ofs << dataFileName << "\n";
        for (int i = 0; i < theNumberOfEvent * 3; i++)
        {
            cout << fileSequence[i] << "\n";
        }
        for (int i = 0; i < theNumberOfEvent * 3; i++)
        {
            ofs << fileSequence[i] << "\n";
        }

        for (int i = 0; i < theNumberOfEvent; i++)
        {
            ofs << eventSequence[i] << "\n";
        }
        ofs.close();
    }
}

void BMBTree::saveTree()
{
    std::ofstream ofs;
    for (int e = 0; e < theNumberOfEvent; e++)
    {
        initMask(fileSequence[e * 3], BMBRootNode, e);
        initMask(fileSequence[e * 3 + 1], BMBMiddleNode, e);
        initMask(fileSequence[e * 3 + 2], BMBLeafNode, e);
    }
}

// void BMBTree::updataTreeByAllLeaf()
// {
//     for (int i = 0; i < theNumberOfLeaf; i++)
//     {
//         for (int e = 0; e < theNumberOfEvent; e++)
//         {
//             if (BMBLeafNode[i].getQueryMask(e))
//             {
//                 BMBMiddleNode[i / 64].updateMaskByBit(e, 1ULL << (i % 64));
//             }
//         }
//     }

//     for (int i = 0; i < theNumberOfMiddleNode; i++)
//     {
//         for (int e = 0; e < theNumberOfEvent; e++)
//         {
//             if (BMBMiddleNode[i].getQueryMask(e))
//             {
//                 BMBRootNode[i / 64].updateMaskByBit(e, 1ULL << (i % 64));
//             }
//         }
//     }
// }

void BMBTree::updataTreeByAllData(std::vector<std::vector<std::string>> data, long long theNumberOfAllData)
{
    long long tData = theNumberOfData;
    long long tleaf = std::ceil(static_cast<float>(tData) / static_cast<float>(64));
    long long tMiddleNode = std::ceil(static_cast<float>(tleaf) / static_cast<float>(64));
    theNumberOfData = theNumberOfAllData;
    for (long long i = 0; i < data.size(); i++)
    {
        for (int e = 0; e < theNumberOfEvent; e++)
        {

            if (evenIsOn(data[i], e))
            {
                BMBLeafNode[(tData + i) / 64].updateMaskByBit(e, 1ULL << (tData + i) % 64);
            }
        }
    }

    cout << "updateMiddle" << endl;
    for (long long i = (tleaf - 1 >= 0) ? tleaf : 0; i < theNumberOfLeaf; i++)
    {
        for (int e = 0; e < theNumberOfEvent; e++)
        {
            if (BMBLeafNode[i].getQueryMask(e))
            {
                BMBMiddleNode[i / 64].updateMaskByBit(e, 1ULL << (i % 64));
            }
        }
    }

    cout << "updateRoot" << endl;
    for (long long i = (tMiddleNode - 1 >= 0) ? tMiddleNode : 0; i < theNumberOfMiddleNode; i++)
    {
        for (int e = 0; e < theNumberOfEvent; e++)
        {
            if (BMBMiddleNode[i].getQueryMask(e))
            {
                BMBRootNode[i / 64].updateMaskByBit(e, 1ULL << (i % 64));
            }
        }
    }
}

void BMBTree::putBitOn(int eventId, long long dataID) {}

void BMBTree::putBitOff(int eventId, long long dataID) {}

void BMBTree::inintParam()
{
    std::ifstream ifs;
    ifs.open("param.txt", std::ios::in);
    if (ifs.is_open())
    {
        ifs >> theNumberOfData;
        ifs >> theNumberOfEvent;
        ifs >> theLengthOfEachData;
        ifs >> dataFileName;
        theNumberOfLeaf = std::ceil(static_cast<float>(theNumberOfData) / static_cast<float>(64));
        theNumberOfMiddleNode = std::ceil(static_cast<float>(theNumberOfLeaf) / static_cast<float>(64));
        theNumberOfRoot = std::ceil(static_cast<float>(theNumberOfMiddleNode) / static_cast<float>(64));
        theNumberOfNode = theNumberOfLeaf + theNumberOfMiddleNode + theNumberOfRoot;
        std::string str;
        for (int i = 0; i < theNumberOfEvent * 3; i++)
        {
            ifs >> str;
            fileSequence.push_back(str);
        }
        for (int i = 0; i < theNumberOfEvent; i++)
        {
            ifs >> str;
            eventSequence.push_back(str);
        }
        ifs.close();
    }
}

void BMBTree::inintTree()
{

    for (int i = 0; i < theNumberOfRoot; i++)
    {
        BMBRootNode.push_back(Node(i));
    }
    for (int i = 0; i < theNumberOfMiddleNode; i++)
    {
        BMBMiddleNode.push_back(Node(i));
    }
    for (int i = 0; i < theNumberOfLeaf; i++)
    {
        BMBLeafNode.push_back(Node(i));
    }

    for (int e = 0; e < theNumberOfEvent; e++)
    {
        std::vector<long long> buffer;
        readMask(fileSequence[e * 3], e, theNumberOfRoot, buffer);
        for (int i = 0; i < theNumberOfRoot; i++)
        {
            BMBRootNode[i].addMask(buffer[i]);
        }
        buffer.clear();
        readMask(fileSequence[e * 3 + 1], e, theNumberOfMiddleNode, buffer);
        for (int i = 0; i < theNumberOfMiddleNode; i++)
        {
            BMBMiddleNode[i].addMask(buffer[i]);
        }

        buffer.clear();
        readMask(fileSequence[e * 3 + 2], e, theNumberOfLeaf, buffer);
        for (int i = 0; i < theNumberOfLeaf; i++)
        {
            BMBLeafNode[i].addMask(buffer[i]);
        }
    }
}

void BMBTree::query(int queryID, std::vector<std::string> &resultData)
{
    std::vector<long long> middleNode, leaf, result, tmp;
    for (int i = 0; i < theNumberOfRoot; i++)
    {
        findAllOn(Hybrid_query(queryID, BMBRootNode[i]), tmp);
        for (int j = 0; j < tmp.size(); j++)
        {
            middleNode.push_back(i * 64 + tmp[j]);
        }
        tmp.clear();
    }

    for (int i = 0; i < middleNode.size(); i++)
    {
        findAllOn(Hybrid_query(queryID, BMBMiddleNode[middleNode[i]]), tmp);
        for (int j = 0; j < tmp.size(); j++)
        {
            leaf.push_back(middleNode[i] * 64 + tmp[j]);
        }
        tmp.clear();
    }

    for (int i = 0; i < leaf.size(); i++)
    {
        findAllOn(Hybrid_query(queryID, BMBLeafNode[leaf[i]]), tmp);
        for (int j = 0; j < tmp.size(); j++)
        {
            result.push_back(leaf[i] * 64 + tmp[j]);
        }
        tmp.clear();
    }
    // cout<<"lastNum:"<<result[result.size()-1]<<endl;
    readData(dataFileName, result, resultData);
}

long long BMBTree::Hybrid_query(int queryID, Node node)
{
    switch (queryID)
    {
    case 10:
        return node.getQueryMask(0);
        break;
    case 11:
        return node.getQueryMask(1);
        break;
    case 20:
        return static_cast<unsigned long long>(node.getQueryMask(0)) & static_cast<unsigned long long>(node.getQueryMask(1));
        break;
    case 21:
        return (~static_cast<unsigned long long>(node.getQueryMask(0))) & static_cast<unsigned long long>(node.getQueryMask(1));
    default:
        return 0;
        break;
    }
}

void BMBTree::readData(std::string fileName, std::vector<long long> result, std::vector<std::string> &resultData)
{
    std::ifstream file(fileName, std::ios::binary);
    vector<vector<std::string>> data;
    if (file)
    {
        for (int i = 0; i < result.size(); i++)
        {
            std::vector<char> buffer(theLengthOfEachData);
            file.seekg(result[i] * theLengthOfEachData, std::ios::beg);
            file.read(buffer.data(), theLengthOfEachData);
            std::string line(buffer.begin(), buffer.end());
            resultData.push_back(line);
        }
        file.close();
    }
}

void BMBTree::updataTree(long long theNumberOfAllData)
{
    while (std::ceil(static_cast<float>(theNumberOfAllData) / static_cast<float>(64)) > theNumberOfLeaf)
    {
        std::vector<long long> nodeMaskBuffer;
        for (int e = 0; e < theNumberOfEvent; e++)
        {
            nodeMaskBuffer.push_back(0);
        }
        BMBLeafNode.push_back(Node(theNumberOfLeaf++, nodeMaskBuffer));
    }

    while (std::ceil(static_cast<float>(theNumberOfLeaf) / static_cast<float>(64)) > theNumberOfMiddleNode)
    {
        std::vector<long long> nodeMaskBuffer;
        for (int e = 0; e < theNumberOfEvent; e++)
        {
            nodeMaskBuffer.push_back(0);
        }
        BMBMiddleNode.push_back(Node(theNumberOfMiddleNode++, nodeMaskBuffer));
    }
    while (std::ceil(static_cast<float>(theNumberOfMiddleNode) / static_cast<float>(64)) > theNumberOfRoot)
    {
        std::vector<long long> nodeMaskBuffer;
        for (int e = 0; e < theNumberOfEvent; e++)
        {
            nodeMaskBuffer.push_back(0);
        }
        BMBRootNode.push_back(Node(theNumberOfRoot++, nodeMaskBuffer));
    }
    theNumberOfNode = theNumberOfLeaf + theNumberOfMiddleNode + theNumberOfRoot;

    std::vector<long long> index;
    std::vector<std::string> datastr;
    std::vector<std::vector<std::string>> data;
    for (int i = theNumberOfData; i < theNumberOfAllData; i++)
    {
        index.push_back(i);
    }
    cout << "updateData:" << index.size() << endl;
    auto beforeTime = std::chrono::steady_clock::now();

    readData(dataFileName, index, datastr);
    transformStrToData(datastr, data);

    auto afterTime = std::chrono::steady_clock::now();

    // 毫秒级
    double duration_millsecond = std::chrono::duration<double, std::milli>(afterTime - beforeTime).count();
    std::cout << duration_millsecond << "ms" << std::endl;
    updataTreeByAllData(data, theNumberOfAllData);
    saveParam();
    saveTree();
}

bool BMBTree::evenIsOn(std::vector<std::string> data, int eventID)
{
    switch (eventID)
    {
    case 0:
        return data[3] >= "5000000000";
        break;
    case 1:
        return data[1] == "0x32be343b94f860124dc4fee278fdcbd38c102d88";
        break;
    default:
        return 0;
        break;
    }
}

void BMBTree::updateDataIntoFile(std::vector<std::vector<std::string>> data)
{
    std::ofstream ofs;
    ofs.open(dataFileName, ios::out | ios::app);
    std::string buffer;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            buffer.append(data[i][j]);
            buffer.append(",");
        }
        int cnt = theLengthOfEachData - buffer.length();
        while (cnt--)
        {
            buffer.append("*");
        }
        ofs << buffer;
    }
    ofs.close();
}

/***************************************************************************/
void BMBTree::Test_addNewData()
{

    inintParam();
    inintTree();
    showTree();
    vector<string> newData;
    newData.push_back("333");
    newData.push_back("0x32be343b94f860124dc4fee278fdcbd38c102d88");
    newData.push_back("22");
    newData.push_back("77");
    // addOneData(newData);
    showTree();
    ifstream ifs;
    ifs.open("data.txt", ios::in);
    string tmp;
    std::vector<char> buffer(theLengthOfEachData);
    ifs.seekg((theNumberOfData - 1) * theLengthOfEachData, std::ios::beg);
    ifs.read(buffer.data(), theLengthOfEachData);
    for (int i = 0; i < buffer.size(); i++)
        cout << buffer[i];
}

void BMBTree::Test_GenerateTree()
{
    theNumberOfLeaf = 0;
    theNumberOfData = 0;
    theNumberOfMiddleNode = 0;
    theNumberOfRoot = 0;
    theNumberOfNode = 0;
    theNumberOfEvent = 2;
    theLengthOfEachData = 200;
    dataFileName = "data.txt";
    std::ifstream file("data.txt", std::ios::binary);
    vector<vector<string>> data;
    if (file)
    {
        int cnt = 0;
        // int num = 10000;
        while (1)
        {

            std::vector<char> buffer(theLengthOfEachData);
            file.read(buffer.data(), theLengthOfEachData);
            if (file.gcount() != theLengthOfEachData)
            {
                break;
            }
            std::string line(buffer.begin(), buffer.end());
            vector<string> row;
            size_t pos = 0;
            string token;
            while ((pos = line.find(",")) != string::npos)
            {
                token = line.substr(0, pos);
                row.push_back(token);
                line.erase(0, pos + 1);
            }
            data.push_back(row);
        }
        file.close();
    }

    long long theNumberOfAllData = data.size();

    fileSequence.push_back("bigValue_root.bin");
    fileSequence.push_back("bigValue_MiddleNode.bin");
    fileSequence.push_back("bigValue_leafNode.bin");
    fileSequence.push_back("fromMe_root.bin");
    fileSequence.push_back("fromMe_MiddleNode.bin");
    fileSequence.push_back("fromMe_leafNode.bin");

    eventSequence.push_back("bigValue");
    eventSequence.push_back("fromMe");
    std::cout << "paramSetSuccess" << std::endl;
    cout << "updateBegain" << endl;
    updataTree(theNumberOfAllData);
    cout << "updataTreeE" << endl;
    showParam();
}
