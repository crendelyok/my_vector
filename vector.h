#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#define DEBUG_COMPILATION
#ifdef DEBUG_COMPILATION
#define DBG
#else
#define DBF if(0)
#endif

#define DBG_ALLOCATION_ERROR DBG std::cout << "Can`t allocate during construction." << std::endl
#define __FILE__ "C:/dev/logs/logs.txt"

//#define COPY_AND_SWAP // if defined then operator "=" uses copy&swap algorithm
//otherwise uses placement new

#include <algorithm>
#include "assert.h"
#include <fstream>

const int VECTOR_SIZE = 4;

class Vector {
private:
    int * data_;
    int capacity_; //allocated
    int size_;
    #ifdef COPY_AND_SWAP
    void swap(Vector &rhs);
    #endif
    bool resize(int);
public:
    Vector();
    Vector(const Vector &);
    explicit Vector (int);
    ~Vector();

    void push_back(int);
    void dump();

    Vector& operator =(const Vector &);
    int& operator [](int);
    //void* operator new(size_t, void*);
};

Vector::Vector():
        data_(new (std::nothrow) int [VECTOR_SIZE]),
        capacity_(VECTOR_SIZE),
        size_(0)
{
    if (data_ == nullptr)
        DBG_ALLOCATION_ERROR;
}

Vector::Vector(int size) :
    data_(new (std::nothrow) int[size]),
    size_(0),
    capacity_(size)
{
    if (data_ == nullptr)
        DBG_ALLOCATION_ERROR;
}

Vector::Vector(const Vector & rhs):
        data_(new (std::nothrow) int[rhs.capacity_]),
        size_(rhs.size_),
        capacity_(rhs.capacity_)
{
    if (data_ == nullptr)
        DBG_ALLOCATION_ERROR;
    else {
        for (int i = 0; i < size_; ++i) {
            data_[i] = rhs.data_[i];
        }
    }
}

Vector::~Vector() {
    delete [] data_;
    data_ = nullptr;
}

#ifdef COPY_AND_SWAP
Vector& Vector::operator = (const Vector &rhs) {
    Vector copy(rhs);
    swap (copy);
    return *this;
}

void Vector::swap(Vector &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(data_, rhs.data_);
    std::swap(capacity_, rhs.capacity_);
}
#else //placement new

/*
void* operator new(std::size_t, std::nothrow_t, void *mem) {
    std::cout << "&&&&&&&";
    std::ofstream fout(__FILE__);
    fout << "New used." << std::endl;
    fout.close();
    return mem;
}
*/

Vector& Vector::operator= (const Vector &rhs) {
    delete(this);
    char buf[sizeof(rhs)] = {};
    //Vector *v = new(buf) Vector;
    new(this) Vector (rhs);
    return *this;
}
#endif // COPY_AND_SWAP

int& Vector::operator [](int idx) {
    assert(0 <= idx && idx < size_);
    return data_[idx];
}

void Vector::push_back(int x) {
    if (size_ < capacity_) {
        data_[size_++] = x;
    }
    else {
        if (resize(size_ * 2))
            push_back(x);
        else
            std::cout << "Can`t push_back." << std::endl;
    }
}

bool Vector::resize(int new_size) {
    if(new_size <= size_) {
        //блок с уменьшением
    }
    else {
        int* new_data = new (std::nothrow) int [new_size];
        if (new_data == nullptr) {
            new_data = new (std::nothrow) int [size_+1];
            new_size = size_ + 1;
            if (new_data == nullptr) {
                std::cout << "Can`t reallocate during resizing." << std::endl;
                return false;
            }
        }
         for (int i = 0; i < size_; ++i) {
             new_data[i] = data_[i];
         }
         delete [] data_;
         data_ = new_data;
         capacity_ = new_size;
         return true;
    }
}

void Vector::dump() {
    for (int i = 0; i < size_; ++i) {
        std::cout << data_[i] << " ";
    }
    std::cout << std::endl;
}

#endif //VECTOR_VECTOR_H
