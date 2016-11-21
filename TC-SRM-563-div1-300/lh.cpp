#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class FoxAndHandle{
	static const int maxn=55;
	int sum[maxn][maxn];
	int lft[maxn];
	
	bool check(int pos,int x){
		if (!lft[x]) return false;
		for (int i=0;i<26;++i) if (lft[i]){
			if (lft[i]>sum[pos][i]) return false;
		}
		return true;
	}
	
	public:
		string lexSmallestName(string s){
			int n=s.length();
			memset(sum,0,sizeof(sum));
			for (int i=n-1;i>=0;--i){
				memcpy(sum[i],sum[i+1],sizeof(sum[i]));
				++sum[i][s[i]-'a'];
			}
			int cnt=0;
			for (int i=0;i<26;++i) cnt+=(lft[i]=sum[0][i]/2);
			int pos=0;
			string ret;
			while (cnt--){
				int tmp=-1;
				for (int i=pos;i<n;++i) if (check(i,s[i]-'a'))
				if (tmp==-1||s[i]<s[tmp]) tmp=i;
				ret+=s[tmp];
				--lft[s[tmp]-'a'];
				pos=tmp+1;
			}
			return ret;
		}
};
