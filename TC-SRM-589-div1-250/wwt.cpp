#include <bits/stdc++.h>

using namespace std;

const int maxn = 26;

int fa[maxn],ch[maxn];

class GooseTattarrattatDiv1
{
public:
	int get(int a)
	{
		return fa[a] == a ? a : fa[a] = get(fa[a]);
	}

	int getmin(string S)
	{
		int n = S.length(),ans = 0;
		for(int i = 0;i < 26;i ++) fa[i] = i;
		for(int i = 0;i < n;i ++) ch[S[i] - 'a'] ++;
		for(int l = 0,r = n - 1;l < r;l ++,r --)
			if (S[l] != S[r]) fa[get(S[l] - 'a')] = get(S[r] - 'a'); //S[l] and S[r] must be the same at last
		for(int i = 0;i < 26;i ++)
			if (fa[i] == i)
			{
				vector<int> cur;
				cur.clear();
				for(int j = 0;j < 26;j ++)
					if (get(j) == i) cur.push_back(ch[j]); //these chars must be the same at last
				sort(cur.begin(),cur.end()); //make cur[0]~cur[size-2] become cur[size - 1]
				for(int j = 0;j < cur.size() - 1;j ++) ans += cur[j];
			}
		return ans;
	}
};
