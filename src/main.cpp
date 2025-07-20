#include "Elevator.hpp"

#include <string>
#include <vector>
#include <sstream>

#include <spdlog/spdlog.h>

// Consider using boost instead in the future 
// Stackoverflow /right-way-to-split-an-stdstring-into-a-vectorstring
std::vector<int> parse_comma_numbers(const std::string& input) {
    std::vector<int> numbers;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ',')) {
        try 
        {
            numbers.push_back(std::stoi(token));
        } catch (...)
        {
            spdlog::error("Invalid number: {}", token);
        }
    }

    return numbers;
}

int main(int argc, char* argv[]) 
{
    spdlog::info("Executing elevator program {} with {} arguments", argv[0], argc);

    if (argc != 4) { // 4 includes the program name itself
        spdlog::error("Incorrect number of arguments found ({})", argv[0]);
        spdlog::error("Expected 4");
        return 1; // Indicate an error
    }

    int number_of_floors;
    int starting_floor;
    std::vector<int> floors;

    try 
    {
        number_of_floors = std::stoi(argv[1]);
        starting_floor = std::stoi(argv[2]);
        floors = parse_comma_numbers(argv[3]);
    }
    catch (...)
    {
        return 1;
    }

    Demo::Elevator demo_elevator(starting_floor, number_of_floors);
    
    demo_elevator.traverse_floors(floors);

    return 0;
}