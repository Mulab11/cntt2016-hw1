#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
const int MOD = 1000000007, MAXN = 55, MAXM = 12;

class SimilarNames
{
private:
	int n, m, num;//number of positions. see the comment 4 lines below.
	int fa[MAXN];
	stack<int> st;//for dfs
	int f[MAXN][MAXM + 1][1 << MAXM], tmpf[MAXM + 1][1 << MAXM];//f[i][j][S]: subtree i, j leaves of info tree, status S, number of possible orders
	//only consider the positions x where there is at least 1 restriction x->y or at least 2 restrictions y->x. <= 12 positions.
	int number[MAXN];
	int infotree[MAXM];
	int bitcnt[1 << MAXM];
	int numleaf[1 << MAXM];
	int C[MAXN][MAXN], A[MAXN][MAXN], fac[MAXN];
	int lowbit(int x)
	{
		return x & (-x);
	}
public:
	int count(vector<string> names, vector<int> info1, vector<int> info2)//worst case: 27ms (test case #83)
	{
		n = names.size();
		m = info1.size();
		names.push_back(string());//empty string, root of the trie
		sort(names.begin(), names.end());//a O(nlogn*size) sort for convenience. we can build the trie in O(n*size) but the bottleneck isn't here
		st.push(0);
		for(int i = 1; i <= n; i++)//dfs
		{
			while(names[i].size() < names[st.top()].size() || names[i].substr(0, names[st.top()].size()) != names[st.top()])
				st.pop();
			fa[i] = st.top();
			st.push(i);
		}
//		for(int i = 0; i <= n; i++)
//		{
//			for(int j = 0; j < son[i].size(); j++)
//				printf("%s ", names[son[i][j]].c_str());
//			printf("%s\n", names[i].c_str());
//		}
		for(int i = 0; i <= n; i++)
		{
			C[i][0] = C[i][i] = 1;
			for(int j = 1; j < i; j++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
		fac[0] = 1;
		for(int i = 1; i <= n; i++)
			fac[i] = (long long)fac[i - 1] * i % MOD;
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= i; j++)
				A[i][j] = (long long)C[i][j] * fac[j] % MOD;
		num = 0;
		memset(number, -1, sizeof(number));
		for(int i = 0; i < m; i++)
			if(number[info1[i]] == -1)
				number[info1[i]] = num++;
//		int tmpnum = num;
		for(int i = 0; i < m; i++)
			if(number[info2[i]] == -1)
				number[info2[i]] = -2;
			else if(number[info2[i]] == -2)
				number[info2[i]] = num++;
		for(int i = 0; i < num; i++)
			infotree[i] = (1 << i);
		for(int tim = 0; tim < num; tim++)//transitive closure... a topo sort will be O(m) but the bottleneck isn't here
			for(int i = 0; i < m; i++)
				if(number[info2[i]] > -1)
					infotree[number[info1[i]]] |= infotree[number[info2[i]]];
		bitcnt[0] = 0;
		for(int i = 1; i < (1 << num); i++)
			bitcnt[i] = bitcnt[i >> 1] + (i & 1);
//		for(int i = 0; i < num; i++)
//			printf("%d %d\n", i, infotree[i]);
		int numleaves = 0;
		memset(numleaf, 0, sizeof(numleaf));
		for(int i = 0; i < m; i++)
			if(number[info2[i]] <= -1)
				numleaf[1 << number[info1[i]]]++, numleaves++;
		numleaf[0] = 0;
		for(int i = 1; i < (1 << num); i++)
			numleaf[i] = numleaf[i ^ lowbit(i)] + numleaf[lowbit(i)];
		memset(f, 0, sizeof(f));
		for(int i = 0; i <= n; i++)
			f[i][0][0] = 1;
		for(int i = n; i >= 1; i--)//reverse dfs order
		{
			for(int j = 0; j <= numleaves; j++)
				for(int S = 0; S < (1 << num); S++)
				{
					tmpf[j][S] = f[i][j][S];
					f[i][j][S] = 0;
				}
			//add point i
			for(int j = 0; j <= numleaves; j++)
				for(int S = 0; S < (1 << num); S++)
					if(tmpf[j][S])
					{
						f[i][j][S] = (f[i][j][S] + tmpf[j][S]) % MOD;
						if(j < numleaves)//add leaf
							f[i][j + 1][S] = (f[i][j + 1][S] + tmpf[j][S]) % MOD;
						for(int x = 0; x < num; x++)//add position x
							if(!((S >> x) & 1) && numleaf[S | (1 << x)] <= j && (infotree[x] & (S | (1 << x))) == infotree[x])
								f[i][j][S | (1 << x)] = (f[i][j][S | (1 << x)] + (long long)tmpf[j][S] * A[j - numleaf[S]][numleaf[1 << x]]) % MOD;
					}
//			for(int j = 0; j <= numleaves; j++)
//				for(int S = 0; S < (1 << num); S++)
//					if(f[i][j][S])
//						printf("f[%d][%d][%d] = %d\n", i, j, S, f[i][j][S]);
			for(int j = 0; j <= numleaves; j++)
				for(int S = 0; S < (1 << num); S++)
				{
					tmpf[j][S] = f[fa[i]][j][S];
					f[fa[i]][j][S] = 0;
				}
			//merge to father
			//O(3^(1.5m)). it's not O(3^(1.5m)*m^2) because if num=1.5m, numleaves=0; if numleaves=O(m), num will be something like 1.4m, then O(3^(1.4m)*m^2) = O(3^(1.5m)).
			//can be optimized to O(3^m*m^2) if we only enum valid pairs.
			for(int j1 = 0; j1 <= numleaves; j1++)
				for(int S1 = 0; S1 < (1 << num); S1++)
					if(f[i][j1][S1])
						for(int j = j1; j <= numleaves; j++)
							for(int S = S1; S < (1 << num); S = ((S + 1) | S1))
								if(tmpf[j - j1][S ^ S1])
									f[fa[i]][j][S] = (f[fa[i]][j][S] + (long long)f[i][j1][S1] * tmpf[j - j1][S ^ S1]) % MOD;
		}
		int ans = f[0][numleaves][(1 << num) - 1];
		ans = (long long)ans * fac[n - numleaves - num] % MOD;
		return ans;
	}
};

