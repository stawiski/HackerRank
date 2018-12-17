#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;

// Define specializations for the Traits class template here.

template<> struct Traits<Fruit>
{
    static const std::string name(const int index) {
        std::string str = "unknown";
        switch (index) {
            case static_cast<int>(Fruit::apple):
            {
                str = "apple";
                break;
            }
            case static_cast<int>(Fruit::orange):
            {
                str = "orange";
                break;
            }
            case static_cast<int>(Fruit::pear):
            {
                str = "pear";
                break;
            }
        }
        return str;
    }
};

template<> struct Traits<Color>
{
    static const std::string name(const int index) {
        std::string str = "unknown";
        switch (index) {
            case static_cast<int>(Color::red):
            {
                str = "red";
                break;
            }
            case static_cast<int>(Color::green):
            {
                str = "green";
                break;
            }
            case static_cast<int>(Color::orange):
            {
                str = "orange";
                break;
            }
        }
        return str;
    }
};

int main()
{
    int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
