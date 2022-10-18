#include <iostream>
#include <malloc.h>
using namespace std;

template <class T>
class Arr
{
private:

	T* arr;
	unsigned short size;

public:
	
	Arr() {}

	Arr(int size) {
		this->size = size;

		if (!(arr = (T*)malloc(size * sizeof(T))))
			throw exception("Error with malloc");

	}

	Arr(T* _arr, int size) {
		if (size < 0)
			throw exception("Wrong size");

		this->size = size;

		if(!(arr = (T*)malloc(size * sizeof(T))))
			throw exception("Error with malloc");

		for (int i = 0; i < size; i++) {
			arr[i] = _arr[i];
		}
	}

	void Insert(int index, T value)
	{
		if (size <= index||index<0)
			throw exception("Wrong index in insert");
			arr[index] = value;
	}

	T GetElement(int index) {
		if (size <= index||index<0)
			throw exception("Wrong index in GetElement");
		return arr[index];
	}

	void Delete(int index) {
		if (size <= index||index<0)
			throw exception("Wrong index in delete");
					
		arr[index] = 0;
	}

	bool Search(T element) {
		for (int i = 0; i < size;i++) {
			if (arr[i] == element) return 1;
		}
		return 0;
	}
	void Sort() {
		for (size_t idx_i = 0; idx_i + 1 < size; ++idx_i) {
			for (size_t idx_j = 0; idx_j + 1 < size - idx_i; ++idx_j) {
				if (arr[idx_j + 1] < arr[idx_j]) {
					T temp = arr[idx_j];
					arr[idx_j] = arr[idx_j + 1];
					arr[idx_j + 1] = temp;
				}
			}
		}
	}

	void display() {
		for (int i = 0; i < size;i++) {
			cout << " " << arr[i];
		}
		cout << endl;
	}

	size_t GetSize() {
		return size;
	}

	const bool operator<(const Arr rightArr) {
		if (size <= rightArr.GetSize()) return true;
		else return false;
	}

	Arr operator + (Arr secondArray) {

		if (strcmp(typeid(T).name(), "char") == 0) {
			Arr newArray(size+secondArray.GetSize());
			for (int i = 0; i < size; i++) {
				newArray.Isert(i, arr[i]);
			}
			int j = 0;
			for (int i = size; i < size + secondArray.GetSize(); i++) {
				newArray.Insert(i, secondArray.GetElement(j++));
			}
			return newArray;
		}


		if (size <= secondArray.GetSize()) {
			Arr newArray(secondArray.GetSize());
			for (int i = 0; i < size; i++) {
				newArray.Insert(i,arr[i] + secondArray.GetElement(i));
			}
			return newArray;
		}
		else {
			Arr newArray(size);
			for (int i = 0; i < secondArray.GetSize(); i++) {
				newArray.Insert(i, arr[i] + secondArray.GetElement(i));
			}
			return newArray;
		}
	}
};

void _terminate() {
	cout << "Terminate" << endl;
	abort();
}

void _unexpected() {
	cout << "Unexpected " << endl;
	abort();
}

int main()
{
	set_terminate(_terminate);
	set_unexpected(_unexpected);
	try {
		cout << "Enter size of array" << endl;
		int size;
		if (!(cin >> size))
			throw exception("Wrong input");
		Arr<int> arr(size);
		cout << "Enter all of the elements" << endl;
		for (int i = 0; i < size; i++) {
			int tmp;
			if (!(cin >> tmp))
				throw exception("Wrong input");
			arr.Insert(i, tmp);
		}
		while (1) {
			switch (getchar()) {
			case 'i': {
				cout << "Enter index" << endl;
				int i;
				if (!(cin >> i))
					throw exception("Wrong input");
				cout << "Enter data" << endl;
				int data;
				if (!(cin >> data))
					throw exception("Wrong input");
				arr.Insert(i, data);
				break;
			}
			case 'd': {
				cout << "Enter index" << endl;
				int i;
				if (!(cin >> i))
					throw exception("Wrong input");
				arr.Delete(i);
				break;
			}
			case 'r': {
				arr.display();
				break;
			}
			case 'c': {
				system("cls");
				break;
			}
				defalt:break;
			}
			cout << "i - insert, d  - delete, r - display, c - clear" << endl;
		}
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
	}
	catch (...)
	{
		unexpected();
	}
	return 0;
}