#include <iostream>
#include <string>


class GenericCreature {
public:
    explicit GenericCreature(const std::string &name) : name(name) {
    }

    void display() const {
        std::cout << "I am " << name << std::endl;
    }

    virtual void eat() const {
        std::cout << "I am eating" << name << std::endl;
    };

protected:
    std::string name;
};

class OceanCreature : virtual public GenericCreature {
public:
    explicit OceanCreature(const std::string &name) : GenericCreature(name) {
    }

    void swim() const {
        std::cout << name << " swimming" << std::endl;
    }

    void eat() const override {
        std::cout << name << " eats fish." << std::endl;
    }
};

class TerrestrialCreature : virtual public GenericCreature {
public:
    explicit TerrestrialCreature(const std::string &name) : GenericCreature(name) {
    }

    void walk() const {
        std::cout << name << " walking" << std::endl;
    }

    void eat() const override {
        std::cout << name << " eats plants." << std::endl;
    }
};

class Amphibious : virtual public OceanCreature, virtual public TerrestrialCreature {
public:
    explicit Amphibious(const std::string &name) : OceanCreature(name), TerrestrialCreature(name),
                                                   GenericCreature(name) {
    }

    void eat() const override {
        std::cout << name << " eats plants and fish." << std::endl;
    }
};

class Bird : virtual public TerrestrialCreature {
public:
    explicit Bird(const std::string &name) : TerrestrialCreature(name), GenericCreature(name) {
    }

    void fly() const {
        std::cout << name << " flying" << std::endl;
    }

    void eat() const override {
        std::cout << name << " eats insects and seeds." << std::endl;
    }
};

class Waterfowl : virtual public Bird, virtual public OceanCreature {
public:
    explicit Waterfowl(const std::string &name)
        : Bird(name), TerrestrialCreature(name), GenericCreature(name), OceanCreature(name) {
    }

    void eat() const override {
        std::cout << name << " eats small aquatic animals." << std::endl;
    }
};

int main() {
    GenericCreature* creatures[] = {
        new OceanCreature("Ocean Creature"),
        new TerrestrialCreature("Terrestrial Creature"),
        new Amphibious("Amphibious Creature"),
        new Bird("Bird"),
        new Waterfowl("Waterfowl")
    };

    std::cout << "\n";
    for (auto* creature : creatures) {
        creature->eat();
        std::cout << std::endl;
    }

    std::cout << "\n\n";


    OceanCreature oceanCreature("Ocean Creature");
    TerrestrialCreature terrestrialCreature("Terrestrial Creature");
    Amphibious amphibiousCreature("Amphibious Creature");
    Bird bird("Bird");
    Waterfowl waterfowl("Waterfowl");

    GenericCreature creaturesObj[] = { oceanCreature, terrestrialCreature, amphibiousCreature, bird, waterfowl };

    for (auto creature : creaturesObj) {
        creature.eat();
        std::cout << std::endl;
    }

    return 0;
}

