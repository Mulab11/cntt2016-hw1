#include <algorithm>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class GUMIAndSongsDiv1 {
  public:
    int maxSongs(std::vector<int> duration, std::vector<int> tone, int T);
};

int GUMIAndSongsDiv1::maxSongs(std::vector<int> duration, std::vector<int> tone, int T)
{
    int n = duration.size();
    std::vector<std::pair<int, int>> songs(n);
    for (int i = 0; i < n; i++) {
        songs[i] = std::make_pair(tone[i], duration[i]);
    }
    std::sort(songs.begin(), songs.end());
    // f[i][j] = minimum time to sing j songs with song i as the last
    // song
    std::vector<std::vector<int>> f = {{0}};
    for (int i = 1; i <= n; i++) {
        std::vector<int> g(i + 1, INF);
        g[0] = 0;
        for (int j = 1; j <= i; j++) {
            for (int k = j - 1; k < i; k++) {
                int tonediff = k ? songs[i - 1].first - songs[k - 1].first : 0;
                g[j] = std::min(g[j], f[k][j - 1] + tonediff + songs[i - 1].second);
            }
        }
        f.push_back(std::move(g));
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i; j <= n; j++) {
            if (f[j][i] <= T) {
                return i;
            }
        }
    }
    return 0;
}
