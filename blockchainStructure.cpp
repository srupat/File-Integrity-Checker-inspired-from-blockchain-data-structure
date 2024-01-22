#define _CRT_SECURE_NO_WARNINGS
#include "Merkle.h"
#include "BlockChain.h"
#include "FileHashing.h"

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
    T1->priority = -1;
    T1->transactions = NULL;
    T1->numTransactions = 0;

    int choice = 0;
    do {
        printf("\n--Menu--\n"
            "0. Exit\n"
            "1. Print blockchain contents\n"
            "2. Create a context\n"
            "3. Integrity check\n"
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
        case 3:
            integrity_check(T1);
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