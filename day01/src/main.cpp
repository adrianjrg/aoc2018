#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

std::set<int> visited;
bool repeat_found = false;
int repeated_frequency;

int calculate_frequencies(std::vector<std::string> lines, int start = 0){
    int sum = start;

    for(auto&& line : lines){
        // Get int from line
        sum += std::stoi(line);

        // If frequncy is unique, add it to set
        // else repeated frequency is found
        if(visited.find(sum) == visited.end()){
            visited.insert(sum);
        } else {
            // Make sure the first oneif kept
            if(!repeat_found){
                repeated_frequency = sum;
            }
            repeat_found = true;
        }
    }

    return sum;
}

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
    int sum = calculate_frequencies(lines, 0);
    std::cout << "Part 1 - sum: " << sum << std::endl; 
    
    while(!repeat_found){
        sum = calculate_frequencies(lines, sum);
    }
    std::cout << "Part 2 - first repeated frequency: " << repeated_frequency << std::endl;
}
