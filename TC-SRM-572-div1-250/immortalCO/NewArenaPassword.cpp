#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int f[60], cnt[60][26];
int g(int i) {return i == f[i] ? i : f[i] = g(f[i]);}
class NewArenaPassword
{
public:
	int minChange(string s, int k)
	{
		int n = s.size();
		for(int i = 0; i != n; ++i) f[i] = i;
		for(int i = 0; i != k; ++i) f[g(i)] = g(n - k + i);
		for(int i = 0; i != n; ++i) ++cnt[g(i)][s[i] - 'a'];
		int ans = n;
		for(int i = 0; i != n; ++i) if(i == g(i))
		{
			int mx = 0;
			for(int w = 0; w != 26; ++w) if(cnt[i][w] > mx) mx = cnt[i][w];
			ans -= mx;
		}
		return ans;
	}
}   user;
