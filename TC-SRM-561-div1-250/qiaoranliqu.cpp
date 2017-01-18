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
int i,j,m,n,p,k,A[N],B[N],C[N],D[N],ans=-1,val[N],vis[N],Ans;
inline bool cmp(int a,int b)
{
		return a>b;
}
bool work(int *A,int *C)
{
	  int i,ck=0;
	  for (i=1;i<=A[0];++i) ck+=A[i]; 
	  for (i=1;i<=C[0];++i) ck-=C[i],Ans+=C[i];
	  if (ck<0) return 0;
	  for (i=1;i<=min(A[0],C[0]);++i) Ans-=min(A[i],C[i]); //优先用大的匹配大的
	  return 1;
}
void check()
{
		int i;
		C[0]=D[0]=0;
		Ans=0;
		for (i=0;i<n;++i) if (!vis[i]) C[++C[0]]=val[i]; else D[++D[0]]=val[i];
		sort(C+1,C+C[0]+1,cmp); sort(D+1,D+D[0]+1,cmp); 
		if (!work(A,C)||!work(B,D)) return; //两种都要满足条件
		if (ans==-1) ans=Ans;
		else ans=min(ans,Ans);
}
void dfs(int x)
{
	 if (x==n) check();
	 else 
	 {
	 		vis[x]=0; dfs(x+1);
			vis[x]=1; dfs(x+1); 
	 }
}
class ICPCBalloons{
	public:
		int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted)
		{
				n=balloonSize.size();
				for (i=0;i<n;++i)
				 if (balloonSize[i]=='M') //先把气球颜色分一下列. A[++A[0]]+=balloonCount[i];
				 else B[++B[0]]=balloonCount[i];
				sort(A+1,A+A[0]+1,cmp);
				sort(B+1,B+B[0]+1,cmp); 
				n=maxAccepted.size();
				for (i=0;i<n;++i) val[i]=maxAccepted[i];
				dfs(0);//枚举每道题用哪种大小
				return ans;
		}
};

