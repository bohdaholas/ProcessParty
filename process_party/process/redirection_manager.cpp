#include <iostream>
#include "redirection_manager.h"

process_party::process::redirection_manager::~redirection_manager() {
    for (int file_fd : close_after) {
        close(file_fd);
    }
}

int process_party::process::redirection_manager::redirect() const {
    for (int pipe_fd : close_before) {
        if (close(pipe_fd) == -1) {
            std::cerr << "Failed redirection to pipe";
            return -1;
        }
    }
    if (stdin_fd != STDIN_FILENO) {
        if (redirect_std_fd(STDIN_FILENO, stdin_fd) == -1) {
            std::cerr << "Failed to redirect stdin";
            return -1;
        }
    }
    if (stdout_fd != STDOUT_FILENO) {
        if (redirect_std_fd(STDOUT_FILENO, stdout_fd) == -1) {
            std::cerr << "Failed to redirect stdout";
            return -1;
        }
    }
    if (stderr_fd != STDERR_FILENO) {
        if (redirect_std_fd(STDERR_FILENO, stderr_fd) == -1) {
            std::cerr << "Failed to redirect stderr";
            return -1;
        }
    }
    return 0;
}

int process_party::process::redirection_manager::redirect_std_fd(int std_fd, int file_fd) {
    if (file_fd == -1) {
        return -1;
    }
    if (close(std_fd) == -1) {
        return -1;
    }
    dup2(file_fd, std_fd);
    return 0;
}

void process_party::process::redirection_manager::set_stdin(const std::string &filename) {
    stdin_fd = open(filename.c_str(), O_RDONLY);
    close_after.push_back(stdin_fd);
}

void process_party::process::redirection_manager::set_stdout(const std::string &filename) {
    stdout_fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR);
    close_after.push_back(stdout_fd);
}

void process_party::process::redirection_manager::set_stderr(const std::string &filename) {
    stderr_fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR);
    close_after.push_back(stderr_fd);
}

void process_party::process::redirection_manager::set_stdin(FILE *fptr) {
    stdin_fd = fileno(fptr);
}

void process_party::process::redirection_manager::set_stdout(FILE *fptr) {
    stdout_fd = fileno(fptr);
}

void process_party::process::redirection_manager::set_stderr(FILE *fptr) {
    stderr_fd = fileno(fptr);
}

void process_party::process::redirection_manager::set_stdin(const pipe_stream &pipe) {
    stdin_fd = pipe.read_fd;
    close_before.push_back(pipe.write_fd);
}

void process_party::process::redirection_manager::set_stdout(const pipe_stream &pipe) {
    stdout_fd = pipe.write_fd;
    close_before.push_back(pipe.read_fd);
}

void process_party::process::redirection_manager::set_stderr(const pipe_stream &pipe) {
    stdout_fd = pipe.write_fd;
    close_before.push_back(pipe.read_fd);
}
