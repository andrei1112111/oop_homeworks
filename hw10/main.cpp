#include <iostream>
#include <vector>
#include <string>


using namespace std;


class GenericCreature {
public:
    virtual void eat() {};

    virtual void display() const {};

    virtual ~GenericCreature() = default;
protected:
    string name;
};


class OceanCreature : public virtual GenericCreature {
public:
    explicit OceanCreature(const string& name) {this->name = name;}

    void eat() override {
        cout << name << " eating sea food" << endl;
    }

    void display() const override {
        cout << "Оcean creature " << name << endl;
    }
};

class Amphibious : public OceanCreature {
public:
    explicit Amphibious(const string& name) : OceanCreature(name) {}

    void eat() override {
        cout << name << " eating land and sea food" << endl;
    }

    void walk() const {
        cout << name << " walking on land" << endl;
    }

    void display() const override {
        cout << "Amphibious creature " << name << endl;
    }
};

class TerrestrialCreature : public virtual GenericCreature {
public:
    explicit TerrestrialCreature(const string& name) {this->name = name;}

    void eat() override {
        cout << name << " eating land food" << endl;
    }

    void walk() const {
        cout << name << " walking on land" << endl;
    }

    void display() const override {
        cout << "Terrestrial creature " << name << endl;
    }
};

class Bird : public TerrestrialCreature {
public:
    explicit Bird(const string& name) : TerrestrialCreature(name) {}

    void eat() override {
        cout << name << " eating insects and seeds" << endl;
    }

    void fly() const {
        cout << name << " flying" << endl;
    }

    void display() const override {
        cout << "Bird " << name << endl;
    }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    explicit Waterfowl(const string& name) : Bird(name), OceanCreature(name) {}

    void eat() override {
        cout << name << " eating fish and plants from land and water" << endl;
    }

    void display() const override {
        cout << "waterfowl " << name << endl;
    }

    void swim() const {
        cout << name << " swimming." << endl;
    }
};


void demonstratePolymorphism(vector<GenericCreature*>& creatures) {
    for (auto* creature : creatures) {
        creature->eat();
        creature->display();
        cout << endl;
    }
}

int main() {
    vector<GenericCreature*> creatures;

    GenericCreature* c1 = new OceanCreature("Shark");
    GenericCreature* c2 = new Amphibious("Frog");
    GenericCreature* c3 = new TerrestrialCreature("Elephant");
    GenericCreature* c4 = new Bird("Sparrow");
    GenericCreature* c5 = new Waterfowl("Duck");

    creatures.push_back(c1);
    creatures.push_back(c2);
    creatures.push_back(c3);
    creatures.push_back(c4);
    creatures.push_back(c5);

    demonstratePolymorphism(creatures);

    delete c1; delete c2; delete c3; delete c4; delete c5;

    return 0;
}
