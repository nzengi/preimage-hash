#include "asa_attack.h"
#include "hash_functions.h"
#include "parallel_processing.h"
#include <iostream>
#include <omp.h>

// Bitcoin adresinin Base58 formunu kontrol eder
bool check_vanity_address(const std::string& address) {
    return address.rfind("13zb1hQbWV", 0) == 0;  // "13zb1hQbWV" ile başlıyorsa true döner
}

std::string perform_vanity_search(uint64_t start, uint64_t end) {
    std::string found_address;
    bool address_found = false;

    // Dinamik iş yükü dengeleme ile 8 thread kullanarak paralel arama yap
    #pragma omp parallel for schedule(dynamic) num_threads(8)
    for (uint64_t i = start; i <= end; ++i) {
        if (address_found) {
            continue;  // Başka bir thread adres bulduysa diğer işlemler durdurulur
        }

        std::string private_key = std::to_string(i);  // Özel anahtarı hex formda stringe çevir

        // Public key oluştur
        std::string public_key = sha256(private_key);  // SHA-256 hash fonksiyonu kullanarak public key hesaplama
        std::string bitcoin_address = ripemd160(public_key);  // Bitcoin adresini oluştur

        if (check_vanity_address(bitcoin_address)) {
            #pragma omp critical
            {
                if (!address_found) {
                    found_address = bitcoin_address;
                    address_found = true;
                    std::cout << "Vanity address bulundu! Adres: " << bitcoin_address << ", Özel Anahtar: 0x" << std::hex << i << std::endl;
                }
            }
        }

        // İlerleme bilgisi yazdırılır
        if (i % 0x1000000 == 0) {
            std::cout << "İlerleme: 0x" << std::hex << i << " girdisi denendi..." << std::endl;
        }
    }

    if (!address_found) {
        std::cout << "Belirtilen aralıkta uygun bir vanity address bulunamadı." << std::endl;
    }

    return found_address;
}

int main() {
    uint64_t start_range = 0x35000000000000000;
    uint64_t end_range = 0x35fffffffffffffff;

    std::cout << "Vanity search başlatılıyor..." << std::endl;
    perform_vanity_search(start_range, end_range);

    return 0;
}
