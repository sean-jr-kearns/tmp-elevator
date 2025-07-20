#include <string>
#include <sstream>
#include <vector>
#include <map>

#include <spdlog/spdlog.h>

namespace Demo::Utilities
{
    /**
     * @brief Parses string of delimited integers
     * @param[in] delimiter delimiter in string separating integers
     * @param[in] input the input string of partitioned numbers (1,2,3,4,...)
     * @returns ordered vector of integers
     */
    static inline std::vector<int> parse_string_on_delimiter(
        char delimiter, std::string input)
    {
        std::vector<int> values;
        std::stringstream ss(input);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            try 
            {
                values.push_back(std::stoi(token));
            } catch (...)
            {
                spdlog::error("> Invalid number: {}", token);
            }
        }

        return values;
    };

    /**
    * @brief converts string to spdlog::level::level_enum
    * @param level spdlog log level
    * @returns spdlog log level enumeration
    */
    static inline spdlog::level::level_enum string_to_log_level(const std::string& level) {
        static const std::map<std::string, spdlog::level::level_enum> level_map = {
            {"trace", spdlog::level::trace},
            {"debug", spdlog::level::debug},
            {"info", spdlog::level::info},
            {"warn", spdlog::level::warn},
            {"error", spdlog::level::err},
            {"critical", spdlog::level::critical},
            {"off", spdlog::level::off}
        };

        auto it = level_map.find(level);

        if (it != level_map.end()) {
            return it->second;
        }

    // Default to info level or handle error
    return spdlog::level::info;
}
}; // namespace Demo::Utilities