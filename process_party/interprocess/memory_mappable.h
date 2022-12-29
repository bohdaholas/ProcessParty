#ifndef PROCESS_PARTY_MEMORY_MAPPABLE_H
#define PROCESS_PARTY_MEMORY_MAPPABLE_H

#include <process_party/common.h>
#include <string>

namespace process_party::interprocess {
    class MemoryMappable {
    public:
        virtual void truncate(size_t memory_region_size);
        [[nodiscard]] virtual const std::string &get_name() const noexcept;
        [[nodiscard]] virtual size_t get_size() const noexcept;
        [[nodiscard]] virtual int get_shared_block_id() const noexcept;
        [[nodiscard]] virtual int get_file_descriptor() const noexcept;
        [[nodiscard]] virtual access_mode_t get_mode() const noexcept;
        [[nodiscard]] int get_ipc_type() const noexcept;
    protected:
        int ipc_type;
    };
}

#endif //PROCESS_PARTY_MEMORY_MAPPABLE_H
