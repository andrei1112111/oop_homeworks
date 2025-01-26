#include <iostream>
#include <vector>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    static int count; // obj count

public:
    Time() {
        this->hours = 0;
        this->minutes = 0;
        this->seconds = 0;
        count++;
        std::cout << "constructor Time(), count: " << count << std::endl;
    }

    Time(const int h, const int m, const int s) {
        this->hours = h;
        this->minutes = m;
        this->seconds = s;
        count++;
        std::cout << "constructor Time(" << h << ", " << m << ", " << s << "), count: " << count << std::endl;
    }

    // Move constructor
    Time(Time&& t) noexcept {
        hours = t.hours;
        minutes = t.minutes;
        seconds = t.seconds;

        t.hours = 0;
        t.minutes = 0;
        t.seconds = 0;

        count++;
        std::cout << "move constructor, count: " << count << std::endl;
    }

    // Move assignment operator
    Time& operator=(Time&& t) noexcept {
        if (this != &t) {
            hours = t.hours;
            minutes = t.minutes;
            seconds = t.seconds;

            t.hours = 0;
            t.minutes = 0;
            t.seconds = 0;
        }
        std::cout << "move assignment, count: " << count << std::endl;
        return *this;
    }

    ~Time() {
        count--;
        std::cout << "destructor, count: " << count << std::endl;
    }

    Time(const Time& t) {
        hours = t.hours;
        minutes = t.minutes;
        seconds = t.seconds;
        count++;
        std::cout << "copy constructor, count: " << count << std::endl;
    }

    void InternalPrint() const {
        std::cout << "HH:MM:SS\n" << hours << ":" << minutes << ":" << seconds << std::endl;
    }

    void SetHours(const int h) { this->hours = h; }

    void SetMinutes(const int m) { this->minutes = m; }

    void SetSeconds(const int s) { this->seconds = s; }

    int GetHours() const { return hours; }

    int GetMinutes() const { return minutes; }

    int GetSeconds() const { return seconds; }

    int ToSeconds() {
        return this->seconds + (this->minutes * 60) + (this->hours * 60 * 60);
    }

    Time &operator=(const Time &other) {
        this->hours = other.hours;
        this->minutes = other.minutes;
        this->seconds = other.seconds;
        return *this;
    }

    void Normalize() {
        this->minutes += this->seconds / 60;
        this->seconds = this->seconds % 60;

        this->hours += this->minutes / 60;
        this->minutes = this->minutes % 60;

        this->hours = this->hours % 24;
    }

    void PrintTime() const{
        std::cout << "H:" << this->GetHours() << " M:" << this->GetMinutes() << " S:" << this->GetSeconds() << std::endl;
    }

    Time& operator+=(int s) {
        seconds += s;
        Normalize();
        return *this;
    }

    Time& operator-=(int s) {
        seconds -= s;
        Normalize();
        return *this;
    }

    static int getCount() {
        return count;
    }
};

int Time::count = 0;

Time operator+(const Time &t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

Time operator-(const Time &t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

bool operator==(const Time &a, const Time &b) {
    return a.GetHours() == b.GetHours() && a.GetMinutes() == b.GetMinutes() && a.GetSeconds() == b.GetSeconds();
}

std::ostream &operator<<(std::ostream &out, const Time &t) {
    out << t.GetHours() << ":" << t.GetMinutes() << ":" << t.GetSeconds();
    return out;
}

std::istream &operator>>(std::istream &in, Time &t) {
    int h, m, s;
    char tmp;
    in >> h >> tmp;
    in >> m >> tmp;
    in >> s >> tmp;

    t = Time(h, m, s);

    return in;
}

int main() {
    std::vector<Time> times;

    // rvalue
    times.push_back(Time(12, 30, 45)); // Move
    times.push_back(Time(15, 45, 30)); // Move

    // Добавление как lvalue
    Time t1(9, 15, 30);
    times.push_back(std::move(t1));  // Copy

    // Move
    Time t2(8, 20, 10);
    t2 = Time(5, 5, 5); // Move assignment

    // Просмотр объектов
    for (const auto& t : times) {
        std::cout << t << std::endl;
    }

    std::cout << "----------------------------------" << std::endl;

    // 1. Получение rvalue
    std::cout << "Adding rvalue to vector:" << std::endl;
    times.push_back(Time(12, 30, 45));

    // 2. Получение lvalue
    std::cout << "\nAdding lvalue to vector:" << std::endl;
    Time t11(9, 15, 30);
    times.push_back(t1);

    // 3. Получение rvalue
    std::cout << "\nUsing move assignment with rvalue:" << std::endl;
    Time t22(8, 20, 10);
    t2 = Time(5, 5, 5);

    // 4. Получение lvalue
    std::cout << "\nUsing move assignment with lvalue:" << std::endl;
    Time t33(7, 12, 50);

    return 0;
}
