#include "preimage_attack.h"
#include "asa_attack.h"
#include <iostream>

std::string find_preimage_in_range(const std::string& target_hash, uint64_t start, uint64_t end) {
    std::string possible_input;
    uint64_t operation_count = 0;

    for (uint64_t i = start; i <= end; ++i) {
        possible_input = std::to_string(i);
        std::string manipulated_hash = manipulate_hash_function(possible_input);

        if (manipulated_hash == target_hash) {
            std::cout << "Preimage bulundu! Girdi: 0x" << std::hex << i << std::endl;
            return possible_input; // Preimage bulundu
        }

        // İşlem sayısını arttır
        operation_count++;

        // Her 1 milyar girdide bir ilerleme bilgisi yazdırılır
        if (operation_count % 1000000000 == 0) {
            std::cout << "İlerleme: 0x" << std::hex << i << " girdisi denendi..." << std::endl;
        }
    }
    
    return ""; // Preimage bulunamadı
}
