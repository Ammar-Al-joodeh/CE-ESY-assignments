#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *buffer;   
    int size;       
    int head;
    int tail;
    int count;
} CircularBuffer;

void init(CircularBuffer *cb, int size) {
    cb->buffer = (char*)malloc(size * sizeof(char));
    cb->size = size;
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int isFull(CircularBuffer *cb) {
    return cb->count == cb->size;
}

int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

void writeBuffer(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("Buffer Overflow\n");
        return;
    }

    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % cb->size;
    cb->count++;
}

char readBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow\n");
        return '\0';
    }

    char data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % cb->size;
    cb->count--;
    return data;
}

int main(void) {
    CircularBuffer cb;

    int userSize;
    printf("Enter buffer size: ");
    scanf("%d", &userSize);
    getchar();

    init(&cb, userSize);

    char name[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';
    }

    const char suffix[] = "CE-ESY";
    strcat(name, suffix);

    for (size_t i = 0; i < strlen(name); i++) {
        writeBuffer(&cb, name[i]);
    }

    printf("Output from buffer: ");
    while (!isEmpty(&cb)) {
        char c = readBuffer(&cb);
        if (c != '\0') {
            putchar(c);
        }
    }
    putchar('\n');

    if (isEmpty(&cb)) {
        printf("Buffer is now empty.\n");
    }

    free(cb.buffer); 
    return 0;
}
