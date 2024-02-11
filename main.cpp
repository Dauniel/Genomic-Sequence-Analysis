#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Sequence {
    std::string header;
    std::string sequence;
};

std::vector<Sequence> readFastaFile(const std::string& filename) {
    std::vector<Sequence> sequences;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return sequences;
    }

    Sequence currentSeq;
    std::string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!currentSeq.sequence.empty()) {
                sequences.push_back(currentSeq); // Save the previous sequence
                currentSeq = Sequence(); // Start a new sequence
            }
            currentSeq.header = line.substr(1); // Skip the '>' character
        } else {
            currentSeq.sequence += line;
        }
    }
    if (!currentSeq.sequence.empty()) {
        sequences.push_back(currentSeq); // Save the last sequence
    }

    return sequences;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <FASTA file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Sequence> sequences = readFastaFile(filename);

    for (const auto& seq : sequences) {
        std::cout << "Header: " << seq.header << std::endl;
        std::cout << "Sequence: " << seq.sequence << std::endl;
        std::cout << "---------------------" << std::endl;
    }

    return 0;
}
