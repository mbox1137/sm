struct Node
{
    double	key;
    struct Node *left;
    struct Node *right;
    char	*str;
};

int tree_find(struct Node *root, double key, char **pstr);
int tree_findc(struct Node *root, double key, char **pstr);
