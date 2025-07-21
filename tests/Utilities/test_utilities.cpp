#include <gtest/gtest.h>
#include "Utilities.hpp"

using Demo::Utilities::parse_string_on_delimiter;

TEST(ParseStringOnDelimiterTest, BasicCommaSplit) 
{
    //SETUP
    char delimiter = ',';
    std::string input = "1,2,3,4";
    std::vector<int> expected = {1, 2, 3, 4};
    //ACT
    auto result = parse_string_on_delimiter(delimiter, input);
    //ASSERT
    EXPECT_EQ(result, expected);
}

TEST(ParseStringOnDelimiterTest, SpaceAndTabSplit) 
{
    //SETUP
    char delimiter = '\t';
    std::string input = "10\t20\t30";
    std::vector<int> expected = {10, 20, 30};
    //ACT
    auto result = parse_string_on_delimiter(delimiter, input);
    //ASSERT
    EXPECT_EQ(result, expected);
}

TEST(ParseStringOnDelimiterTest, EmptyString) 
{
    //SETUP
    char delimiter = ',';
    std::string input = "";
    //ACT
    auto result = parse_string_on_delimiter(delimiter, input);
    //ASSERT
    EXPECT_TRUE(result.empty());
}

TEST(ParseStringOnDelimiterTest, NonNumericPartsIgnored) 
{
    //SETUP
    char delimiter = ',';
    std::string input = "1,2,x,4";
    std::vector<int> expected = {1, 2, 4};
    //ACT
    auto result = parse_string_on_delimiter(delimiter, input);
    //ASSERT
    EXPECT_EQ(result, expected);
}
