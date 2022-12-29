#ifndef PROCESS_PARTY_SHARED_MEMORY_H
#define PROCESS_PARTY_SHARED_MEMORY_H

#include <string>

constexpr int NOT_DEFINED = -1;

namespace process_party::interprocess {
    class shared_memory_object : MemoryMappable {
    public:
        shared_memory_object() = delete;
        virtual ~shared_memory_object();
        explicit shared_memory_object(const std::string &shm_obj_name,
                             access_mode_t access_mode = read_write,
                             creation_mode_t creation_mode = open_or_create,
                             bool destroy_on_exit = false);

        void truncate(size_t memory_region_size);
        [[nodiscard]] const std::string &get_name() const noexcept;
        [[nodiscard]] size_t get_size() const noexcept;
        [[nodiscard]] int get_shared_block_id() const noexcept;
        [[nodiscard]] access_mode_t get_mode() const noexcept;

        static bool remove(const std::string &shm_obj_name);
    private:
        key_t key;
        creation_mode_t creation_mode;
        access_mode_t access_mode;
        int shared_block_id = NOT_DEFINED;
        std::string shm_obj_name;
        size_t memory_region_size = 0;
        bool destroy_on_exit;
    };
}

#endif //PROCESS_PARTY_SHARED_MEMORY_H
