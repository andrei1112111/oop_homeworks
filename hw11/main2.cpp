#include <iostream>
#include <vector>
#include <string>
#include <memory>


using namespace std;


class GenericCreature {
public:
    virtual void eat() = 0;
    virtual void display() const = 0;
    virtual ~GenericCreature() = default;

protected:
    string name;
};

class OceanCreature : public virtual GenericCreature {
public:
    explicit OceanCreature(const string& name) { this->name = name; }

    void eat() override {
        cout << name << " eating sea food" << endl;
    }

    void display() const override {
        cout << "Ocean creature " << name << endl;
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

class Crocodile : public Amphibious {
public:
    explicit Crocodile(const string& name) : Amphibious(name) {}

    void eat() override {
        cout << name << " eating legs and hands" << endl;
    }

    void display() const override {
        cout << "Crocodile " << name << endl;
    }
};

class Alligator : public Amphibious {
public:
    explicit Alligator(const string& name) : Amphibious(name) {}

    void eat() override {
        cout << name << " eating meat" << endl;
    }

    void display() const override {
        cout << "Alligator " << name << endl;
    }
};

class TerrestrialCreature : public virtual GenericCreature {
public:
    explicit TerrestrialCreature(const string& name) { this->name = name; }

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

class Pigeon : public Bird {
public:
    explicit Pigeon(const string& name) : Bird(name) {}

    void eat() override {
        cout << name << " eating seeds and grains" << endl;
    }

    void display() const override {
        cout << "Pigeon " << name << endl;
    }
};

class Parrot : public Bird {
public:
    explicit Parrot(const string& name) : Bird(name) {}

    void eat() override {
        cout << name << " eating fruits and nuts" << endl;
    }

    void display() const override {
        cout << "Parrot " << name << endl;
    }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    explicit Waterfowl(const string& name) : Bird(name), OceanCreature(name) {}

    void eat() override {
        cout << name << " eating fish and plants from land and water" << endl;
    }

    void display() const override {
        cout << "Waterfowl " << name << endl;
    }

    void swim() const {
        cout << name << " swimming." << endl;
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
