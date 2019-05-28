/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-07
* @brief         带环链表
*
* @description   给定一个链表，判断它是否有环
*
* @example       样例 1:
                 输入: 21->10->4->5,  then tail connects to node index 1(value 10).
                 输出: true

                 样例 2:
                 输入: 21->10->4->5->null
                 输出: false
* @solution
*/

#include "commonutils.h"

class LinkedListCycle : public CommonUtils
{
public:
    bool hasCycle(ListNode * head)
    {
        if(head == NULL)
        {
            return false;
        }
        ListNode *fast = head->next, *slow = head;

        while(fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
            if(slow == fast)
            {
                return true;
            }

            if(fast != NULL)
            {
                fast = fast->next;
            }
            if(slow == fast)
            {
                return true;
            }
        }

        return false;
    }

    bool hasCycle2(ListNode * head)
    {
        if(head == NULL || head->next == NULL)
        {
            return false;
        }

        ListNode* fast = head->next;
        ListNode* slow = head;

        while(fast != slow)
        {
            if(fast == NULL || slow == NULL)
            {
                return false;
            }
            slow = slow->next;
            fast = fast->next;
            if(fast != NULL)
            {
                fast = fast->next;
            }
        }

        return false;
    }

};
