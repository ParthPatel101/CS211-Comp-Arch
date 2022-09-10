#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Struct to hold the open and close braces and the pointer to the next element.
struct element {
    // char open; // not needed
    char close;
    struct element* next;
};

// Append the new element to the start of the stack
// This is one potential way to write this function signature
struct element* push (
    struct element* stack,
    // char open, // not needed
    char close
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
        char returnedChar = temp->close; //gets the data from the original first element
        *stack = temp -> next; //sets the first element to be the next element
        free(temp); //free the temp
        return returnedChar; //returns the popped data
    } else {
        return '\0';
    }
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element* root = NULL;
    bool balanced = true;
    
    char buff;
    while ( fscanf(fp, "%c", &buff)==1 ) {
        switch(buff) {
            case '<':
                root = push(root, '>');
                break;
            case '(':
                root = push(root, ')');
                break;
            case '[':
                root = push(root, ']');
                break;
            case '{':
                root = push(root, '}');
                break;
            case '>':
                if ((int) pop(&root) != (int) '>') {
                    balanced = false;
                    
                }
                break;
            case ')':
                if ((int) pop(&root) != (int) ')') {
                    balanced = false;
                }
                break;
            case ']':   
                if ((int) pop(&root) != (int) ']') {
                    balanced = false;
                }
                break;
            case '}':
                if ((int) pop(&root) != (int) '}') {
                    balanced = false;
                }
                break;
            default:
                printf("Invalid character\n" );
                break;
        }
    }
    
    printf (balanced ? "yes" : "no" );
    fclose(fp);
    return 0;
}
