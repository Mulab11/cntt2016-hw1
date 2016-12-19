#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

int cnt[26], f[26];
int g(int i) {return f[i] == i ? i : f[i] = g(f[i]);}

class GooseTattarrattatDiv1
{
public:
	int getmin(string S)
	{
		const int N = S.size();
		for(int i = 0; i != N; ++i) ++cnt[int(S[i] -= 'a')];
		for(int i = 0; i != 26; ++i) f[i] = i;
		for(int l = 0, r = N - 1; l < r; ++l, --r)
			if(S[l] != S[r])  f[g(S[l])] = g(S[r]);
		vector<int> vec[26];
		for(int i = 0; i != 26; ++i) vec[g(i)].push_back(cnt[i]);
		int ans = 0;
		for(int i = 0; i != 26; ++i) if(g(i) == i)
		{
			vector<int> a = vec[i];
			sort(a.begin(), a.end());
			for(int i = 0; i + 1 < a.size(); ++i)
				ans += a[i];
		}
		return ans;
	}
}	user;
