#include <iostream>
using std::cin, std::cout;

int main()
{   
    int days_arr[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int y1, m1, d1, h1, min1, s1, y2, m2, d2, h2, min2, s2;
    cin >> y1 >> m1 >> d1 >> h1 >> min1 >> s1;
    cin >> y2 >> m2 >> d2 >> h2 >> min2 >> s2;


    int days = (y2 - y1) * 365;
    for (int month = 1; month < m2; ++month) {
        days += days_arr[month - 1];
    }

    for (int month = 1; month < m1; ++month) {
        days -= days_arr[month - 1];
    }

    days = days - d1 + d2;

    int sec = (h2 - h1) * 3600 + (min2 - min1) * 60 + s2 - s1;
    if (sec < 0) {
        days -= 1;
        sec += 24 * 3600;
    }
    cout << days << ' ' << sec;

    return 0;
}
