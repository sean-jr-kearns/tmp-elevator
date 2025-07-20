#include "Elevator.hpp"
#include "Utilities.hpp"

#include <string>
#include <vector>
#include <sstream>

#include "cxxopts.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

int main(int argc, char* argv[]) 
{
    // Initialize cxxopts options 
    cxxopts::Options options("ElevatorSim", "Elevator simulator");

    options.add_options()
        ("s,starting_floor", "Starting floor", cxxopts::value<int>()->default_value("0"))
        ("t,floors", "Floors to traverse", cxxopts::value<std::string>()->default_value("1,10,20,30,40"))
        ("l,log_level", "Log level (trace, debug, info, warn, err, critical, off)", 
                cxxopts::value<std::string>()->default_value("info"))
        ("f,log_file", "Log file path (optional)", 
                cxxopts::value<std::string>())
        ("h,help", "Print help");

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        spdlog::info(options.help());
        return 0;
    }

    // Handle spdlog log level and file options
    spdlog::level::level_enum log_level = Demo::Utilities::string_to_log_level(
        result["log_level"].as<std::string>());

    spdlog::set_level(log_level);

    if (result.count("log_file")) 
    {
        auto file_logger = spdlog::basic_logger_mt("file_logger", result["log_file"].as<std::string>());
        spdlog::set_default_logger(file_logger);
    }

    spdlog::info("> Logging initialized with level: {}", result["log_level"].as<std::string>());
    spdlog::info("> Elevator config:");
    spdlog::info("\t> Starting floor: {}", result["starting_floor"].as<int>());
    spdlog::info("\t> Floors to traverse: {}", result["floors"].as<std::string>());

    // Initialize script elevator variables
    char delimeter = ',';
    int starting_floor = result["starting_floor"].as<int>();
    std::vector<int> floors = Demo::Utilities::parse_string_on_delimiter(
        delimeter, result["floors"].as<std::string>());

    // Run demo elevator simulation 
    // (e.g. traverse floors and log execution details)
    Demo::Elevator demo_elevator(starting_floor);
    
    demo_elevator.traverse_floors(floors);

    return 0;
}