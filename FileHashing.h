#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "BlockChain.h"

// Function to calculate the hash value of a file
uint64_t calculate_file_hash(const char* file_path);

void integrity_check(Block* block);