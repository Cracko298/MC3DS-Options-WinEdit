#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>

void modifyFile(const std::string& filePath) {
    std::vector<uint8_t> targetBytes = {0xD8, 0x05, 0x00, 0x00, 0x6D, 0x70};
    std::ifstream file(filePath, std::ios::binary);
    if (file) {
        std::vector<uint8_t> content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        if (content.size() >= targetBytes.size() &&
            std::equal(targetBytes.begin(), targetBytes.end(), content.begin())) {

            std::replace(content.begin(), content.end(), static_cast<uint8_t>(0x00), static_cast<uint8_t>(0x20));
            std::ofstream modifiedFile(filePath, std::ios::binary);
            
            modifiedFile.write(reinterpret_cast<const char*>(content.data()), content.size());
            std::cout << "Modification successful." << std::endl;
        } else {
            std::cout << "Target bytes not found, no modification needed." << std::endl;
        }
    } else {
        std::cerr << "Error opening file." << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::string filePath = "options.txt";
    
    if(argc == 2) filePath = argv[1];

    modifyFile(filePath);

    return 0;
}
