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

enum creation_mode_t {
    create_only = IPC_CREAT | IPC_EXCL,
    open_or_create = IPC_CREAT,
    open_only = 0
};

enum access_mode_t {
    read_only = S_IRUSR,
    write_only = S_IWUSR,
    read_write = S_IRUSR | S_IWUSR
};

#endif //PROCESS_PARTY_COMMON_H
