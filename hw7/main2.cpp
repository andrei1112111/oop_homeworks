#include <iostream>
#include <stdexcept>


class Time;
class Watch;


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
    Time() noexcept : hours(0), minutes(0), seconds(0) {
        count++;
        std::cout << "constructor Time(), count: " << count << std::endl;
    }

    Time(int h, int m, int s) {
        if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
            throw std::invalid_argument(
                "Invalid time values: " + std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s));
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

    Time(const Time &t) noexcept : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {
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

    Time &operator=(const Time &other) noexcept {
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

    Time &operator+=(int s) noexcept {
        seconds += s;
        Normalize();
        return *this;
    }

    Time &operator-=(int s) noexcept {
        seconds -= s;
        Normalize();
        return *this;
    }

    static int getCount() noexcept {
        return count;
    }

    void PrintTime24() const noexcept {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }

    void PrintTime12() const noexcept {
        int hour12 = hours % 12;
        if (hour12 == 0) hour12 = 12; // 12 AM or 12 PM
        std::string am_pm = (hours < 12) ? "AM" : "PM";
        std::cout << hour12 << ":" << minutes << ":" << seconds << " " << am_pm << std::endl;
    }

    friend Watch;
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


class Watch {
private:
    bool is24HourFormat = true;
    Time *time_;

public:
    explicit Watch(Time *t) : time_(t) {
        std::cout << "Watch constructor called." << std::endl;
    }

    ~Watch() {
        std::cout << "Watch deconstructor called." << std::endl;
    }

    void ShowTime() const;

    void SetTime(int h, int m, int s);

    void SetFormat(bool format24);
};


void Watch::ShowTime() const {
    std::cout << "Watch Time: ";
    if (is24HourFormat) {
        time_->PrintTime24();
    } else {
        time_->PrintTime12();
    }
}

// Set format to either 24-hour or 12-hour
void Watch::SetFormat(bool format24) {
    is24HourFormat = format24;
}

void Watch::SetTime(int h, int m, int s) {
    time_->SetHours(h);
    time_->SetMinutes(m);
    time_->SetSeconds(s);
}


class WallClock : public Watch {
public:
    WallClock(Time *t) : Watch(t) {
        std::cout << "WallClock constructor called." << std::endl;
    }

    ~WallClock() {
        std::cout << "WallClock deconstructor called." << std::endl;
    }
};

class CuckooClock : public WallClock {
public:
    CuckooClock(Time *t) : WallClock(t) {
        std::cout << "CuckooClock constructor called." << std::endl;
    }

    ~CuckooClock() {
        std::cout << "CuckooClock deconstructor called." << std::endl;
    }
};

class SmartWatch : public Watch {
public:
    SmartWatch(Time *t) : Watch(t) {
        std::cout << "SmartWatch constructor called." << std::endl;
    }

    ~SmartWatch() {
        std::cout << "SmartWatch deconstructor called." << std::endl;
    }
};


int main() {
    Time t(10, 30, 45);

    std::cout << "-----w" << std::endl;
    Watch Watch1(&t);

    Watch1.SetTime(1, 2, 3);
    Watch1.ShowTime();

    std::cout << "-----wc" << std::endl;
    WallClock WallClock1(&t);

    WallClock1.ShowTime();


    Watch1.SetTime(19, 2, 33);

    std::cout << "-----cc" << std::endl;
    CuckooClock CuckooClock1(&t);
    CuckooClock1.SetFormat(true);
    CuckooClock1.ShowTime();

    std::cout << "-----sw" << std::endl;
    SmartWatch SmartWatch1(&t);
    SmartWatch1.SetFormat(false);
    SmartWatch1.ShowTime();

    std::cout << "-----dec" << std::endl;

    return 0;
}


// 11.1 | 14(все) | 12.1(+12.2 рассуждения) | 13 | 15
// ----   -------  -----------------------
// 0      00          0                         0
