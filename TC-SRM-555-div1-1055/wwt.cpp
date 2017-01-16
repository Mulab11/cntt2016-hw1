/*
枚举以每个位置i作为开头，可以得到s[i]表示可以随便选的位置集合。令l为最多往左走了l步，r为往右走了r步，那么有l<=i<n-r，假如n-l-r+1比较小，
我们就可以直接容斥算答案了。假如n-l-r+1很大，我们可以发现每个s[i]都是连续的一段区间，并且他们的长度都不会超过(i+r)-(i-l)+1=r+l+1，
那么，假如我们容斥中选了超过r+l+1个集合时，他们的交集必然为空，所以在容斥时加个特判就好了。复杂度？
当n=36时,max(c(n-x,0)+c(n-x,1)+...+c(n-x,x))不超过2*10^7。
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class MapGuessing
{
public:
	vector<ll> ava;
	string __co,go;
	int n;

	ll dfs(int i,ll s)
	{
		if (!s) return (i == ava.size()); //交集为空就不要做了
		if (i == ava.size()) return (1ll << __builtin_popcountl(s)); //合法的方案数
		return dfs(i + 1,s) - dfs(i + 1,s & ava[i]);
	}

	ll find(int st)
	{
		static char s[55];
		ll cov = 0,tmp = 0;
		for(int i = 0;i < __co.length();i ++)
		{
			if (__co[i] == '<') -- st; else
				if (__co[i] == '>') ++ st; else
				{
					cov |= (1ll << st);
					s[st] = __co[i];
					bool ok = 1;
					for(int j = 0;j < n;j ++)
						if ((cov & (1ll << j)) && s[j] != go[j]) {ok = 0;break;}
					if (ok) tmp = cov;
				}
		}
		return tmp; //找到哪些点被固定了
	}	

	long long countPatterns(string goal, vector<string> code)
	{
		n = goal.size();
		go = goal;
		for(int i = 0;i < code.size();i ++)
			for(int j = 0;j < code[i].length();j ++) __co = __co + code[i][j];
		int l = 0,r = 0,delta = 0;
		for(int i = 0;i < __co.size();i ++)
		{
			if (__co[i] == '<') -- delta;
			if (__co[i] == '>') ++ delta;
			l = max(l,-delta),r = max(r,delta);
		}	
		for(int i = l;i + r < n;i ++)
			ava.push_back(find(i));
		return (1ll << n) - dfs(0,(1ll << n) - 1);		
	}
};
