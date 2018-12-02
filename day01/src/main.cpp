#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** args){
    // Import input file
    std::ifstream input("input.txt");

    std::vector<std::string> lines;
    std::string line;
    while(std::getline(input, line)){
        lines.push_back(line);
    }
    input.close();

    // Process lines
    int sum = 0;
    for(auto&& line : lines)
    {
        int line_value = std::stoi(line);
        sum += line_value;
    }
    std::cout << "Part 1 - sum: " << sum << std::endl; 
}
