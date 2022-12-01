#ifndef PROCESS_PARTY_ENVIRONMENT_H
#define PROCESS_PARTY_ENVIRONMENT_H

#include <vector>
#include <unordered_map>
#include <filesystem>

namespace process_party {
    namespace process {
        class environment {
        public:
            environment();
            ~environment();

            char **get_raw();
            void set_env(const std::string &key, const std::string &value);
            void add_to_env(const std::string &key, const std::string &value);

        private:
            size_t count_vars();

            std::unordered_map<std::string, std::string> environment_map;
            char **raw_environment_map;
        };
    }

    namespace this_process {
        int get_id();
        process_party::process::environment get_environment();
        std::vector<std::filesystem::path> path();
    }
}


#endif //PROCESS_PARTY_ENVIRONMENT_H
