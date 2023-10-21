#include"Merkle.h"

MerkleNode* create_merkle_node(uint64_t data) {
    MerkleNode* node = (MerkleNode*)malloc(sizeof(MerkleNode));
    if (node == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to calculate a simple hash (summation for simplicity)
uint64_t simple_hash(uint64_t input1, uint64_t input2) {
        // Choose two large prime numbers (you can replace these with other primes)
        uint64_t prime1 = 4294967311; // A large prime less than 2^32
        uint64_t prime2 = 4294967357; // Another large prime less than 2^32

        // Use a combination of multiplication, addition, and bitwise operations
        uint64_t hash = ((input1 * prime1) + (input2 * prime2)) ^ ((input1 ^ input2) << 32);
        
        // Mix the bits for improved distribution
        hash = (hash ^ (hash >> 33)) * 0xFF51AFD7ED558CCDull;
        hash = (hash ^ (hash >> 33)) * 0xC4CEB9FE1A85EC53ull;
        hash = hash ^ (hash >> 33);

        return hash;
}

// Function to build a Merkle tree
MerkleNode* build_merkle_tree(uint64_t* transactions, int start, int end) {

    if (start == end) {
        return create_merkle_node(transactions[start]);
    }

    int mid = (start + end) / 2;

    MerkleNode* left_child = build_merkle_tree(transactions, start, mid);
    MerkleNode* right_child = build_merkle_tree(transactions, mid + 1, end);

    // Calculate the hash value for the current node
    int hash_value = simple_hash(left_child->data, right_child->data);

    MerkleNode* current_node = create_merkle_node(hash_value);
    current_node->left = left_child;
    current_node->right = right_child;

    return current_node;
}

// Function to calculate the Merkle root hash value
uint64_t calculate_merkle_root(MerkleNode* root) {
    return root->data;
}

// Function to print the Merkle tree (in-order traversal)
void print_merkle_tree(MerkleNode* node) {
    if (node != NULL) {
        print_merkle_tree(node->left);
        printf("%" PRIu64" ", node->data);
        print_merkle_tree(node->right);
    }
}
