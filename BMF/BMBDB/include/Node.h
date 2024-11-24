#ifndef NODE_H
#define NODE_H

#include <vector>

class Node {
public:
    Node();
    Node(int id);
    Node(int id, const std::vector<long long> nodeMaskBuffer);
    ~Node();

    // Returns the mask corresponding to the queryId.
    long long getQueryMask(int queryId);

    void updateMaskByBit(int eventId, long long oper);

    void addMask(long long newMask);

private:
    int id;
    std::vector<unsigned long long> nodeMask;
};

#endif // NODE_H


