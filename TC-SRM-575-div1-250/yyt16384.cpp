#include <string>

class TheNumberGameDivOne {
  public:
    std::string find(long long n);
};

std::string TheNumberGameDivOne::find(long long n)
{
    // First player wins if n is odd or 2^(2k+1)
    if (n % 2) {
        return "Brus";
    }
    int s = 0;
    while ((1LL << s) < n) {
        s++;
    }
    if ((1LL << s) == n && s % 2) {
        return "Brus";
    } else {
        return "John";
    }
}
