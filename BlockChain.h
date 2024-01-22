#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct block {
    int numTransactions;
    uint64_t* transactions;
    char** FileHashes;
    int priority;
    uint64_t prevHash;
    uint64_t currentHash;
    struct block* link;
}Block;

Block* create_Block(Block* T1, int num_transactions);

void configure_block(block* T1, block* T);

void print_block(block* T);
