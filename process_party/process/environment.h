#ifndef PROCESS_PARTY_ENVIRONMENT_H
#define PROCESS_PARTY_ENVIRONMENT_H

#include <vector>
#include <unordered_map>
#include <filesystem>

namespace process_party {
    namespace process {
        // TODO: fix bugs + write tests
        class environment {
        public:
            environment();
            ~environment();

            char **get_raw();
            void set_env(const std::string &key, const std::string &value);
            void clear_env();
            std::string get_env(const std::string &key);
            bool is_env_present(const std::string &key);
            void add_to_env(const std::string &key, const std::string &value);
            size_t count_vars();
            bool empty();

        private:
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
