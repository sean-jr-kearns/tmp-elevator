#include <gtest/gtest.h>
#include "Elevator.hpp"

#include <vector>
#include <memory>

using Demo::Elevator;

class ElevatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        elevator = std::make_unique<Elevator>(10, 0, 10);
    }

    std::unique_ptr<Elevator> elevator;
};

TEST_F(ElevatorTest, ConstructorDoesNotThrow) {
    EXPECT_NO_THROW(Elevator(10, 0, 10));
}

TEST_F(ElevatorTest, TravelDurationBetweenFloorsCorrect) {
    int duration = elevator->get_travel_duration_between_floors(10, 1, 4);
    EXPECT_EQ(duration, 30);
}

TEST_F(ElevatorTest, TraverseFloorsEmptyReturnsFalse) {
    std::vector<int> empty;
    EXPECT_FALSE(elevator->traverse_floors(empty));
}

TEST_F(ElevatorTest, TraverseFloorsValidFloorsReturnsTrue) {
    std::vector<int> floors = {2, 5, 3};
    EXPECT_TRUE(elevator->traverse_floors(floors));
}

TEST_F(ElevatorTest, SetValidFloorTravelTime) {
    EXPECT_TRUE(elevator->set_floor_travel_time(10));
}

TEST_F(ElevatorTest, SetInvalidFloorTravelTimeNegative) {
    EXPECT_FALSE(elevator->set_floor_travel_time(-1));
}

TEST_F(ElevatorTest, SetValidStartingFloor) {
    EXPECT_TRUE(elevator->set_starting_floor(5));
}

TEST_F(ElevatorTest, SetInvalidStartingFloorNegative) {
    EXPECT_FALSE(elevator->set_starting_floor(-2));
}

TEST_F(ElevatorTest, SetInvalidStartingFloorAboveRange) {
    EXPECT_FALSE(elevator->set_starting_floor(100));
}

TEST_F(ElevatorTest, SetValidNumberOfFloors) {
    EXPECT_TRUE(elevator->set_number_of_floors(20));
}

TEST_F(ElevatorTest, SetInvalidNumberOfFloorsZero) {
    EXPECT_FALSE(elevator->set_number_of_floors(0));
}
