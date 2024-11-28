#include <iostream>


using namespace std;


class House {
public:
    virtual void build() const = 0;
    virtual ~House() = default;
};

class WoodHouse : public House {
public:
    void build() const override {
        cout << "Building Wooden House" << endl;
    }
};

class BrickHouse : public House {
public:
    void build() const override {
        cout << "Building Brick House" << endl;
    }
};

class ConcreteHouse : public House {
public:
    void build() const override {
        cout << "Building Concrete House" << endl;
    }
};


class Developer {
public:
    virtual House* buildHouse() const = 0;
    virtual ~Developer() = default;
};

class WoodHouseDeveloper : public Developer {
public:
    House* buildHouse() const override {
        return new WoodHouse();
    }
};

class BrickHouseDeveloper : public Developer {
public:
    House* buildHouse() const override {
        return new BrickHouse();
    }
};

class ConcreteHouseDeveloper : public Developer {
public:
    House* buildHouse() const override {
        return new ConcreteHouse();
    }
};


void buildQuarter(Developer& developer, int numHouses) {
    cout << "Building " << numHouses << " houses..." << endl;
    vector<unique_ptr<House>> houses;

    for (int i = 0; i < numHouses; ++i) {
        unique_ptr<House> house(developer.buildHouse());
        houses.push_back(std::move(house));
    }

    for (const auto& house : houses) {
        house->build();
    }

    cout << "Built!" << endl << endl;
}

int main() {
    WoodHouseDeveloper woodDeveloper;
    buildQuarter(woodDeveloper, 6);

    BrickHouseDeveloper brickDeveloper;
    buildQuarter(brickDeveloper, 8);

    ConcreteHouseDeveloper concreteDeveloper;
    buildQuarter(concreteDeveloper, 10);

    return 0;
}
