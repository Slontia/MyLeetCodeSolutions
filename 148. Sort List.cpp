// 这个解法采用二叉树排序，很慢，学习一下归并排序和链表快排

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class SortTreeNode {
public:
    SortTreeNode(ListNode* const& p) : listp_(p), left_(nullptr), right_(nullptr) {}
    
    ~SortTreeNode() {
        if (left_) delete(left_);
        if (right_) delete(right_);
    }
    
    void Put(ListNode* const& p) {
        save_to_branch(p, (p->val < listp_->val) ? left_ : right_);
    }
    
    /* Returns head of linklist. */
    ListNode* Link(ListNode* const& tail) {
        /* Link right. */
        listp_->next = link_to_branch(right_, tail);
        
        /* Link Left */
        return link_to_branch(left_, listp_);
    }
    
private:
    ListNode* listp_;
    SortTreeNode* left_;
    SortTreeNode* right_;

    ListNode* link_to_branch(SortTreeNode*& branch, ListNode* const& tail) {
        return branch ? branch->Link(tail) : tail;
    }
    
    void save_to_branch(ListNode* const& p, SortTreeNode*& branch) {
        if (!branch) {
            branch = new SortTreeNode(p);
        } else {
            branch->Put(p);
        }
    }
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head) return nullptr;
        auto root = SortTreeNode(head);
        for (auto p = head->next; p; p = p->next) root.Put(p);
        return root.Link(nullptr);
    }
};
