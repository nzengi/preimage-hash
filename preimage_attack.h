#ifndef PREIMAGE_ATTACK_H
#define PREIMAGE_ATTACK_H

#include <string>

// Preimage saldırısı için bir hash çıktısına karşılık gelen girdiyi bul
std::string find_preimage_in_range(const std::string& target_hash, uint64_t start, uint64_t end);

#endif // PREIMAGE_ATTACK_H
