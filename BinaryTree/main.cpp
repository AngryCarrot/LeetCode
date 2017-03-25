#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
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
    /** 106. Construct Binary Tree from Inorder and Postorder Traversal
     * @brief buildTreeIP
     * @param preorder
     * @param inorder
     * @return
     */
    TreeNode* buildTreeIP(vector<int>& inorder, vector<int>& postorder)
    {
        const int length = inorder.size();
        TreeNode* root = this->buildTreeIP(inorder, postorder, 0, inorder.size(), 0, postorder.size());
        return root;
    }
    TreeNode* buildTreeIP(vector<int> &inorder, vector<int> &postorder, int ii, int ij, int pi, int pj)
    {
        TreeNode* root = nullptr;
        if (ii == ij || pi == pj)
        {
            return root;
        }
        root = new TreeNode(postorder[pj - 1]);
        int idx = 0;
        for (int i = 0; i < postorder.size(); ++i)
        {
            if (inorder[i] == root->val)
            {
                idx = i;
                break;
            }
        }
        int lenl = idx - ii;
        int lenr = ij - idx - 1;

        root->left = this->buildTreeIP(inorder, postorder, ii, ii+lenl, pi, pi + lenl);

        root->right = this->buildTreeIP(inorder, postorder, idx + 1, idx + 1 + lenr, pj - 1 - lenr, pj - 1);

        return root;
    }

    /** 105. Construct Binary Tree from Preorder and Inorder Traversal
     * @brief buildTreePI
     * @param preorder
     * @param inorder
     * @return
     */
    TreeNode* buildTreePI(vector<int>& preorder, vector<int>& inorder)
    {
        const int length = preorder.size();
        TreeNode* root = buildTreePI(preorder, inorder, 0, length , 0, length);
        return root;
    }
    TreeNode* buildTreePI(vector<int> &preorder, vector<int> &inorder, int pi, int pj, int ii, int ij)
    {
        // tree        8 4 5 3 7 3
        // preorder    8 [4 3 3 7] [5]
        // inorder     [3 3 4 7] 8 [5]
        // 每次从 preorder 头部取一个值 mid，作为树的根节点
        // 检查 mid 在 inorder 中 的位置，则 mid 前面部分将作为 树的左子树，右部分作为树的右子树

        if(pi >= pj || ii >= pj)
        {
            return nullptr;
        }

        int mid = preorder[pi];
        auto f = find(inorder.begin() + ii,inorder.begin() + ij,mid);

        int dis = f - inorder.begin() - ii;

        TreeNode* root = new TreeNode(mid);
        root -> left = buildTreePI(preorder, inorder, pi + 1, pi + 1 + dis, ii, ii + dis);
        root -> right = buildTreePI(preorder, inorder, pi + 1 + dis, pj, ii + dis + 1, ij);
        return root;
    }

    /** 501. Find Mode in Binary Search Tree
     * @brief findMode
     * @details Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.
     * @param root
     * @return
     */
    vector<int> findMode(TreeNode* root)
    {
    }
    /** 337. House Robber III
     * @brief rob
     * @param root
     * @return
     * @example 思路不对忽略了[2,1,3,null,4]情况下，可以同时去第二层和第三层，只要这两层被用到的数字不是直接相连就行
     *      2
     *  1       3
     *    4
     * 3+4=7
     */
    int rob3(TreeNode* root)
    {
        // level order to preserve each sum of level
        // dynamic program like rob1 on each level's sum
        if (!root)
        {
            return 0;
        }
        if (!root->left && !root->right)
        {
            return root->val;
        }
        vector<int> nums;
        queue<TreeNode *> q;
        q.push(root);
        while (q.empty())
        {
            int sum = 0;
            int size = q.size();
            for (int i = 0; i != size; ++i)
            {
                TreeNode *t = q.front();
                q.pop();
                sum += t->val;
                if (t->left)
                {
                    q.push(t->left);
                }
                if (t->right)
                {
                    q.push(t->right);
                }
            }
            nums.push_back(sum);
        }
        const int length = nums.size();
        int *p = new int[length];
        p[0] = nums[0];
        p[1] = max(nums[1], p[0]);
        for (int i = 0; i != length; ++i)
        {
            p[i] = max(p[i - 2] + nums[i], p[i - 1]);
        }
        int answer = p[length - 1];
        delete []p;
        return answer;
    }
/*
Step I -- Think naively

At first glance, the problem exhibits the feature of "optimal substructure": if we want to rob maximum amount of money from current binary tree (rooted at root), we surely hope that we can do the same to its left and right subtrees.

So going along this line, let's define the function rob(root) which will return the maximum amount of money that we can rob for the binary tree rooted at root; the key now is to construct the solution to the original problem from solutions to its subproblems, i.e., how to get rob(root) from rob(root.left), rob(root.right), ... etc.

Apparently the analyses above suggest a recursive solution. And for recursion, it's always worthwhile figuring out the following two properties:

    Termination condition: when do we know the answer to rob(root) without any calculation? Of course when the tree is empty -- we've got nothing to rob so the amount of money is zero.

    Recurrence relation: i.e., how to get rob(root) from rob(root.left), rob(root.right), ... etc. From the point of view of the tree root, there are only two scenarios at the end: root is robbed or is not. If it is, due to the constraint that "we cannot rob any two directly-linked houses", the next level of subtrees that are available would be the four "grandchild-subtrees" (root.left.left, root.left.right, root.right.left, root.right.right). However if root is not robbed, the next level of available subtrees would just be the two "child-subtrees" (root.left, root.right). We only need to choose the scenario which yields the larger amount of money.


Step II -- Think one step further

In step I, we only considered the aspect of "optimal substructure", but think little about the possibilities of overlapping of the subproblems. For example, to obtain rob(root), we need rob(root.left), rob(root.right), rob(root.left.left), rob(root.left.right), rob(root.right.left), rob(root.right.right); but to get rob(root.left), we also need rob(root.left.left), rob(root.left.right), similarly for rob(root.right). The naive solution above computed these subproblems repeatedly, which resulted in bad time performance. Now if you recall the two conditions for dynamic programming: "optimal substructure" + "overlapping of subproblems", we actually have a DP problem. A naive way to implement DP here is to use a hash map to record the results for visited subtrees.


Step III -- Think one step back

In step I, we defined our problem as rob(root), which will yield the maximum amount of money that can be robbed of the binary tree rooted at root. This leads to the DP problem summarized in step II.

Now let's take one step back and ask why we have overlapping subproblems. If you trace all the way back to the beginning, you'll find the answer lies in the way how we have defined rob(root). As I mentioned, for each tree root, there are two scenarios: it is robbed or is not. rob(root) does not distinguish between these two cases, so "information is lost as the recursion goes deeper and deeper", which results in repeated subproblems.

If we were able to maintain the information about the two scenarios for each tree root, let's see how it plays out. Redefine rob(root) as a new function which will return an array of two elements, the first element of which denotes the maximum amount of money that can be robbed if root is not robbed, while the second element signifies the maximum amount of money robbed if it is robbed.

Let's relate rob(root) to rob(root.left) and rob(root.right)..., etc. For the 1st element of rob(root), we only need to sum up the larger elements of rob(root.left) and rob(root.right), respectively, since root is not robbed and we are free to rob its left and right subtrees. For the 2nd element of rob(root), however, we only need to add up the 1st elements of rob(root.left) and rob(root.right), respectively, plus the value robbed from root itself, since in this case it's guaranteed that we cannot rob the nodes of root.left and root.right.

As you can see, by keeping track of the information of both scenarios, we decoupled the subproblems and the solution essentially boiled down to a greedy one.
*/
    // TLE
    int rob3NB(TreeNode *root)
    {
        map<TreeNode*, int> m;
        return rob3NBSub(root, m);
    }
    int rob3NBSub(TreeNode *root, map<TreeNode*, int> m)
    {
        if (!root)
        {
            return 0;
        }
        auto search = m.find(root);
        if (search != m.end())
        {
            return search->second;
        }
        int value = 0;
        if (root->left)
        {
            value += this->rob3NBSub(root->left->left, m) + this->rob3NBSub(root->left->right, m);
        }
        if (root->right)
        {
            value += this->rob3NBSub(root->right->left, m) + this->rob3NBSub(root->right->right, m);
        }
        value = max(value + root->val, this->rob3NBSub(root->left, m) + this->rob3NBSub(root->right, m));
        m[root] = value;
        return value;
    }
    int rob3NBNB(TreeNode *root)
    {
        vector<int> result = this->rob3NBNBSub(root);
        return max(result[0], result[1]);
    }
    vector<int> rob3NBNBSub(TreeNode *root)
    {
        if (!root)
        {
            return vector<int>(2, 0);
        }
        vector<int> left = this->rob3NBNBSub(root->left);
        vector<int> right = this->rob3NBNBSub(root->right);

        vector<int> result(2, 0);
        result[0] = max(left[0], left[1]) + max(right[0], right[1]);
        result[1] = root->val + left[0] + right[0];
        return result;
    }

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

void f(int a, int *b, int* &c)
{
    c = b;
//    cout << *c << endl;
//    cout << *b << endl;
//    b = c;
//    cout << *b << endl;
}

int main()
{
    cout << "Hello World!" << endl;
    int a = 10;
    int b = 11;
    int c = 12;
    int *pa = &a;
    int *pb = &b;
    int *pc = &c;
    cout << "before: " << *pc << endl;
    f(a, pb, pc);
    cout << "after: " << *pc << endl;
    return 0;
}

