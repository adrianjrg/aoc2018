#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct repeat_char {
    char letter;
    int count = 0;
};

std::vector<repeat_char> find_repeats(std::string id){
    std::vector<repeat_char> repeats;

    for(auto&& c : id)
    {
        bool char_found = false;        
        for(auto&& r : repeats)
        {
            if(r.letter == c){
                r.count++;
                char_found = true;
            }
        }

        if(!char_found){
            repeat_char t = {c, 1};
            repeats.push_back(t);
        }
    }
    return repeats;
}

int get_char_difference_count(std::string l1, std::string l2){
    int differences = 0;
    for(size_t i = 0; i < l1.size(); i++)
    {
        int diff = l1[i] - l2[i];
        if(diff != 0)
            differences++;
    }
    return differences;
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
    int double_repetition = 0;
    int triple_repetition = 0;

    for(auto&& line : lines)
    {
        auto repeats = find_repeats(line);

        bool add_double = false;
        bool add_triple = false;
        for(auto&& r : repeats)
        {
            if (r.count == 2) {
                add_double = true;
            }
            if (r.count == 3) {
                add_triple = true;;
            }
        }
        if (add_double)
            double_repetition++;
        if (add_triple)
            triple_repetition++;
    }

    int custom_checksum = double_repetition * triple_repetition;
    std::cout << "Part 1 - checksum: " << custom_checksum << std::endl;

    std::string s1;
    std::string s2;
    for(size_t i = 0; i < lines.size(); i++)
    {
        for(size_t j = i + 1; j < lines.size(); j++)        
        {
            auto diff = get_char_difference_count(lines[i], lines[j]);
            if(diff == 1){
                s1 = lines[i];
                s2 = lines[j];
            }
        }   
    }

    std::cout << "Part 2 - shared characters: ";
    for(size_t i = 0; i < s1.size(); i++)
    {
        if(s1[i] - s2[i] == 0)
            std::cout << s1[i];
    }
    std::cout << std::endl;
}