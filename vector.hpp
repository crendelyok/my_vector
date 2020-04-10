#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include "assert.h"
#include <iostream>

const int VECTOR_SIZE = 4;

typedef int val_t;

class Vector {
private:
	val_t * data_;
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

	void push_back(val_t);
	val_t& pop(); 
	val_t& at(int); 
	void dump();



	Vector& operator =(const Vector&);
	val_t& operator [](int);
	Vector operator +(const Vector&) const;
	//void* operator new(size_t, void*);
};

#endif //VECTOR_VECTOR_H
