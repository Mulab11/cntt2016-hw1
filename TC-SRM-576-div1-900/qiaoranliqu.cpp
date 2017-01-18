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
#define Mo 1000000009

using namespace std;
int i,j,m,n,p,k,ans,l;
long long A[M],B[M];
long long ID[N][N],W;
map<long long,int>mp;
void jia(int &x,int y)
{
	x+=y; if (x>=Mo) x-=Mo; 
}
int power(int x,int y)
{
		if (y<0) return 1;
		int sum=1;
		for (;y;y>>=1)
		{
				if (y&1) sum=1ll*sum*x%Mo;
				x=1ll*x*x%Mo;
		}
		return sum;
}
int C[N];
void work(long long x)
{
		int i,j;
		if (x>W) return;
		if (mp[x]) return;
		mp[x]=1;
		C[0]=0;
		for (i=0;i<n;++i)
			for (j=0;j<m;++j)
				C[++C[0]]=(1ll*i*W+j)%x;
		sort(C+1,C+C[0]+1);
		C[0]=unique(C+1,C+C[0]+1)-(C+1);
		jia(ans,Mo-power(26,x-C[0])); 
}
void Gao(long long x) //枚举每个x的约数,然后计算不合法的方案 
{
		 long long i;
		 for (i=1;i*i<=x;++i)
		 	if (x%i==0)
		 {
		 		work(i);
		 		work(x/i);
		 }
} 
int inv25=power(25,Mo-2);
int fuck(int x)
{
	return 1ll*(power(26,x+1)+Mo-1)*inv25%Mo;
}
long long D[M];
void baoli(long long x)
{
	long long i;
	for (i=1;i*i<=x;++i)
		if (x%i==0) 
		{
			 D[++D[0]]=i;
			 D[++D[0]]=x/i;
		}
}
void jian(long long x)
{
	if (x>W) return;
	int i,j;
	jia(ans,Mo-power(26,x-n*m));
	C[0]=0;
	for (i=0;i<n;++i)
		for (j=0;j<m;++j)
			C[++C[0]]=(1ll*i*W+j)%x;
	sort(C+1,C+C[0]+1);
	C[0]=unique(C+1,C+C[0]+1)-(C+1);
	jia(ans,power(26,x-C[0])); 	
}
void gg() //对于被确定的位置不同的数,一定按照长度被划成一段一段的,分开计算 
{
	for (i=1;i<=B[0];++i) baoli(B[i]);
	sort(D+1,D+D[0]+1);
	D[0]=unique(D+1,D+D[0]+1)-(D+1);
	for (i=1;i<=*D;++i) jian(D[i]);
}
class CharacterBoard{
	public:
	int countGenerators(vector <string> fragment, int W, int i0, int j0)
	{
			//本问题中,显然与i0,j0的值无关,可视为0,0 
			n=fragment.size(); ::W=W;
			m=fragment[0].length();
			for (i=0;i<n;++i)
				for (j=0;j<m;++j)
				 ID[i][j]=1ll*i*W+j;
			for (i=0;i<n;++i) //直接计算可行方案比较难,不妨计算不可行的答案,那么就是对于两个不相同的点,如果L是他们距离差的约数,那么L就是不合法的. 
				for (j=0;j<m;++j) 
					for (k=0;k<n;++k)
						for (l=0;l<m;++l)
						{
							if (fragment[i][j]!=fragment[k][l]) A[++A[0]]=abs(ID[i][j]-ID[k][l]);
							B[++B[0]]=abs(ID[i][j]-ID[k][l]);
						}
			sort(B+1,B+B[0]+1);
			B[0]=unique(B+1,B+B[0]+1)-(B+1); 
			sort(A+1,A+A[0]+1);
			jia(ans,min(W,n*m-1));
			if (W>=n*m)
			jia(ans,fuck(W-n*m));
			gg();
			A[0]=unique(A+1,A+A[0]+1)-(A+1);
			for (i=1;i<=A[0];++i) Gao(A[i]);
			return ans;
	}
}MRT;

int main()
{
	cout<<MRT.countGenerators({"ruf", "ftr", "suw", "dxd"}, 13, 0, 0);
}
