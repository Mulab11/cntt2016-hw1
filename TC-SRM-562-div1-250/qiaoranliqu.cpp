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

#define N 2005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
int A[N][N],r[N],b[N],g[N];
void change(char x,int &y)
{
	  if (y==1) r[i]--;
	  if (y==2) b[i]--;
	  if (y==3) g[i]--;
	  if (x=='R') y=1,r[i]++;
	  if (x=='B') y=2,b[i]++;
	  if (x=='G') y=3,g[i]++; 
}
class PastingPaintingDivOne{
	public:
		vector<long long> countColors(vector <string> clipboard, int T)
		{
				int n=clipboard.size(),m=clipboard[0].length();
			    for (i=1;i<=1000;++i) //暴力做前面几次操作 
			    {
			    		r[i]=r[i-1]; g[i]=g[i-1]; b[i]=b[i-1];
			    		for (j=0;j<n;++j)
			    			for (k=0;k<m;++k)
			    				if (clipboard[j][k]!='.')
			    					change(clipboard[j][k],A[j+i][k+i]);
			    }
			    vector<long long>ans;
			    if (T<=1000)  
			    {
			    		ans.pb(r[T]); ans.pb(g[T]); ans.pb(b[T]);
						return ans; 
				} //对于后面的操作,增量都是不变的 
			    ans.pb(r[1000]+1ll*(r[1000]-r[999])*(T-1000));
			    ans.pb(g[1000]+1ll*(g[1000]-g[999])*(T-1000));
			    ans.pb(b[1000]+1ll*(b[1000]-b[999])*(T-1000));
			    return ans;
		}
};
