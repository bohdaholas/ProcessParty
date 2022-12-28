#ifndef PROCESS_PARTY_REDIRECTION_MANAGER_H
#define PROCESS_PARTY_REDIRECTION_MANAGER_H

#include <unistd.h>
#include <string>
#include <fcntl.h>

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

        int redirect() const;

    private:
        int stdin_fd = STDIN_FILENO;
        int stdout_fd = STDOUT_FILENO;
        int stderr_fd = STDERR_FILENO;

        int stdin_opened = false;
        int stdout_opened = false;
        int stderr_opened = false;

        static int redirect_std_fd(int std_fd, int file_fd);
    };
}

#endif //PROCESS_PARTY_REDIRECTION_MANAGER_H
