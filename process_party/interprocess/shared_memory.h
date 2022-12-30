#ifndef PROCESS_PARTY_SHARED_MEMORY_H
#define PROCESS_PARTY_SHARED_MEMORY_H

#include <string>

constexpr int NOT_DEFINED = -1;

namespace process_party::interprocess {
    class shared_memory_object : public MemoryMappable {
    public:
        shared_memory_object() = delete;
        virtual ~shared_memory_object();
        explicit shared_memory_object(const std::string &shm_obj_name,
                             access_mode_t access_mode = read_write,
                             creation_mode_t creation_mode = open_or_create);

        void truncate(size_t memory_region_size) override;
        [[nodiscard]] const std::string &get_name() const noexcept override;
        [[nodiscard]] size_t get_size() const noexcept override;
        [[nodiscard]] int get_shared_block_id() const noexcept override;
        [[nodiscard]] access_mode_t get_mode() const noexcept override;

        static bool remove(const std::string &shm_obj_name);
    private:
        int key;
        creation_mode_t creation_mode;
        access_mode_t access_mode;
        int shared_block_id = NOT_DEFINED;
        std::string shm_obj_name;
        size_t memory_region_size = 0;
    };
}

#endif //PROCESS_PARTY_SHARED_MEMORY_H
