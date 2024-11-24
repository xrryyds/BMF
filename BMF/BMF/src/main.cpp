#include <iostream>
#include "../include/Node.h"
#include "../include/tree.h"
#include "../include/tools.h"
#include "../include/IO.h"
#include <bitset>
#include <algorithm>
#include <memory>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <chrono>
using namespace std;

long long theNumberOfAllData = 7305462;
int theLengthOfEachData = 200;

void Test_GenerateParam()
{
    std::vector<std::string> eventSequence;
    std::vector<std::string> fileSequence;

    long long theNumberOfData = 10000l;
    int theNumberOfEvent = 2;

    fileSequence.push_back("event1_root_fileName");
    fileSequence.push_back("event1_MiddleNode_fileName");
    fileSequence.push_back("event1_leafNode_fileName");
    fileSequence.push_back("event2_root_fileName");
    fileSequence.push_back("event2_MiddleNode_fileName");
    fileSequence.push_back("event2_leafNode_fileName");

    eventSequence.push_back("event1");
    eventSequence.push_back("event2");
    std::cout << "paramSetSuccess" << std::endl;
    std::ofstream ofs;
    ofs.open("param.txt", std::ios::out);
    if (ofs.is_open())
    {
        std::cout << "paramFileOpenSuccess" << std::endl;
        ofs << theNumberOfData << "\n";
        ofs << theNumberOfEvent << "\n";
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
    std::cout << "inintParamFinished" << std::endl;
}

void Test_ReadParam()
{
    std::vector<std::string> eventSequence;
    std::vector<std::string> fileSequence;
    long long theNumberOfData;
    long long theNumberOfRoot;
    long long theNumberOfLeaf;
    long long theNumberOfMiddleNode;
    long long theNumberOfNode;
    int theNumberOfEvent;
    std::ifstream ifs;
    ifs.open("param.txt", std::ios::in);
    if (ifs.is_open())
    {
        ifs >> theNumberOfData;
        ifs >> theNumberOfEvent;
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

    std::cout << "theNumberOfData:" << theNumberOfData << std::endl;
    std::cout << "theNumberOfRoot:" << theNumberOfRoot << std::endl;
    std::cout << "theNumberOfMiddleNode:" << theNumberOfMiddleNode << std::endl;
    std::cout << "theNumberOfLeaf:" << theNumberOfLeaf << std::endl;
    std::cout << "theNumberOfNode:" << theNumberOfNode << std::endl;
    std::cout << "theNumberOfEvent:" << theNumberOfEvent << std::endl;

    std::cout << "eventList:" << std::endl;
    for (int i = 0; i < theNumberOfEvent; i++)
    {
        std::cout << " **********" << eventSequence[i] << std::endl;
    }

    std::cout << "fileList:" << std::endl;
    for (int i = 0; i < theNumberOfEvent; i++)
    {
        std::cout << " *********" << fileSequence[i * 3] << std::endl;
        std::cout << " *********" << fileSequence[i * 3 + 1] << std::endl;
        std::cout << " *********" << fileSequence[i * 3 + 2] << std::endl;
    }
}

void Test_SingleQuery(int queryID, long long theNumberOfAllData)
{
    BMBTree tree;
    tree.init(theNumberOfAllData);
    // tree.showParam();
    // tree.showTree();
    std::vector<std::string> result;

    auto beforeTime = std::chrono::steady_clock::now();

    tree.query(queryID, result);

    int cnt = 0;
    for(int i=0;i<result.size();i++)cnt++;
    auto afterTime = std::chrono::steady_clock::now();

    // 毫秒级
    double duration_millsecond = std::chrono::duration<double, std::milli>(afterTime - beforeTime).count();
    std::cout << duration_millsecond << "ms" << std::endl;

    // std::cout << result.size() << "\n";
    // for (int i = result.size() - 5; i < result.size(); i++)
    // {
    //     std::cout << result[i] << "\n";
    // }
    std::cout << result.size() << std::endl;
}

void readCSV()
{
    ifstream file("7.csv");
    vector<vector<string>> data;

    string line;
    int num =0;
    while (getline(file, line))
    {
        cout<<line<<endl;
        break;
        if(num == 1010000 || num == 2010000||num == 3010000 ||num == 4010000 ||num == 5010000 ||num == 6010000 ||num == 7010000){
            cout<<line<<endl;
        }
        vector<string> row;
        size_t pos = 0;
        string token;
        while ((pos = line.find(",")) != string::npos)
        {
            token = line.substr(0, pos);
            row.push_back(token);
            line.erase(0, pos + 1);
        }
        row.push_back(line);
        data.push_back(row);
    }

    cout << data.size();
}

// length = 290
void preData(int length)
{
    ifstream file("6.csv");
    vector<vector<string>> data;

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        vector<string> row;
        size_t pos = 0;
        string token;
        int cnt = 0;
        while ((pos = line.find(",")) != string::npos)
        {
            token = line.substr(0, pos);
            if (cnt == 2 || cnt == 3 || cnt == 4 || cnt == 8)
            {
                row.push_back(token);
            }
            line.erase(0, pos + 1);
            cnt++;
        }
        data.push_back(row);
    }

    cout << data.size() << endl;
    std::ofstream ofs;
    ofs.open("data.txt", std::ios::out);
    if (ofs.is_open())
    {
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
    }
}

// length = 200
void testReadData(int k)
{
    std::ifstream file("data.txt", std::ios::binary);
    if (file)
    {
        std::vector<char> buffer(k);
        file.read(buffer.data(), k);
        std::string data(buffer.begin(), buffer.end());
        std::cout << data << std::endl;

        std::vector<char> buffer2(k);
        file.read(buffer2.data(), k);
        std::string data2(buffer2.begin(), buffer2.end());
        std::cout << data2 << std::endl;

        std::vector<char> buffer3(k);
        file.read(buffer3.data(), k);
        std::string data3(buffer3.begin(), buffer3.end());
        std::cout << data3 << std::endl;
    }
}

void Test_GenerateTree()
{
    BMBTree tree;
    tree.Test_GenerateTree();
}

void init()
{
    std::ifstream ifs;
    ifs.open("globalParameter.txt", std::ios::in);
    if (ifs.is_open())
    {
        ifs >> theNumberOfAllData;
        ifs >> theLengthOfEachData;
        ifs.close();
    }
}

void save()
{
    std::ofstream ofs;
    ofs.open("globalParameter.txt", std::ios::out);
    if (ofs.is_open())
    {
        ofs << theNumberOfAllData << "\n";
        ofs << theLengthOfEachData << "\n";
        ofs.close();
    }
}

int main()
{
    // preData(200);
    // Test_GenerateTree();
    // readCSV();
    // init();

    

    Test_SingleQuery(11, 7305457);




    // long long buffer = 9981;
    // long long buffer2 = 77499;
    // long long buffer3 = 7749;
    // std::ofstream fileo("test.bin", std::ios::binary);
    // for (int i = 0; i < 5; i++)
    // {
    //     fileo.write(reinterpret_cast<char *>(&buffer), sizeof(long long));
    // }
    // fileo.write(reinterpret_cast<char *>(&buffer2), sizeof(long long));
    // fileo.write(reinterpret_cast<char *>(&buffer3), sizeof(long long));
    // fileo.close();

    // std::ofstream file2("test.bin", std::ios::binary);

    // file2.seekp(6 * sizeof(long long), std::ios::beg);
    // file2.write(reinterpret_cast<char *>(&buffer), sizeof(long long));
    // file2.write(reinterpret_cast<char *>(&buffer2), sizeof(long long));
    // file2.close();

    // long long number;
    // // 以二进制模式打开文件进行读取
    // std::ifstream file("test.bin", std::ios::binary);
    // if (!file.is_open())
    // {
    //     std::cerr << "无法打开文件" << std::endl;
    //     return 1;
    // }

    // file.seekg(6 * sizeof(long long), std::ios::beg);

    // file.read(reinterpret_cast<char *>(&number), sizeof(long long));

    // std::cout << number << std::endl;

    // file.read(reinterpret_cast<char *>(&number), sizeof(long long));

    // std::cout << number << std::endl;

    // file.close();
}
