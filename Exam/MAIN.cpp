#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include"vecvec.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream& out_stream, const vecvec<T>& right) //выводим в виде матрицы
{
	for (int i = 0; i < right.get_first_layer_size(); ++i)
	{
		for (int j = 0; j < right.get_second_layer_size(i); ++j) cout << right.ptr_arr[i][j] << " ";
	}
	cout << endl;

	return out_stream;
}

template <typename T>
istream& operator>>(istream& in_stream, vecvec<T>& right)
{
	T element;
	cin >> element;
	right.push_back(0, element); //добавляем введенное значение в первый массив

	return in_stream;
}

int main()
{
	vecvec<int> test = vecvec<int>();
	test.push_back(0, 34);
	test.push_back(0, 456);
	test.push_back(0, 82);

	cout << test;

	return 0;
}