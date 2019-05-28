/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-29
* @brief         链表排序
*
* @description   在 O(n log n) 时间复杂度和常数级的空间复杂度下给链表排序
* @example       样例 1:
    输入:  1->3->2->null
    输出:  1->2->3->null

样例 2:
    输入: 1->7->2->6->null
    输出: 1->2->6->7->null
* @solution
*/


#include "commonutils.h"

class SortList : protected CommonUtils
{
public:
    ListNode * sortList(ListNode * head)
    {
        if(head == NULL)
        {
            return head;
        }

        ListNode* result = mergeSort(head, NULL);
        return result;
    }

    void quickSort(ListNode* left, ListNode* right)
    {
        if(left == right)
        {
            return;
        }
        ListNode* l = left, *r = left;
        int key = l->val;
        while(r != right)
        {
            if(r->val < key)
            {
                l = l->next;
                int temp = l->val;
                l->val = r->val;
                r->val = temp;

            }
            r = r->next;

        }

        int temp =l->val;
        l->val = left->val;
        left->val = temp;

        quickSort(left, l);
        quickSort(l->next, right);
    }



    void quickSort2(ListNode* left, ListNode* right)
    {
        if(left == right)
        {
            return;
        }
        ListNode* l = left, *r = left->next;
        int key = l->val;



    }

    ListNode* mergeSort(ListNode* left, ListNode* right)
    {
        if(left->next == right)
        {
            left->next = NULL;
            return left;
        }

        ListNode* slow = left, *fast = left->next;
        while(fast != right)
        {
            slow = slow->next;
            fast = fast->next == right ? right : fast->next->next;
        }

        ListNode* l = mergeSort(left, slow);
        ListNode* r = mergeSort(slow, right);
        ListNode* head = new ListNode(0);
        ListNode* cur = head;
        while(l != NULL && r != NULL)
        {
            if(l->val <= r->val)
            {
                cur->next = l;
                l = l->next;
            }
            else
            {
                cur->next = r;
                r = r->next;
            }

            cur = cur->next;
        }

        if(l != NULL)
        {
            cur->next = l;
        }

        if(r != NULL)
        {
            cur->next = r;
        }

        cur = head->next;

        delete head;
        return cur;

    }


    void run()
    {
        vector<int> nums({0,3,1,-1});
        ListNode* head = new ListNode(nums[0]);
        ListNode* cur = head;
        for(int i=1; i<nums.size(); i++)
        {
            cur->next = new ListNode(nums[i]);
            cur = cur->next;
        }
        printListNode(head);
        this->sortList(head);
        printListNode(head);
    }
};


