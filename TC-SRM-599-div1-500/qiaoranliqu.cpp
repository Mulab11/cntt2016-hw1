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

#define N 5005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,lim,Ans=(int)1e9,l;
short int big[N*N];
int sqr(int x)
{
		return x*x;
}
vector<pair<int,int> >v[N]; 
class FindPolygons
{
	public:
	double minimumPolygon(int L)
	{
		if (L==2||L&1) return -1.0;
		for (i=1;i<=L;++i) big[sqr(i)]=i;
		lim=L*L; 
		for (i=0;i<=L;++i)
			for (j=0;j<=L;++j)
				if (i||j)
			{
				int len=sqr(i)+sqr(j);
				if (len>=lim||!big[len]) continue;
				v[big[len]].pb(mk(i,j));
			}
		for (i=1;i<=L;++i)
			for (j=0;j<(int)v[i].size();++j)
			{
				int sx=v[i][j].fi,sy=v[i][j].se;
				for (k=i;k<=L-i;++k)
					for (l=0;l<(int)v[k].size();++l)
					{
						int ex=v[k][l].fi,ey=v[k][l].se,
						len=sqr(sx-ex)+sqr(sy-ey); 
						if (sx*ey==ex*sy) continue;
						if (len>=lim||!big[len]) continue;
						if (i+k+big[len]==L)
							Ans=min(Ans,max(i,max(k,(int)big[len]))-min(i,min(k,(int)big[len])));
					}
			}
		if (Ans==(int)1e9)
		{
				if (L%4==0) Ans=0;
				else Ans=1;
		}
		return (double)Ans;
	}
}MRT;

int main()
{
	 cout<<MRT.minimumPolygon(4);
}

