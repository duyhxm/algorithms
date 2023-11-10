#include<iostream>
#include<vector>
#include<utility>
#include<cmath>
#include<iomanip>

std::pair<int, int> min_max(std::vector<int> a)
{
	std::pair<int, int> v = { 0,0 };
	v.first = a[0];
	v.second = a[0];
	for (int i = 1; i < a.size(); i++)
	{
		if (a[i] < v.first)
			v.first = a[i];
		if (a[i] > v.second)
			v.second = a[i];
	}
	return v;
}

int bucket(std::pair<int, int> v, int range)
{
	return (v.second - v.first + 1) / range + 1;
}

int index(std::pair<int, int> v, int value, int range)
{
	return (value - v.first + 1) / range;
}

void heapify(std::vector<int> &a, int size, int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < size && a[left] > a[largest])
		largest = left;
	if (right < size && a[right] > a[largest])
		largest = right;
	if (largest != i)
	{
		std::swap(a[i], a[largest]);
		heapify(a, size, largest);
	}
}

void heap_sort(std::vector<int> &a)
{
	for (int i = a.size() / 2 - 1; i >= 0; i--)
	{
		heapify(a, a.size(), i);
	}
	for (int i = a.size()-1; i >= 1; i--)
	{
		std::swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

void bucket_sort(std::vector<int>& a, int range)
{
	std::pair<int, int> v = min_max(a);
	int b = bucket(v, range);
	std::vector<std::vector<int>> bucket_arr(b);
	
	for (int i = 0; i < a.size(); i++)
	{
		int k = index(v, a[i], range);
		bucket_arr[k].push_back(a[i]);
	}
	int c = 0;
	for (int i = 0; i < b; i++)
	{
		if (bucket_arr[i].empty())
			continue;
		heap_sort(bucket_arr[i]);
		for (int j = 0; j < bucket_arr[i].size(); j++)
		{
			a[c] = bucket_arr[i][j];
			c++;
		}
	}
}

void print(std::vector<int> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (i % 15 == 0)
			std::cout << std::endl;
		std::cout << a[i] << "     ";
	}
}
int main()
{
	int n=0;
	std::cout << "Enter the size: ";
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		a[i] = rand() % 10000;

	std::cout << std::endl;

	print(a);
	std::cout << std::endl;

	bucket_sort(a, 20);
	std::cout << std::endl;

	print(a);
	std::cout << std::endl;

	system("pause>0");
	return 0;
}