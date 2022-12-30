#include <process_party/common.h>
#include <atomic>
#include "pipe_stream.h"

process_party::process::pipe_stream::pipe_stream() {
#if IS_LINUX
    int p[2];

    if (pipe(p) < 0) {
        exit(EXIT_FAILURE);
    }
    read_fd = p[0];
    write_fd = p[1];
#endif
}
