// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <cassert>

template<typename T>		// Берем первый добавленный, последний перезаписываем
class TPQueue {
private:
	T* arr;
	int top;
	int curr;
	int count;
	int size;
public:
	TPQueue(int = 100);
	~TPQueue();
	T get() const;
	T pop();
	void push(const T&);
	bool isEmpty() const;
	bool isFull() const;
};

template<typename T>
TPQueue<T>::TPQueue(int sizeQ) :
	size(sizeQ),
	top(0),
	curr(0),
	count(0)
{
	arr = new T[size + 1];
}

template<typename T>
TPQueue<T>::~TPQueue() {
	delete[] arr;
}

template<typename T>
void TPQueue<T>::push(const T& data) {
	assert(count < size);

	if (count == 0) {
		arr[curr++] = data;
		count++;
	} else {
		int k = curr - 1;
		bool flag = 0;
		while (k >= top && data.prior > arr[k].prior) {
			flag = 1;
			arr[k + 1] = arr[k];
			arr[k] = data;
			k--;
		}
		if (flag == 0) arr[curr] = data;
		curr++;
		count++;
	}

	if (curr > size) curr -= size + 1;
}

template<typename T>
T TPQueue<T>::pop() {
	assert(count > 0);

	T data = arr[top++];
	count--;

	if (top > size) top -= size + 1;
	return data;
}

template<typename T>
T TPQueue<T>::get() const {
	assert(count > 0);
	return arr[top];
}

template<typename T>
bool TPQueue<T>::isEmpty() const {
	return count == 0;
}

template<typename T>
bool TPQueue<T>::isFull() const {
	return count == size;
}

struct SYM {
	char ch;
	int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
