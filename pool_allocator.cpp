#include <vector>
#include <iostream>

template <class T, std::size_t size>
class pool_allocator {
    public:
        typedef T value_type;

        using propagate_on_container_copy_assigment = std::true_type;
        using propagate_on_container_move_assigment = std::true_type;
        using propagate_on_container_swap = std::true_type;

        pool_allocator() noexcept {
            std::cout << "construct start" << "\n";
            data = static_cast<char*>(::operator new(size * sizeof(T)));
            pos = 0;
            std::cout << "construct_end " << "\n";
        }

        ~pool_allocator() noexcept {
            std::cout << "destruct start" << "\n";
            delete[] data;
            std::cout << "destruct end" << "\n";
        }

        template<class U> pool_allocator(const pool_allocator<U, size>&) noexcept {
            pool_allocator();
        }

        pool_allocator select_on_container_copy_construction() const {
            return pool_allocator();
        }

        T* allocate(std::size_t n) {
            std::cout << "allocate start" << "\n";
            if (pos + n > size) {
                std::cout << "error " << n << " " << pos << " " << size << "\n";
                throw std::bad_alloc();
            }
            int cur = pos;
            pos += n;
            std::cout << "allocate end" << "\n";
            return reinterpret_cast<T*>(data) + cur;
        }

        void deallocate(T* p, std::size_t n) {}

        template<class U>
        struct rebind {
            typedef pool_allocator<U, size> other;
        };

    private:
        char* data;
        int pos;
};

int main() {
    std::vector<int, pool_allocator<int, 1000> > v;
    v.push_back(1);
    std::cout << v[0];
}