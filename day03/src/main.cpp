#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility>

void parseLine(std::string& line, int& id, int& x, int& y, int& width, int& height){
    // Pattern is:
    // #<id> @ <x>,<y>: <width>,<height>
    id =     std::stoi(line.substr(line.find('#') + 1));
    x =      std::stoi(line.substr(line.find('@') + 1));
    y =      std::stoi(line.substr(line.find(',') + 1));
    width =  std::stoi(line.substr(line.find(':') + 1));
    height = std::stoi(line.substr(line.find('x') + 1));
}

void setClaims(std::map<std::pair<int, int>, int>& claimedSquares, int& x, int& y, int& width, int& height){
    for(size_t i = 0; i < width; i++)
    {
        for(size_t j = 0; j < height; j++)
        {
            std::pair<int, int> coords(x + i, y + j);
            if(claimedSquares.find(coords) == claimedSquares.end()){
                claimedSquares.insert(std::pair<std::pair<int,int>,int> (coords, 1));
            } else {
                claimedSquares[coords]++;
            }
        }   
    }
}

bool isOverlapping(std::map<std::pair<int, int>, int>& claimedSquares, int& x, int& y, int& width, int& height){
    bool overlapping = false;
    for(size_t i = 0; i < width; i++)
    {
        for(size_t j = 0; j < height; j++)
        {
            std::pair<int, int> coords(x + i, y + j);
            if(claimedSquares[coords] != 1){
                return true;
            }
        }   
    }
    return overlapping;
}

int main(int argc, char** args){
    // Import input file
    std::ifstream input("input03.txt");

    std::vector<std::string> lines;
    std::string line;
    while(std::getline(input, line)){
        lines.push_back(line);
    }
    input.close();

    std::map<std::pair<int, int>, int> claimedSquares;

    int id, x, y, width, height;
    
    for(auto&& line : lines)
    {
        parseLine(line, id, x, y, width, height);
        setClaims(claimedSquares, x, y, width, height);
    }
    
    int overlaps = 0;
    for(auto&& pair : claimedSquares)
    {
        if(pair.second > 1){
            overlaps++;
        }
    }

    int nonOverlappingId = -1;
    for(auto&& line : lines)
    {
        parseLine(line, id, x, y, width, height);
        if(!isOverlapping(claimedSquares, x, y, width, height)){
            nonOverlappingId = id;
            break;
        }
    }

    std::cout << "Part 1 - overlaps: " << overlaps << std::endl;
    std::cout << "Part 2 - nonoverlapping id: " << nonOverlappingId << std::endl;
}