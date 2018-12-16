#include <iostream>
using namespace std;

#include <array>

template<bool... digits> int reversed_binary_value()
{
    /* Get an array of bools from variadic template. */
    const std::array<bool, sizeof...(digits)> bits{digits...};
    int value = 0;
    /* Loop through "bits" array. */
    for (unsigned int i = 0; i < bits.size(); i++) {
        /* If true then corresponding bit is set. */
        if (bits[i]) {
            value |= (1 << i);
        }
    }

    return value;
}

template <int n, bool...digits>
struct CheckValues {
    static void check(int x, int y)
    {
        CheckValues<n-1, 0, digits...>::check(x, y);
        CheckValues<n-1, 1, digits...>::check(x, y);
    }
};

template <bool...digits>
struct CheckValues<0, digits...> {
    static void check(int x, int y)
    {
        int z = reversed_binary_value<digits...>();
        std::cout << (z+64*y==x);
    }
};

int main()
{
    int t; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int x, y;
        cin >> x >> y;
        CheckValues<6>::check(x, y);
        cout << "\n";
    }
}
