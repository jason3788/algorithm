#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char key[10];
    int bf;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

Node *createNode(char key[]) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    int i;
    strcpy(newNode->key, key);
    newNode->bf = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int getHeight(Node *node) {
    if (node == NULL) {
        return 0;
    } else {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } 
		else {
            return rightHeight + 1;
        }
    }
}


int getBalanceFactor(Node *node) {
    return getHeight(node->left) - getHeight(node->right);
}


Node *rotateLeft(Node *node) {
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->bf = getBalanceFactor(node);
    newRoot->bf = getBalanceFactor(newRoot);
    return newRoot;
}

Node *rotateRight(Node *node) {
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->bf = getBalanceFactor(node);
    newRoot->bf = getBalanceFactor(newRoot);
    return newRoot;
}

Node *rotateLeftRight(Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node *rotateRightLeft(Node *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Node *balance(Node *node) {
    int bf = getBalanceFactor(node);
    if (bf > 1) {
        if (getBalanceFactor(node->left) > 0) {
        	node = rotateRight(node);
        } 
		else {
            node = rotateLeftRight(node);
        }
    } 
	else if (bf < -1) {
        if (getBalanceFactor(node->right) < 0) {
        	node = rotateLeft(node);
        } else {
            node = rotateRightLeft(node);
        }
    }
    return node;
}

Node *insert(Node *node, char key[]) {
    if (node == NULL) {
        return createNode(key);
    } 
	else if (strcmp(key, node->key) < 0) {
        node->left = insert(node->left, key);
    } 
	else if (strcmp(key, node->key) > 0) {
        node->right = insert(node->right, key);
    } 
	else {
        return node;
    }
    return balance(node);
}

Node *findMin(Node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node *Delete(Node *node, char key[]) {
    if (node == NULL) {
        return NULL;
    } 
	else if (strcmp(key, node->key) < 0) {
        node->left = Delete(node->left, key);
    } 
	else if (strcmp(key, node->key) > 0) {
        node->right = Delete(node->right, key);
    } 
	else { 
	    if (node->left == NULL && node->right == NULL) {
	        free(node);
	        return NULL;
	    } 
		else if (node->left == NULL) {
	        Node *temp = node->right;
	        free(node);
	        return temp;
	    } 
		else if (node->right == NULL) {
	        Node *temp = node->left;
	        free(node);
	        return temp;
	    } 
		else {
	        Node *minNode = findMin(node->right);
	        strcpy(node->key, minNode->key);
	        node->right = Delete(node->right, minNode->key);
	    }
	}
	node->bf = getBalanceFactor(node);
	return balance(node);
}

void printInorder(Node *node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%s ", node->key);
    printInorder(node->right);
}
void printPostorder(Node *node)
{
    if (node == NULL)
        return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%s ", node->key);
}

int main() {
	Node *root = NULL;
	root = insert(root, "blueberry");
	root = insert(root, "raspberry");
	root = insert(root, "mulberry");
	root = insert(root, "orange");
	root = insert(root, "citron");
	root = insert(root, "pomelo");
	root = insert(root, "sunkist");
	root = insert(root, "grapefruit");
	
	root = Delete(root, "orange");
	root = Delete(root, "citron");
	
	root = insert(root, "apple");
	root = insert(root, "mango");
	root = insert(root, "cherry");
	root = insert(root, "olive");

	root = Delete(root, "mulberry");
	root = Delete(root, "cherry");
	
	root = insert(root, "guava");
	root = insert(root, "pear");
	root = insert(root, "tomato");
	root = insert(root, "watermelon");
	
	printf("Inorder:\n");
	printInorder(root);
	printf("\n\n");
	printf("Postorder:\n");
	printPostorder(root);
	printf("\n");
	return 0;
}
