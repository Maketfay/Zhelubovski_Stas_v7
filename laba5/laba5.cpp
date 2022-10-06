//arraay
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

template <class T>
class Arr
{
public:
	vector<T> v;
	Arr() {}
	Arr(T* _arr, int size) {
		for (int i = 0; i < size; i++) {
			v.push_back(_arr[i]);
		}
	}
	void Push(T element) {
		v.push_back(element);
	}

	void Insert(int index, T value)
	{
		if(v.size() > index)
			v[index] = value;
	}
	void Delete(int index) {
			if (v.size() > index) {
				auto iter = v.cbegin();
				v.erase(iter + index);
			}
	}
	bool Search(T element) {
		for (T i: v) {
			if (i == element) return 1;
		}
		return 0;
	}
	void Sort() {
		sort(v.begin(), v.end());
	}
	void display() {
		for (T i : v) {
			cout << " " << i;
		}
		cout << endl;
	}
	size_t GetSize() {
		return v.size();
	}
	const bool operator<(const Arr rightArr) {
		if (v.size() <= rightArr.GetSize()) return true;
		else return false;
	}
	Arr operator + (Arr secondArray) {
		if (strcmp(typeid(T).name(), "char")==0) {
		   Arr newArray;
		   newArray.v = v;
		   for (T i : secondArray.v) {
			   newArray.Push(i);
		   }
		   return newArray;
		}
		Arr newArray;
		if (v.size() <= secondArray.GetSize()) {
			for (int i = 0; i < v.size(); i++) {
				newArray.Push(v[i] + secondArray.v[i]);
			}
			return newArray;
		}
		else {
			for (int i = 0; i < secondArray.GetSize(); i++) {
				newArray.Push(v[i] + secondArray.v[i]);
			}
			return newArray;
		}
	}
};

int main() {
	cout << "Choose a type: \n" << "1.int\n" << "2.double\n" << "3.char" << endl;
	short a;
	cin >> a;
	switch (a) {
	case 1: {
		cout << "Enter 5 elements" << endl;
		int ms[5];
		for (int i = 0; i < 5; i++) {
			cin >> ms[i];
		}
		Arr<int> arr(ms, sizeof(ms) / sizeof(int));
		arr.Insert(0, 21);
		cout << "Enter element for search: " << endl;
		int b;
		cin >> b;
		if (arr.Search(b))cout << "This element exist" << endl;
		else cout << "This element not exist" << endl;
		Arr<int> arr1 = arr;
		Arr<int> arr4;
		arr4 = arr + arr1;
		arr4.display();
		arr4.Sort();
		arr4.display();
		break;
	}
	case 2: {
		cout << "Enter 5 elements" << endl;
		double ms[5];
		for (int i = 0; i < 5; i++) {
			cin >> ms[i];
		}
		Arr<double> arr(ms, sizeof(ms) / sizeof(double));
		arr.Insert(0, 21.2);
		cout << "Enter element for search: " << endl;
		double b;
		cin >> b;
		if (arr.Search(b))cout << "This element exist" << endl;
		else cout << "This element not exist" << endl;
		Arr<double> arr1 = arr;
		Arr<double> arr4;
		arr4 = arr + arr1;
		arr4.display();
		arr4.Sort();
		arr4.display();
		break;
	}
	case 3: {
		cout << "Enter 5 elements" << endl;
		char ms[5];
		for (int i = 0; i < 5; i++) {
			cin >> ms[i];
		}
		Arr<char> arr(ms, sizeof(ms) / sizeof(char));
		arr.Insert(0, 'a');
		cout << "Enter element for search: " << endl;
		char b;
		cin >> b;
		if (arr.Search(b))cout << "This element exist" << endl;
		else cout << "This element not exist" << endl;
		Arr<char> arr1 = arr;
		Arr<char> arr4;
		arr4 = arr + arr1;
		arr4.display();
		arr4.Sort();
		arr4.display();
		break;
		break;
	}
	default: {
		cout << "Bad input" << endl;
		return 1;
	}
	}

	return 0;
 
}