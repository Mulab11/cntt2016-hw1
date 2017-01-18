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

#define N 55
#define M 300005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,tot,flag[N];
struct seg{
		int sx,sy,ex,ey;
}A[N];
struct Point{
	int x,y;
}B[M];
void get(int x)
{
		int i; int Max=(int)-1e8,Min=(int)1e8;
		for (i=0;i<n;++i)
			if (A[i].sx<=x&&x<=A[i].ex)
			{
					if (A[i].sx==A[i].ex)
					{
							Min=min(Min,A[i].sy+1);
							Max=max(Max,A[i].ey-1);
					}
					else if (A[i].sx==x) Min=min(Min,A[i].sy+1),
										 Max=max(Max,A[i].sy-1);
					else if (A[i].ex==x) Min=min(Min,A[i].ey+1),
										 Max=max(Max,A[i].ey-1);
					else 
					{
							double pos=
							A[i].sy+1.*(A[i].ey-A[i].sy)*(x-A[i].sx)/(A[i].ex-A[i].sx);
							if (abs((int)pos-pos)<1e-7)
							{
								if (flag[i]==0)
									Min=(int)pos;
								else Max=(int)pos;
							}
							else if (pos>=0)
							{
								if (flag[i]==0)
								Min=min(Min,(int)pos+1);
								else 
								Max=max(Max,(int)pos);
							}
							else 
							{
								if (flag[i]==0)
								Min=min(Min,(int)pos);
								else 
								Max=max(Max,(int)pos-1); 
							}
					}
			}
			for (i=Min;i<=Max&&tot<=300000;++i) B[++tot]=(Point){x,i};
}
class ConvexPolygonGame{
	public:
		string winner(vector <int> X, vector <int> Y)
		{
				n=X.size();
				for (i=0;i<n;++i)
				{
						A[i]=(seg){X[i],Y[i],X[(i+1)%n],Y[(i+1)%n]};
						if (A[i].sx>A[i].ex) swap(A[i].sx,A[i].ex),swap(A[i].sy,A[i].ey),flag[i]=1;
				}
				int x;
				for (x=-100000;x<=100000;++x)  
				{
					get(x);
					if (tot>300000) return "Masha";
				}
				if (tot<=2) return "Petya";
				for (i=3;i<=tot;++i)
					if (1ll*(B[i].x-B[1].x)*(B[2].y-B[1].y)!=1ll*(B[i].y-B[1].y)*(B[2].x-B[1].x))
					return "Masha";
				return "Petya";
		}
}MRT;

int main()
{
	 cout<<MRT.winner({-100000, 0, 100000, 0}, {-100000, -1, 100000, 1});	
}

