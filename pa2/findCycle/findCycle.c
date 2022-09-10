#include "../graphutils.h"

// A program to find a cycle in a directed graph
struct element {
    // char open; // not needed
    graphNode_t close;
    struct element* next;
};

// Append the new element to the start of the stack
// This is one potential way to write this function signature
struct element* push (
    struct element* stack,
    // char open, // not needed
    graphNode_t close
) {
    struct element* newElement = malloc(sizeof(struct element)); //creates a new node and allocates data for it
    newElement->close = close; //add the data into the new node
    newElement->next = stack;
    stack = newElement; //sets the head pointer to firstNode
    return stack; //returns the firstNode

}

// Remove element from the top of the stack
char pop (struct element** stack ) {
    if (*stack != NULL) {
        struct element* temp = *stack; //gets the first element in the linkedlist
        graphNode_t returnedChar = temp->close; //gets the data from the original first element
        *stack = temp -> next; //sets the first element to be the next element
        free(temp); //free the temp
        return returnedChar; //returns the popped data
    } else {
        return '\0';
    }
}

// You may use DFS or BFS as needed
bool DFS (size_t graphNodeCount, AdjacencyListNode* adjacencyList, int* visited, int* endLoop, graphNode_t parent, graphNode_t current, struct element** root) {

    // First see if current node has already been visited, indicating a cycle found
    if (visited[current] == 0) {
        endLoop[0] = current;
        // printf("%d ", endLoop[0]);
        *root = push(*root, current);
        // printf("%ld ",(*root)->close);
        return true;
    }

    // Current node was not already visited, so now mark it as visited
    visited[current] = 0;
    // Now iterate through each of the neighboring graph nodes
    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while (neighbor) {
        if (neighbor->graphNode == parent) { //case when the edge is not directed
            printf("%ld %ld\n", neighbor->graphNode, current);
            exit(0);
        }
            // If the neighbor nodes is not the parent node (the node from which we arrived at current), call DFS
        if (DFS(graphNodeCount, adjacencyList, visited, endLoop, current, neighbor->graphNode, root) == true) {
            if (current == endLoop[0]) {
                while(*root != NULL) {
                    graphNode_t data = pop(root);
                    printf( "%ld ", data);
                }
                exit(0);
            }
            else {
                // printf("%ld ", current);
                *root = push(*root, current);
                // printf("%ld ",(*root)->close);
                return true;
            }
        }
    neighbor = neighbor->next;
    }

    // All DFS searches from current node found no cycles, so graph is a tree from this node
    visited[current] = 1;
    return false;
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    
    bool isCyclic = false;
    for (unsigned source=0; source<graphNodeCount; source++) {
        int* visited = malloc(graphNodeCount*sizeof(int));
        struct element* rooot = NULL;
        int* endLoop = malloc(1*sizeof(int));
        for (int i = 0; i < graphNodeCount; i++) {
            visited[i] = -1;
        }
        isCyclic = DFS(graphNodeCount, adjacencyList, visited, endLoop, source, source, &rooot);
        // while (rooot != NULL) {
        //     graphNode_t data = pop(&rooot);
        //     printf( "%ld ", data);
        // }
        free(rooot);
        free(visited);
        free(endLoop);
    }

    if (!isCyclic) { printf("DAG\n"); }
    
    freeAdjList ( graphNodeCount, adjacencyList );
    return EXIT_SUCCESS;
}
