#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

typedef struct tree {
    node *root;
} tree;

typedef struct queue_node {
    node *node;
    struct queue_node *next;
} queue_node;

enum choice {
    ADD_NODE = 1,
    DISPLAY_TREE,
    SEARCH_NODE,
    INORDER_TRAVERSAL,
    PREORDER_TRAVERSAL,
    POSTORDER_TRAVERSAL,
    DFS_TRAVERSAL,
    BFS_TRAVERSAL,
    CHECK_TREE_BALANCE,
    MIRROR_TREE,
    EXIT
};

tree *create_tree() {
    tree *new_tree = (tree *)malloc(sizeof(tree));
    if (new_tree == NULL) {
        printf("Memory allocation error!");
        exit(EXIT_FAILURE);
    }
    new_tree->root = NULL;
    return new_tree;
}

void free_tree(node *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int get_height(node *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + max(get_height(node->left), get_height(node->right));
}

int get_balance_factor(node *node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

node *get_right_rotate(node *node) {
    node *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
}




node *get_left_rotate(node *node) {
    node *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
}

node *get_balance_tree(node *node) {
    if (node == NULL) {
        return NULL;
    }

    node->left = get_balance_tree(node->left);
    node->right = get_balance_tree(node->right);

    int balance = get_balance_factor(node);

    if (balance > 1) { // taller left
        if (get_balance_factor(node->left) < 0) {
            node->left = get_left_rotate(node->left);
        }
        return get_right_rotate(node);
    }
    if (balance < -1) { // taller right
        if (get_balance_factor(node->right) > 0) {
            node->right = get_right_rotate(node->right);
        }
        return get_left_rotate(node);
    }

    return node;
}

int is_balanced(node *node) {
    if (node == NULL) {
        return 1;
    }

    int left_height = get_height(node->left);
    int right_height = get_height(node->right);

    if (abs(left_height - right_height) <= 1) {
        return 1;
    } else {
        return 0;
    }
}

void add_node(tree *tree, node **root, int value) {
    if (*root == NULL) {
        node *new_node = (node *)malloc(sizeof(node));
        if (new_node == NULL) {
            printf("Memory allocation error!");
            exit(EXIT_FAILURE);
        }
        new_node->key = value;
        new_node->left = NULL;
        new_node->right = NULL;
        *root = new_node;
    } else {
        if (value < (*root)->key) {
            add_node(tree, &((*root)->left), value);
        } else if (value > (*root)->key) {
            add_node(tree, &((*root)->right), value);
        } else {
            printf("Value %d already exists in the tree!\n", value);
        }
        *root = get_balance_tree(*root);
    }
}

void display_tree(node *node) {
    if (node != NULL) {
        display_tree(node->left);
        printf("%d ", node->key);
        display_tree(node->right);
    }
}

void display_inorder_traversal(node *root) {
    if (root != NULL) {
        display_inorder_traversal(root->left);
        printf("%d ", root->key);
        display_inorder_traversal(root->right);
    }
}

void display_preorder_traversal(node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        display_preorder_traversal(root->left);
        display_preorder_traversal(root->right);
    }
}

void display_postorder_traversal(node *root) {
    if (root != NULL) {
        display_postorder_traversal(root->left);
        display_postorder_traversal(root->right);
        printf("%d ", root->key);
    }
}

void display_dfs_traversal(node *node) {
    if (node != NULL) {
        printf("%d ", node->key);
        display_dfs_traversal(node->left);
        display_dfs_traversal(node->right);
    }
}

void display_bfs_traversal(tree *tree, node *root);

void enqueue_tree(queue_node **front, queue_node **rear, node *node) {
    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
    if (new_node == NULL) {
        printf("Memory allocation error!");


        exit(EXIT_FAILURE);
    }
    new_node->node = node;
    new_node->next = NULL;
    if (*front == NULL) {
        *front = *rear = new_node;
    } else {
        (*rear)->next = new_node;
        *rear = new_node;
    }
}

node *dequeue_tree(queue_node **front, queue_node **rear) {
    if (*front == NULL) {
        return NULL;
    } else {
        queue_node *temp = *front;
        *front = (*front)->next;
        if (*front == NULL) {
            *rear = NULL;
        }
        node *node = temp->node;
        free(temp);
        return node;
    }
}

void display_bfs_traversal(tree *tree, node *root) {
    if (root == NULL) {
        return;
    }

    queue_node *front = NULL;
    queue_node *rear = NULL;

    enqueue_tree(&front, &rear, root);

    while (front != NULL) {
        node *node = dequeue_tree(&front, &rear);
        printf("%d ", node->key);
        if (node->left != NULL) {
            enqueue_tree(&front, &rear, node->left);
        }
        if (node->right != NULL) {
            enqueue_tree(&front, &rear, node->right);
        }
    }
}

node *get_mirror_tree(node *node) {
    if (node == NULL) {
        return NULL;
    }

    node *left = get_mirror_tree(node->left);
    node *right = get_mirror_tree(node->right);

    node->left = right;
    node->right = left;

    return node;
}

int search_node(node *root, int value) {
    if (root == NULL) {
        return 0;
    }
    if (root->key == value) {
        return 1;
    }
    if (value < root->key) {
        return search_node(root->left, value);
    } else {
        return search_node(root->right, value);
    }
}

int main() {
    tree *tree = create_tree();
    if (tree == NULL) {
        printf("Memory allocation error!");
        exit(EXIT_FAILURE);
    }

    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Add Node\n");
        printf("2. Display Tree\n");
        printf("3. Search Node\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. DFS Traversal\n");
        printf("8. BFS Traversal\n");
        printf("9. Check Tree Balance\n");
        printf("10. Mirror Tree\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case ADD_NODE:
                printf("Enter the value to add: ");
                scanf("%d", &value);
                add_node(tree, &(tree->root), value);
                break;
            case DISPLAY_TREE:
                display_tree(tree->root);
                printf("\n");
                break;
            case SEARCH_NODE:
                printf("Enter the value to search: ");
                scanf("%d", &value);
                if (search_node(tree->root, value)) {
                    printf("Value %d found in the tree.\n", value);
                } else {
                    printf("Value %d not found in the tree.\n", value);
                }
                break;
            case INORDER_TRAVERSAL:
                display_inorder_traversal(tree->root);
                printf("\n");
                break;
            case PREORDER_TRAVERSAL:
                display_preorder_traversal(tree->root);
                printf("\n");
                break;
            case POSTORDER_TRAVERSAL:
                display_postorder_traversal(tree->root);
                printf("\n");
                break;
            case DFS_TRAVERSAL:
                display_dfs_traversal(tree->root);
                printf("\n");
                break;
            case BFS_TRAVERSAL:
                display_bfs_traversal(tree, tree->root);
                printf("\n");
                break;
            case CHECK_TREE_BALANCE:
                if (is_balanced(tree->root)) {
                    printf("The tree is balanced.\n");
                } else {
                    printf("The tree is not balanced.\n");
                }
                break;
            case MIRROR_TREE:
                tree->root = get_mirror_tree(tree->root);
                printf("The tree has been mirrored.\n");
                break;
            case EXIT:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != EXIT);

    free_tree(tree->root);
    free(tree);
    return 0;
}
