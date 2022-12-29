#ifndef PROCESS_PARTY_ANONYMOUS_SHARED_MEMORY_H
#define PROCESS_PARTY_ANONYMOUS_SHARED_MEMORY_H

#include <cstddef>
#include <string>
#include "process_party/common.h"

namespace process_party::interprocess {
    class anonymous_shared_memory : public MemoryMappable {
    public:
        anonymous_shared_memory() = delete;
        explicit anonymous_shared_memory(size_t size);

        [[nodiscard]] size_t get_size() const noexcept override;
    private:
        size_t memory_region_size = 0;
    };
}

#endif //PROCESS_PARTY_ANONYMOUS_SHARED_MEMORY_H
