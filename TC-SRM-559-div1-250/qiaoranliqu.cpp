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

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,dx[N],dy[N];
long long ans;
int check(int x,int y)
{
		if (x<0||x>=n||y<0||y>=m) return 0;
		return 1;
}
class HyperKnight{
	public:
		long long countCells(int a, int b, int numRows, int numColumns, int k)
		{
			n=numRows; m=numColumns; int K=k;
			int x[8]={a,a,-a,-a,b,b,-b,-b},y[8]={b,-b,b,-b,a,-a,a,-a};	
			dx[++dx[0]]=0; dx[++dx[0]]=n;//把所有关键的x和y都拿出来 
			dx[++dx[0]]=a; dx[++dx[0]]=b;
			dx[++dx[0]]=n-a; dx[++dx[0]]=n-b;
			dy[++dy[0]]=0; dy[++dy[0]]=m;
			dy[++dy[0]]=a; dy[++dy[0]]=b;
			dy[++dy[0]]=m-a; dy[++dy[0]]=m-b;
			sort(dx+1,dx+dx[0]+1);
			dx[0]=unique(dx+1,dx+dx[0]+1)-(dx+1);
			sort(dy+1,dy+dy[0]+1);
			dy[0]=unique(dy+1,dy+dy[0]+1)-(dy+1);
			for (i=1;i<dx[0];++i) //枚举每个不同的块,每个块里满足条件的个数都是一样的. 
				for (j=1;j<dy[0];++j)
					{
							int cnt=0;
							for (k=0;k<8;++k)
								if (check(dx[i]+x[k],dy[j]+y[k])) ++cnt;
							if (cnt==K) ans+=1ll*(dx[i+1]-dx[i])*(dy[j+1]-dy[j]);
					}
			return ans;
		}
};
