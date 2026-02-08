//
// Created by lhl on 2026/2/8.
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
#include <stdbool.h>
#include <math.h>

int depth(struct TreeNode* root) {
    if (root == NULL) return 0;
    int depth_left = depth(root->left);
    int depth_right = depth(root->right);
    return 1 + (depth_left > depth_right ? depth_left : depth_right);
}

bool check(struct TreeNode* root) {
    if (root == NULL) return true;
    if (abs(depth(root->left) - depth(root->right)) > 1) return false;
    return check(root->left) && check(root->right);
}

bool isBalanced(struct TreeNode* root) {
    return check(root);
}

// Gemini Version
/*// 辅助函数：返回树的高度。
// 如果发现子树不平衡，则直接返回 -1 (作为错误代码)
int getHeight(struct TreeNode* root) {
    if (root == NULL) return 0;

    // 递归计算左子树高度
    int leftH = getHeight(root->left);
    if (leftH == -1) return -1; // 剪枝：左边已经不平衡，直接返回

    // 递归计算右子树高度
    int rightH = getHeight(root->right);
    if (rightH == -1) return -1; // 剪枝：右边已经不平衡，直接返回

    // 当前节点判断：如果左右高度差大于1，说明不平衡
    if (abs(leftH - rightH) > 1) return -1;

    // 如果平衡，返回当前高度 (左右较大者 + 1)
    return 1 + (leftH > rightH ? leftH : rightH);
}

bool isBalanced(struct TreeNode* root) {
    // 如果返回 -1 说明不平衡，否则平衡
    return getHeight(root) != -1;
}*/
