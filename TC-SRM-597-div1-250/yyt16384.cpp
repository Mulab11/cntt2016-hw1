#include <array>
#include <string>

class LittleElephantAndString {
  public:
    int getNumber(std::string A, std::string B);

  private:
    static const int SZ = 26;

    bool checkNoSolution(const std::string &A, const std::string &B);
};

int LittleElephantAndString::getNumber(std::string A, std::string B)
{
    if (checkNoSolution(A, B)) {
        return -1;
    }
    // Every character will only be moved at most once, and the unmoved
    // characters will form a suffix of B
    int ans = A.length();
    auto p = A.rbegin();
    for (auto it = B.rbegin(); it != B.rend(); it++) {
        char c = *it;
        while (p != A.rend() && *p != c) {
            p++;
        }
        if (p == A.rend()) {
            break;
        }
        ans--;
        p++;
    }
    return ans;
}

bool LittleElephantAndString::checkNoSolution(const std::string &A, const std::string &B)
{
    // No solution if A and B does not contain the same characters
    std::array<int, SZ> cnt = {0};
    for (auto x : A) {
        cnt[x - 'A']++;
    }
    for (auto x : B) {
        cnt[x - 'A']--;
    }
    for (auto x : cnt) {
        if (x) {
            return true;
        }
    }
    return false;
}
