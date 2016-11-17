class TrafficCongestion {
  public:
    int theMinCars(int treeHeight);

  private:
    static const int MOD = 1000000007;
};

int TrafficCongestion::theMinCars(int treeHeight)
{
    int u = 1;
    int s = 0;
    // The path visiting root should be as long as possible, and then
    // the tree is split into several subtrees
    // f[i] = sum(f[j], 0 <= j <= i - 2) * 2 + 1
    for (int i = 0; i < treeHeight; i++) {
        int v = (s * 2 + 1) % MOD;
        s = (s + u) % MOD;
        u = v;
    }
    return u;
}
