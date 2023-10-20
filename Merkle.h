#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <string.h>
#include <inttypes.h>

// Define the structure of a Merkle tree node
typedef struct MerkleNode {
    uint64_t data;                   // Hash value for this node
    struct MerkleNode* left;    // Pointer to the left child node
    struct MerkleNode* right;   // Pointer to the right child node
} MerkleNode;


// Function to create a new Merkle tree node
MerkleNode* create_merkle_node(uint64_t data);

// Function to calculate a simple hash (summation for simplicity)
uint64_t simple_hash(uint64_t input1, uint64_t input2);

// Function to build a Merkle tree
MerkleNode* build_merkle_tree(uint64_t* transactions, int start, int end);

// Function to calculate the Merkle root hash value
uint64_t calculate_merkle_root(MerkleNode* root);

// Function to print the Merkle tree (in-order traversal)
void print_merkle_tree(MerkleNode* node);
