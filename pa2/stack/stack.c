#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct element {
    int number;
    struct element* next;
};

// Append the new element to the start of the stack
// show what happens on the stack and on the heap


struct element* push (
    struct element* stack,
    int number
) {
    struct element* newElement = malloc(sizeof(struct element));
    newElement->number = number;
    newElement->next = stack;
    stack = newElement;
    return stack;

}

// Remove element from the top of the stack
int pop (struct element** stack) {
    if (*stack != NULL) {
        struct element* temp = *stack;
        int number = temp->number;
        *stack = temp -> next;
        free(temp);
        return number;
    } else {
        perror("Empty Stack");
        return(0);
    }
}

int main(int argc, char* argv[])
{

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element* root = NULL;

    char buff[5];
    while ( fscanf(fp, "%s", buff) != -1 ) {

        if ( strcmp(buff,"PUSH")==0 ) {
            unsigned int number;
            fscanf(fp, "%d", &number);
            root = push(root, number);
        } else if ( strcmp(buff,"POP")==0 ) {
            pop(&root); // discard the return
        } else {
            printf("UNEXPECTED INPUT\n");
            return EXIT_FAILURE;
        }
    }

    while (root != NULL) {
        int data = pop(&root);
        printf( "%d\n", data );
    }

    fclose(fp);
    return 0;
}
