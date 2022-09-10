#include <stdlib.h>
#include <stdio.h>

// A program to perform a LEVEL ORDER (BREADTH-FIRST) TRAVERSAL of a binary search tree

// BINARY SEARCH TREE

typedef struct BSTNode BSTNode;
struct BSTNode {
    int key;
    struct BSTNode* l_child; // nodes with smaller key will be in left subtree
    struct BSTNode* r_child; // nodes with larger key will be in right subtree
};

// Add new data to the BST using recursion
struct BSTNode* insert(struct BSTNode* root, int key) {
    if (root == NULL) {
        root = malloc(sizeof(struct BSTNode));
        root->l_child = NULL;
        root->r_child = NULL;
        root->key = key;
    }
     if ( key<root->key ) {
        root->l_child = insert( root->l_child, key );
    } else if ( key==root->key ) {
        // duplicates are ignored
    } else { // key>root->key
        root->r_child = insert( root->r_child, key );
    }
    return root;
}

// Delete the BST using recursion
void delete_bst(struct BSTNode* root) {
    if (root == NULL) {
        return;
    }
    delete_bst(root->l_child);
    delete_bst(root->r_child);
    free(root);
}


// LINKED LIST IMPLEMENTATION OF QUEUE

// queue needed for level order traversal
typedef struct QueueNode QueueNode;
struct QueueNode {
    struct BSTNode* data;
    struct QueueNode* next; // pointer to next node in linked list
};

struct Queue {
    struct QueueNode* front; // front (head) of the queue
    struct QueueNode* back; // back (tail) of the queue
};

typedef struct Queue Queue;
// Append a new QueueNode to the back of the Queue
void enqueue (Queue* queue, BSTNode* data ) {
    struct QueueNode* newQueueNode = malloc(sizeof(struct QueueNode));
    newQueueNode->data = data;
    newQueueNode-> next = NULL;
    if (queue->back == NULL) {
        queue->front = newQueueNode;
        queue->back = newQueueNode;
    } else {
        queue->back->next = newQueueNode;
        queue->back = newQueueNode; 
    }
}

struct BSTNode* dequeue ( Queue* queue ) {

    if (queue->front==NULL) { // If the Queue is currently empty
        return '\0';
    } else {

        // The QueueNode at front of the queue to be removed
        QueueNode* temp = queue->front;
        struct BSTNode* data = temp->data;

        queue->front = temp->next;
        if (queue->back==temp) { // If the Queue will become empty
            queue->back = NULL;
        }

        free(temp);
        return data;
    }
}


int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    BSTNode* root = NULL;
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {
        root = insert (root, key);
    }
    fclose(fp);

    // USE A QUEUE TO PERFORM LEVEL ORDER TRAVERSAL
    Queue queue = { .front=NULL, .back=NULL };
    BSTNode* currBSTNode = root;
    do {
        if (currBSTNode != NULL) {
            printf("%d ", currBSTNode->key);
        }
        if (currBSTNode->l_child != NULL) {
            enqueue(&queue, currBSTNode->l_child);
        }
        if (currBSTNode->r_child != NULL) {
            enqueue(&queue, currBSTNode->r_child);
        }
       currBSTNode = dequeue(&queue);
    } while ( currBSTNode!=NULL );
    free(currBSTNode);
    delete_bst(root);
    return EXIT_SUCCESS;
}
