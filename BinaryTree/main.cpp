#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BinaryTree
{
public:
    TreeNode* mirrorTree(TreeNode* root)
    {
        if (!root)
        {
            return nullptr;
        }
        TreeNode *newNode = new TreeNode(root->val);
        newNode->left = mirrorTree(root->right);
        newNode->right = mirrorTree(root->left);
        return newNode;
    }

    // tools for isSymmetry
    bool isEqual(TreeNode* a, TreeNode* b)
    {
        if (!a && !b)
        {
            return true;
        }
        else
        {
            if ((a && !b) || (b && !a))
            {
                return false;
            }
        }
        if (a->val == b->val)
        {
            return this->isEqual(a->left, b->right) && this->isEqual(a->right, b->left);
        }
        else
        {
            return false;
        }
    }
    // binary tree [1,2,2,3,4,4,3] is symmetric
    // binary tree [1,2,2,null,3,null,3] is not:
    bool isSymmetric(TreeNode* root)
    {
        if (!root)
        {
            return true;
        }
        if (root->left && !root->right)
        {
            return false;
        }
        if (!root->left && root->right)
        {
            return false;
        }
        TreeNode* mirror = this->mirrorTree(root);
        return this->isEqual(mirror, root);
    }
    // ZigZag Level Order
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root)
        {
            return result;
        }
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* t = nullptr;
        int i = 0;
        while (!q.empty())
        {
            vector<int> l;
            ++i;
            int k = q.size();
            for (int j = 0; j != k; ++j)
            {
                t = q.front();
                if (t->left)
                {
                    q.push(t->left);
                }
                if (t->right)
                {
                    q.push(t->right);
                }
                q.pop();
                l.push_back(t->val);
            }
            if (0 == i % 2)
            {
                reverse(l.begin(), l.end());
            }
            result.push_back(l);
        }
        return result;
    }
    // Level Order from bottom to top
    vector<vector<int>> levelOrderBottom(TreeNode* root)
    {
//        stack<vector<int>> resultStack;
        vector<vector<int>> result;
        if (!root)
        {
            return result;
        }
        int level = 0;
        int k = 0;
        TreeNode* t;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            ++level;
            vector<int> r;
            k = q.size();
            for (int j = 0; j != k; ++j)
            {
                t = q.front();
                r.push_back(t->val);
                if (t->left)
                {
                    q.push(t->left);
                }
                if (t->right)
                {
                    q.push(t->right);
                }
                q.pop();
            }
//            resultStack.push(r);
            result.push_back(r);
        }
//        while (!resultStack.empty())
//        {
//            result.push_back(resultStack.top());
//            resultStack.pop();
//        }
        reverse(result.begin(), result.end());
        return result;
    }
    // Level Order
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        vector<vector<int>> result;
        if (!root)
        {
            return result;
        }
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* t = nullptr;
        int i = 0;
        while (!q.empty())
        {
            vector<int> l;
            ++i;
            int k = q.size();
            for (int j = 0; j != k; ++j)
            {
                t = q.front();
                if (t->left)
                {
                    q.push(t->left);
                }
                if (t->right)
                {
                    q.push(t->right);
                }
                q.pop();
                l.push_back(t->val);
            }
            result.push_back(l);
        }
        return result;
    }

    int minDepth(TreeNode* root)
    {
        return minDepthDFS(root);
    }

    int maxDepth(TreeNode* root)
    {
        if (!root)
        {
            return 0;
        }
        int ld = this->maxDepth(root->left) + 1;
        int rd = this->maxDepth(root->right) + 1;
        return max(ld, rd);
    }

protected:
    int minDepthBFS(TreeNode* root)
    {
        if (!root)
        {
            return 0;
        }
        queue<TreeNode*> q;
        q.push(root);
        int i = 0;
        TreeNode* p = nullptr;
        while (!q.empty())
        {
            ++i;
            // k保存当前层次的节点数
            int k = q.size();
            for (int j = 0; j != k; ++j)
            {
                p = q.front();
                if (p->left)
                {
                    q.push(p->left);
                }
                if (p->right)
                {
                    q.push(p->right);
                }
                q.pop();
                if (!p->left && !p->right)
                {
                    return i;
                }
            }
        }
        return -1;
    }
    int minDepthDFS(TreeNode* root) {
        if (!root)
        {
            return 0;
        }
        if(!root->left)
        {
            return minDepth(root->right)+1;
        }
        if(!root->right)
        {
            return minDepth(root->left)+1;
        }
        return min(minDepth(root->left), minDepth(root->right))+1;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

