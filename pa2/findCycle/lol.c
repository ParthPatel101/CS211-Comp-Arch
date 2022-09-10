#include "../graphutils.h"

// A program to find a cycle in a directed graph

// You may use DFS or BFS as needed
bool DFS (
    size_t graphNodeCount,
    AdjacencyListNode* adjacencyList,
    bool* visited,
    graphNode_t parent,
    graphNode_t current
) {

    // First see if current node has already been visited, indicating a cycle found
    if (visited[current]) {
        return false;
    }

    // Current node was not already visited, so now mark it as visited
    visited[current] = true;

    // Now iterate through each of the neighboring graph nodes
    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while (neighbor) {
        if (neighbor->graphNode == parent) {
            printf("%ld %ld\n", neighbor->graphNode, current);
            exit(0);
        }
        if (neighbor->graphNode!=parent) {
            // If the neighbor nodes is not the parent node (the node from which we arrived at current), call DFS
            return DFS(graphNodeCount, adjacencyList, visited, current, neighbor->graphNode);
        }
        neighbor = neighbor->next;
    }

    // All DFS searches from current node found no cycles, so graph is a tree from this node
    return true;
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    
    bool isCyclic = false;
    for (unsigned source=0; source<graphNodeCount; source++) {
        bool* visited = calloc (graphNodeCount, sizeof(bool));
        isCyclic = DFS(graphNodeCount, adjacencyList, visited, source, source);
        free(visited);
    }

    if (!isCyclic) { printf("DAG\n"); }
    
    freeAdjList ( graphNodeCount, adjacencyList );
    return EXIT_SUCCESS;
}
