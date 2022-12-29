#ifndef PROCESS_PARTY_MAPPED_REGION_H
#define PROCESS_PARTY_MAPPED_REGION_H

#include <process_party/common.h>
#include <process_party/interprocess/shared_memory.h>
#include <string>

namespace process_party::interprocess {
    class mapped_region {
    public:
        mapped_region() = delete;
        mapped_region(const process_party::interprocess::shared_memory_object &shm_obj);
        mapped_region(const process_party::interprocess::shared_memory_object &shm_obj,
                      size_t offset);
        mapped_region(const process_party::interprocess::shared_memory_object &shm_obj,
                      size_t offset,
                      size_t size);

        virtual ~mapped_region();

        [[nodiscard]] std::size_t get_size() const noexcept;
        [[nodiscard]] void *get_address() const noexcept;
        [[nodiscard]] access_mode_t get_mode() const noexcept;
        bool flush(std::size_t = 0, std::size_t = 0, bool = true);
        static std::size_t get_page_size() noexcept;
    private:
        size_t region_start;
        size_t region_end;
        void *address;
        access_mode_t access_mode;
    };
}

#endif //PROCESS_PARTY_MAPPED_REGION_H
