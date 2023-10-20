#define _CRT_SECURE_NO_WARNINGS
#include"Merkle.h"
#include<iostream>

struct block {
    int numTransactions;
    int* transactions;
    char** FileHashes;
    uint64_t prevHash;
    uint64_t currentHash;
    struct block* link;
};

// Function to calculate the hash value of a file
int calculate_file_hash(const char* file_path) {
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


block* create_Block(block* T1, int num_transactions) {
    T1->numTransactions++;

    block* temp = T1;

    while (temp->link != NULL) {
        temp = temp->link;
    }
    block* new_block = (block*)malloc(sizeof(block));
    temp->link = new_block;
    new_block->link = NULL;

    new_block->FileHashes = (char**)malloc(sizeof(char*) * num_transactions);
    for (int i = 0; i < num_transactions; i++) {
        new_block->FileHashes[i] = (char*)malloc(sizeof(char) * 100);
    }

    new_block->numTransactions = num_transactions;
    new_block->transactions = (int*)malloc(sizeof(int) * num_transactions);
    new_block->currentHash = 0;
    new_block->prevHash = 0;
    return new_block;
}

void configure_block(block* T1, block* T) {
    block* temp = T1;
    while (temp->link != T) {
        temp = temp->link;
    }
    T->prevHash = temp->currentHash;
    temp = T;
    char c;
    printf("Enter the File Paths for transactions:\n ");
    for (int i = 0; i < T->numTransactions; i++) {
        int size = sizeof(T->FileHashes[i]);
        printf("Enter the file path: ");

        while ((c = getchar()) != 10) {}

        fgets(T->FileHashes[i], 100, stdin);
        if (T->FileHashes[i] == NULL) {
            perror("Error reading file path");
        }

        // Remove any trailing whitespace, including newline characters
        size_t len = strlen(T->FileHashes[i]);
        while (len > 0 && (T->FileHashes[i][len - 1] == '\n' || T->FileHashes[i][len - 1] == '\r')) {
            T->FileHashes[i][--len] = '\0';
        }

        T->transactions[i] = calculate_file_hash(T->FileHashes[i]);
    }

    // Build the Merkle tree
    MerkleNode* merkle_root = build_merkle_tree(T->transactions, 0, T->numTransactions - 1);
    printf("Merkle Tree (in-order traversal): ");
    print_merkle_tree(merkle_root);
    printf("\n");

    T->currentHash = calculate_merkle_root(merkle_root);
    printf("%d", T->currentHash);
}

void print_block(block* T) {

    printf("\nContents of created block...\n");
    printf("Previous Hash: %d\n", T->prevHash);
    printf("Current Hash : %d\n", T->currentHash);
    printf("List of file paths : \n");
    for (int i = 0; i < T->numTransactions; i++) {
        printf("File path %d: %s\n", i + 1, T->FileHashes[i]);
    }

    printf("Number of transactions : %d\n", T->numTransactions);
    printf("Transaction List...\n");

    for (int i = 0; i < T->numTransactions; i++) {
        printf("    Transaction - %d\n", T->transactions[i]);
    }
}

void print_blockchain(block* T1) {
    block* T = T1->link;
    for (int i = 0; i < T1->numTransactions; i++) {
        print_block(T);
        T = T->link;
    }
    printf("\n...End of chain...");
}

int main() {

    //Keeps data of blockchain members 
    block* T1 = (block*)malloc(sizeof(block));
    T1->currentHash = 0;
    T1->prevHash = 0;
    T1->link = NULL;
    T1->transactions = NULL;
    T1->numTransactions = 0;

    int choice = 0;
    do {
        printf("\n--Menu--\n"
            "0. Exit\n"
            "1. Print blockchain contents\n"
            "2. Make a Transaction Context\n"
            "Enter choice: "
        );
        scanf_s("%d", &choice);

        switch (choice) {
        case 0:
            printf("Exiting...\n");
            exit(0);

        case 1:
            print_blockchain(T1);
            break;
        case 2:
            int num_transactions;
            printf("Enter the number of transactions: ");
            scanf_s("%d", &num_transactions);

            block* T = create_Block(T1, num_transactions);
            configure_block(T1, T);
            break;
        }

    } while (choice);


}