#include "commonutils.h"

CommonUtils::CommonUtils()
{

}


void CommonUtils::printVector(vector<int> &v)
{
    for(int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<'\t';
    }
    cout<<endl;
}

void CommonUtils::printVector2(vector<vector<int>> &v)
{
    for(int i=0; i<v.size(); i++)
    {
        for(int j=0; j<v[i].size(); j++)
        {
            cout<<v[i][j]<<'\t';
        }
        cout<<endl;
    }
    cout<<endl;
}


void CommonUtils::printListNode(ListNode* head)
{
    while(head != NULL)
    {
        cout<<head->val<<'\t';
        head = head->next;
    }

    cout<<endl;
}

void CommonUtils::deleteListNode(ListNode *head)
{
    while(head != NULL)
    {
        ListNode* temp = head->next;
        delete head;
        head = temp;
    }
}
