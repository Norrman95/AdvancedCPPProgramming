#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>

using namespace std;

vector<int> v(100);
forward_list<int> fList = { 17, 2, 86, 14, 43 };
int a[100];

template <class ForwardIterator>
int getLength(ForwardIterator begin, ForwardIterator end)
{
	int length = 0;

	for (ForwardIterator it = begin; it != end; ++it)
	{
		length++;
	}

	return length;
}

template <class ForwardIterator>
void ForwardSort(ForwardIterator begin, ForwardIterator end)
{
	int length = getLength(begin, end);
	ForwardIterator current, next; 

	for (int i = 0; i < length - 1; i++)
	{
		current = begin;
		next = ++begin;
		for (int j = 0; j < length - i - 1; j++)
		{
			if (*current > *next)
			{
				int temp = *current;
				*current = *next;
				*next = temp;
			}
			current = next;
			next = ++next;
		}
	}
}

void vAsc()
{
	sort(v.begin(), v.end());
}
void vDesc()
{
	sort(v.rbegin(), v.rend());
}
void aAsc()
{
	sort(begin(a), end(a));
}
void aDesc()
{
	sort(begin(a), end(a), [](const int a, const int b)
	{
		return a > b;
	});
}

void RemoveIf()
{
	remove_if(v.begin(), v.end(), [](const int& value)
	{
		return ((value % 2) == 0);
	});
}

void aPrint()
{
	for (size_t i = 0; i < 100; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
void vPrint()
{
	for (size_t i = 0; i < 100; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}
void fPrint()
{
	for (auto it = fList.begin(); it != fList.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main()
{
	iota(v.begin(), v.end(), 100);
	for (size_t i = 0; i < 100; i++)
	{
		a[i] = i;
	}

	random_shuffle(v.begin(), v.end());
	random_shuffle(begin(a), end(a));

	//Vector
	cout << "Vector before" << endl;
	vPrint();

	vAsc();
	cout << endl << "asc" << endl;
	vPrint();

	vDesc();
	cout << endl << "desc" << endl;
	vPrint();

	//Array
	cout << endl << "Array before" << endl;
	aPrint();

	aAsc();
	cout << endl << "asc" << endl;
	aPrint();

	aDesc();
	cout << endl << "desc" << endl;
	aPrint();

	//Remove
	RemoveIf();
	cout << endl << "Even removed" << endl;
	vPrint();

	//Forward_list	
	cout << endl << "fList Before" << endl;
	fPrint();

	ForwardSort(fList.begin(), fList.end());

	cout << endl << "fList After" << endl;
	fPrint();

	cin.get();
	return 0;
}