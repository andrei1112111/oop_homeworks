#include <iostream>


using namespace std;


class GearStrategy {
public:
    virtual double calculateSpeed(double rpm) const = 0;
    virtual ~GearStrategy() = default;
};


class Gear1Strategy : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm / 1000 * 1.2;
    }
};


class Gear2Strategy : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm / 1000 * 2.4;
    }
};


class Gear3Strategy : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm / 1000 * 3.6;
    }
};


class Gear4Strategy : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm / 1000 * 4.8;
    }
};


class Gear5Strategy : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm / 1000 * 6.0;
    }
};


class ReverseGearStrategy : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return -(rpm / 1000 * 1.5);
    }
};


class Car {
private:
    double rpm;
    shared_ptr<GearStrategy> currentGearStrategy;

public:
    Car(double rpm = 0, shared_ptr<GearStrategy> initialStrategy = make_shared<Gear1Strategy>())
        : rpm(rpm), currentGearStrategy(initialStrategy) {}

    double getSpeed() const {
        return currentGearStrategy->calculateSpeed(rpm);
    }

    void changeGear(std::unique_ptr<GearStrategy> &&strategy) {
        currentGearStrategy = std::move(strategy);
    }

    void printCarInfo() const {
        cout << "RPM: " << rpm << " | Speed: " << getSpeed() << " km/h" << endl;
    }
};


int main() {
    Car car(3000);

    car.printCarInfo();
    car.changeGear(make_unique<Gear1Strategy>());
    car.printCarInfo();
    car.changeGear(make_unique<Gear2Strategy>());
    car.printCarInfo();
    car.changeGear(make_unique<Gear3Strategy>());
    car.printCarInfo();
    car.changeGear(make_unique<Gear4Strategy>());
    car.printCarInfo();
    car.changeGear(make_unique<ReverseGearStrategy>());
    car.printCarInfo();

    return 0;
}
