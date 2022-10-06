//home 
#include <iostream>
#include <string.h>

using namespace std;

bool IsTrueColor(string color) {
	if (color[0] != '#') return 0;
	if (color.size() != 7) return 0;
	for (int i = 1; i < 7; i++) {
		if ((color[i] >= 'A' && color[i] <= 'F') || (color[i] >= '0' && color[i] <= '9') || (color[i] >= 'a' && color[i] <= 'f')) continue;
		return 0;
	}
	return 1;
}

class building {
protected:
	double square;
	string color;
public:
	building(){}
	building(unsigned int square , string color) {
		this->square = square;
		if (IsTrueColor(color)) this->color = color;
		else color = "#000000";
	}
	virtual void display() {
		cout << "Square: "<<square<<"Color: "<<color<<endl;
	}
	~building() {
		cout << "Distructor \"Building\"" << endl;
	};
};

class Garage : virtual public building {
protected:
	int capacityOfCars;
public:
	Garage(){}
	Garage(int square, string color, int capacityOfCars){
		this->square = square;
		this->color = color;
		this->capacityOfCars = capacityOfCars;
	}
	void display() override {
		cout << "Square: " << square << "Color: " << color <<"Capacity of cars"<<capacityOfCars << endl;
	}
	~Garage() {
		cout << "Distructor \"Garage\"" << endl;
	}
};

class Home : virtual public building {
protected:
	unsigned int quantityOfRooms;
public:
	Home() {}
	Home(int square, string color, int quantityOfRooms) {
		this->square = square;
		this->color = color;
		this->quantityOfRooms = quantityOfRooms;
	}
	void display() override {
		cout << "Square: " << square << "Color: " << color << "Quantity of rooms" << quantityOfRooms << endl;
	}
	~Home() {
		cout << "Distructor \"Home\"" << endl;
	}
};

class Flat final: public Home {
private:
	int numberFloor;
public:
	Flat(int square=1, string color="#000000", int quantityOfRooms=1, int numberFloor=1) :Home(square, color, quantityOfRooms) {
		this->numberFloor = numberFloor;
	}
	void display() override {
		cout << " Square: " << square << " Color: " << color << " Quantity of rooms" << quantityOfRooms<<" Number of floor"<<numberFloor << endl;
	}
	~Flat() {
		cout << "Distructor \"Flat\"" << endl;
	}
};

class UndegroundGarage final: public Garage {
private:
	double depth;
public:
	UndegroundGarage(int square = 1, string color = "#000000", int capacityOfCars = 1, double depth = 0) :Garage(square, color, capacityOfCars) {
		this->depth = depth;
	}
	void display() override {
		cout << " Square: " << square << " Color: " << color << " Capacity of cars: " << capacityOfCars << " Depth: " << depth << endl;
	}
	~UndegroundGarage() {
		cout << "Distructor \"Undeground Garage\"" << endl;
	}
};

class HomeWithGarage : public Home, public Garage {
private:
	unsigned int quantityOfGarages;
public:
	HomeWithGarage(int square = 1, string color = "#000000", int quantityOfRooms = 1, int capacityOfCars = 1, unsigned int quantityOfGarages = 1) : Home() {
		this->square = square;
		this->color = color;
		this->quantityOfRooms = quantityOfRooms;
		this->capacityOfCars = capacityOfCars;
		this->quantityOfGarages = quantityOfGarages;
	}
	void display() override
	{
		cout << " Square: " << square 
			<< " Color: " << color
			<< " Quantity of rooms" << quantityOfRooms 
			<< " Capacity of cars: "<< capacityOfCars<<
			" Quantity of garages"<< quantityOfGarages<< endl;
	}
	~HomeWithGarage() {
	cout<< "Distructor \"HomeWithGarage\"" << endl;
	}
};

int main() {
	Flat obj1(25, "#010101", 3, 5);
	cout << "Flat: " << endl;
	obj1.display();
	UndegroundGarage obj2(100, "#123ad6", 1, 12.2);
	cout << "Undeground Garage: " << endl;
	obj2.display();
	HomeWithGarage obj3(10, "#121212", 4, 3, 2);
	cout << "Home with garage: " << endl;
	obj3.display();
	cout << "\n\n\n\n\n\n";
	return 0;
}