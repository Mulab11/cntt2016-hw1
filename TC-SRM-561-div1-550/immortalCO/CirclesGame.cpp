#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

vector<int> e[55];
ll app;

int f[55];

void calc(int i, int pre, int val)
{
	for(int k = e[i].size(); k--; )
		if(e[i][k] != pre) val ^= f[e[i][k]];
	app |= 1ll << val;
	for(int k = e[i].size(); k--; )
		if(e[i][k] != pre) calc(e[i][k], i, val ^ f[e[i][k]]);
}

int dp(int i, int pre)
{
	for(int k = e[i].size(); k--; )
		if(e[i][k] != pre) dp(e[i][k], i);
	app = 0;
	calc(i, pre, 0);
	return f[i] = __builtin_ctzll(~app);
}

class CirclesGame
{
public:
	string whoCanWin(vector<int> px, vector<int> py, vector<int> pr)
	{
		const int N = px.size();
		for(int i = 0; i != N; ++i)
		{
			int p = N;
#define sqr(x) ((x) * (x))
			for(int j = 0; j != N; ++j)
				if(pr[j] > pr[i] && sqr(px[i]-px[j])+sqr(py[i]-py[j])<=sqr(pr[j])
				   && (p == N || pr[p] > pr[j])) p = j;
			e[p].push_back(i);
		}
		int ans = 0;
		for(int k = e[N].size(); k--; )
			ans ^= dp(e[N][k], N);
		return ans ? "Alice" : "Bob";
	}
}	user;
