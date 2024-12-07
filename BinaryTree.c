#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 16
#define FALSE 0
#define TRUE 1

/*A tree Node declaration*/
struct TreeNode{
  int val;
  struct Node* left;
  struct Node* right;
};

typedef struct TreeNode *Tree;
/*Function signatures*/
Tree CreateTree(void);
Tree MakeEmptyTree(Tree);
Tree InsertElement(int, Tree);
void DisplayTree(Tree);
void iterativeFindMin(Tree t);
void iterativeFindMax(Tree t);
Tree recursivefindMin(Tree t);
Tree recursivefindMax(Tree t);
Tree find_element(int val, Tree t);
Tree DeleteTree(int val, Tree t);
int main()
{
    Tree myTree, pos;
    int exit, val, height;
    char command;


        myTree = CreateTree();
        exit = FALSE;

        while (!exit)
        {
               fflush(stdin);
               printf("\nMenu:\n i)nitialize\n n)ew element \n a)find max \n m)find min \n f)find \n d)delete \n e)xit\nEnter command: ");
               scanf("%c", &command);
               fflush(stdin);
               int value,delete;

                  switch(command)
                  {
                         case 'i':
                                myTree = MakeEmptyTree(myTree);
                                break;
                         case 'n':
                                printf("enter value: ");
                                scanf("%d", &val);
                                myTree = InsertElement(val, myTree);
                                DisplayTree(myTree);
                                break;
                         case 'e':
                                exit = TRUE;
                                break;
                         case 'a':
                                recursivefindMax(myTree);
                                break;
                         case 'm':
                                recursivefindMin(myTree);
                                break;
                         case 'f':
                                printf("Enter value to search: ");
                                scanf("%d",&value);
                                find_element(value,myTree);
                         case 'd':
                             printf("Enter value to delete: ");
                             scanf("%d",&delete);
                             myTree = DeleteTree(delete,myTree);
                             DisplayTree(myTree);
                             break;

                         default:
                                 printf("command not recognized\n");
                                 break;
                  }


        }

    printf("\n\n");
    system("PAUSE");
    return 0;
}

/*Function that mainly creates a tree which is initially NULL*/
Tree CreateTree(void)
{
    return NULL;
}

/*Function that takes a tree and makes it an empty tree by removing all the nodes from that tree*/
Tree MakeEmptyTree(Tree t)
{
     if (t != NULL)
     {
         MakeEmptyTree(t->left);
         MakeEmptyTree(t->right);
         free(t);
     }
     return NULL;
}

Tree InsertElement(int val, Tree t)
{
   if (t == NULL){
       t = (Tree) malloc(sizeof(struct TreeNode));
       if (t == NULL)
           printf("Out of space.\n");
       else{
           t ->val = val;
           t->left = t->right = NULL;
       }
   }
   else if (val < t->val)
       t ->left = InsertElement(val, t->left);
   else if (val > t->val)
       t ->right = InsertElement(val, t->right);
   return t;
}

/*This function takes a tree and displays its content on the screen*/
void DisplayTree(Tree t)
{
   if (t !=NULL){ // in order type
		DisplayTree(t->left);
		printf("%d\n", t->val);
		DisplayTree(t->right);
   }
}
void iterativeFindMin(Tree t){
    if (t == NULL)
        exit(1);
    while (t->left != NULL){
        t = t->left;
    }
     printf("Min is %d",t->val);
}
void iterativeFindMax(Tree t){
    if (t == NULL)
        exit(1);
    while (t->right != NULL){
        t = t->right;
    }
    printf("Max is %d",t->val);
}

Tree recursivefindMax(Tree t){
    if (t == NULL){
        return NULL;
    }
    if (t->right != NULL)
        return recursivefindMax(t->right);
    else {
        printf("max is %d", t->val);
        return t;
    }
}
Tree recursivefindMin(Tree t){
    if (t == NULL){
        return NULL;
    }
    if (t->left != NULL)
        return recursivefindMin(t->left);
    else {
        printf("min is %d",t->val);
        return t;
    }
}

Tree find_element(int val, Tree t) {
    if (t == NULL) {
        printf("Value %d not found in the tree.\n", val);
        return NULL;
    }
    if (val == t->val) {
        printf("Value %d found in the tree.\n", val);
        return t;
    }
    else if (val < t->val) {
        return find_element(val, t->left);
    }
    else {
        return find_element(val, t->right);
    }
}

Tree DeleteTree(int val, Tree t){
    Tree parent = NULL, current = t;

    while (current != NULL && current->val != val){
        parent = current;
        if (val < current ->val){
            current = current ->left;
        }
        else
            current = current ->right;
    }

    if (current == NULL){
        printf("Value not found\n");
        return t;
    }
        // Case 1: Node with no children (leaf node)
    if (current->left == NULL && current->right == NULL){
        if (current == t) { // If the node to delete is the root
            t = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
        // Case 2: Node with one child
    else if (current->left == NULL || current->right == NULL) {
        Tree child = (current->left != NULL) ? current->left : current->right;
        if (current == t) { // If the node to delete is the root
            t = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(current);
    }
        // Case 3: Node with two children
    else {
        // Find the in-order successor (smallest value in the right subtree)
        Tree successor = current->right;
        Tree successorParent = current;

        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        // Replace current node's value with successor's value
        current->val = successor->val;

        // Delete the successor node
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        free(successor);
    }

    return t;
}

