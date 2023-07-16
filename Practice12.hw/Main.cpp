#include <iostream>
#include <algorithm>

template <typename T>
class Array {
private:
    T* data;  // Вказівник на динамічний масив елементів
    int size;  // Розмір масиву
    int capacity;  // Кількість елементів, під які виділено пам'ять

public:
    Array() : data(nullptr), size(0), capacity(0) {}

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int grow = 1) {
        if (newSize <= capacity) {
            size = newSize;
        }
        else {
            int newCapacity = std::max(newSize, capacity + grow);
            T* newData = new T[newCapacity];

            // Копіюємо елементи зі старого масиву в новий
            std::copy(data, data + size, newData);

            delete[] data;
            data = newData;
            size = newSize;
            capacity = newCapacity;
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            T* newData = new T[size];

            // Копіюємо елементи зі старого масиву в новий
            std::copy(data, data + size, newData);

            delete[] data;
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }
};

int main() {
    Array<int> arr;
    arr.SetSize(5);
    for (int i = 0; i < arr.GetSize(); ++i) {
        arr[i] = i + 1;
    }

    std::cout << "Size: " << arr.GetSize() << std::endl;
    std::cout << "UpperBound: " << arr.GetUpperBound() << std::endl;

    arr.SetSize(10, 5);
    std::cout << "Size after resizing: " << arr.GetSize() << std::endl;
    std::cout << "UpperBound after resizing: " << arr.GetUpperBound() << std::endl;

    arr.FreeExtra();
    std::cout << "Size after freeing extra memory: " << arr.GetSize() << std::endl;
    std::cout << "UpperBound after freeing extra memory: " << arr.GetUpperBound() << std::endl;

    arr.RemoveAll();
    std::cout << "Size after removing all elements: " << arr.GetSize() << std::endl;
    std::cout << "UpperBound after removing all elements: " << arr.GetUpperBound() << std::endl;

    return 0;
}
