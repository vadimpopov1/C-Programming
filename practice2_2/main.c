#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
    struct node *down;
};
typedef struct node Node;

void addNode(Node **head, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->down = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
}

void linkLists(Node *top, Node *bottom) {
    while (top != NULL && bottom != NULL) {
        top->down = bottom;
        top = top->next;
        bottom = bottom->next;
    }
    while (top != NULL) {
        top->down = NULL;
        top = top->next;
    }
    while (bottom != NULL) {
        bottom->down = NULL;
        bottom = bottom->next;
    }
}

void generateDotFile(Node *top, Node *bottom, Node *current, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error to get a file!\n");
        return;
    }
    
    fprintf(fp, "digraph LinkedList {\n");
    fprintf(fp, "node [shape=circle];\n");
    fprintf(fp, "rankdir=LR;\n");
    
    Node *temp = top;
    int id = 1;
    while (temp != NULL) {
        fprintf(fp, "node%d [label=\"%d\"%s];\n", id, temp->data, temp == current ? ", color=red" : "");
        if (temp->next != NULL)
            fprintf(fp, "node%d -> node%d;\n", id, id + 1);
        temp = temp->next;
        id++;
    }
    
    int bottomStartId = id;
    temp = bottom;
    while (temp != NULL) {
        fprintf(fp, "node%d [label=\"%d\"%s];\n", id, temp->data, temp == current ? ", color=red" : "");
        if (temp->next != NULL)
            fprintf(fp, "node%d -> node%d;\n", id, id + 1);
        temp = temp->next;
        id++;
    }
    
    temp = top;
    int topId = 1;
    while (temp != NULL) {
        if (temp->down != NULL)
            fprintf(fp, "node%d -> node%d [style=dashed, color=blue];\n", topId, bottomStartId);
        temp = temp->next;
        topId++;
        bottomStartId++;
    }
    
    fprintf(fp, "}\n");
    fclose(fp);
}

void navigateList(Node *start, Node *top, Node *bottom) {
    Node *current = start;
    char input;
    const char *dot_filename = "linked_list.dot";
    
    while (1) {
        generateDotFile(top, bottom, current, dot_filename);
        printf("Current value: %d\n", current->data);
        if (current->next)
            printf("1 way (W): %d\n", current->next->data);
        else
            printf("1 way (W): NULL\n");
        if (current->down)
            printf("2 way (D): %d\n", current->down->data);
        else
            printf("2 way (D): NULL\n");
        
        printf("Enter (W/D/Q): ");
        scanf(" %c", &input);
        
        switch (input) {
            case 'W':
            case 'w':
                if (current->next) current = current->next;
                break;
            case 'd':
            case 'D':
                if (current->down) current = current->down;
                break;
            case 'q':
            case 'Q':
                return;
            default:
                printf("Unknown commad. Use W/D/Q.\n");
        }
    }
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *topList = NULL;
    Node *bottomList = NULL;
    int value;

    printf("List N. Enter values (0 to stop): ");
    while (1) {
        scanf("%d", &value);
        if (value == 0) break;
        addNode(&topList, value);
    }

    printf("List K. Enter values (0 to stop): ");
    while (1) {
        scanf("%d", &value);
        if (value == 0) break;
        addNode(&bottomList, value);
    }

    linkLists(topList, bottomList);
    
    navigateList(topList, topList, bottomList);

    freeList(topList);
    freeList(bottomList);
    return 0;
}
