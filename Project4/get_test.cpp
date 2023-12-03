#include <sstream>
#include <fstream>
#include "get_test.h"

namespace get_test
{
    static std::vector<fs::path> get_txt_files_names(const fs::path& directory)
    {
        std::vector<fs::path> files;

        if (fs::is_directory(directory))
            for (const auto& entry : fs::directory_iterator(directory))
                if (fs::is_regular_file(entry) && entry.path().extension() == ".txt")
                    files.push_back(entry.path());

        return files;
    }

    static test_t get_test_from_file(const fs::path& file)
    {
        std::vector<Command> commands;
        std::ifstream in(file);
        std::string line;

        std::getline(in, line);
        std::string description(line);

        while (std::getline(in, line))
            commands.emplace_back(line);

        return std::make_pair(description, commands);
    }

    std::vector<test_t> get_tests(const fs::path& directory)
    {
        auto files = get_txt_files_names(directory);
        std::vector<test_t> comands_sets;

        for (const auto& file : files)
            comands_sets.push_back(get_test_from_file(file));

        return comands_sets;
    }
}