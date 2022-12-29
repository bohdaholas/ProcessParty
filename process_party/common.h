#ifndef PROCESS_PARTY_COMMON_H
#define PROCESS_PARTY_COMMON_H

constexpr int UNIX_ERR_CODE = -1;

//#define IS_WINDOWS (#ifdef _WIN64)
#define IS_WINDOWS (defined(WIN32)     ||  \
                    defined(_WIN32)    ||  \
                    defined(__WIN32__) ||  \
                    defined(__NT__))
#define IS_MACOS   (defined(__APPLE__))
#define IS_LINUX   (defined(__linux))

#if IS_WINDOWS
#define NUM_T DWORD
#define ENV_DELIM ";"
#define FS_DELIM "\\"
#elif IS_LINUX
#define NUM_T int
#define ENV_DELIM ":"
#define FS_DELIM "/"
#elif IS_MACOS
#define NUM_T int
#endif

#include <fcntl.h>
#include <sys/ipc.h>
#include <fstream>

enum creation_mode_t {
    create_only,
    open_or_create,
    open_only
};

enum ipc_type_t {
    ipc_file,
    ipc_shared_memory,
    ipc_anonymous
};

inline bool file_exists(const std::string& filename) {
    std::ifstream file(filename.c_str());
    return file.good();
}

inline int get_creation_mode(creation_mode_t creation_mode,
                             ipc_type_t ipc_type) {
    switch (creation_mode) {
        case create_only:
            switch (ipc_type) {
                case ipc_file:
                    return O_CREAT | O_EXCL;
                case ipc_shared_memory:
                case ipc_anonymous:
                    return IPC_CREAT | IPC_EXCL;
            }
            break;
        case open_or_create:
            switch (ipc_type) {
                case ipc_file:
                    return O_CREAT;
                case ipc_shared_memory:
                case ipc_anonymous:
                    return IPC_CREAT;
            }
            break;
        case open_only:
        default:
            return 0;
    }
}

enum access_mode_t {
    read_only = S_IRUSR,
    write_only = S_IWUSR,
    read_write = S_IRUSR | S_IWUSR
};

#endif //PROCESS_PARTY_COMMON_H
