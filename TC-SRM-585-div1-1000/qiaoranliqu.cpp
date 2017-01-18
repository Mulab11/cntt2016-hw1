#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define N 300005

#define ls (t<<1)
#define rs ((t<<1)|1)
#define mid ((l+r)>>1)

using namespace std;
int i,j,m,p,k,tot,f[N];
struct Point{int x,y;}A[N*2],B[N];
long long add[N*4],tree[N*4],ans;
inline Point operator -(Point a,Point b) { return (Point){a.x-b.x,a.y-b.y}; } 
long long cross(Point a,Point b)
{
	 return 1ll*a.x*b.y-1ll*b.x*a.y;
}
bool onL(Point A,Point B,Point C)
{
	 return cross(B-A,C-A)>0;
}
void down(int t,int len)
{   
    int L=(len-(len>>1)),R=len>>1;
    add[ls]+=add[t]; add[rs]+=add[t];
    tree[ls]+=add[t]*L; tree[rs]+=add[t]*R;
	add[t]=0;
}
long long ask(int ll,int rr,int l,int r,int t)
{
	  if (ll>rr) return 0;
	  if (ll<=l&&r<=rr) return tree[t];
	  else 
	  {
	  	    down(t,r-l+1); long long S=0;
	  	    if (ll<=mid) S+=ask(ll,rr,l,mid,ls);
	  	    if (rr>mid)  S+=ask(ll,rr,mid+1,r,rs);
	  	    return S;
	  }
}
void ins(int ll,int rr,int c,int l,int r,int t)
{
	  if (ll>rr) return;
	  if (ll<=l&&r<=rr)
	  {
	  	   add[t]+=c;
	  	   tree[t]+=(r-l+1)*c;
	  }
	  else 
	  {
	  	  down(t,r-l+1);
		  if (ll<=mid) ins(ll,rr,c,l,mid,ls);
		  if (rr>mid)  ins(ll,rr,c,mid+1,r,rs);
		  tree[t]=tree[ls]+tree[rs];
	  }
}
class EnclosingTriangle{
	  public:
	  long long getNumber(int n,vector<int> RA,vector<int> RB)
{
	  m=RA.size();
	  for (i=1;i<=m;++i)
	      B[i].x=RA[i-1],B[i].y=RB[i-1];
	  for (i=0;i<=n;++i) A[++tot]=(Point){0,i};
	  for (i=1;i<=n;++i) A[++tot]=(Point){i,n};
	  for (i=n-1;i>=0;--i) A[++tot]=(Point){n,i};
	  for (i=n-1;i>0;--i) A[++tot]=(Point){i,0};
	  for (i=1;i<=tot;++i) A[i+tot]=A[i];
	  for (i=1;i<=tot;++i) 
	  {
	      f[i]=max(f[i-1],i+1);
		  for (;;)
		  {
		         for (j=1;j<=m;++j) if (onL(A[i],A[f[i]+1],B[j])) break;
				 if(j>m) f[i]++; else break;
		  }
	 }
	 int C=1,B=1;
	 for (i=1;i<=tot;++i)
	 {
	 	    while (B<=tot&&f[i]>=B) ins(B+1,min(f[B],tot),1,1,tot,1),++B;
	 	    ins(i+1,min(f[i],tot),-1,1,tot,1);
	 	    while (C<=tot&&f[C]<i+tot) ++C;
	 	    ans+=ask(C,tot,1,tot,1);
	 }
	 return ans;
  }
};
