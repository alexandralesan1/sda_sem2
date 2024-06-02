#include <stdio.h>
#include <stdlib.h>

enum Choice{

INSERT_NODE = 1,
INORDER_TRAVERSAL,
PREORDER_TRAVERSAL,
POSTORDER_TRAVERSAL,
MAX_DEPTH,
SEARCH_KEY,
DEPTH_OF_NODE,
HEIGHT_OF_NODE,
PRINT_LEAVES,
CLEAR_TREE

};



struct tree_node {
    int key;
    struct tree_node* left;
    struct tree_node* right;
};

/**
 * Creates a new node with the given key value.
 *
 * @param key The value of the node to be created.
 * @return A pointer to the newly created node.
 */
struct tree_node* create_node(int key) {
    struct tree_node* new_node = (struct tree_node*)malloc(sizeof(struct tree_node));
    if (new_node == NULL) {
        printf("Eroare la alocarea de memorie pentru un nou nod.\n");
        exit(1);
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
/**
 * Searches for a node with the specified key in the binary tree.
 *
 * @param root The root node of the binary tree.
 * @param key The key value to search for.
 * @return A pointer to the node with the specified key if found, otherwise NULL.
 */

struct tree_node* search_node(struct tree_node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    struct tree_node* right_result = search_node(root->right, key);
    if (right_result != NULL) {
        return right_result;
    }
    return search_node(root->left, key);
}




/**
 * Inserts child nodes to a parent node in the binary tree.
 *
 * @param root A pointer to a pointer to the root node of the binary tree.
 * @param parent_key The key value of the parent node.
 * @param left_child_key The key value of the left child node (-1 if no left child).
 * @param right_child_key The key value of the right child node (-1 if no right child).
 */


void insert_node(struct tree_node** root, int parent_key, int left_child_key, int right_child_key) {
    struct tree_node* parent = search_node(*root, parent_key);
    if (parent == NULL) {
        printf("Nodul parinte cu cheia %d nu exista in arbore.\n", parent_key);
        return;
    }
    if (parent->left != NULL && parent->right != NULL) {
        printf("Nodul parinte cu cheia %d are deja doi fii.\n", parent_key);
        return;
    }
    if (left_child_key != -1) {
        parent->left = create_node(left_child_key);
    }
    if (right_child_key != -1) {
        parent->right = create_node(right_child_key);
    }
}

/**
 * Performs an inorder traversal of the binary tree and prints the key values of the nodes.
 *
 * @param root The root node of the binary tree.
 */

void inorder_traversal(struct tree_node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->key);
        inorder_traversal(root->right);
    }
}



/**
 * Performs a preorder traversal of the binary tree and prints the key values of the nodes.
 *
 * @param root The root node of the binary tree.
 */
void preorder_traversal(struct tree_node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}




/**
 * Performs a postorder traversal of the binary tree and prints the key values of the nodes.
 *
 * @param root The root node of the binary tree.
 */
void postorder_traversal(struct tree_node* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->key);
    }
}



/**
 * Clears the binary tree by freeing the memory allocated for each node.
 *
 * @param root The root node of the binary tree.
 */
void clear_tree(struct tree_node* root) {
    if (root == NULL) {
        return;
    }
    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}



/**
 * Calculates the maximum depth of the binary tree.
 *
 * @param root The root node of the binary tree.
 * @return The maximum depth of the binary tree.
 */
int max_depth(struct tree_node* root) {
    if (root == NULL) {
        return 0;
    }
    int left_depth = max_depth(root->left);
    int right_depth = max_depth(root->right);
    return (left_depth > right_depth) ? (left_depth + 1) : (right_depth + 1);
}


/**
 * Calculates the depth of a node with the specified key in the binary tree.
 *
 * @param root The root node of the binary tree.
 * @param search_key The key value of the node to calculate depth for.
 * @return The depth of the node if found, otherwise -1.
 */
int depth_of_node(struct tree_node* root, int search_key) {
    struct tree_node* node = search_node(root, search_key);
    if (node == NULL) {
        return -1;
    }
    int depth = 0;
    struct tree_node* current = root;
    while (current != NULL) {
        if (search_key < current->key) {
            current = current->left;
        } else if (search_key > current->key) {
            current = current->right;
        } else {
            break;
        }
        depth++;
    }
    return depth;
}



/**
 * Calculates the height of a node with the specified key in the binary tree.
 *
 * @param root The root node of the binary tree.
 * @param search_key The key value of the node to calculate height for.
 * @return The height of the node if found, otherwise -1.
 */
int height_of_node(struct tree_node* root, int search_key) {
    struct tree_node* node = search_node(root, search_key);
    if (node == NULL) {
        return -1;
    }
    int height(struct tree_node* node) {
        if (node == NULL) {
            return 0;
        }
        int left_height = height(node->left);
        int right_height = height(node->right);
        return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
    }
    return height(node);
}


/**
 * Prints the key values of all leaf nodes in the binary tree.
 *
 * @param root The root node of the binary tree.
 */
void print_leaves(struct tree_node* root) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->key);
    }
    print_leaves(root->left);
    print_leaves(root->right);
}

int main() {
    struct tree_node* root = NULL;
    int parent_key, left_child_key, right_child_key;

    printf("Introduceti cheia radacinii arborelui: ");
    scanf("%d", &parent_key);
    root = create_node(parent_key);

    while (1) {
        printf("\nMeniu:\n");
        printf("%d. Inserare noduri (maxim 2) pentru un nod existent in arbore\n", INSERT_NODE);
        printf("2. Afisare arbore (parcurgere inordine)\n");
        printf("3. Afisare arbore (parcurgere preordine)\n");
        printf("4. Afisare arbore (parcurgere postordine)\n");
        printf("5. Calculare adancime arbore\n");
        printf("6. Cautarea unui nod in baza unei chei de cautare\n");
        printf("7. Calculare adancimii unui nod ( nodul va fi selectat in baza unei chei de cautare )\n");
        printf("8. Calculare inaltimii unui nod ( nodul va fi selectat in baza unei chei de cautare )\n");
        printf("9. Afisarea tuturor frunzelor arborelui\n");
        printf("10. Curatirea elementelor arborelui\n");
        printf("11. Eliberarea memoriei arborelui\n");
        printf("12. Iesire\n");
        printf("Introduceti optiunea: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case INSERT_NODE:
                printf("Introduceti cheia nodului parinte: ");
                scanf("%d", &parent_key);
                printf("Introduceti cheia fiului stang (-1 pentru niciun fiu): ");
                scanf("%d", &left_child_key);
                printf("Introduceti cheia fiului drept (-1 pentru niciun fiu): ");
                scanf("%d", &right_child_key);
                insert_node(&root, parent_key, left_child_key, right_child_key);
                break;
            case INORDER_TRAVERSAL:
                printf("Elementele arborelui (parcurgere inordine): ");
                inorder_traversal(root);
                printf("\n");
                break;
            case PREORDER_TRAVERSAL:
                printf("Elementele arborelui (parcurgere preordine): ");
                preorder_traversal(root);
                printf("\n");
                break;
            case POSTORDER_TRAVERSAL:
                printf("Elementele arborelui (parcurgere postordine): ");
                postorder_traversal(root);
                printf("\n");
                break;
            case MAX_DEPTH:
                printf("Adancimea arborelui este: %d\n", max_depth(root));
                break;
            case SEARCH_KEY:
                printf("Introduceti cheia de cautare: ");
                int search_key;
                scanf("%d", &search_key);
                struct tree_node* result = search_node(root, search_key);
                if (result != NULL) {
                    printf("Nodul cu cheia %d a fost gasit in arbore.\n", search_key);
                } else {
                    printf("Nodul cu cheia %d nu a fost gasit in arbore.\n", search_key);
                }
                break;
            case DEPTH_OF_NODE:
                printf("Introduceti cheia nodului pentru care sa se calculeze adancimea: ");
                int node_key_depth;
                scanf("%d", &node_key_depth);
                int node_depth = depth_of_node(root, node_key_depth);
                if (node_depth == -1) {
                    printf("Nodul cu cheia %d nu a fost gasit in arbore.\n", node_key_depth);
                } else {
                    printf("Adancimea nodului cu cheia %d este: %d\n", node_key_depth, node_depth);
                }
                break;
            case HEIGHT_OF_NODE:
                printf("Introduceti cheia nodului pentru care sa se calculeze inaltimea: ");
                int node_key_height;
                scanf("%d", &node_key_height);
                int node_height = height_of_node(root, node_key_height);
                if (node_height == -1) {
                    printf("Nodul cu cheia %d nu a fost gasit in arbore.\n", node_key_height);
                } else {
                    printf("Inaltimea nodului cu cheia %d este: %d\n", node_key_height, node_height);
                }
                break;
            case PRINT_LEAVES:
               printf("Frunzele arborelui sunt: ");
               print_leaves(root);
               printf("\n");
               break;
            case CLEAR_TREE:
               printf("Curatarea arborelui...\n");
               clear_tree(root);
               printf("Arborele a fost curatat.\n");
               root = NULL;
               break;
            case 11:
               printf("Eliberarea memoriei arborelui...\n");
               clear_tree(root);
               printf("Memoria arborelui a fost eliberată.\n");
               root = NULL;
               break;
            case 12:
                printf("Programul se inchide...\n");
                clear_tree(root);
                exit(0);
            default:
                printf("Optiune invalida. Va rugam sa introduceti o optiune valida.\n");
        }
    }

    return 0;
}
