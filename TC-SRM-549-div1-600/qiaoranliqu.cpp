#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 13
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,now,pw3[M],val[N],col[N],row[N];
int f[10000005];
struct Node{int x,y;}hat[N];
int Size(int x)
{
		int s=0;
		while (x) 
		{
				if (x%3>0) ++s;
				x/=3; 
		} 
		return s;
}
int work(int x)
{
		memset(col,0,sizeof(col));
		memset(row,0,sizeof(row));
		int i;
		for (i=0;i<now;++i) 
			if (x%pw3[i+1]<2*pw3[i]) row[hat[i].x]^=1,col[hat[i].y]^=1; 
		for (i=0;i<n;++i) if (row[i]) return 0;
		for (i=0;i<m;++i) if (col[i]) return 0;
		return 1;
}
int dfs(int now,int x,int ret)
{
 	if (x==::now) 
	{
	 	if (ret==0) return work(now);
	 	return 0;
	}
	if (now%pw3[x+1]>=pw3[x]) return dfs(now,x+1,ret);
	if (dfs(now,x+1,ret)) return 1;
	if (ret) return dfs(now+2*pw3[x],x+1,ret-1);
	return 0;
}
int check(int x) //判断一个最终状态是否有可能成为解 
{
		int i,num=0,t=0;
				for (i=0;i<now;++i)
					if (x%pw3[i+1]>=2*pw3[i]) t+=val[num++];
		if (dfs(x,0,k-num)) return t;
		return -1;
}
int get(int x,int y)
{
		if (x==-1||y==-1) return max(x,y);
		return min(x,y);
}
class MagicalHats{
		public:
			int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses)
			{
					  sort(coins.begin(),coins.end());
					  k=coins.size();
					  for (i=0;i<(int)coins.size();++i) val[i]=coins[i];
					  n=board.size(); m=board[0].length();
					  pw3[0]=1;
					  for (i=1;i<N+5;++i) pw3[i]=pw3[i-1]*3;
					  for (i=0;i<n;++i)
					  	for (j=0;j<m;++j)
					  		if (board[i][j]=='H') hat[now++]=(Node){i,j};
					  memset(f,-1,sizeof(f));
					  for (i=pw3[now]-1;i>=0;--i) //倒着枚举所有状态. 
					  {	
					  		int size=Size(i);
					  		if (size>numGuesses) continue; 
					  		if (size==numGuesses) f[i]=check(i); //某个最终态 
							else 
							{
									int ans=-1;
									for (j=0;j<now;++j)
										if (i%pw3[j+1]<pw3[j])
										ans=max(ans,get(f[i+pw3[j]],f[i+2*pw3[j]]));
									f[i]=ans;
							}
					  }
					  return f[0];
			}
}FFT;

int main()
{
	vector<string> s;
	vector<int> v;
	s.pb("HHH"); s.pb("HHH"); s.pb("H.H"); v.pb(13); v.pb(13); v.pb(13); v.pb(13); 
	printf("%d\n",FFT.findMaximumReward(s,v,2));
}

