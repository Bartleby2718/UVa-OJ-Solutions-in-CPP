#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

double getValue(int p, int q, int r, int s, int t, int u, double x)
{
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

bool doubleEquals(double d1, double d2)
{
    return abs(d1 - d2) <= numeric_limits<double>::epsilon();
}

int main()
{
    int p, q, r, s, t, u; // 0 ≤ p, r ≤ 20 and −20 ≤ q, s, t ≤ 0
    while (cin >> p >> q >> r >> s >> t >> u)
    {
        double from = 0, to = 1, mid;
        double fromValue = getValue(p, q, r, s, t, u, from);
        double toValue = getValue(p, q, r, s, t, u, to);
        // The derivative is negative in the interval [0, 1]
        // so no solution if it starts below 0 or ends above 0
        if (fromValue < 0 || toValue > 0)
        {
            cout << "No solution" << endl;
            continue;
        }
        while (mid = (from + to) / 2, !doubleEquals(from, to))
        {
            double midValue = getValue(p, q, r, s, t, u, mid);
            ((midValue > 0) ? from : to) = mid;
        }
        cout << fixed << setprecision(4) << mid << endl;
    }
    return 0;
}
