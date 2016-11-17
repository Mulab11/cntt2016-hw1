static int gcd(int x, int y)
{
    int z;
    while (y) {
        z = x % y;
        x = y;
        y = z;
    }
    return x;
}

class PyramidSequences {
  public:
    long long distinctPairs(int N, int M);
};

long long PyramidSequences::distinctPairs(int N, int M)
{
    int d = gcd(2 * N - 2, 2 * M - 2);
    // (A[i], B[j]) is possible <=> i = j (mod d)
    // In sequence A, value x occurs in index x and 2 * N - x
    // Value pair (x, y) is possible <=> min(x % d, (2 * N - x) % d) =
    // min(y % d, (2 * M - y) % d) <=> min((x - 1) % d, (-x + 1) % d) =
    // min((y - 1) % d, (-y + 1) % d)
    // min((x - 1) % d, (-x + 1) % d) has a period of d
    int pca = (N - 1) / (d / 2);
    int cnta0 = pca / 2 + 1;
    int cntad = (pca + 1) / 2;
    int pcb = (M - 1) / (d / 2);
    int cntb0 = pcb / 2 + 1;
    int cntbd = (pcb + 1) / 2;
    return (long long)cnta0 * cntb0 + (long long)cntad * cntbd + (long long)pca * pcb * (d / 2 - 1);
}
