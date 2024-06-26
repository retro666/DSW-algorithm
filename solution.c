/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* balanceBST(struct TreeNode* root) {
    if (root->right) {
        if (!root->left && !root->right->right && !root->right->left) {
            return root;
        }
    } else if (root->left) {
        if (!root->left->right && !root->left->left) {
            return root;
        }
    } else {
        return root;
    }
  
    struct TreeNode* i = root;
    struct TreeNode* t;
    while (i->right) {
        t = i;
        i = i->right;
        struct TreeNode* m = i->left;
        i->left = t;
        t->right = m;
    }
    root = i;
    t = i;
    i = i->left;
    int cnt = 2;
    while (i->left || i->right) {
        if (i->right) {
            t->left = i->right;
            struct TreeNode* n = i;
            i = i->right;
            struct TreeNode* m = i->left;
            i->left = n;
            n->right = m;
        } else {
            t = i;
            i = i->left;
            ++cnt;
        }
    }
  
    int icnt = 0x7FFFFFFF >> __builtin_clz(cnt + 1);
    cnt -= icnt;
    if (cnt) {
        i = root->left;
        root->left = 0;
        i->right = root;
        root = i;
        if (--cnt) {
            do {
                t = i;
                i = i->left->left;
                t->left->left = 0;
                i->right = t->left;
                t->left = i;
            } while (--cnt);
        }
    }
    do {
        i = root->left;
        root->left = i->right;
        i->right = root;
        root = i;
        while (__builtin_popcount(--icnt) > 1) {
            t = i;
            struct TreeNode* m = t->left;
            i = m->left;
            t->left = i;
            m->left = i->right;
            i->right = m;
        }
    } while (__builtin_popcount(--icnt) > 1);
    return root;
}
