#pragma once
#include <cmath>
#include <iostream>
using namespace std;

template <typename T>
class vector
{
    private:
        T* array;
        int Size;
        int Capacity; // chứa dung lượng tối đa của vector
        void CapacityUp(int newCapacity); // tăng số lượng phần tử của vector
    public:
        vector();
        ~vector();
        int size() const; // trả về số lượng phần tử được sử dụng trong vector
        int capacity() const; // trả về sức chứa của vector
        bool empty(); // Trả về dữ liệu vùng chứa có trống hay không, nếu trống thì trả về True, nếu có phần tử thì trả về False
        const vector<T>& operator= (const vector<T> &vt); 
        T& operator[] (const int index); 
        T& at(const int index); // tương tự như đa năng hóa toán tử truy cập
        void push_back(const T& value); // them phần tử vao cuoi vector
        void pop_back(); // xoá phần tử ở cuối vector
        void insert(const T& value, int position); // chèn phần tử value có kiểu dữ liệu T vào vị trí position
        void erase(const int& pos); // xoá phần tử ở vị trí pos
        void clear(); // loại bỏ tất cả các phần tử của vùng chứa vector.
        T* data(); // trả về con trỏ trực tiếp đến memory array được sử dụng bên trong vector để lưu trữ các thành phần của nó
};

template <typename T>
void vector<T>::CapacityUp(int newCapacity)
{
    if (newCapacity < this->Size)
        return;
    if (this->array != nullptr)
    {
        T* newData = new T[newCapacity];
        for (int i = 0; i < this->Size-1; i++)
            newData[i] = this->array[i];
        delete[] this->array;
        this->array = new T[newCapacity];
        this->array = newData;    
    }
    else
        this->array = new T[newCapacity];
    this->Capacity = newCapacity;
}

template <typename T>
vector<T>::vector() 
{
    this->Size = this->Capacity = 0;
    this->array = nullptr;
}
template <typename T>
vector<T>::~vector()
{
    delete[] this->array; 
}

template <typename T>
int vector<T>::size() const 
{
    return this->Size;
}

template <typename T>
int vector<T>::capacity() const
{
    return this->Capacity;
}

template <typename T>
bool vector<T>::empty()
{
    return this->Size == 0;
}

template <typename T>
const vector<T>& vector<T>::operator=(const vector<T> &vt)
{
    this->Size = vt.Size;
    this->Capacity = vt.Capacity;
    this->array = new T[this->Capacity];
    for (int i = 0; i < this->Size; ++i)
        this->array[i] = vt.array[i];
    return *this;
}

template <typename T>
T& vector<T>::operator[](const int index)
{
    if (index > this->Size || index < 0)
    {
        static T temp;
        return temp;
    }
    return *(this->array + index);
}

template <typename T>
T& vector<T>::at(const int index)
{
    if (index > this->Size || index < 0)
    {
        static T temp;
        return temp;
    }
    return *(this->array + index);
}

template <typename T>
void vector<T>::push_back(const T& value)
{
    this->Size++;
    if (this->Size > this->Capacity) this->CapacityUp(pow(2, ceil(log(this->Size)/log(2))));
    this->array[this->Size - 1] = const_cast<T&>(value);
}

template <typename T>
void vector<T>::pop_back()
{
    if(!this->empty())
    {
        delete (this->array + this->Size - 1);
        this->Size--;
    }
}

template <typename T>
void vector<T>::insert(const T& value, int position)
{
    this->Size++;
    if (this->Size > this->Capacity) this->CapacityUp(pow(2, ceil(log(this->Size)/log(2))));
    T* temp = new T[this->Size];
    for (int i = 0; i < position; i++)
    {
        temp[i] = this->array[i];
    }
    temp[position] = value;
    for (int i = position + 1; i < this->Size; i++)
    {
        temp[i] = this->array[i - 1];
    }
    delete[] this->array;
    this->array = new T[this->Capacity];
    this->array = temp;
}

template <typename T>
void vector<T>::erase(const int& pos)
{
    if (!this->empty() && pos >= 0 && pos < this->Size)
    {
        for(int i = pos; i < this->Size - 1; i++)
            this->array[i] = this->array[i + 1];
        this->Size--;
        if (this->Size < this->Capacity / 2)
        {
            T* newArray = new T[this->Capacity / 2];
            for (int i = 0; i < this->Size; i++)
                newArray[i] = this->array[i];
            delete[] this->array;
            this->array = new T[this->Capacity / 2];
            this->array = newArray;
            this->Capacity /= 2;
        }
    }
}
template <typename T>
void vector<T>::clear()
{
    this->Size = 0;
}
template <typename T>
T* vector<T>::data()
{
    return this->array;
}
