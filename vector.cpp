#define DEBUG_COMPILATION
#ifdef DEBUG_COMPILATION
#define DBG
#define $(MESSAGE) \
	std::cout << __FILE__ << " : " << __LINE__ << " | " << MESSAGE << std::endl;
#else
#define $(MESSAGE) 
#define DBG if(0)
#endif

#define DBG_ALLOCATION_ERROR DBG std::cout << __FILE__ << " : " <<  \
	__LINE__ << " Can`t allocate during construction." << std::endl


#define COPY_AND_SWAP // if defined then operator "=" uses copy&swap algorithm
//otherwise uses placement new

#include "vector.hpp"

Vector::Vector():
		data_(new (std::nothrow) int [VECTOR_SIZE]),
		capacity_(VECTOR_SIZE),
		size_(0)
{
	$("Default vector construct");
	if (data_ == nullptr)
		DBG_ALLOCATION_ERROR;
}

Vector::Vector(int size):
	data_(new (std::nothrow) val_t[size]),
	capacity_(size),
	size_(0)
{
	$("(size) vector construct");
	if (data_ == nullptr)
		DBG_ALLOCATION_ERROR;
}

Vector::Vector(const Vector & rhs):
		data_(new (std::nothrow) val_t[rhs.capacity_]),
		capacity_(rhs.capacity_),
		size_(rhs.size_)
{
	$("Vector from Vector construct");
	if (data_ == nullptr) {
		DBG_ALLOCATION_ERROR;
	}
	else {
		for (int i = 0; i < size_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
}

Vector::~Vector() {
	$("Vector deconstruct");
	delete [] data_;
	data_ = nullptr;
}

//access specified element with bounds checking
val_t& Vector::at(int index) {
	assert(0 <= index && index <= size_);
	return data_[index];
}

#ifdef COPY_AND_SWAP
Vector& Vector::operator= (const Vector &rhs) {
	$("Copy and swap operator =");
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
	$("Placement new operator =");
	this -> ~Vector();
	new(this) Vector (rhs);
	return *this;
}
#endif // COPY_AND_SWAP

//access specified element without bounds checking
//if you want to check it, use Vector::at(int index)
int& Vector::operator [](int idx) { 
	//assert(0 <= idx && idx < size_);
	return data_[idx];
}

Vector Vector::operator +(const Vector& right) const{
	assert (size_ == right.size_);
	$("operator +");
	Vector res(*this);	
	for (int i = 0; i < size_; ++i) {
		res.data_[i] += right.data_[i];
	}
	return res;
}

void Vector::push_back(val_t x) {
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
		val_t* new_data = new (std::nothrow) val_t [new_size];
		if (new_data == nullptr) {
			new_data = new (std::nothrow) val_t [size_+1];
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
	return true;
}

val_t& Vector::pop() {	
	assert(size_ > 0);
	//resize()?
	return data_[size_--];
}

void Vector::dump() {
	for (int i = 0; i < size_; ++i) {
		std::cout << data_[i] << " ";
	}
	std::cout << std::endl;
}

