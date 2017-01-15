#include <bits/stdc++.h>

using namespace std;

const int maxn = 55,mo = int(1e9) + 7;

vector<int> lk[maxn],subset[1 << 16];
int fa[maxn],n,m,full,trans[1 << 16][maxn],f[maxn][1 << 16]; 
//一个状态S有m位，每一位是0..2,分别表示：当前对这个限制没有影响；这个限制深度大的点已经选了；这个限制已经满足
//trans[S][i]表示原来状态为S，当前的根放在了i位置后新的S'

class SimilarNames
{
public:
	//以前缀关系建树
	void dfs(int now) //从下往上dp合并
	{
		for(auto p : lk[now]) dfs(p);
		f[now][0] = 1;
		for(auto p : lk[now])
		{
			static int bak[1 << 16];
			memset(bak,0,sizeof bak);
			for(int s = 0;s <= full;s ++)
				for(auto s1 : subset[s]) bak[s] = (bak[s] + f[now][s1] * 1ll * f[p][s - s1]) % mo; //合并子树的S，S之间不能有交
			memcpy(f[now],bak,sizeof bak);
		}
		if (now == n) return;
		static int bak[1 << 16];
		memset(bak,0,sizeof bak);
		for(int s = 0;s <= full;s ++)
		{
			bool get = 0;
			for(int p = 0;p < n;p ++)
				if (trans[s][p] != -1) //枚举根放哪个位置
				{
					if (trans[s][p] == s) {get = 1;continue;} //这个位置不造成任何影响，为了避免重复计算，最后再*(n-m)!考虑这些不造成影响的位置的贡献
					bak[trans[s][p]] = (bak[trans[s][p]] + f[now][s]) % mo;
				}
			if (get) bak[s] = (bak[s] + f[now][s]) % mo;
		}
		memcpy(f[now],bak,sizeof bak);
	}

	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int count(vector <string> names, vector <int> info1, vector <int> info2)
	{
		n = names.size(),m = info1.size();
		for(int i = 0;i < n;i ++) fa[i] = -1;
		for(int i = 0;i < names.size();i ++)
			for(int j = 0;j < names.size();j ++)
				if (i != j && names[i].length() > names[j].length()) //建树，找到长度最大的是i前缀的j
				{
					bool ok = 1;
					for(int k = 0;k < names[j].length();k ++)
						if (names[j][k] != names[i][k]) ok = 0;
					if (ok && (fa[i] == -1 || names[j].length() > names[fa[i]].length())) fa[i] = j;
				}
		for(int i = 0;i < n;i ++)
		{
			if (fa[i] == -1) fa[i] = n;
			lk[fa[i]].push_back(i);
		}
		memset(trans,255,sizeof trans);
		full = 0;
		for(int s = 0;s < (1 << (2 * m));s ++)
		{
			static int va[16];
			bool ok = 1;
			for(int i = 0,ns = s;i < m;i ++,ns >>= 2)
			{
				va[i] = (ns & 3);
				if (va[i] == 3) {ok = 0;break;}
			}
			if (!ok) continue;
			full = max(full,s);
			for(int s1 = 0;s1 < (1 << m);s1 ++) //求出s的子集，每一位要么为0要么等于s的这一位
			{
				bool legal = 1;
				int ns = 0;
				for(int i = m - 1;i >= 0;i --) 
					if ((s1 & (1 << i)))
					{
						if (!va[i]) legal = 0;
						ns = (ns << 2) | va[i];
					} else ns <<= 2;
				if (legal) subset[s].push_back(ns);
			}
			for(int i = 0;i < n;i ++) 
			{
				ok = 1;
				int ns = s;
				for(int j = 0;j < m;j ++)
				{
					if (i == info1[j])
					{
						if (va[j] != 1) ok = 0; //必须恰好只放了深度大的点
						ns += (1 << (j * 2));
					}
					if (i == info2[j])
					{
						if (va[j] != 0) ok = 0;//必须还没有影响
						ns += (1 << (j * 2));
					}
				}
				if (!ok) continue;
				trans[s][i] = ns;
			}
		}
		dfs(n);
		vector<int> ava;
		for(auto p : info1) ava.push_back(p);
		for(auto p : info2) ava.push_back(p);
		sort(ava.begin(),ava.end());
		int ans = f[n][full],v = unique(ava.begin(),ava.end()) - ava.begin();
		for(int i = 1;i <= n - v;i ++) ans = ans * 1ll * i % mo;
		return ans;
	}
};
