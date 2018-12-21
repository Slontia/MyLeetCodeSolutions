// 这里没有必要用unordered_map的，dfs就好，一个节点只需要考虑它的两个子节点

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    std::unordered_map<TreeNode*, std::pair<int, int>> summap; // <sum, subsum>
    
    int get_sum(TreeNode* p) {
        int sum = p->val;
        if (p->left) sum += summap[p->left].second;
        if (p->right) sum += summap[p->right].second;
        return sum;
    }
    
    int get_subsum(TreeNode* p) {
        int subsum = 0;
        if (p->left) subsum += summap[p->left].first;
        if (p->right) subsum += summap[p->right].first;
        return subsum;
    }
    
    void record_sum(TreeNode* p) {
        if (p->left) rob(p->left);
        if (p->right) rob(p->right);
        int subsum = get_subsum(p);
        int sum = std::max(subsum, get_sum(p));
        summap.emplace(p, std::pair<int, int>(sum, subsum));
    }
    
    int rob(TreeNode* root) {
        if (!root) return 0;
        record_sum(root);
        return summap[root].first;
        
    }
};
