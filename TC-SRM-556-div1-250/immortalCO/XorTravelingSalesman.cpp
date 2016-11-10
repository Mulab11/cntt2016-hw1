#include <vector>
#include <string>
using namespace std;

const int MaxN = 50;
int n, v[MaxN], G[30];
// G 是线性基
bool e[MaxN][MaxN];
void add(int x)
{
    for(int k = 30; k >= 0; --k)
        if((x >> k) & 1)
        {
            if(G[k]) x ^= G[k];
            else return (void) (G[k] = x);
        }
}

bool vis[MaxN];
void dfs(int i)
{
    vis[i] = 1;
    add(v[i]);
    for(int j = 0; j != n; ++j)
        if(!vis[j] && e[i][j]) dfs(j);
    
}
class XorTravelingSalesman
{
public:
    int maxProfit(vector<int> input_val, vector<string> input_edge)
    {
        n = input_val.size();
       	for(int i = 0; i != n; ++i)
            v[i] = input_val[i];
        for(int i = 0; i != n; ++i)
            for(int j = 0; j != n; ++j)
                e[i][j] = (input_edge[i][j] == 'Y');
        dfs(0);
        int ans = 0;
        for(int i = 30; i >= 0; --i)
            if((ans ^ G[i]) > ans) ans ^= G[i];
        return ans;
    }
}	user;
