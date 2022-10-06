//home 
#include <iostream>

using namespace std;

class Building {
protected:
    double  square;
    double usableSquare;
public: 
    Building() 
    {
    }
    Building(double square, double usableSquare) {
        this->square = square;
        this->usableSquare = usableSquare;
    }
    virtual double GetUselessSquare() = 0;
    virtual void display() = 0;
    virtual ~Building() {}
};

class ProductionBuilding : public Building {
protected:
    double squareTechnicalRooms;
public:
    ProductionBuilding(double square, double usableSquare, double squareTechnicalRooms): Building(square, usableSquare)
    {
        this->squareTechnicalRooms = squareTechnicalRooms;
    }
    virtual double GetUselessSquare() override 
    {
       return  square -= (usableSquare + squareTechnicalRooms);
    }
    virtual void display() {
        cout << "\nProduction building: \n" << "Square: " << square
            << " Usable square: " << usableSquare
            << " Square technical rooms: " << squareTechnicalRooms
            << endl;
    }
    virtual ~ProductionBuilding() {}

};

class Electrostation : public ProductionBuilding {
private:
    double squareCoolingShop;
public:
    Electrostation(double square, double usableSquare, double squareTechnicalRooms, double squareCoolingShop) : ProductionBuilding(square, usableSquare, squareTechnicalRooms)
    {
        this->squareCoolingShop = squareCoolingShop;
    }
    virtual double GetUselessSquare() override
    {
        return  square -= (usableSquare + squareTechnicalRooms+squareCoolingShop);
    }
    virtual void display() {
        cout << "\nElectrostation: \n" << "Square: " << square
            << " Usable square: " << usableSquare
            << " Square technical rooms: " << squareTechnicalRooms
            <<" Square cooling shop: "<< squareCoolingShop
            << endl;
    }
    virtual ~Electrostation() {}

};

class ResidentialBuilding : public Building {
protected:
    double squareTechnicalRooms;
public:
    ResidentialBuilding(double square, double usableSquare, double squareTechnicalRooms) : Building(square, usableSquare)
    {
        this->squareTechnicalRooms = squareTechnicalRooms;
    }
    virtual double GetUselessSquare() override
    {
        return  square -= (usableSquare + squareTechnicalRooms);
    }
    virtual void display() {
        cout << "\nResidential building: \n" << "Square: " << square
            << " Usable square: " << usableSquare
            << " Square technical rooms: " << squareTechnicalRooms
            << endl;
    }
    virtual ~ResidentialBuilding() {}

};

int main()
{
    Building** buildings = new Building*[3];
    buildings[0] = new ProductionBuilding(1500, 632.54, 234.64);
    buildings[1] = new ResidentialBuilding(232.43, 198.87, 13.32);
    buildings[2] = new Electrostation(5008.23, 1234.53,987.2 ,2345.12);

    for (int i = 0; i < 3; i++) {
        buildings[i]->display();
        cout << "Useless square: " << buildings[i]->GetUselessSquare() << endl;
    }
    return 0;
}

