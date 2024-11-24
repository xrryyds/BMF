#include "../include/Node.h"

Node::Node(int tid) {
    id = tid;
} 

Node::Node(int tid, std::vector<long long> nodeMaskBuffer){
    id = tid;
    for(int i = 0; i < nodeMaskBuffer.size(); i++){
        nodeMask.push_back(nodeMaskBuffer[i]);
    }
}

Node::~Node() {}  // 析构函数的实现

long long Node::getQueryMask(int queryId) {
    return nodeMask[queryId];
}

void Node::updateMaskByBit(int eventId, long long oper) {
    nodeMask[eventId] |= oper;
}

void Node::addMask(long long newMask) {
    nodeMask.push_back(newMask);
}