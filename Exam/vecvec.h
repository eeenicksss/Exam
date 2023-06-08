#pragma once

#include "iostream"
#include "stdlib.h"
#include "stdio.h"

using namespace std;

template<typename T>
class vecvec
{
private:
	T **ptr_arr;
	int first_layer_size;
	int* second_layer_sizes;
public:
	vecvec() //представляет собой динамический массив указателей на динамические массивы
	{
		first_layer_size = 1; // размер массива указателей
		second_layer_sizes = new int[1]; // динамический массив с размерами динамических массивов
		second_layer_sizes[0] = 1;
		ptr_arr = new T*[first_layer_size];
		*ptr_arr = new T[second_layer_sizes[0]];
	}

	~vecvec()
	{
		for (int i = 0; i != first_layer_size; ++i)
		{
			delete[] ptr_arr[i];
		}
		delete[] ptr_arr;
	}

	int get_first_layer_size()
	{
		return first_layer_size;
	}

	int get_second_layer_size(int index)
	{
		try
		{
			if (index >= first_layer_size || index < 0) throw range_error("index out of range");
			return second_layer_sizes[index];
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			return 0;
		}
	}

	void push_back(int first_layer_index, T value) //добавить элемент в конец одного из массивов
	{
		try
		{
			if (first_layer_index >= first_layer_size || first_layer_index < 0) throw range_error("index out of range");
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		second_layer_sizes[first_layer_index] ++;
		T *new_ptr_index = new T[second_layer_sizes[first_layer_index]];
		for (int i = 0; i != second_layer_sizes[first_layer_index]; ++i)
		{
			new_ptr_index[i] = ptr_arr[first_layer_index][i];
		}
		new_ptr_index[second_layer_sizes[first_layer_index]] = value;
		delete[] ptr_arr[first_layer_index];
		ptr_arr[first_layer_index] = new_ptr_index;
	}

	void insert(int first_layer_index, int second_layer_index, T value) //вставить элемент по инексу
	{
		try
		{
			if (first_layer_index >= first_layer_size || first_layer_index < 0) throw range_error("first layer index out of range");
			if (second_layer_index >= second_layer_sizes[first_layer_index] || second_layer_index < 0) throw range_error("second layer index out of range");
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		second_layer_sizes[first_layer_index] ++;
		T *new_ptr_index = new T[second_layer_sizes[first_layer_index]];
		for (int i = 0; i != second_layer_sizes[first_layer_index]; ++i)
		{
			new_ptr_index[i + (second_layer_index <= i)] = ptr_arr[first_layer_index][i];
		}
		new_ptr_index[second_layer_index] = value;
		delete[] ptr_arr[first_layer_index];
		ptr_arr[first_layer_index] = new_ptr_index;
	}

	void push_back_vec(T* vec_value) //добавить в конец массива указателей новый
	{
		first_layer_size++;
		T *new_ptr_arr = new T * [first_layer_size];
		for (int i = 0; i != first_layer_size; ++i)
		{
			new_ptr_arr[i] = ptr_arr[i];
		}
		T *new_ptr_arr[first_layer_size] = vec_value;

		delete[] ptr_arr;
		ptr_arr = new_ptr_arr;
	}

	void incert_vec(int first_layer_index, T* vec_value) //всавить новый указатель в массив указателей по индексу
	{
		try
		{
			if (first_layer_index >= first_layer_size || first_layer_index < 0) throw range_error("index out of range");
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		first_layer_size++;
		T *new_ptr_arr = new T * [first_layer_size];
		for (int i = 0; i != first_layer_size; ++i)
		{
			new_ptr_arr[i + (first_layer_index <= i)] = ptr_arr[i];
		}
		new_ptr_arr[first_layer_index] = vec_value;

		delete[] ptr_arr;
		ptr_arr = new_ptr_arr;
	}

	void erase(int first_layer_index, int second_layer_index) // удалить элемент по индексу
	{
		try
		{
			if (first_layer_index >= first_layer_size || first_layer_index < 0) throw range_error("first layer index out of range");
			if (second_layer_index >= second_layer_sizes[first_layer_index] || second_layer_index < 0) throw range_error("second layer index out of range");
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		second_layer_sizes[first_layer_index] --;
		T* new_ptr_index = new T[second_layer_sizes[first_layer_index]];
		for (int i = 0; i != second_layer_sizes[first_layer_index]; ++i)
		{
			new_ptr_index[i] = ptr_arr[first_layer_index][i + (i >= second_layer_index)];
		}
		delete[] ptr_arr[first_layer_index];
		ptr_arr[first_layer_index] = new_ptr_index;
	}

	void erase_vec(int first_layer_index) //удалить массив по индексу
	{
		try
		{
			if (first_layer_index >= first_layer_size || first_layer_index < 0) throw range_error("index out of range");
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		first_layer_size--;
		T* new_ptr_arr = new T * [first_layer_size];
		for (int i = 0; i != first_layer_size; ++i)
		{
			new_ptr_arr[i] = ptr_arr[i + (i >= first_layer_index)];
		}
		delete[] ptr_arr[first_layer_index];
		delete[] ptr_arr;
		ptr_arr = new_ptr_arr;
	}
};
