#include <memory_resource>

template<class T, class Allocator = std::allocator<T> >
class container {
    public:
        class iterator {
            public:
                iterator() : p(nullptr) {}
                iterator(T* p) : p(p) {}
                const iterator operator++(int) {
                    auto it = *this;
                    p += sizeof(T);
                    return it;
                }
                bool operator==(iterator other) {
                    return p == other.p;
                }
                bool operator!=(iterator other) {
                    return p != other.p;
                }
                T& operator*() {
                    return *p;
                }
            private:
                T* p;
        };

        container() {}
        
        void add(const T& val) {
            if (size == capacity) {
                capacity = capacity * 2 + 1;
                auto newData = alloc.allocate(capacity);
                std::copy(data, data + size * sizeof(T), newData);
                std::swap(data, newData);
                alloc.deallocate(newData, size);
            }

            alloc.construct(data + size * sizeof(T), val);
            ++size;
        }

        iterator begin() {
            return iterator(data);
        }

        iterator end() {
            return iterator();
        }

    private:
        std::size_t size = 0;
        std::size_t capacity = 0;
        T* data;
        Allocator alloc;
};