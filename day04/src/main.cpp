#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility>

struct ShiftInfo{
    int year;
    int month;
    int day;
    int hour;
    int minute;

    bool operator < (const ShiftInfo& si) const {
        if(year != si.year)
            return year < si.year;
        if(month != si.month)
            return month < si.month;
        if(day != si.day)
            return day < si.day;
        if(hour != si.hour)
            return hour < si.hour;

        return minute < si.minute;
    }
};

void parseTimestamp(std::string& line, ShiftInfo& info, std::string& comment){
    // Pattern is:
    // [YYYY-MM-DD hh:mm] <action>
    info.year   = std::stoi(line.substr(1, 4));
    info.month  = std::stoi(line.substr(6, 2));
    info.day    = std::stoi(line.substr(9, 2));
    info.hour   = std::stoi(line.substr(12, 2));
    info.minute = std::stoi(line.substr(15, 2));

    comment = line.substr(19);
}

void parseComments(std::map<ShiftInfo, std::string>& shifts, 
                   std::map<int, std::map<int, int>>& guardSleepMap){
    int guardId;
    ShiftInfo startSleep;
    ShiftInfo endSleep;

    for(auto&& shift : shifts)
    {
        switch(shift.second[0]){
            case 'G': // New guard
                guardId = std::stoi(shift.second.substr(7));
                break;
            case 'f': // falls asleep
                startSleep = shift.first;
                break;
            case 'w': // wakes up
                endSleep = shift.first;
                for(size_t i = startSleep.minute; i < endSleep.minute; i++)
                {
                    guardSleepMap[guardId][i]++;
                }
                break;
            default:
                std::cout << "Something went wrong" << std::endl;
        }
    }
}

int main(int argc, char** args){
    // Import input file
    std::ifstream input("input04.txt");

    std::vector<std::string> lines;
    std::string line;
    while(std::getline(input, line)){
        lines.push_back(line);
    }
    input.close();

    std::map<ShiftInfo, std::string> shifts;
    ShiftInfo info;
    std::string comment;    
    for(auto&& line : lines)
    {
        parseTimestamp(line, info, comment);
        shifts.insert(std::pair<ShiftInfo, std::string>(info, comment));
    }

    // maps of <guardId, <minute, asleepCount>>
    std::map<int, std::map<int, int>> guardSleepMap;
    parseComments(shifts, guardSleepMap);

    int guardIdMostSleep;
    int mostMinutesSlept = 0;
    for(auto&& guardSleep : guardSleepMap)
    {
        int sumSleep = 0;
        for(auto&& minute : guardSleep.second)
        {
            sumSleep += minute.second;
        }
        if(sumSleep > mostMinutesSlept){
            guardIdMostSleep = guardSleep.first;
            mostMinutesSlept = sumSleep;
        }
    }
    
    int mostSleptMinute;
    int highestSleepOccurance = 0;
    for(auto&& minute : guardSleepMap[guardIdMostSleep])
    {
        if(minute.second > highestSleepOccurance){
            mostSleptMinute = minute.first;
            highestSleepOccurance = minute.second;
        }
    }    

    std::cout << "Part 1 - guardIdMostSleep * mostSleptMinute: " << guardIdMostSleep * mostSleptMinute << std::endl;

    int guardIdMostSleptPerMinute;
    int highestSleptMinute;
    int highestSleepPerMinute = 0;
    for(auto&& guardSleep : guardSleepMap)
    {
        for(auto&& minute : guardSleep.second)
        {
            if(minute.second > highestSleepPerMinute){
                guardIdMostSleptPerMinute = guardSleep.first;
                highestSleptMinute = minute.first;
                highestSleepPerMinute = minute.second;
            }
        }
    }

    std::cout << "Part 2 - guardIdMostSleptPerMinute * highestSleptMinute: " 
              << guardIdMostSleptPerMinute * highestSleptMinute
              << std::endl;
}
