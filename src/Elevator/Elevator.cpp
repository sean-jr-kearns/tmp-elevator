#include "Elevator.hpp"

#include <string>
#include <vector>

#include <spdlog/spdlog.h>


Demo::Elevator::Elevator(
    int floor_travel_time, int starting_floor, int number_of_floors) :
    m_floor_travel_time(floor_travel_time),
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
    int travel_time, int last_floor, int next_floor)
{
    return abs(last_floor - next_floor) * travel_time;
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
            m_floor_travel_time, m_starting_floor, floors.front());
    std::string _floors_visited = std::to_string(m_starting_floor);

    for (std::vector<int>::iterator it = floors.begin(); it != floors.end(); ++it)
    {
        spdlog::info("Traveling between floors {} and {}", m_last_floor, *it);

        int _travel_duration = Demo::Elevator::get_travel_duration_between_floors(
            m_floor_travel_time, m_last_floor, *it);
    
        _total_travel_duration += _travel_duration;
        _floors_visited += (", " + std::to_string(*it));

        spdlog::info("Took {} seconds to reach floor {}", _travel_duration, *it);
    }

    spdlog::info("{} {}", _total_travel_duration, _floors_visited);

    return true;
};


bool Demo::Elevator::set_floor_travel_time(int travel_time)
{
    if (travel_time < 0)
    {
        spdlog::warn("Invalid floor_travel_time.");
        return false;
    }

    m_floor_travel_time = travel_time;

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

    m_floor_travel_time = number_of_floors;

    return true;
};