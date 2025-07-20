#include "Elevator.hpp"
#include "ElevatorConstants.hpp"

#include <string>
#include <vector>

#include <spdlog/spdlog.h>

Demo::Elevator::Elevator(
    int starting_floor, int number_of_floors) :
    m_starting_floor(starting_floor),
    m_last_floor(starting_floor),
    m_number_of_floors(number_of_floors)
{
    spdlog::info("Elevator constructor called.");
};

Demo::Elevator::~Elevator()
{
    spdlog::info("Elevator destructor called.");
};

int Demo::Elevator::get_travel_duration_between_floors(
    int last_floor, int next_floor)
{
    return abs(last_floor - next_floor) * ElevatorConstants::kFloorTravelTime;
};
       
bool Demo::Elevator::traverse_floors(std::vector<int> floors)
{
    // Exit early if there are no floors
    if (floors.empty())
    {
        spdlog::warn("No floors found to traverse.");
        return false;
    }

    // Get travel duration from starting floor to first floor in floors 
    int _total_travel_duration = Demo::Elevator::get_travel_duration_between_floors(
        m_starting_floor, floors.front());
    std::string _floors_visited = std::to_string(m_starting_floor);

    for (std::vector<int>::iterator it = floors.begin(); it != floors.end(); ++it)
    {
        spdlog::info("Traveling between floors {} and {}", m_last_floor, *it);

        int _travel_duration = Demo::Elevator::get_travel_duration_between_floors(
            m_last_floor, *it);
    
        _total_travel_duration += _travel_duration;
        _floors_visited += (", " + std::to_string(*it));

        spdlog::info("Took {} seconds to reach floor {}", _travel_duration, *it);
    }

    spdlog::info("{} {}", _total_travel_duration, _floors_visited);

    return true;
};

bool Demo::Elevator::set_starting_floor(int starting_floor)
{
    if (starting_floor < 0 || starting_floor > m_number_of_floors)
    {
        spdlog::warn("Invalid starting floor.");
        return false;
    }

    m_starting_floor = starting_floor;

    return true;
};

bool Demo::Elevator::set_number_of_floors(int number_of_floors)
{
    if (number_of_floors <= 0)
    {
        spdlog::warn("Invalid number of floors. Elevator must have at " 
            "least 1 floor");
        return false;
    }

    m_number_of_floors = number_of_floors;

    return true;
};