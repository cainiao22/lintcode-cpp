#ifndef COMMONUTILS_H
#define COMMONUTILS_H


#include<iostream>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<string>
#include<set>
#include<algorithm>

using namespace std;

//前置声明
class GraphEdge;

class GraphNode
{
public:
    GraphNode(int val):visited(false), val(val)
    {
    }
    void addEdge(GraphEdge* edge)
    {
        this->edgeList.push_back(edge);
    }

    int val;
    bool visited;
    vector<GraphEdge*> edgeList;
};


class GraphEdge
{
public:
    GraphEdge(int color):visited(false), color(color)
    {

    }

    void addNode(GraphNode* node)
    {
        this->nodeList.push_back(node);
    }

    bool visited;
    int color;
    vector<GraphNode*> nodeList;
};



class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int val) {
        this->val = val;
        this->next = NULL;
    }
};

class TreeNode
{
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val)
    {
        this->val = val;
        this->left = this->right = NULL;
    }
};

class CommonUtils
{
public:
    int INF = 1e9;
    CommonUtils();
protected:
    void printVector(vector<int> &v);
    void printVector2(vector<vector<int>> &v);
    void printListNode(ListNode* head);
    void deleteListNode(ListNode* head);
};







#endif // COMMONUTILS_H
