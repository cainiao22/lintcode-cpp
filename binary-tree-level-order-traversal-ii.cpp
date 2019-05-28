/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-15
* @brief         二叉树的层次遍历 II

* @description   给出一棵二叉树，返回其节点值从底向上的层次序遍历（按从叶节点所在层到根节点所在的层遍历，然后逐层从左往右遍历）
*
* @example
*
*                例1:

*                输入:
*                {1,2,3}
*                输出:
*                [[2,3],[1]]
*                解释:
*                    1
*                   / \
*                  2   3
*                它将被序列化为 {1,2,3}
*                层次遍历
*                例2:
*
*                输入:
*                {3,9,20,#,#,15,7}
*                输出:
*                [[15,7],[9,20],[3]]
*                解释:
*                    3
*                   / \
*                  9  20
*                    /  \
*                   15   7
*                它将被序列化为 {3,9,20,#,#,15,7}
*                层次遍历
* @solution
*/

#include "commonutils.h"

class BinaryTreeLevelOrderTraversaLII : protected CommonUtils
{
public:
    vector<vector<int>> levelOrderBottom(TreeNode * root)
    {
        vector<vector<int>> result;
        if(root == NULL)
        {
            return result;
        }
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty())
        {
            vector<int> item(q.size());
            int len = q.size();
            for(int i=0; i<len; i++)
            {
                TreeNode* top = q.front();
                q.pop();
                item[i] = top->val;
                if(top->left != NULL)
                {
                    q.push(top->left);
                }
                if(top->right != NULL)
                {
                    q.push(top->right);
                }
            }

            result.push_back(item);
        }

        for(int i=0, j=result.size() - 1; i < j; i++, j --)
        {
            vector<int> temp = result[i];
            result[i] = result[j];
            result[j] = temp;
        }


        return result;
    }

    vector<vector<int>> result;
    void helper(TreeNode* node, int level)
    {
        if(node == NULL)
        {
            return;
        }
        if(level >= result.size())
        {
            result.push_back({});
        }
        result[level].push_back(node->val);
        helper(node->left, level + 1);
        helper(node->right, level + 1);
    }

    vector<vector<int>> levelOrderBottom2(TreeNode * root)
    {
        this->helper(root, 0);
        for(int i=0, j=result.size() - 1; i < j; i++, j --)
        {
            vector<int> temp = result[i];
            result[i] = result[j];
            result[j] = temp;
        }


        return result;
    }

    int max_depth(TreeNode* node)
    {
        if(node == NULL)
        {
            return 0;
        }
        int left = max_depth(node->left);
        int right = max_depth(node->right);
        return 1 + (left > right ? left : right);
    }

    void dfs(TreeNode* node, vector<int> &item, int curLevel, int maxLevel)
    {
        if(node == NULL || curLevel > maxLevel)
        {
            return;
        }

        if(curLevel == maxLevel)
        {
            item.push_back(node->val);
        }
        dfs(node->left, item, curLevel + 1, maxLevel);
        dfs(node->right, item, curLevel + 1, maxLevel);
    }

    //直接反向遍历
    vector<vector<int>> levelOrderBottom3(TreeNode * root)
    {
        int maxDepth = max_depth(root) - 1;
        vector<vector<int>> result;
        while (maxDepth >= 0)
        {
            vector<int> item;
            dfs(root, item, 0, maxDepth);
            result.push_back(item);
            maxDepth --;
        }

        return result;
    }


    void run()
    {
        TreeNode root(1), left(2), right(3);
        root.left = &left;
        root.right = &right;
        this->levelOrderBottom2(&root);
        printVector2(result);
    }
};

