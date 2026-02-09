//
// Created by lhl on 2026/2/9.
//
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode
{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

#include <stdlib.h>
#define MAX 10005


void scan(struct TreeNode* root, int* treeSize, struct TreeNode** nodes) {
    if (root == NULL) return;
    scan(root->left, treeSize, nodes);
    nodes[*treeSize] = root;
    *treeSize += 1;
    scan(root->right, treeSize, nodes);
}

void build(struct TreeNode* root, struct TreeNode** nodes, int lleft, int lSize, int rleft, int rSize) {
    root->left = NULL, root->right = NULL;
    if (lSize > 0){
        root->left = nodes[lleft + lSize / 2];
        build(root->left, nodes, lleft, lSize / 2, lleft + lSize / 2 + 1, lSize - lSize / 2 - 1);
    }
    if (rSize > 0){
        root->right = nodes[rleft + rSize / 2];
        build(root->right, nodes, rleft, rSize / 2, rleft + rSize / 2 + 1, rSize - rSize / 2 - 1);
    }
}


struct TreeNode* balanceBST(struct TreeNode* root) {
    int treeSize = 0;
    struct TreeNode** nodes = malloc(sizeof(struct TreeNode*) * MAX);
    scan(root, &treeSize, nodes);
    build(nodes[treeSize / 2], nodes, 0, treeSize / 2, treeSize / 2 + 1,
          treeSize - treeSize / 2 - 1);
    return nodes[treeSize / 2];
}

// Gemini Version
// 这里的 build 函数返回当前构建好的子树根节点，逻辑非常清晰
/*struct TreeNode* build(struct TreeNode** nodes, int left, int right) {
    if (left > right) return NULL;

    // 1. 取中间点
    int mid = left + (right - left) / 2;
    struct TreeNode* root = nodes[mid];

    // 2. 递归构建左右子树
    // 左子树范围：[left, mid - 1]
    // 右子树范围：[mid + 1, right]
    root->left = build(nodes, left, mid - 1);
    root->right = build(nodes, mid + 1, right);

    return root;
}*/
