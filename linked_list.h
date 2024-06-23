#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

// Define the TreeNode structure
typedef struct TreeNode
{
  int data1; // Frequency of the pixel intensity value
  int data2; // Pixel intensity value if leaf node, otherwise total number of nodes for internal nodes
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

// Define the ListNode structure
typedef struct ListNode
{
  TreeNode *treeNode;
  struct ListNode *next;
} ListNode;

// Function prototypes
TreeNode *createTreeNode(int data1, int data2 , TreeNode *left, TreeNode *right);
ListNode *createListNode(TreeNode *treeNode);
void insertListNode(ListNode **head, TreeNode *treeNode);
void deleteListNode(ListNode **head, TreeNode *treeNode);
int isEmpty(ListNode *head);
void traverseList(ListNode *head);
void sortLinkedList(ListNode **head);

#endif 