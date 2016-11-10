#include <string>
#include <vector>
#include <cstring>
using namespace std;
#define IL inline
#define RG register
#define dmin(a, b) ((a) < (b) ? (a) : (b))

const int MaxN = 60;
const int MaxM = MaxN * MaxN;
struct Graph
{
    struct Pointer{int to, flow; Pointer *next, *rev;} *fir[MaxN], *cur[MaxN];
    Pointer mem[MaxM << 1], *tot;
    int n, S, T;
    IL void init(RG int _n, RG int _S, RG int _T)
    {
        n = _n, S = _S, T = _T;
        tot = mem;
        memset(fir + 1, 0, n * sizeof fir[0]);
    }
    IL void add(RG int a, RG int b, RG int f)
    {
        *++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
        *++tot = (Pointer) {a, 0, fir[b]}, fir[b] = tot;
        fir[a]->rev = fir[b];
        fir[b]->rev = fir[a];
    }
    IL void link(RG int a, RG int b, RG int f)
    {
        *++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
        *++tot = (Pointer) {a, f, fir[b]}, fir[b] = tot;
        fir[a]->rev = fir[b];
        fir[b]->rev = fir[a];
    }
    int dist[MaxN];
    IL bool bfs()
    {
        static int q[MaxN];
        RG int l = 1, r = 0, d;
        RG Pointer *k;
        memset(dist + 1, 0, n << 2);
        dist[q[++r] = T] = 1;
        while(l <= r)
        {
            d = dist[q[l]] + 1;
            for(k = fir[q[l++]]; k; k = k->next)
            {
                if(k->rev->flow && !dist[k->to])
                    dist[q[++r] = k->to] = d;
            }
        }
        return dist[S];
    }
    int dfs(RG int i, RG int lim)
    {
        if(i == T || !lim) return lim;
        RG int want = dist[i] - 1;
        RG int used = 0, temp;
        for(RG Pointer* &k = cur[i]; k; k = k->next)
            if(dist[k->to] == want && k->flow)
            {
                temp = dfs(k->to, dmin(lim - used, k->flow));
                used += temp;
                k->flow -= temp;
                k->rev->flow += temp;
                if(used == lim) break;
            }
        return used;
    }
    IL int solve()
    {
        RG int ans = 0;
        while(bfs())
        {
            memcpy(cur + 1, fir + 1, n * sizeof *fir);
            ans += dfs(S, 1 << 30);
        }
        return ans;
    }
} G;

class OldBridges
{
public:
    bool pig(vector<string> e, int s0, int t0, int n0, int s1, int t1, int n1)
    {
        int n = e.size(), F[2] = {2, 100000};
        G.init(n + 2, n + 1, n + 2);
        for(int i = 0; i != n; ++i)
            for(int j = i; j != n; ++j)
                if(e[i][j] != 'X')
                    G.link(i + 1, j + 1, F[e[i][j] == 'N']);
        G.add(G.S, s0 + 1, n0); G.add(t0 + 1, G.T, n0);
        G.add(G.S, s1 + 1, n1); G.add(t1 + 1, G.T, n1);
        return G.solve() == n0 + n1;
    }
    string isPossible(vector<string> edge, int s0, int t0, int n0, int s1, int t1, int n1)
    {
        n0 <<= 1; n1 <<= 1;
        return pig(edge, s0, t0, n0, s1, t1, n1) && pig(edge, s0, t0, n0, t1, s1, n1)
        ? "Yes" : "No";
    }
}	user;
