/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-11
* @brief         二叉树中的最大路径和

* @description 给出一棵二叉树，寻找一条路径使其路径和最大，路径可以在任一节点中开始和结束
*              （路径和为两个节点之间所在路径上的节点权值之和）
*
*
* @example
*
*            样例 1:
             输入:  给定一棵树（只有一个节点）:
             2
             输出：2

             样例 2:
             输入:  给定一棵树：

             1
            / \
           2   3

    输出: 6
* @solution 分治法 求左右两个子树到该节点的最大路径和
*/

#include<iostream>
#include<algorithm>

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

class BinaryTreeMaximum
{
public:
    int result = -1e9;
    int maxPathSum(TreeNode * root)
    {
        helper(root);
        return result == -1e9 ? 0 : result;
    }

    int helper(TreeNode * root)
    {
        int item = 0;
        // write your code here
        if(root != NULL)
        {
            item = root->val;
            int left = helper(root->left);
            int right = helper(root->right);
            //它的最大值只是只加上左边或者只加上右边
            item = max(item + right, item + left);
            result = max(result, item);
            //左右都加上
            result = max(result, left + right + root->val);
            //只包含root一个节点
            result = max(result, root->val);
        }

        return item;
    }

    void run()
    {
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(-2);
        root->right = new TreeNode(3);
        cout<<this->maxPathSum(root)<<endl;
    }
};

