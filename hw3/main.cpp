#include <iostream>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time() {
        this->hours = 0;
        this->minutes = 0;
        this->seconds = 0;
    }

    Time(const int h, const int m, const int s) {
        this->hours = h;
        this->minutes = m;
        this->seconds = s;
    }

    ~Time() {}

    Time(const Time &);

    void InternalPrint() const {
        std::cout << "HH:MM:SS\n" << hours << ":" << minutes << ":" << seconds << std::endl;
    }

    void SetHours(const int h) { this->hours = h; };

    void SetMinutes(const int m) { this->minutes = m; };

    void SetSeconds(const int);

    int GetHours() const;

    int GetMinutes() const;

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

    Time &operator+=(int s) {
        seconds += s;
        Normalize();
        return *this;
    }

    Time &operator-=(int s) {
        seconds -= s;
        Normalize();
        return *this;
    }
};

void Time::SetSeconds(const int s) { this->seconds = s; }

int Time::GetHours() const { return hours; }

int Time::GetMinutes() const { return minutes; }

Time::Time(const Time &t) {
    hours = t.hours;
    this->minutes = t.minutes;
    this->seconds = t.seconds;
}

Time operator+(const Time &t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

Time operator-(const Time &t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

bool operator==(const Time &a, const Time &b) {
    return a.GetHours() == b.GetHours() and a.GetMinutes() == b.GetMinutes() and a.GetSeconds() == b.GetSeconds();
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
    Time t;
    t.SetHours(36);
    t.SetSeconds(63);
    t.InternalPrint();
    std::cout << "Hours: " << t.GetHours() << std::endl;
    std::cout << "Seconds: " << t.GetSeconds() << std::endl;

    Time tt(23, -10, 5);
    Time t1 = tt;
    Time t2;
    t2 = tt;

    t += 40;
    std::cout << t << "\n";

    t += 60 * 60;
    std::cout << t << "\n";

    t += 60 * 60 * 11;
    std::cout << t << "\n";

    return 0;
}

