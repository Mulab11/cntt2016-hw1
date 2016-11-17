#include <vector>

class PenguinEmperor {
  public:
    int countJourneys(int numCities, long long daysPassed);

  private:
    static const int MOD = 1000000007;

    std::vector<int> countWaysToChoose(int n, long long m);
    std::vector<int> circularConvolution(const std::vector<int> &x, const std::vector<int> &y);
};

int PenguinEmperor::countJourneys(int numCities, long long daysPassed)
{
    std::vector<int> t1 = countWaysToChoose(numCities, daysPassed / numCities);
    std::vector<int> t2 = countWaysToChoose(numCities, daysPassed / numCities + 1);
    // f[i] = number of ways to end up in city i after processing
    // current distances
    std::vector<int> f(numCities);
    f[0] = 1;
    for (int i = 0; i < numCities; i++) {
        std::vector<int> u(numCities);
        if (i == 0 || i * 2 == numCities) {
            // Only one choice for each day
            int s = (daysPassed / numCities + (i >= 1 && i <= daysPassed % numCities)) % 2;
            u[i * s] = 1;
        } else if (i <= daysPassed % numCities) {
            for (int j = 0; j < numCities; j++) {
                int x = j * i % numCities;
                u[x] = (u[x] + t2[j]) % MOD;
            }
        } else {
            for (int j = 0; j < numCities; j++) {
                int x = j * i % numCities;
                u[x] = (u[x] + t1[j]) % MOD;
            }
        }
        f = circularConvolution(f, u);
    }
    return f[0];
}

std::vector<int> PenguinEmperor::countWaysToChoose(int n, long long m)
{
    std::vector<int> s(n);
    s[0] = 1;
    std::vector<int> x(n);
    x[1]++;
    x[n - 1]++;
    while (m) {
        if (m & 1) {
            s = circularConvolution(s, x);
        }
        x = circularConvolution(x, x);
        m >>= 1;
    }
    return s;
}

std::vector<int> PenguinEmperor::circularConvolution(const std::vector<int> &x, const std::vector<int> &y)
{
    int n = x.size();
    std::vector<int> z(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            z[(i + j) % n] = (z[(i + j) % n] + (long long)x[i] * y[j]) % MOD;
        }
    }
    return z;
}
