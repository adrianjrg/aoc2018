#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

bool areReactive(char& a, char& b){
    return abs(a - b) == 32;
}

std::string reactString(std::string input){
    
    for(int i = 0; i < input.size() - 1; i++)
    {
        if(areReactive(input[i], input[i + 1])){
            input.erase(i, 2);
            i = std::max(-1, i - 2); // -1 as i++ after loop
        }
    }
    
    return input;
} 

int main(int argc, char** args){
    // Import input file
    std::ifstream input("input05.txt");

    std::vector<std::string> lines;
    std::string line;
    while(std::getline(input, line)){
        lines.push_back(line);
    }
    input.close();

    // Everything is one one line
    auto part1 = reactString(lines[0]);
    std::cout << "Part 1: length left: " << part1.size() << std::endl;

    int shortestReaction = 99999;
    for(size_t i = 0; i < 26; i++)
    {
        char letter = 'A' + i;
        std::string str(lines[0]);
        str.erase(std::remove_if(str.begin(), 
                                 str.end(), 
                                 [letter](unsigned char x){return x == letter || x == (letter + 32);}),
                  str.end());
        auto shortened = reactString(str);
        shortestReaction = std::min(shortestReaction, (int)shortened.size());
    }
    std::cout  << "Part 2: shortest length: " << shortestReaction << std::endl;
}
