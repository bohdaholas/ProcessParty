#include <process_party/interprocess.h>
#include "anonymous_shared_memory.h"

process_party::interprocess::anonymous_shared_memory::anonymous_shared_memory(
        size_t size) {
    ipc_type = ipc_anonymous;
    memory_region_size = size;
}

size_t
process_party::interprocess::anonymous_shared_memory::get_size() const noexcept {
    return memory_region_size;
}
