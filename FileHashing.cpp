#include "FileHashing.h"

// Function to calculate the hash value of a file
uint64_t calculate_file_hash(const char* file_path) {
    FILE* file;
    if (fopen_s(&file, file_path, "rb") != 0) {
        perror("Error opening file");
        exit(1);
    }

    uint64_t hash_value = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        hash_value = (hash_value * 31) + c; // A simple hash function
    }

    fclose(file);

    return hash_value;
}

void integrity_check(Block* head) {
    Block* _trav = head->link;

    for (int i = 1; _trav; i++) {
        printf("\n---Block-%d---\n",i);
        for (int j = 0; j < _trav->numTransactions; j++) {
            uint64_t _hash = calculate_file_hash(_trav->FileHashes[j]);
            if (_hash != _trav->transactions[j])
                printf("\tFile %d affected.\n", j);
        }
        _trav = _trav->link;
    }
    printf("...End of chain...");
}
    