#include <stdlib.h>
#include <stdio.h>

typedef struct node_type
{
    char id; /* node name */
    int label ; /* appropriate type for label */
    struct node_type *left, *right;
} NodeT;
NodeT *createBinTree()
{
    NodeT *p;
    char c;
    /* read node id */
    scanf("%c", &c);
    if ( c == '*' )
        return NULL; /* empty tree; do nothing */
    else /* else included for clarity */
    {
        /* build node pointed to by p */
        p = ( NodeT *) malloc( sizeof( NodeT ));
        if ( p == NULL )
            perror( "Out of space in createBinTree" );
        /* fill in node */
        p->id = c;
        p->left = createBinTree();
        p->right = createBinTree();
    }
    return p;
}

int main()
{
    printf("write in a single line the input of char,\n * means no more sub trees at that branch\ninput:" );
    createBinTree();
}
