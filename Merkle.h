#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure of a Merkle tree node
typedef struct MerkleNode {
    int data;                   // Hash value for this node
    struct MerkleNode* left;    // Pointer to the left child node
    struct MerkleNode* right;   // Pointer to the right child node
} MerkleNode;


// Function to create a new Merkle tree node
MerkleNode* create_merkle_node(int data);

// Function to calculate a simple hash (summation for simplicity)
int simple_hash(int input1, int input2);

// Function to build a Merkle tree
MerkleNode* build_merkle_tree(int* transactions, int start, int end);

// Function to calculate the Merkle root hash value
int calculate_merkle_root(MerkleNode* root);

// Function to print the Merkle tree (in-order traversal)
void print_merkle_tree(MerkleNode* node);
