#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include <string.h>

// Ask the user for the number of rows and columns
int askForNumberOfRows()
{
  int rows;
  printf("Enter the number of rows: ");
  scanf("%d", &rows);
  return rows;
}

int askForNumberOfColumns()
{
  int columns;
  printf("Enter the number of columns: ");
  scanf("%d", &columns);
  return columns;
}

// Read the 2D array pixel intensity values from the user
int **readPixelIntensityValues(int rows, int columns)
{
  int **pixel_intensity_values = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
  {
    pixel_intensity_values[i] = (int *)malloc(columns * sizeof(int));
  }

  printf("%s", "Enter the pixel intensity values : \n");

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf("image[%d][%d] = ", i, j);
      scanf("%d", &pixel_intensity_values[i][j]);
    }
  }

  return pixel_intensity_values;
}

// free the 2D array pixel intensity values
void freePixelIntensityValues(int **pixel_intensity_values, int rows)
{
  for (int i = 0; i < rows; i++)
  {
    free(pixel_intensity_values[i]);
  }
  free(pixel_intensity_values);
}

// print the 2D array pixel intensity values
void printPixelIntensityValues(int **pixel_intensity_values, int rows, int columns)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf("%d ", pixel_intensity_values[i][j]);
    }
    printf("\n");
  }
}

int doesExist(int *unique_pixel_intensity_values_array, int pixel_intensity_value, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (unique_pixel_intensity_values_array[i] == pixel_intensity_value)
    {
      return 1;
    }
  }
  return 0;
}

// calculate frequency of each pixel intensity value
int *allExistingPixelIntensityValues(int **pixel_intensity_values, int rows, int columns, int &unique_values_count)
{
  int *unique_pixel_intensity_values_array = (int *)malloc(rows * columns * sizeof(int));

  int i, j;
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < columns; j++)
    {
      if (doesExist(unique_pixel_intensity_values_array, pixel_intensity_values[i][j], rows * columns) == 0)
      {
        unique_pixel_intensity_values_array[unique_values_count] = pixel_intensity_values[i][j];
        unique_values_count++;
      }
    }
  }

  unique_pixel_intensity_values_array = (int *)realloc(unique_pixel_intensity_values_array, unique_values_count * sizeof(int));
  return unique_pixel_intensity_values_array;
}

// calculate the frequency of each pixel intensity value
int *calculateFrequencyOfPixelIntensityValues(int **pixel_intensity_values, int *unique_pixel_intensity_values_array, int rows, int columns, int unique_values_count)
{
  int *frequency_of_pixel_intensity_values = (int *)malloc(unique_values_count * sizeof(int));

  int i, j, k;
  for (i = 0; i < unique_values_count; i++)
  {
    frequency_of_pixel_intensity_values[i] = 0;
  }

  for (i = 0; i < unique_values_count; i++)
  {
    for (j = 0; j < rows; j++)
    {
      for (k = 0; k < columns; k++)
      {
        if (unique_pixel_intensity_values_array[i] == pixel_intensity_values[j][k])
        {
          frequency_of_pixel_intensity_values[i]++;
        }
      }
    }
  }

  return frequency_of_pixel_intensity_values;
}

void printTable1(int *unique_pixel_intensity_values_array, int *frequency_of_pixel_intensity_values, int unique_values_count)
{
  printf("Pixel Intensity Value | Frequency\n");
  printf("-------------------------------\n");

  for (int i = 0; i < unique_values_count; i++)
  {
    printf("%d | %d\n", unique_pixel_intensity_values_array[i], frequency_of_pixel_intensity_values[i]);
  }
}

TreeNode *createTreeNode(int data1, int data2, TreeNode *left, TreeNode *right)
{
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  node->data1 = data1;
  node->data2 = data2;
  node->left = left;
  node->right = right;
  return node;
}

ListNode *createListNode(TreeNode *treeNode)
{
  ListNode *newListNode = (ListNode *)malloc(sizeof(ListNode));
  if (!newListNode)
  {
    printf("Memory allocation error\n");
    return NULL;
  }
  newListNode->treeNode = treeNode;
  newListNode->next = NULL;
  return newListNode;
}

// Function to insert a tree node into the linked list
void insertListNode(ListNode **head, TreeNode *treeNode)
{
  ListNode *newListNode = createListNode(treeNode);
  newListNode->next = *head;
  *head = newListNode;
}

// Function to delete a tree node from the linked list
void deleteListNode(ListNode **head, TreeNode *treeNode)
{
  ListNode *temp = *head, *prev = NULL;

  // If head node itself holds the tree node to be deleted
  if (temp != NULL && temp->treeNode == treeNode)
  {
    *head = temp->next; // Change head
    free(temp);         // Free old head
    return;
  }

  // Search for the tree node to be deleted, keep track of the previous node
  while (temp != NULL && temp->treeNode != treeNode)
  {
    prev = temp;
    temp = temp->next;
  }

  // If tree node was not present in linked list
  if (temp == NULL)
    return;

  // Unlink the node from linked list
  prev->next = temp->next;

  free(temp); // Free memory
}

// Function to check if the linked list is empty
int isEmpty(ListNode *head)
{
  return head == NULL;
}

// Function to traverse the linked list
void traverseList(ListNode *head)
{
  ListNode *current = head;
  while (current != NULL)
  {
    printf("TreeNode with data1: %d, data2: %d\n", current->treeNode->data1, current->treeNode->data2);
    current = current->next;
  }
}
// Function to sort the linked list based on data1 in ascending order
void sortLinkedList(ListNode **head)
{
  if (*head == NULL)
    return; // If the list is empty, return

  ListNode *current, *nextNode;
  TreeNode *tempTreeNode;
  int swapped;

  do
  {
    swapped = 0;
    current = *head;

    while (current->next != NULL)
    {
      nextNode = current->next;

      if (current->treeNode->data1 > nextNode->treeNode->data1)
      {
        // Swap the tree nodes
        tempTreeNode = current->treeNode;
        current->treeNode = nextNode->treeNode;
        nextNode->treeNode = tempTreeNode;

        swapped = 1;
      }
      current = current->next;
    }
  } while (swapped);
}

// Function to  get the number of nodes connected to the root node
int getNumberOfNodes(TreeNode *root)
{
  if (root == NULL)
  {
    return 0;
  }
  return 1 + getNumberOfNodes(root->left) + getNumberOfNodes(root->right);
}

TreeNode *createHuffmanTree(ListNode **current_nodes)
{
  // create new linked list called addedToTree
  ListNode *addedToTree = NULL;
  TreeNode *root = NULL;
  while (isEmpty(*current_nodes) == 0)
  {
    // sort the linked list current_nodes in ascending order
    sortLinkedList(current_nodes);

    // take the first two nodes from the linked list current_nodes
    ListNode *first_node = *current_nodes;
    ListNode *second_node = (*current_nodes)->next;

    if (second_node == NULL)
    {
      root = first_node->treeNode;
      return root;
    }
    // create a new node with data1 = sum of the data1 of the two nodes, data2 = sum of the data2 of the two nodes
    TreeNode *new_node = createTreeNode(first_node->treeNode->data1 + second_node->treeNode->data1, 0, first_node->treeNode, second_node->treeNode);
    new_node->data2 = getNumberOfNodes(new_node) - 1;

    // insert the new node into the linked list current_nodes
    insertListNode(current_nodes, new_node);

    // delete the two nodes from the linked list current_nodes and insert them to addedToTree
    insertListNode(&addedToTree, first_node->treeNode);
    insertListNode(&addedToTree, second_node->treeNode);
    deleteListNode(current_nodes, first_node->treeNode);
    deleteListNode(current_nodes, second_node->treeNode);
  }
  return root;
}

// Helper function to print the tree structure with indentation
void printHuffmanTreeHelper(TreeNode *node, int depth)
{
  if (node == NULL)
  {
    return;
  }

  // Print indentation based on the depth of the node
  for (int i = 0; i < depth; i++)
  {
    printf("  ");
  }

  // Print the current node's data
  printf("data1: %d, data2: %d\n", node->data1, node->data2);

  // Recursively print the left and right subtrees with increased depth
  printHuffmanTreeHelper(node->left, depth + 1);
  printHuffmanTreeHelper(node->right, depth + 1);
}

// Function to print the Huffman tree
void printHuffmanTree(TreeNode *huffmanTree)
{
  printHuffmanTreeHelper(huffmanTree, 0);
}

char *getCodeWord(TreeNode *node, TreeNode *leaf, char *code, int depth)
{
  if (node == NULL)
  {
    return NULL;
  }

  // If the current node is the leaf node we are looking for
  if (node == leaf)
  {
    code[depth] = '\0'; // Null-terminate the string
    return code;
  }

  // Traverse the left subtree
  code[depth] = '0';
  char *leftCode = getCodeWord(node->left, leaf, code, depth + 1);
  if (leftCode != NULL)
  {
    return leftCode;
  }

  // Traverse the right subtree
  code[depth] = '1';
  char *rightCode = getCodeWord(node->right, leaf, code, depth + 1);
  if (rightCode != NULL)
  {
    return rightCode;
  }

  // If the leaf node is not found in either subtree, return NULL
  return NULL;
}

// Function to calculate the sizes for each leaf node
int *calculateSizes(int *frequency_of_pixel_intensity_values, char **code_word, int unique_values_count)
{
  int *leaf_node_sizes = (int *)malloc(unique_values_count * sizeof(int));

  for (int i = 0; i < unique_values_count; i++)
  {
    int code_length = strlen(code_word[i]);
    leaf_node_sizes[i] = frequency_of_pixel_intensity_values[i] * code_length;
  }

  return leaf_node_sizes;
}

// Function to print the table with unique pixel intensity values, their frequencies, code words, and sizes
void printTable2(int *unique_pixel_intensity_values_array, int *frequency_of_pixel_intensity_values, char **code_word, int *sizes, int unique_values_count)
{
  printf("Pixel Intensity Value | Frequency | Code Word | Size\n");
  printf("-----------------------------------------------------\n");

  for (int i = 0; i < unique_values_count; i++)
  {
    printf("%20d | %9d | %9s | %4d\n", unique_pixel_intensity_values_array[i],
           frequency_of_pixel_intensity_values[i],
           code_word[i],
           sizes[i]);
  }
}

char *convertToBinarySequence(int **pixel_intensity_values, int rows, int columns, int *unique_pixel_intensity_values_array, char **code_word, int unique_values_count, int total_size)
{
  // Allocate memory for the binary sequence
  char *binary_sequence = (char *)malloc((total_size + 1) * sizeof(char));
  if (binary_sequence == NULL)
  {
    printf("Memory allocation error\n");
    return NULL;
  }
  binary_sequence[0] = '\0'; // Initialize the binary sequence as an empty string

  // Convert pixel intensity values to binary sequence
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      for (int k = 0; k < unique_values_count; k++)
      {
        if (pixel_intensity_values[i][j] == unique_pixel_intensity_values_array[k])
        {
          strcat(binary_sequence, code_word[k]);
          break;
        }
      }
    }
  }

  return binary_sequence;
}
  int main()
  {
    int number_of_rows = askForNumberOfRows();
    int number_of_columns = askForNumberOfColumns();
    int original_size = number_of_rows * number_of_columns * 8;
    int **pixel_intensity_values = readPixelIntensityValues(number_of_rows, number_of_columns);
    printPixelIntensityValues(pixel_intensity_values, number_of_rows, number_of_columns);

    // step 1 : calculate the frequency of each pixel intensity value
    int unique_values_count = 0;
    int *unique_pixel_intensity_values_array = allExistingPixelIntensityValues(pixel_intensity_values, number_of_rows, number_of_columns, unique_values_count);
    int *frequency_of_pixel_intensity_values = calculateFrequencyOfPixelIntensityValues(pixel_intensity_values, unique_pixel_intensity_values_array, number_of_rows, number_of_columns, unique_values_count);
    // print
    printf("Number of Unique Pixel Intensity Values: %d\n", unique_values_count);
    printf("Unique Pixel Intensity Values: ");
    for (int i = 0; i < unique_values_count; i++)
    {
      printf("%d ", unique_pixel_intensity_values_array[i]);
    }
    printf("\n");
    printTable1(unique_pixel_intensity_values_array, frequency_of_pixel_intensity_values, unique_values_count);

    // step 2 : create a leaf node for each unique pixel intensity value. data1 represents the frequency value. data2 represents the pixel intensity value for leaf nodes
    ListNode *head = NULL;
    TreeNode **leaf_nodes = (TreeNode **)malloc(unique_values_count * sizeof(TreeNode *));

    for (int i = 0; i < unique_values_count; i++)
    {
      TreeNode *leaf_node = createTreeNode(frequency_of_pixel_intensity_values[i], unique_pixel_intensity_values_array[i], NULL, NULL);
      leaf_nodes[i] = leaf_node; // Store the reference to the leaf node.
      insertListNode(&head, leaf_node);
    }

    // print leaf nodes
    printf("Leaf Nodes: \n");
    traverseList(head);
    printf("--------------------------------------------\n");

    // step 3 : Huffman tree construction
    TreeNode *huffmanTree = createHuffmanTree(&head);
    printHuffmanTree(huffmanTree);
    printf("--------------------------------------------\n");

    // step 4 : Huffman code generation
    char **code_word = (char **)malloc(unique_values_count * sizeof(char *));
    for (int i = 0; i < unique_values_count; i++)
    {
      code_word[i] = (char *)malloc(number_of_rows * number_of_columns * sizeof(char));
      code_word[i] = getCodeWord(huffmanTree, leaf_nodes[i], code_word[i], 0);
    }

    // print the Huffman codes
    printf("Huffman Codes: \n");
    for (int i = 0; i < unique_values_count; i++)
    {
      printf("Pixel Intensity Value: %d, Huffman Code: %s\n", unique_pixel_intensity_values_array[i], code_word[i]);
    }
    printf("--------------------------------------------\n");

    // step 5 : Calculate the total size of the binary sequence
    // Calculate and print the sizes for each leaf node
    int *leaf_node_sizes = calculateSizes(frequency_of_pixel_intensity_values, code_word, unique_values_count);
    printf("Leaf Node Sizes: \n");
    int total_size = 0;
    for (int i = 0; i < unique_values_count; i++)
    {
      printf("Pixel Intensity Value: %d, Size: %d\n", unique_pixel_intensity_values_array[i], leaf_node_sizes[i]);
      total_size += leaf_node_sizes[i];
    }

    printf("--------------------------------------------\n");

    
    printTable2(unique_pixel_intensity_values_array, frequency_of_pixel_intensity_values, code_word, leaf_node_sizes, unique_values_count);
    // step 6 : Convert the pixel intensity values to binary sequence
    char *binary_sequence = convertToBinarySequence(pixel_intensity_values, number_of_rows, number_of_columns, unique_pixel_intensity_values_array, code_word, unique_values_count, total_size);
    printf("Binary Sequence: %s\n", binary_sequence);

    // step 7 : Calculate the compression threshold
    int compressed_size = total_size;
    float compression_ratio = (float)compressed_size/original_size;
    printf("Original Size: %d bits\n", original_size);
    printf("Compressed Size: %d bits\n", compressed_size);
    printf("Compression Threshold: %.2f \n", compression_ratio);

    // free the memory
    freePixelIntensityValues(pixel_intensity_values, number_of_rows);
    free(unique_pixel_intensity_values_array);
    free(frequency_of_pixel_intensity_values);
    for (int i = 0; i < unique_values_count; i++)
    {
      free(code_word[i]);
    }
    free(code_word);

    return 0;
  }
