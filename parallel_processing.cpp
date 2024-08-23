#include "parallel_processing.h"
#include "hash_functions.h"
#include <omp.h>
#include <iostream>

// Paralel işlem ile preimage saldırısı
std::string parallel_preimage_attack(const std::string& target_hash) {
    std::string found_preimage;
    bool preimage_found = false;

    #pragma omp parallel for num_threads(8)
    for (uint64_t i = 0; i < UINT64_MAX; ++i) {
        if (preimage_found) continue;

        std::string candidate = std::to_string(i);
        std::string hash = ripemd160(candidate);

        if (hash == target_hash) {
            #pragma omp critical
            {
                if (!preimage_found) {
                    found_preimage = candidate;
                    preimage_found = true;
                    std::cout << "Preimage bulundu: " << candidate << std::endl;
                }
            }
        }

        if (i % 1000000 == 0) {
            std::cout << "İlerleme: 0x" << std::hex << i << std::endl;
        }
    }

    if (!preimage_found) {
        std::cout << "Preimage bulunamadı." << std::endl;
    }

    return found_preimage;
}
