#include <algorithm>
using namespace std;
int cnt[26], st[26], sum[26], ext[26];
class GooseTattarrattatDiv1
{
public:
	int Find(int x)
	{
		return st[x] == x ? x : st[x] = Find(st[x]);
	}
	void Union(int u, int v)
	{
		if(Find(u) != Find(v))
			st[Find(u)] = v;
	}
	int getmin(string s)
	{
		int n = s.length();
		for(int i = 0; i < 26; i++)
			st[i] = i;
		for(int i = 0; i < n; i++)
			cnt[s[i] - 'a']++;
		for(int i = 0; i < n / 2; i++)
			Union(s[i] - 'a', s[n - i - 1] - 'a'); //对应位置上的字母必须相同 
		for(int i = 0; i < 26; i++)
			sum[Find(i)] += cnt[i], ext[Find(i)] = max(ext[Find(i)], cnt[i]);
		int ans = 0;
		for(int i = 0; i < 26; i++)
		{
			if(st[i] == i)
				ans += sum[i] - ext[i]; //把所有必须相同的字母都换成出现次数最多的字母 
		}
		return ans;
	}
};