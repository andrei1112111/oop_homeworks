#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class GenericCreature {
public:
    explicit GenericCreature(const std::string &name) : name(name) {}

    void display() const {
        std::cout << "I am " << name << std::endl;
    }

    virtual void eat() const {
        std::cout << "I am eating " << name << std::endl;
    }

protected:
    std::string name;
};

class OceanCreature : virtual public GenericCreature {
public:
    explicit OceanCreature(const std::string &name) : GenericCreature(name) {}

    void swim() const {
        std::cout << name << " swimming" << std::endl;
    }

    void eat() const override {
        std::cout << name << " eats fish." << std::endl;
    }
};

class TerrestrialCreature : virtual public GenericCreature {
public:
    explicit TerrestrialCreature(const std::string &name) : GenericCreature(name) {}

    void walk() const {
        std::cout << name << " walking" << std::endl;
    }

    void eat() const override {
        std::cout << name << " eats plants." << std::endl;
    }
};

class Amphibious : public OceanCreature, public TerrestrialCreature {
public:
    explicit Amphibious(const std::string &name)
        : GenericCreature(name), OceanCreature(name), TerrestrialCreature(name) {}

    void eat() const override {
        std::cout << name << " eats plants and fish." << std::endl;
    }
};

class Bird : virtual public TerrestrialCreature {
public:
    explicit Bird(const std::string &name) : TerrestrialCreature(name), GenericCreature(name) {}

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
        : Bird(name), TerrestrialCreature(name), GenericCreature(name), OceanCreature(name) {}

    void eat() const override {
        std::cout << name << " eats small aquatic animals." << std::endl;
    }
};

class Crocodile : public Amphibious {
public:
    explicit Crocodile(const string& name) : Amphibious(name) {}

    void eat() const {
        cout << name << " eating legs and hands" << endl;
    }

    void display() const {
        cout << "Crocodile " << name << endl;
    }
};

class Alligator : public Amphibious {
public:
    explicit Alligator(const string& name) : Amphibious(name) {}

    void eat() const {
        cout << name << " eating meat" << endl;
    }

    void display() const {
        cout << "Alligator " << name << endl;
    }
};

class Pigeon : public Bird {
public:
    explicit Pigeon(const string& name) : Bird(name) {}

    void eat() const {
        cout << name << " eating seeds and grains" << endl;
    }

    void display() const {
        cout << "Pigeon " << name << endl;
    }
};

class Parrot : public Bird {
public:
    explicit Parrot(const string& name) : Bird(name) {}

    void eat() const {
        cout << name << " eating fruits and nuts" << endl;
    }

    void display() const {
        cout << "Parrot " << name << endl;
    }
};

class Creator {
public:
    virtual unique_ptr<GenericCreature> createCreature(const string& name) = 0;
    virtual ~Creator() = default;
};

class AmphibiousCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature(const string& name) override {
        if (name == "Crocodile") {
            return unique_ptr<GenericCreature>(new Crocodile(name));
        } else if (name == "Alligator") {
            return unique_ptr<GenericCreature>(new Alligator(name));
        }
        return nullptr;
    }
};

class BirdCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature(const string& name) override {
        if (name == "Pigeon") {
            return unique_ptr<GenericCreature>(new Pigeon(name));
        } else if (name == "Parrot") {
            return unique_ptr<GenericCreature>(new Parrot(name));
        }
        return nullptr;
    }
};

void demonstratePolymorphism(vector<unique_ptr<GenericCreature>>& creatures) {
    for (auto& creature : creatures) {
        creature->eat();
        creature->display();
        cout << endl;
    }
}

int main() {
    vector<unique_ptr<GenericCreature>> creatures;

    AmphibiousCreator amphibiousCreator;
    creatures.push_back(amphibiousCreator.createCreature("Crocodile"));
    creatures.push_back(amphibiousCreator.createCreature("Alligator"));

    BirdCreator birdCreator;
    creatures.push_back(birdCreator.createCreature("Pigeon"));
    creatures.push_back(birdCreator.createCreature("Parrot"));

    demonstratePolymorphism(creatures);

    return 0;
}
