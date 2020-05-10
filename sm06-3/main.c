#include <stdio.h>
#include <stdlib.h>

struct Tree
{
    int value;
    struct Tree *left;
    struct Tree *right;
};

typedef struct Tree Tree;
typedef Tree * TrE;
TrE root = NULL;

void push (int num)
{
    if (!root)
    {
        root = malloc(sizeof(Tree));
        if (root == NULL)
        {
            fprintf(stderr, "sorry, not enough memory\n");
            exit(1);
        }
        root->left = NULL;
        root->right = NULL;
        root->value = num;
        return;
    }

    TrE iter = root;
    TrE item;

    while (1)
    {
        if (iter->value == num)
            return;

        if (num < iter->value)
        {
            if (iter->left)
                iter = iter->left;
            else
            {
                item = malloc(sizeof(Tree));
                if (item == NULL)
                {
                    fprintf(stderr, "sorry, not enough memory\n");
                    exit(1);
                }
                item->left = NULL;
                item->right = NULL;
                item->value = num;
                iter->left = item;
                return;
            }
        }

        if (num > iter->value)
        {
            if (iter->right)
                iter = iter->right;
            else
            {
                item = malloc(sizeof(Tree));
                if (item == NULL)
                {
                    fprintf(stderr, "sorry, not enough memory\n");
                    exit(1);
                }
                item->left = NULL;
                item->right = NULL;
                item->value = num;
                iter->right = item;
                return;
            }
        }
    }
}

void print_del_tree(TrE root)
{
    if (!root)
        return;

    print_del_tree(root->right);
    printf("%d ", root->value);
    print_del_tree(root->left);
    free(root);
}

int main()
{
    int num;
    int flag = 0;

    while (scanf("%d", &num) != EOF)
    {
        if (!num)
        {
            print_del_tree(root);
            printf("0 ");
            root = NULL;
            flag = 0;
            continue;
        }
        push(num);
        flag = 1;
    }

    if (flag)
    {
        print_del_tree(root);
        printf("0");
    }

    printf("\n");

    return 0;
}
