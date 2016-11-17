#include <string>
#include <unordered_map>
#include <vector>

class EllysBulls {
  public:
    std::string getNumber(std::vector<std::string> guesses, std::vector<int> bulls);

  private:
    static const int SZ = 10;

    int countCorrectPositions(const std::string &s1, const std::string &s2);
};

std::string EllysBulls::getNumber(std::vector<std::string> guesses, std::vector<int> bulls)
{
    int n = guesses[0].length();
    int m = guesses.size();
    int hf = n / 2;
    int pwr = 1;
    for (int i = 0; i < hf; i++) {
        pwr *= SZ;
    }
    // Enumerate the right half of the string
    std::unordered_map<std::string, std::string> mp;
    for (int i = 0; i < pwr; i++) {
        std::string s;
        int u = i;
        for (int j = 0; j < hf; j++) {
            s += u % SZ + '0';
            u /= SZ;
        }
        std::string res;
        bool ok = true;
        for (int j = 0; j < m; j++) {
            int p = bulls[j] - countCorrectPositions(s, guesses[j].substr(n - hf));
            if (p < 0) {
                ok = false;
                break;
            }
            res += p + '0';
        }
        if (ok) {
            auto it = mp.find(res);
            if (it == mp.end()) {
                mp[res] = s;
            } else {
                mp[res] = "Ambiguity";
            }
        }
    }
    int pwl = 1;
    for (int i = 0; i < n - hf; i++) {
        pwl *= SZ;
    }
    // Enumerate the left half of the string
    std::string ans = "Liar";
    for (int i = 0; i < pwl; i++) {
        std::string s;
        int u = i;
        for (int j = 0; j < n - hf; j++) {
            s += u % SZ + '0';
            u /= SZ;
        }
        std::string res;
        for (int j = 0; j < m; j++) {
            int p = countCorrectPositions(s, guesses[j].substr(0, n - hf));
            res += p + '0';
        }
        auto it = mp.find(res);
        if (it != mp.end()) {
            if (it->second == "Ambiguity" || ans != "Liar") {
                return "Ambiguity";
            } else {
                ans = s + it->second;
            }
        }
    }
    return ans;
}

int EllysBulls::countCorrectPositions(const std::string &s1, const std::string &s2)
{
    int cnt = 0;
    for (int i = 0; i < (int)s1.length(); i++) {
        if (s1[i] == s2[i]) {
            cnt++;
        }
    }
    return cnt;
}
