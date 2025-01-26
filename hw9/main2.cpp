#include <iostream>
#include <string>


class GenericCreature {
public:
    explicit GenericCreature(const std::string &name) : name(name) {
    }

    void display() const {
        std::cout << "I am " << name << std::endl;
    }

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
};

class TerrestrialCreature : virtual public GenericCreature {
public:
    explicit TerrestrialCreature(const std::string &name) : GenericCreature(name) {
    }

    void walk() const {
        std::cout << name << " walking" << std::endl;
    }
};

class Amphibious : virtual public OceanCreature, virtual public TerrestrialCreature {
public:
    explicit Amphibious(const std::string &name) : OceanCreature(name), TerrestrialCreature(name),
                                                   GenericCreature(name) {
    }
};

class Bird : virtual public TerrestrialCreature {
public:
    explicit Bird(const std::string &name) : TerrestrialCreature(name), GenericCreature(name) {
    }

    void fly() const {
        std::cout << name << " flying" << std::endl;
    }
};

class Waterfowl : virtual public Bird, virtual public OceanCreature {
public:
    explicit Waterfowl(const std::string &name)
        : Bird(name), TerrestrialCreature(name), GenericCreature(name), OceanCreature(name) {
    }
};

int main() {
    GenericCreature creature("Creature");
    creature.display();

    OceanCreature oceanCreature("Ocean Creature");
    oceanCreature.display();
    oceanCreature.swim();

    Amphibious amphibious("Amphibious Creature");
    amphibious.display();
    amphibious.swim();
    amphibious.walk();

    TerrestrialCreature terrestrial("Terrestrial Creature");
    terrestrial.display();
    terrestrial.walk();

    Bird bird("Bird");
    bird.display();
    bird.walk();
    bird.fly();

    Waterfowl waterfowl("Waterfowl");
    waterfowl.display();
    waterfowl.walk();
    waterfowl.fly();
    waterfowl.swim();

    return 0;
}
