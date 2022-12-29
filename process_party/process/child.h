#ifndef PROCESS_PARTY_CHILD_H
#define PROCESS_PARTY_CHILD_H

#include <vector>

namespace process_party::process {
    class child {
    public:
        child() = delete;
        ~child() = default;

        explicit child(const std::string &cmd);
        child(const std::string &exe_path,
              const std::vector<std::string> &args);
        child(const std::filesystem::path &exe_path,
              const std::vector<std::string> &args);
        child(const std::string &exe_path,
              const std::vector<std::string> &args,
              const std::vector<std::pair<int, int>> &redirection_list);
        void wait();
        bool running();
        void detach();
        [[nodiscard]] int get_exit_code() const;
        void terminate() const;
    private:
        pid_t child_pid;
        std::string cmd;
        int exit_code;

        void launch_child(const std::string &cmd);
    };
}

#endif //PROCESS_PARTY_CHILD_H
