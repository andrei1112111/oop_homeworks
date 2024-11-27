#include <iostream>
#include <string>


class GenericCreature {
public:
    explicit GenericCreature(const std::string &name) : name(name) {}

    void display() const {
        std::cout << "I am " << name << std::endl;
    }

protected:
    std::string name;
};

class OceanCreature : public GenericCreature {
public:
    explicit OceanCreature(const std::string &name) : GenericCreature(name) {}

    void swim() const {
        std::cout << name << " swimming" << std::endl;
    }
};

class Amphibious : public OceanCreature {
public:
    explicit Amphibious(const std::string &name) : OceanCreature(name) {}

    void walk() const {
        std::cout << name << " walking" << std::endl;
    }
};

class TerrestrialCreature : public GenericCreature {
public:
    explicit TerrestrialCreature(const std::string &name) : GenericCreature(name) {}

    void walk() const {
        std::cout << name << " walking" << std::endl;
    }
};

class Bird : public TerrestrialCreature {
public:
    explicit Bird(const std::string &name) : TerrestrialCreature(name) {}

    void fly() const {
        std::cout << name << " flying" << std::endl;
    }
};

class Waterfowl : public Bird {
public:
    explicit Waterfowl(const std::string &name) : Bird(name) {}

    void swim() const {
        std::cout << name << " swimming" << std::endl;
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
