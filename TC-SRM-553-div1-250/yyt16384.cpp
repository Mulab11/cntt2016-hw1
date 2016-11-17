#include <stack>
#include <vector>

class Suminator {
  public:
    int findMissing(std::vector<int> program, int wantedResult);

  private:
    long long getResult(const std::vector<int> &a);
};

int Suminator::findMissing(std::vector<int> program, int wantedResult)
{
    int pos = -1;
    for (int i = 0; i < (int)program.size(); i++) {
        if (program[i] == -1) {
            pos = i;
            break;
        }
    }
    std::vector<int> c = program;
    // Try changing it into 0
    c[pos] = 0;
    if (getResult(c) == wantedResult) {
        return 0;
    }
    // Try changing it into 1
    c[pos] = 1;
    long long s1 = getResult(c);
    if (s1 == wantedResult) {
        return 1;
    }
    if (wantedResult < s1) {
        // Cannot make the answer smaller
        return -1;
    }
    c[pos] = 2;
    long long s2 = getResult(c);
    if (s1 == s2) {
        // Answer is independent of x
        return -1;
    } else {
        return wantedResult - s1 + 1;
    }
}

long long Suminator::getResult(const std::vector<int> &a)
{
    std::stack<long long> s;
    for (auto x : a) {
        if (x == 0) {
            if (s.size() >= 2) {
                long long w = s.top();
                s.pop();
                s.top() += w;
            }
        } else {
            s.push(x);
        }
    }
    return s.empty() ? 0 : s.top();
}
