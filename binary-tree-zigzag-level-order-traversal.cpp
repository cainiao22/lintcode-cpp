/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-11
* @brief         二叉树的锯齿形层次遍历
* @description
* @example
* @solution
*/

#include<iostream>
#include<vector>
#include<stack>


using namespace std;

class TreeNode
{
  public:
     int val;
     TreeNode *left, *right;
     TreeNode(int val) {
         this->val = val;
         this->left = this->right = NULL;
     }
};

class BinaryTreeZigzagLevelOrder
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode * root)
    {
        vector<vector<int>> result;
        stack<TreeNode*> s, s2;
        if(root != NULL)
        {
            s.push(root);
        }
        bool right = true;
        while(!s.empty())
        {
            int len = s.size();
            vector<int> item(len);
            for(int i=0; i<len; i++)
            {
                TreeNode* top = s.top();
                s.pop();
                item[i] = top->val;
                if(right)
                {
                    if(top->left != NULL)
                    {
                        s2.push(top->left);
                    }
                    if(top->right != NULL)
                    {
                        s2.push(top->right);
                    }
                }
                else
                {
                    if(top->right != NULL)
                    {
                        s2.push(top->right);
                    }
                    if(top->left != NULL)
                    {
                        s2.push(top->left);
                    }
                }
            }
            result.push_back(item);
            stack<TreeNode*> temp = s;
            s = s2;
            s2 = temp;
            right = !right;
        }

        return result;
    }

    void run()
    {
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        this->zigzagLevelOrder(root);
    }

};

