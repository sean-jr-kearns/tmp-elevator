#pragma once

#include <string>
#include <vector>

namespace Demo
{
    class Elevator 
    {
    public:
        //! @brief Default constructor (deleted)
        Elevator() = delete;

        /**
        * @brief Constructor with inputs
        * @param[in] starting_floor Floor that the elevator starts at
        */
        Elevator(int starting_floor);

        //! @brief Destructor
        ~Elevator();

        //! @brief Copy constructor (deleted)
        Elevator(const Elevator& that) = delete;

        //! @brief Copy assignment operator (deleted)
        Elevator& operator=(const Elevator& other) = delete;

        //! @brief Move constructor (default)
        Elevator(Elevator&& other) noexcept = default;

        //! @brief Move assignment operator (default)
        Elevator& operator=(Elevator&& other) noexcept = default;
    
    public:
        /**
        * @brief Travels ordered floors
        * @param[in] floors Floors to be traveled to
        * @return Returns true if traveled floors are acquired, otherwise returns false
        */
        bool traverse_floors(std::vector<int> floors);

    private: 
        /**
        * @brief Gets total travel time between two traversable floors
        * @param[in] floors Total number of floors traveled to
        * @return Returns true if travel time is acquired, otherwise returns false
        */
        int get_travel_duration_between_floors(int last_floor, int next_floor);

    private:
        //! Starting floor of the elevator
        int m_starting_floor;

        //! Last floor the elevator was at
        int m_last_floor;
    }; //class Elevator
}; //namespace Demo