#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 105
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,cnt[N],goal[N],sum[N][N],gg[N];
int aluba(int x,int y)
{
		if (x==-1||x==y) return 1;
		return 0;
}
int could(int ID,int x) //判断这个位置选了之后能不能合法 
{
		int i;
		if (!gg[x]) return 0;
		for (i=0;i<26;++i)
			if (sum[ID][i]<gg[i]-(x==i)) return 0;
		return 1;
}
int check(string S)
{
	int i,now=0;
	memcpy(gg,cnt,sizeof(gg));
	for (i=0;i<(int)S.length();++i) //每次贪心,能选就选 
		if (now<(int)S.length()/2&&aluba(goal[now],S[i]-'a')&&could(i+1,S[i]-'a'))
		++now,--gg[S[i]-'a'];
	return now==(int)S.length()/2;
		  
}
class FoxAndHandle{
	public:
	string lexSmallestName(string S)
	{
			string s;
			memset(goal,-1,sizeof(goal));
			for (i=0;i<(int)S.length();++i)  cnt[S[i]-'a']++;
			for (i=(int)S.length()-1;i>=0;--i)
				  for (j=0;j<26;++j)
				  	if (i) sum[i][j]=sum[i+1][j]+(S[i]==j+'a');
			for (i=0;i<26;++i) cnt[i]/=2; 
			for (i=0;i<(int)S.length()/2;++i) //逐位确定确定每个位置 
			{
					for (j=0;j<26;++j)
					{
							goal[i]=j;
							if (check(S)) break;
					}
					s+=goal[i]+'a';
			}
			return s;
	}
};
