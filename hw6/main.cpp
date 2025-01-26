#include <iostream>
#include <stdexcept>
#include <memory>


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


class Time {
private:
    int hours;
    int minutes;
    int seconds;

    static int count; // obj count

    void validateTime() const {
        if (hours < 0 || hours >= 24) {
            throw std::invalid_argument("Invalid hours value: " + std::to_string(hours));
        }
        if (minutes < 0 || minutes >= 60) {
            throw std::invalid_argument("Invalid minutes value: " + std::to_string(minutes));
        }
        if (seconds < 0 || seconds >= 60) {
            throw std::invalid_argument("Invalid seconds value: " + std::to_string(seconds));
        }
    }

public:
    Time() noexcept {
        this->hours = 0;
        this->minutes = 0;
        this->seconds = 0;
        count++;
        std::cout << "constructor Time(), count: " << count << std::endl;
    }

    Time(int h, int m, int s) {
        if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
            throw std::invalid_argument("Invalid time values: " + std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s));
        }
        hours = h;
        minutes = m;
        seconds = s;
        count++;
        std::cout << "constructor Time(" << h << ", " << m << ", " << s << "), count: " << count << std::endl;
    }

    ~Time() noexcept {
        count--;
        std::cout << "destructor, count: " << count << std::endl;
    }

    Time(const Time &t) noexcept {
        hours = t.hours;
        minutes = t.minutes;
        seconds = t.seconds;
        count++;
        std::cout << "copy constructor, count: " << count << std::endl;
    }

    void InternalPrint() const noexcept {
        std::cout << "HH:MM:SS\n" << hours << ":" << minutes << ":" << seconds << std::endl;
    }

    void SetHours(int h) {
        if (h < 0 || h >= 24) {
            throw std::invalid_argument("Invalid hours value: " + std::to_string(h));
        }
        hours = h;
    }

    void SetMinutes(int m) {
        if (m < 0 || m >= 60) {
            throw std::invalid_argument("Invalid minutes value: " + std::to_string(m));
        }
        minutes = m;
    }

    void SetSeconds(int s) {
        if (s < 0 || s >= 60) {
            throw std::invalid_argument("Invalid seconds value: " + std::to_string(s));
        }
        seconds = s;
    }

    int GetHours() const noexcept { return hours; }

    int GetMinutes() const noexcept { return minutes; }

    int GetSeconds() const noexcept { return seconds; }

    int ToSeconds() const noexcept {
        return seconds + (minutes * 60) + (hours * 60 * 60);
    }

    Time& operator=(const Time &other) noexcept {
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
        return *this;
    }

    void Normalize() noexcept {
        minutes += seconds / 60;
        seconds = seconds % 60;
        hours += minutes / 60;
        minutes = minutes % 60;
        hours = hours % 24;
    }

    void PrintTime() const noexcept {
        std::cout << "H:" << hours << " M:" << minutes << " S:" << seconds << std::endl;
    }

    Time& operator+=(int s) noexcept {
        seconds += s;
        Normalize();
        return *this;
    }

    Time& operator-=(int s) noexcept {
        seconds -= s;
        Normalize();
        return *this;
    }

    static int getCount() noexcept {
        return count;
    }
};

int Time::count = 0;

Time operator+(const Time &t, int s) {
    Time newTime(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
    newTime.Normalize();
    return newTime;
}

Time operator-(const Time &t, int s) {
    Time newTime(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
    newTime.Normalize();
    return newTime;
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
    try {
        Time t1(25, 61, 61);
    } catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    try {
        Time t2;
        t2.SetHours(25);
    } catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    Time* t1 = new Time(12, 30, 45);
    t1->PrintTime();
    delete t1;

    Time* tArray = new Time[3];
    for (int i = 0; i < 3; ++i) {
        tArray[i].PrintTime();
    }
    delete[] tArray;

    std::cout << std::endl << "!!!" << std::endl;

    std::vector<Time> timeVec;
    timeVec.push_back(Time(12, 30, 45));
    timeVec.push_back(Time(14, 45, 55));
    timeVec.push_back(Time(18, 20, 30));
    for (const auto& t : timeVec) {
        t.PrintTime();
    }

    std::shared_ptr<Time> tShared = std::make_shared<Time>(12, 30, 45);
    tShared->PrintTime();

    std::unique_ptr<Time> tUnique = make_unique<Time>(12, 30, 45);
    tUnique->PrintTime();

    return 0;
}
