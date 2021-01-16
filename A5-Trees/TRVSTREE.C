// TREE TRAVERSAL [161013]
// Example code to show preorder, inorder and postorder tree traversal.

#include <stdio.h>

// Structure definition for a tree node.
struct treenode {
        int value;
        struct treenode  *left;
        struct treenode  *right;
        };

// Typedef to make typing a little easier
typedef struct treenode TREENODE;

// Declarations of tree nodes.
// First, the leafs (or leaves).  They have no children, so initialize
// with value and NULL pointers.
TREENODE L1 = {  2, NULL, NULL };
TREENODE L2 = { 14, NULL, NULL };
TREENODE L3 = { 21, NULL, NULL };
TREENODE L4 = { 23, NULL, NULL };
TREENODE L5 = { 31, NULL, NULL };

// Next, nodes with children.
TREENODE P1 = { 12,  &L1,  &L2 };
TREENODE P2 = { 18, NULL,  &L3 };
TREENODE P3 = { 16,  &P1,  &P2 };
TREENODE P4 = { 27,  &L4,  &L5 };
TREENODE P5 = { 22,  &P3,  &P4 };

// Finally, pointer to root node
TREENODE *treeroot = &P5;


void preorder_print (TREENODE *r)
// Preorder - handle root node first, then left tree, then right tree
{
    printf (" %3d", r->value);
    if (r->left  != NULL)   preorder_print (r->left);
    if (r->right != NULL)   preorder_print (r->right);
}//preorder_print()


void inorder_print (TREENODE *r)
// Inorder - handle left tree first, then root node, then right tree
{
    if (r->left  != NULL)   inorder_print (r->left);
    printf (" %3d", r->value);
    if (r->right != NULL)   inorder_print (r->right);
}//inorder_print()


void postorder_print (TREENODE *r)
// Postorder - handle left tree first, then right tree, then root node
{
    if (r->left  != NULL)   postorder_print (r->left);
    if (r->right != NULL)   postorder_print (r->right);
    printf (" %3d", r->value);
}//preorder_print()


int main (void)
{
    printf ("PREORDER:\n\t");
    preorder_print (treeroot);

    printf ("\n\nINORDER:\n\t");
    inorder_print (treeroot);

    printf ("\n\nPOSTORDER:\n\t");
    postorder_print (treeroot);

    printf ("\nEND OF TEST\n");
    return 0;
}//main()