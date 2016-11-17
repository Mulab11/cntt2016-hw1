#include <algorithm>
#include <vector>

class SpellCards {
  public:
    int maxDamage(std::vector<int> level, std::vector<int> damage);
};

int SpellCards::maxDamage(std::vector<int> level, std::vector<int> damage)
{
    int n = level.size();
    // It is always possible to use any set of cards with total cost <=
    // n
    // f[i] = maximum damage after using cards with total level <= i
    std::vector<int> f(n + 1);
    for (int i = 0; i < n; i++) {
        for (int j = n; j >= level[i]; j--) {
            f[j] = std::max(f[j], f[j - level[i]] + damage[i]);
        }
    }
    return f[n];
}
