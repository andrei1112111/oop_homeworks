#include <iostream>
#include "mytime.h"


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

    std::cout << "\nCURRENT COUNT: " << Time::getCount() << std::endl << std::endl;

    {
        Time t;
        t.SetHours(1);
        Time t2 = t;
        t2.SetHours(2);
        t2.PrintTime();
        {
            t2.SetHours(12);
            t2.PrintTime();
            Time t2(22, 22, 22);
            t2.PrintTime();
        }
        t2.PrintTime();
        Time t3(3, 3, 3);
        t3 = t;
        t3.SetHours(3);
        t3.PrintTime();
    }


    return 0;
}
