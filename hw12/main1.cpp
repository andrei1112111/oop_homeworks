#include <iostream>
#include <vector>


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

class Fence {
public:
    virtual void build() const = 0;
    virtual ~Fence() = default;
};

class WoodFence : public Fence {
public:
    void build() const override {
        cout << "Building Wooden Fence" << endl;
    }
};

class BrickFence : public Fence {
public:
    void build() const override {
        cout << "Building Brick Fence" << endl;
    }
};

class ConcreteFence : public Fence {
public:
    void build() const override {
        cout << "Building Concrete Fence" << endl;
    }
};

class Barn {
public:
    virtual void build() const = 0;
    virtual ~Barn() = default;
};

class WoodBarn : public Barn {
public:
    void build() const override {
        cout << "Building Wooden Barn" << endl;
    }
};

class BrickBarn : public Barn {
public:
    void build() const override {
        cout << "Building Brick Barn" << endl;
    }
};

class ConcreteBarn : public Barn {
public:
    void build() const override {
        cout << "Building Concrete Barn" << endl;
    }
};


class Developer {
public:
    virtual House* buildHouse() const = 0;
    virtual Fence* buildFence() const = 0;
    virtual Barn* buildBarn() const = 0;
    virtual ~Developer() = default;
};


class WoodDeveloper : public Developer {
public:
    House* buildHouse() const override {
        return new WoodHouse();
    }
    Fence* buildFence() const override {
        return new WoodFence();
    }
    Barn* buildBarn() const override {
        return new WoodBarn();
    }
};

class BrickDeveloper : public Developer {
public:
    House* buildHouse() const override {
        return new BrickHouse();
    }
    Fence* buildFence() const override {
        return new BrickFence();
    }
    Barn* buildBarn() const override {
        return new BrickBarn();
    }
};

class ConcreteDeveloper : public Developer {
public:
    House* buildHouse() const override {
        return new ConcreteHouse();
    }
    Fence* buildFence() const override {
        return new ConcreteFence();
    }
    Barn* buildBarn() const override {
        return new ConcreteBarn();
    }
};

void buildQuarter(Developer& developer, int numHouses) {
    cout << "Building " << numHouses << " houses..." << endl;

    vector<unique_ptr<House>> houses;
    vector<unique_ptr<Fence>> fences;
    vector<unique_ptr<Barn>> barns;

    for (int i = 0; i < numHouses; ++i) {
        houses.push_back(unique_ptr<House>(developer.buildHouse()));
        fences.push_back(unique_ptr<Fence>(developer.buildFence()));
        barns.push_back(unique_ptr<Barn>(developer.buildBarn()));
    }

    for (const auto& house : houses) {
        house->build();
    }

    for (const auto& fence : fences) {
        fence->build();
    }

    for (const auto& barn : barns) {
        barn->build();
    }

    cout << "Built!" << endl << endl;
}

int main() {
    WoodDeveloper woodDeveloper;
    buildQuarter(woodDeveloper, 6);

    BrickDeveloper brickDeveloper;
    buildQuarter(brickDeveloper, 8);

    ConcreteDeveloper concreteDeveloper;
    buildQuarter(concreteDeveloper, 10);

    return 0;
}
