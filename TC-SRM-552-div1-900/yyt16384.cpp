#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

class HolyNumbers {
  public:
    long long count(long long upTo, int maximalPrime);

  private:
    std::vector<int> primes;
    std::vector<char> isprime;

    void initPrimes(int n);
};

long long HolyNumbers::count(long long upTo, int maximalPrime)
{
    initPrimes(maximalPrime);
    std::vector<int> primepi(maximalPrime + 1);
    for (int i = 1; i <= maximalPrime; i++) {
        primepi[i] = primepi[i - 1] + isprime[i];
    }
    std::unordered_map<long long, long long> fs = {{upTo, 1}};
    long long ans = 0;
    for (int i = 0; i < (int)primes.size(); i++) {
        int x = primes[i];
        std::unordered_map<long long, long long> gs;
        for (auto m : fs) {
            if (m.first < (long long)x * x) {
                // Only one more prime factor allowed, calculate the
                // answer directly
                ans += m.second * (1 + std::max(primepi[std::min<long long>(m.first, maximalPrime)] - i, 0));
            } else {
                gs[m.first] += m.second;
                long long t = m.first / x;
                while (t) {
                    gs[t] += m.second;
                    t /= (long long)x * x;
                }
            }
        }
        fs = std::move(gs);
    }
    for (auto m : fs) {
        ans += m.second;
    }
    return ans;
}

void HolyNumbers::initPrimes(int n)
{
    primes.clear();
    isprime.resize(n + 1, true);
    isprime[0] = false;
    isprime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < (int)primes.size() && i * primes[j] <= n; j++) {
            isprime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}
