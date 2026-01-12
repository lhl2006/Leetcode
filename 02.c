/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val;
    struct ListNode *next;
};


#include<stdlib.h>

struct ListNode* createNode(int data,int *carry){
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = (data + *carry) % 10;
    if(data + *carry > 9){
        *carry = 1;
    }else{
        *carry = 0;
    }
    node->next = NULL;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0;
    struct ListNode* result = NULL;
    struct ListNode* last = NULL;
    struct ListNode* op1 = l1;
    struct ListNode* op2 = l2;

    while(op1 && op2){
        struct ListNode* temp = createNode(op1->val + op2->val,&carry);
        if(result==NULL){
            result = last = temp;
        }else{
            last->next = temp;
            last = temp;
        }
        op1 = op1->next;
        op2 = op2->next;
    }
    while(op1){
        struct ListNode* temp = createNode(op1->val,&carry);
        last->next = temp;
        last = temp;
        op1 = op1->next;
    }
    while(op2){
        struct ListNode* temp = createNode(op2->val,&carry);
        last->next = temp;
        last = temp;
        op2 = op2->next;
    }
    if(carry){
        last->next = createNode(0,&carry);
    }
    return result;
}