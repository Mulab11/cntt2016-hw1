// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringGame.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class StringGame{
	int n;
	int cnt[maxn][26];
	bool alive[maxn],used[26];
	public:
	vector <int> getWinningStrings(vector <string> S){
		n=S.size();
		memset(cnt,0,sizeof(cnt));
		for (int i=0;i<n;++i)
			for (int j=0;j<S[i].size();++j)
				++cnt[i][S[i][j]-'a'];
		vector<int> ret;
		for (int x=0;x<n;++x){
			bool found=0;
			for (int y=0;y<n&&!found;++y)if (y!=x){
				found=1;
				for (int k=0;k<26&&found;++k)
					if (cnt[x][k]!=cnt[y][k]) found=0;
			}
			if (found) continue;
			memset(alive,1,sizeof(alive));
			memset(used,0,sizeof(used));
			for (int i=0;i<26;++i)
				for (int k=0;k<26;++k)if (!used[k]){
					found=0;
					for (int y=0;y<n&&!found;++y)
						if (alive[y]&&cnt[y][k]>cnt[x][k])
							found=1;
					if (!found){
						used[k]=1;
						for (int y=0;y<n&&!found;++y)
							if (cnt[y][k]<cnt[x][k]) alive[y]=0;
						break;
					}
				}
			found=0;
			for (int y=0;y<n&&!found;++y)if (y!=x)
				if (alive[y]) found=1;
			if (!found) ret.push_back(x);
		}
		return ret;
	}
};
