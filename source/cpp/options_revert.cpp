#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <string.h>
#include <stdio.h>

void modifyFile(const std::string& filePath, const std::string& outputFilePath) {
    std::vector<uint8_t> targetBytes = {0xD8, 0x05, 0x00, 0x00, 0x6D, 0x70};
    std::ifstream file(filePath, std::ios::binary);
    if (file) {
        std::vector<uint8_t> content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        if (content.size() >= targetBytes.size() &&
            std::equal(targetBytes.begin(), targetBytes.end(), content.begin())) {

            std::replace(content.begin(), content.end(), static_cast<uint8_t>(0x00), static_cast<uint8_t>(0x20));
            std::ofstream modifiedFile(outputFilePath, std::ios::binary);

            if (modifiedFile) {
                modifiedFile.write(reinterpret_cast<const char*>(content.data()), content.size());
                std::cout << "Modification successful." << std::endl;
            } else {
                std::cerr << "Error creating '" << outputFilePath << "'. Check write permissions and disk space." << std::endl;
            }

        } else {
            std::cout << "Target bytes not found, no modification needed." << std::endl;
        }
    } else {
        std::cerr << "Error opening '" << filePath << "'. Is the path correct?" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::string filePath = "options.txt";
    std::string outputFilePath = filePath;

    // Help text following the Unix standards.
    if (argc == 2 && strcmp(argv[1],"--help") == 0) {
        std::cout << "Usage: options_revert [INPUT_PATH] [OUTPUT_PATH]" << std::endl << std::endl;

        std::cout << "Arguments:" << std::endl;
        std::cout << "  INPUT_PATH    Path to the input file. Default: 'options.txt'" << std::endl;
        std::cout << "  OUTPUT_PATH   Path to the output file. Input file will be overwritten if this argument wasn't specified." << std::endl;
        
        return 0;
    }

    if(argc >= 2) filePath = argv[1];
    if(argc == 3) outputFilePath = argv[2];

    if(argc > 3){
        std::cerr << "Too many arguments." << std::endl;
        return 1;
    }

    modifyFile(filePath, outputFilePath);

    return 0;
}
