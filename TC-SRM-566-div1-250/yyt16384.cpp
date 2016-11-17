#include <vector>

class PenguinSledding {
  public:
    long long countDesigns(int numCheckpoints, std::vector<int> checkpoint1, std::vector<int> checkpoint2);
};

long long PenguinSledding::countDesigns(int numCheckpoints, std::vector<int> checkpoint1, std::vector<int> checkpoint2)
{
    std::vector<int> deg(numCheckpoints);
    for (auto x : checkpoint1) {
        deg[x - 1]++;
    }
    for (auto x : checkpoint2) {
        deg[x - 1]++;
    }
    std::vector<std::vector<char>> g(numCheckpoints, std::vector<char>(numCheckpoints));
    for (int i = 0; i < (int)checkpoint1.size(); i++) {
        int x = checkpoint1[i] - 1;
        int y = checkpoint2[i] - 1;
        g[x][y] = true;
        g[y][x] = true;
    }
    long long ans = 0;
    // The new graph must not have paths with length >= 3
    // Count triangles
    for (int i = 0; i < numCheckpoints; i++) {
        for (int j = i + 1; j < numCheckpoints; j++) {
            if (g[i][j]) {
                for (int k = j + 1; k < numCheckpoints; k++) {
                    if (g[i][k] && g[j][k]) {
                        ans++;
                    }
                }
            }
        }
    }
    // Enumerate the center point
    for (int i = 0; i < numCheckpoints; i++) {
        // All edges connected to i may be chosen or not
        ans += 1LL << deg[i];
    }
    // One-edge answers are counted twice
    ans -= checkpoint1.size();
    // Empty answers are counted n times
    ans -= numCheckpoints - 1;
    return ans;
}
