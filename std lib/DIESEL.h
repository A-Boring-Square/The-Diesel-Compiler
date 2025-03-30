/*
MIT License

Copyright (c) 2024 A-Boring-Square

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef DSL_STD_LIB_H
#define DSL_STD_LIB_H


/*
    This file defines the common standard library functions and types for Diesel when transpiled to C.
    
    NOTE FOR OS DEVS:
    If you want Diesel to run on your OS, **port this file** as Diesel **only**
    relies on the functions and structures defined here.
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>


// ===========================================================
//                    FIXED-SIZE DATA TYPES
// ===========================================================

// Signed integer types (platform-independent sizes)
typedef int8_t   DSL_int8;
typedef int16_t  DSL_int16;
typedef int32_t  DSL_int32;
typedef int64_t  DSL_int64;

// Unsigned integer types
typedef uint8_t  DSL_uint8;
typedef uint16_t DSL_uint16;
typedef uint32_t DSL_uint32;
typedef uint64_t DSL_uint64;

// Floating-point types
typedef float    DSL_float32;
typedef double   DSL_float64;

// ===========================================================
//                MEMORY MANAGEMENT UTILITIES
// ===========================================================

// Macro for safe memory allocation. Ensures the pointer is allocated
// or triggers a crash if allocation fails.
#define DSL_Allocate(ptr, type) \
    do { \
        *(ptr) = (type*)malloc(sizeof(type)); \
        if (*(ptr) == NULL) { \
            DSL_Crash_And_Burn("Memory allocation failed"); \
        } \
    } while(0)

// Function to safely free allocated memory.
void DSL_Free(void* ptr) {
    if (ptr) free(ptr);
}

// ===========================================================
//                DOUBLY LINKED LIST IMPLEMENTATION
// ===========================================================

// Node structure for the doubly linked list.
typedef struct DSL_Node {
    void* data;            // Pointer to the stored data
    struct DSL_Node* prev; // Pointer to the previous node
    struct DSL_Node* next; // Pointer to the next node
} DSL_Node;

// Structure representing the doubly linked list itself.
typedef struct DSL_List {
    DSL_Node* head;        // Pointer to the first node
    DSL_Node* tail;        // Pointer to the last node
    size_t element_size;   // Size of each element in the list
    size_t count;          // Number of elements in the list
} DSL_List;

// ===========================================================
//                DOUBLY LINKED LIST FUNCTIONS
// ===========================================================

// Creates a new doubly linked list with a specified element size.
DSL_List DSL_ListCreate(size_t element_size) {
    DSL_List list = {NULL, NULL, element_size, 0};
    return list;
}

// Adds a new element to the front of the list.
void DSL_ListAddFront(DSL_List* list, void* item) {
    DSL_Node* node = (DSL_Node*)malloc(sizeof(DSL_Node));
    if (!node) DSL_Crash_And_Burn("Failed to allocate memory for node");

    node->data = malloc(list->element_size);
    if (!node->data) DSL_Crash_And_Burn("Failed to allocate node data");
    
    memcpy(node->data, item, list->element_size);
    node->prev = NULL;
    node->next = list->head;

    if (list->head) list->head->prev = node;
    else list->tail = node; // If the list was empty, set the tail to the new node

    list->head = node;
    list->count++;
}

// Adds a new element to the back of the list.
void DSL_ListAddBack(DSL_List* list, void* item) {
    DSL_Node* node = (DSL_Node*)malloc(sizeof(DSL_Node));
    if (!node) DSL_Crash_And_Burn("Failed to allocate memory for node");

    node->data = malloc(list->element_size);
    if (!node->data) DSL_Crash_And_Burn("Failed to allocate node data");

    memcpy(node->data, item, list->element_size);
    node->next = NULL;
    node->prev = list->tail;

    if (list->tail) list->tail->next = node;
    else list->head = node; // If the list was empty, set the head to the new node

    list->tail = node;
    list->count++;
}

// Removes a specific node from the list and frees its memory.
void DSL_ListRemove(DSL_List* list, DSL_Node* node) {
    if (!node) return;

    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;

    free(node->data);
    free(node);
    list->count--;
}

// Destroys the entire list and frees all associated memory.
void DSL_ListDestroy(DSL_List* list) {
    DSL_Node* current = list->head;
    while (current) {
        DSL_Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = list->tail = NULL;
    list->count = 0;
}

// ===========================================================
//                STATIC LIST IMPLEMENTATION
// ===========================================================

#define DSL_MAX_STATIC_LIST_SIZE 128

// Structure for a static list (fixed-size array)
typedef struct {
    void* data[DSL_MAX_STATIC_LIST_SIZE]; // Preallocated array
    size_t element_size;  // Size of each element
    size_t count;         // Number of elements currently in the list
} DSL_StaticList;

// Initializes a static list.
void DSL_StaticListInit(DSL_StaticList* list, size_t element_size) {
    list->element_size = element_size;
    list->count = 0;
}

// Adds an element to a static list.
void DSL_StaticListAdd(DSL_StaticList* list, void* item) {
    if (list->count >= DSL_MAX_STATIC_LIST_SIZE) {
        DSL_Crash_And_Burn("Static list overflow");
    }

    list->data[list->count] = malloc(list->element_size);
    if (!list->data[list->count]) DSL_Crash_And_Burn("Failed to allocate static list element");

    memcpy(list->data[list->count], item, list->element_size);
    list->count++;
}

// Removes an element from the static list.
void DSL_StaticListRemove(DSL_StaticList* list, size_t index) {
    if (index >= list->count) return;

    free(list->data[index]);

    for (size_t i = index; i < list->count - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->count--;
}

// Destroys a static list and frees memory.
void DSL_StaticListDestroy(DSL_StaticList* list) {
    for (size_t i = 0; i < list->count; i++) {
        free(list->data[i]);
    }
    list->count = 0;
}

// ===========================================================
//                   INPUT & OUTPUT FUNCTIONS
// ===========================================================

// Prints formatted output to the console.
void DSL_Out(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

// Reads input from the user and returns a static buffer.
char* DSL_In(const char* prompt) {
    printf("%s", prompt);
    static char buffer[256];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        DSL_Crash_And_Burn("Failed to read input");
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}

// ===========================================================
//                  ERROR HANDLING FUNCTIONS
// ===========================================================

// Terminates execution with an error message.
void DSL_Crash_And_Burn(const char* error_message) {
    fprintf(stderr, "Error: %s\n", error_message);
    abort();
}

#endif