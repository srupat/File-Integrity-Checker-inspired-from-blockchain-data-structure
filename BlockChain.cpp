#include "BlockChain.h"
#include "FileHashing.h"
#include "Merkle.h"


Block* create_Block(Block* T1, int num_transactions) {
    T1->numTransactions++;

    Block* temp = T1;

    while (temp->link != NULL) {
        temp = temp->link;
    }
    Block* new_block = (Block*)malloc(sizeof(Block));
    temp->link = new_block;
    new_block->link = NULL;

    new_block->FileHashes = (char**)malloc(sizeof(char*) * num_transactions);
    for (int i = 0; i < num_transactions; i++) {
        new_block->FileHashes[i] = (char*)malloc(sizeof(char) * 100);
    }

    new_block->numTransactions = num_transactions;
    new_block->transactions = (uint64_t*)malloc(sizeof(uint64_t) * num_transactions);
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
    printf("Previous Hash: %" PRIu64 "\n", T->prevHash);
    printf("Current Hash : %" PRIu64 "\n", T->currentHash);
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