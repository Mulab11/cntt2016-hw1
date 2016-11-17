class TriangleXor {
  public:
    int theArea(int W);
};

int TriangleXor::theArea(int W)
{
    double ans = 0;
    double r = 0;
    for (int i = 0; i < W; i++) {
        // Consider the parts within triangle (i, 0), (i + 1, 0), (0, 1)
        double xl = (double)W / (W + i);
        double xr = (double)W / (W + i + 1);
        r += (i % 2 ? -1 : 1) * xl * xr;
        ans += r / 2;
    }
    // Consider the parts within triangle (0, 1), (W, 0), (W, 1)
    double s = 0;
    for (int i = 0; i <= W; i++) {
        double x = (double)W / (W + i);
        s += (i % 2 ? -1 : 1) * x;
    }
    ans += s * W / 2;
    return ans;
}
