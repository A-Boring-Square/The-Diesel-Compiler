#ifndef DSL_STD_LIB_H
#define DSL_STD_LIB_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>  // Include stdarg.h for variable arguments

// Fixed-size integer types (from stdint.h)
typedef int8_t   DSL_int8;
typedef int16_t  DSL_int16;
typedef int32_t  DSL_int32;
typedef int64_t  DSL_int64;
typedef uint8_t  DSL_uint8;
typedef uint16_t DSL_uint16;
typedef uint32_t DSL_uint32;
typedef uint64_t DSL_uint64;

// Fixed-size floating-point types
typedef float   DSL_float32;  // 32-bit float
typedef double  DSL_float64;  // 64-bit double

// Macro to call DSL_Allocate with sizeof automatically
#define DSL_Allocate(ptr, type) \
    do { \
        *(ptr) = malloc(sizeof(type)); \
    } while(0)

// Dynamic array management
void DSL_Free(void* ptr) {
    free(ptr);
}

// String manipulation functions
size_t DSL_StringLength(const char* str) {
    return strlen(str);
}

char* DSL_StringCopy(const char* str) {
    size_t len = strlen(str) + 1; // +1 for the null terminator
    char* copy = (char*)malloc(len);
    if (copy != NULL) {
        strcpy(copy, str);
    }
    return copy;
}

int DSL_StringCompare(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

void DSL_StringConcat(char* dest, const char* src) {
    strcat(dest, src);
}

// List management
void* DSL_ListAdd(void* list, size_t* size, void* item, size_t item_size) {
    void* new_list = realloc(list, (*size + 1) * item_size);
    if (new_list != NULL) {
        memcpy((char*)new_list + (*size * item_size), item, item_size);
        (*size)++;
    }
    return new_list;
}

void* DSL_ListRemove(void* list, size_t* size, size_t index, size_t item_size) {
    if (index >= *size) {
        return list;
    }
    
    void* new_list = malloc((*size - 1) * item_size);
    if (new_list != NULL) {
        memcpy(new_list, list, index * item_size);
        memcpy((char*)new_list + index * item_size, 
               (char*)list + (index + 1) * item_size, 
               (*size - index - 1) * item_size);
        (*size)--;
    }
    return new_list;
}

// Memory utilities
void* DSL_Pointer(void* ptr) {
    return ptr;
}


// Output function that supports variable arguments (like printf)
void DSL_Out(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);  // Use vprintf to handle variable arguments
    va_end(args);
}

// Input function with dynamic allocation, copying to a stack buffer, and freeing memory
char* DSL_In(const char* prompt) {
    printf("%s", prompt);
    
    // Dynamically allocate memory for a large enough buffer to store input
    size_t dynamicBufferSize = 256;  // You can adjust this size as needed
    char* dynamicBuffer = (char*)malloc(dynamicBufferSize);
    if (dynamicBuffer == NULL) {
        DSL_Crash_And_Burn("Failed to allocate memory for input");
    }

    // Get input from the user using fgets (can handle a large amount of input)
    fgets(dynamicBuffer, dynamicBufferSize, stdin);

    // Determine the actual length of the input (without newline)
    size_t inputLength = strcspn(dynamicBuffer, "\n");  // Find the position of the newline
    dynamicBuffer[inputLength] = '\0';  // Null-terminate the string and remove newline

    // Allocate stack buffer of the same size as the dynamic input
    static char stackBuffer[256];  // Stack buffer (maximum size 256)
    if (inputLength > sizeof(stackBuffer) - 1) {
        DSL_Crash_And_Burn("Input exceeds stack buffer size");
    }
    
    // Copy data from dynamic buffer to stack buffer
    memcpy(stackBuffer, dynamicBuffer, inputLength + 1);  // +1 to include null terminator

    // Free the dynamically allocated buffer
    free(dynamicBuffer);

    return stackBuffer;  // Return the stack buffer with the copied input
}

// Error handling
void DSL_Crash_And_Burn(const char* error_message) {
    fprintf(stderr, "Error: %s\n", error_message);
    abort();  // ABORT ABORT MAYDAY MADAY
}

#endif // DSL_STD_LIB_H
