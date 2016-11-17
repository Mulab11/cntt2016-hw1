#include <array>
#include <string>
#include <utility>
#include <vector>

class Trie {
  public:
    static const int SZ = 26;

    std::vector<char> isstr = {false};
    std::vector<std::array<int, SZ>> edge{1};
    std::vector<int> fa = {-1};

    Trie();
    Trie(const std::vector<std::string> &strs);

    std::pair<int, int> addString(const std::string &s);
};

Trie::Trie()
{
    edge[0].fill(-1);
}

Trie::Trie(const std::vector<std::string> &strs) : Trie()
{
    for (const auto &x : strs) {
        addString(x);
    }
}

std::pair<int, int> Trie::addString(const std::string &s)
{
    int now = 0;
    int inspt = -1;
    for (auto c : s) {
        int x = c - 'a';
        if (edge[now][x] == -1) {
            if (inspt == -1) {
                inspt = now;
            }
            edge[now][x] = isstr.size();
            isstr.push_back(false);
            edge.push_back(std::array<int, SZ>());
            edge.back().fill(-1);
            fa.push_back(now);
        }
        now = edge[now][x];
    }
    isstr[now] = true;
    return std::make_pair(now, inspt == -1 ? now : inspt);
}

class UndoHistory {
  public:
    int minPresses(std::vector<std::string> lines);
};

int UndoHistory::minPresses(std::vector<std::string> lines)
{
    // One enter key for each line
    int ans = lines.size();
    Trie trie;
    int prev = 0;
    for (int i = 0; i < (int)lines.size(); i++) {
        std::pair<int, int> x = trie.addString(lines[i]);
        int now = x.first;
        int br = x.second;
        if (br == prev) {
            // No need to undo
            ans += 0;
        } else if (trie.fa[br] == prev) {
            // Type one more character instead of undoing
            ans += 1;
        } else {
            // Perform undo operation
            ans += 2;
        }
        prev = now;
    }
    // One key for each character
    ans += trie.edge.size() - 1;
    return ans;
}
