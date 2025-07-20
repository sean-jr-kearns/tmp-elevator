#include <gtest/gtest.h>
#include "Elevator.hpp"

#include <vector>
#include <memory>

using Demo::Elevator;

class ElevatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        elevator = std::make_unique<Elevator>(0);
    }

    std::unique_ptr<Elevator> elevator;
};

TEST_F(ElevatorTest, ConstructorDoesNotThrow) {
    //SETUP
    //ACT
    //ASSERT
    EXPECT_NO_THROW(Elevator(0));
}

TEST_F(ElevatorTest, TraverseFloorsEmptyReturnsFalse) {
    //SETUP
    std::vector<int> empty;
    //ACT
    //ASSERT
    EXPECT_FALSE(elevator->traverse_floors(empty));
}

TEST_F(ElevatorTest, TraverseFloorsValidFloorsReturnsTrue) {
    //SETUP
    std::vector<int> floors = {2, 5, 3};
    //ACT
    //ASSERT
    EXPECT_TRUE(elevator->traverse_floors(floors));
}