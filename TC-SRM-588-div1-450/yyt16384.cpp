#include <algorithm>
#include <unordered_set>
#include <vector>

class KeyDungeonDiv1 {
  public:
    int maxKeys(std::vector<int> doorR, std::vector<int> doorG, std::vector<int> roomR, std::vector<int> roomG, std::vector<int> roomW, std::vector<int> keys);
};

int KeyDungeonDiv1::maxKeys(std::vector<int> doorR, std::vector<int> doorG, std::vector<int> roomR, std::vector<int> roomG, std::vector<int> roomW, std::vector<int> keys)
{
    int n = doorR.size();
    // Number of keys after opening doors in set
    std::vector<int> keycnt(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        int s = keys[0] + keys[1] + keys[2];
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                s += roomR[j] + roomG[j] + roomW[j] - doorR[j] - doorG[j];
            }
        }
        keycnt[i] = s;
    }
    // Assume all white keys are turned into either red or green keys
    // f[i] = number of red keys possible after opening doors in set i
    std::vector<std::unordered_set<int>> f(1 << n);
    for (int i = 0; i <= keys[2]; i++) {
        f[0].insert(keys[0] + i);
    }
    for (int i = 0; i < (1 << n); i++) {
        for (auto x : f[i]) {
            int y = keycnt[i] - x;
            for (int j = 0; j < n; j++) {
                if (!((i >> j) & 1) && x >= doorR[j] && y >= doorG[j]) {
                    // Open door j
                    for (int k = 0; k <= roomW[j]; k++) {
                        f[i | (1 << j)].insert(x - doorR[j] + roomR[j] + k);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        if (!f[i].empty()) {
            ans = std::max(ans, keycnt[i]);
        }
    }
    return ans;
}
