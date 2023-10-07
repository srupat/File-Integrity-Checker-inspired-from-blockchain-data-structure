#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the hash value of a file
unsigned int calculate_file_hash(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    unsigned int hash_value = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        hash_value = (hash_value * 31) + c; // A simple hash function
    }

    fclose(file);

    return hash_value;
}