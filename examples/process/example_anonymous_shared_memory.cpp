#include <iostream>
#include <cstring>
#include <process_party/interprocess.h>
#include <process_party/process.h>
#include <sys/wait.h>

namespace ppp = process_party::process;
namespace ppip = process_party::interprocess;

using namespace std;

int main(int argc, char **argv) {
    ppip::anonymous_shared_memory shm(getpagesize());
    ppip::mapped_region region(shm, 0, shm.get_size());
    char *mem = static_cast<char *>(region.get_address());
    *mem = 'a';
    std::printf("Before fork: %c\n", *mem);

    int status;
    pid_t pid = fork();
    if (pid == 0) {
        std::printf("Child: %c -> b\n", *mem);
        *mem = 'b';
    } else if (pid < 0) {
        return EXIT_FAILURE;
    } else {
        waitpid(pid, &status, 0);
        std::printf("Parent: %c\n", *mem);
    }

    return EXIT_SUCCESS;
}