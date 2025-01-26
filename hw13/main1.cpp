#include <iostream>
#include <vector>


class House {
public:
    virtual void showHouse() const = 0;
    virtual ~House() = default;
};


class WoodHouse : public House {
    void showHouse() const override {
        std::cout << "This is a Wood House." << std::endl;
    }
};

class BrickHouse : public House {
    void showHouse() const override {
        std::cout << "This is a Brick House." << std::endl;
    }
};

class ConcreteHouse : public House {
    void showHouse() const override {
        std::cout << "This is a Concrete House." << std::endl;
    }
};


class Documentation {
public:
    void addPage(const std::string& page) {
        pages.push_back(page);
    }

    void showDocs() const {
        std::cout << "Documentation for the house:\n";
        for (const auto& page : pages) {
            std::cout << page << std::endl;
        }
    }

private:
    std::vector<std::string> pages;
};


class HouseBuilder {
public:
    virtual void buildWalls() = 0;
    virtual void buildFloor() = 0;
    virtual void buildRoof() = 0;
    virtual std::unique_ptr<House> getHouse() = 0;
    virtual std::unique_ptr<Documentation> getDocumentation() = 0;
    virtual ~HouseBuilder() = default;
};


class WoodHouseBuilder : public HouseBuilder {
public:
    WoodHouseBuilder() {
        house = std::make_unique<WoodHouse>();
        doc = std::make_unique<Documentation>();
    }

    void buildWalls() override {
        doc->addPage("Building wooden walls.");
        std::cout << "Building wooden walls." << std::endl;
    }

    void buildFloor() override {
        doc->addPage("Building wooden floor.");
        std::cout << "Building wooden floor." << std::endl;
    }

    void buildRoof() override {
        doc->addPage("Building wooden roof.");
        std::cout << "Building wooden roof." << std::endl;
    }

    std::unique_ptr<House> getHouse() override {
        return std::move(house);
    }

    std::unique_ptr<Documentation> getDocumentation() override {
        return std::move(doc);
    }

private:
    std::unique_ptr<House> house;
    std::unique_ptr<Documentation> doc;
};


class BrickHouseBuilder : public HouseBuilder {
public:
    BrickHouseBuilder() {
        house = std::make_unique<BrickHouse>();
        doc = std::make_unique<Documentation>();
    }

    void buildWalls() override {
        doc->addPage("Building brick walls.");
        std::cout << "Building brick walls." << std::endl;
    }

    void buildFloor() override {
        doc->addPage("Building brick floor.");
        std::cout << "Building brick floor." << std::endl;
    }

    void buildRoof() override {
        doc->addPage("Building brick roof.");
        std::cout << "Building brick roof." << std::endl;
    }

    std::unique_ptr<House> getHouse() override {
        return std::move(house);
    }

    std::unique_ptr<Documentation> getDocumentation() override {
        return std::move(doc);
    }

private:
    std::unique_ptr<House> house;
    std::unique_ptr<Documentation> doc;
};


class ConcreteHouseBuilder : public HouseBuilder {
public:
    ConcreteHouseBuilder() {
        house = std::make_unique<ConcreteHouse>();
        doc = std::make_unique<Documentation>();
    }

    void buildWalls() override {
        doc->addPage("Building concrete walls.");
        std::cout << "Building concrete walls." << std::endl;
    }

    void buildFloor() override {
        doc->addPage("Building concrete floor.");
        std::cout << "Building concrete floor." << std::endl;
    }

    void buildRoof() override {
        doc->addPage("Building concrete roof.");
        std::cout << "Building concrete roof." << std::endl;
    }

    std::unique_ptr<House> getHouse() override {
        return std::move(house);
    }

    std::unique_ptr<Documentation> getDocumentation() override {
        return std::move(doc);
    }

private:
    std::unique_ptr<House> house;
    std::unique_ptr<Documentation> doc;
};


class Director {
public:
    void constructWoodenHouse(HouseBuilder& builder) {
        builder.buildWalls();
        builder.buildFloor();
        builder.buildRoof();
    }

    void constructBrickHouse(HouseBuilder& builder) {
        builder.buildWalls();
        builder.buildFloor();
        builder.buildRoof();
    }

    void constructConcreteHouse(HouseBuilder& builder) {
        builder.buildWalls();
        builder.buildFloor();
        builder.buildRoof();
    }
};

int main() {
    Director director;

    WoodHouseBuilder woodBuilder;
    director.constructWoodenHouse(woodBuilder);
    auto woodHouse = woodBuilder.getHouse();
    auto woodDoc = woodBuilder.getDocumentation();

    BrickHouseBuilder brickBuilder;
    director.constructBrickHouse(brickBuilder);
    auto brickHouse = brickBuilder.getHouse();
    auto brickDoc = brickBuilder.getDocumentation();

    ConcreteHouseBuilder concreteBuilder;
    director.constructConcreteHouse(concreteBuilder);
    auto concreteHouse = concreteBuilder.getHouse();
    auto concreteDoc = concreteBuilder.getDocumentation();


    std::cout << "\nWooden House Documentation:\n";
    woodDoc->showDocs();

    std::cout << "\nBrick House Documentation:\n";
    brickDoc->showDocs();

    std::cout << "\nConcrete House Documentation:\n";
    concreteDoc->showDocs();

    return 0;
}
