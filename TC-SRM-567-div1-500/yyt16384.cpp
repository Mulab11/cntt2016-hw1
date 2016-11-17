#include <array>
#include <string>
#include <vector>

class StringGame {
  public:
    std::vector<int> getWinningStrings(std::vector<std::string> S);

  private:
    static const int SZ = 26;

    bool isWinningString(const std::string &a, const std::vector<std::string> &c);
};

std::vector<int> StringGame::getWinningStrings(std::vector<std::string> S)
{
    std::vector<int> ans;
    for (int i = 0; i < (int)S.size(); i++) {
        std::vector<std::string> c = S;
        c.erase(c.begin() + i);
        if (isWinningString(S[i], c)) {
            ans.push_back(i);
        }
    }
    return ans;
}

bool StringGame::isWinningString(const std::string &a, const std::vector<std::string> &c)
{
    std::array<int, SZ> cntself = {0};
    for (auto x : a) {
        cntself[x - 'a']++;
    }
    std::vector<std::array<int, SZ>> cntother(c.size(), {0});
    for (int i = 0; i < (int)c.size(); i++) {
        for (auto x : c[i]) {
            cntother[i][x - 'a']++;
        }
    }
    std::array<bool, SZ> posvis = {0};
    std::vector<char> otherstrok(c.size(), true);
    for (int i = 0; i < SZ; i++) {
        int r = -1;
        for (int j = 0; j < SZ; j++) {
            if (!posvis[j]) {
                bool isgt = true;
                bool ok = true;
                for (int k = 0; k < (int)c.size(); k++) {
                    if (otherstrok[k]) {
                        if (cntother[k][j] > cntself[j]) {
                            ok = false;
                            break;
                        } else if (cntother[k][j] == cntself[j]) {
                            isgt = false;
                        }
                    }
                }
                if (!ok) {
                    continue;
                }
                if (isgt) {
                    // Win by choosing character j next
                    return true;
                }
                r = j;
                break;
            }
        }
        if (r == -1) {
            return false;
        }
        // Choose character r next
        posvis[r] = true;
        for (int j = 0; j < (int)c.size(); j++) {
            if (otherstrok[j] && cntother[j][r] < cntself[r]) {
                otherstrok[j] = false;
            }
        }
    }
    return false;
}
