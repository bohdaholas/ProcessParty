#ifndef PROCESS_PARTY_REDIRECTION_MANAGER_H
#define PROCESS_PARTY_REDIRECTION_MANAGER_H

#include <unistd.h>
#include <string>
#include <vector>
#include <fcntl.h>
#include "process_party/interprocess/pipe_stream.h"

namespace process_party::process {
    class redirection_manager {
    public:
        redirection_manager() = default;

        ~redirection_manager();

        void set_stdin(const std::string &filename);

        void set_stdout(const std::string &filename);

        void set_stderr(const std::string &filename);

        void set_stdin(FILE *fptr);

        void set_stdout(FILE *fptr);

        void set_stderr(FILE *fptr);

        void set_stdin(const pipe_stream &pipe);

        void set_stdout(const pipe_stream &pipe);

        void set_stderr(const pipe_stream &pipe);

        int redirect() const;

    private:
        int stdin_fd = STDIN_FILENO;
        int stdout_fd = STDOUT_FILENO;
        int stderr_fd = STDERR_FILENO;

        std::vector<int> close_before{};
        std::vector<int> close_after{};

        static int redirect_std_fd(int std_fd, int file_fd);
    };
}

#endif //PROCESS_PARTY_REDIRECTION_MANAGER_H
