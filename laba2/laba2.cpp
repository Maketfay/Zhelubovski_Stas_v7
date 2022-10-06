//Массив дробных чисел
/*
Перегрузить операторы-члены класса:
-присвоение, =*
-индексация элемента, []*
-инициализация, ()*
-унарные арифмитические, ++*
-бинарные арифмитические, +*
-сравнение, ==*
Перегрузить дружественные функции-операторы:
-унарные арифмитические, --*
-бинарные арифмитические, -*
-сравнения, < *
-вывода в поток, <<*
Функции преобразования
*/
#include <iostream>
#include <iterator>

using namespace std;

class DescriptionArr {
private:
    int count;
    double max;
    double min;
public:
    DescriptionArr() {
        count = max = min = 0;
    }
    DescriptionArr(int count, double max, double min) {
        this->count = count;
        this->max = max;
        this->min = min;
    }
    void ShowDescription() {
        cout << "Count: " << count << " Max: " << max << " Min: " << min << endl;
    }
};

class Array_double {
private:
    double* arr;
    int count;
public:
    Array_double() {
        arr = new double;
        count = 1;
        arr[0] = 0.0;
    }

    Array_double(const Array_double& Arr) {
        count = Arr.count;
        arr = Arr.arr;
    }

    Array_double(double arr[], int count) {
        this->count = count;
        this->arr = new double(count);
        for (int i = 0; i < count; i++) {
            this->arr[i] = arr[i];
        }
    }

    Array_double(int count) {
        this->count = count;
        arr = new double(count);
        for (int i = 0; i < count; i++) {
            arr[i] = 0.0;
        }
    }

    void ShowArr() {
        cout << "This array: " << endl;
        for (int i = 0; i < count; i++) {
            cout << arr[i] << endl;
        }
    }

    Array_double operator + (Array_double secondArray) {

        if (count >= secondArray.count) {
            Array_double newArray = count;
            for (int i = 0; i < secondArray.count; i++) {
                newArray.arr[i] = arr[i] + secondArray.arr[i];
            }
            return newArray;
        }
        else {
            Array_double newArray = secondArray.count;
            for (int i = 0; i < this->count; i++) {
                newArray.arr[i] = secondArray.arr[i] + arr[i];
            }
            return newArray;
        }
    }

    Array_double operator ++() {
        for (int i = 0; i < count; i++) {
            ++arr[i];
        }
        return Array_double(arr, count);
    }

    Array_double operator ++(int) {
        Array_double temp(arr, count);
        for (int i = 0; i < count; i++) {
            arr[i]++;
        }
        return temp;
    }

    Array_double& operator=(const Array_double& secondArr) {
        arr = secondArr.arr;
        count = secondArr.count;
        return *this;
    }

    bool operator == (Array_double secondArray) {
        if (count != secondArray.count) return false;
        for (int i = 0; i < count; i++) {
            if (arr[i] != secondArray.arr[i]) return false;
        }
        return true;
    }

    double& operator[](int n) {
        if (n < 0 || n >= count)
        {
            cout << "Wrong index" << endl;
            exit(1);
        }
        return arr[n];
    }

    friend ostream& operator<<(ostream& out, const Array_double& Array);

    friend const Array_double operator-(const Array_double& leftArr, const Array_double& rightArr);

    friend const bool operator<(const Array_double& leftArr, const Array_double& rightArr);

    friend const Array_double operator--(Array_double& arr);

    friend const Array_double operator--(Array_double& arr, int);

    operator double() const {
        double max = -999999999;
        for (int i = 0; i < count; i++) {
            if (arr[i] > max) max = arr[i];
        }
        return max;
    }

    operator DescriptionArr() const {
        double max = -999999999;
        double min = 999999999;
        for (int i = 0; i < count; i++) {
            if (arr[i] > max) max = arr[i];
            if (arr[i] < min)min = arr[i];
        }
        return DescriptionArr(count, max, min);
    }
};

const Array_double operator--(Array_double& Arr) {
    for (int i = 0; i < Arr.count; i++) {
        Arr.arr[i]--;
    }
    return Arr;
}

const Array_double operator--(Array_double& Arr, int) {
    Array_double oldArr(Arr);
    for (int i = 0; i < Arr.count; i++) {
        Arr.arr[i]--;
    }
    return oldArr;
}

ostream& operator<<(ostream& out, const Array_double& Array)
{
    for (int i = 0; i < Array.count; i++) {
        out << Array.arr[i] << endl;
    }
    return out;
}

const Array_double operator-(const Array_double& leftArr, const Array_double& rightArr) {
    int count1 = leftArr.count;
    int count2 = rightArr.count;
    Array_double NewArr = count1;
    int i = 0;
    while (count1-- && count2--) {
        NewArr.arr[i] = leftArr.arr[i] - rightArr.arr[i++];
    }
    return NewArr;
}

const bool operator<(const Array_double& leftArr, const Array_double& rightArr) {
    if (leftArr.count <= rightArr.count) return true;
    else return false;
}

int main()
{
    double arr1[] = { 1.0, 2.0, 3.0 };
    double arr2[] = { 2.5, 1.5, 3.2 };
    Array_double Darr1(arr1, (sizeof(arr1) / sizeof(double)));
    Array_double Darr2(arr2, (sizeof(arr2) / sizeof(double)));
    cout << "There are two arrays: \n First: \n" << Darr1 << "\n Second: \n" << Darr2 << endl;
    Array_double Darr3 = Darr1 + Darr2;
    cout << "After sum: \n" << Darr3;
    if (Darr1 == Darr2) cout << "Arr1 is equal arr2" << endl;
    else cout << "Arr1 is not equal arr2" << endl;
    cout << "After ++: \n" << ++Darr3;
    cout << "\n[1]: \n" << Darr3[1] << endl;
    Array_double Darr4;
    Darr4 = Darr2;
    cout << "\nAfter = : \n" << Darr4;
    Array_double Darr5(Darr4);
    cout << "\nAfter () : \n" << Darr5 << endl;
    Darr5 = Darr3 - Darr1;
    cout << "After sub: \n" << Darr5 << endl;
    cout << "After --: \n" << ++Darr5;
    if (Darr1 > Darr2) cout << "Arr1 more that Arr2" << endl;
    else cout << "Arr1 not more that Arr2" << endl;
    double max = Darr2;
    cout << "Max el: " << max << endl;
    cout << "After cast" << endl;
    DescriptionArr desc = Darr2;
    desc.ShowDescription();
    return 0;
}