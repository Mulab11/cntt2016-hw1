#include<bits/stdc++.h>
using namespace std;
int A[15][4]={{1,1,1,1},{1,1,1,2},{1,1,2,1},{1,1,2,2},{1,1,2,3},{1,2,1,1},{1,2,1,2},{1,2,1,3},{1,2,2,1},{1,2,2,2},{1,2,2,3},{1,2,3,1},{1,2,3,2},{1,2,3,3},{1,2,3,4}};
int B[15]={1,2,2,2,3,2,2,3,2,2,3,3,3,3,4},i,j,k,D,P=1234567891,K,p,q,l,r,u,z[5];
struct MAT{int f[9][15][9][15];}s,x,e;
MAT MULT(MAT x,MAT y)
{
	MAT z=e;int i,j,k,l,m,n;
	for(i=0;i<=8;i++)for(j=0;j<15;j++)for(m=0;m<=8;m++)for(n=0;n<15;n++)if(x.f[i][j][m][n])for(k=0;k<=8;k++)for(l=0;l<15;l++)z.f[i][j][k][l]=(1ll*x.f[i][j][m][n]*y.f[m][n][k][l]+z.f[i][j][k][l])%P;
	return z;
}
int SELECT(int n,int m)
{
	int r=1,i=0;
	if(n<m)return 0;
	for(;i<m;i++)r=1ll*r*(n-i)%P;
	return r;
}
class TheBrickTowerHardDivOne
{
	public:
		int find(int C,int _K,long long H)
		{
			freopen("1.out","w",stdout);
			for(K=_K;i<15;i++)for(j=0;j<15;j++)
			{
				for(p=0;p<=B[i];p++)for(q=0;q<=B[i];q++)if(q==B[i]||B[j]<2||q!=p)for(l=0;l<=B[i];l++)if(l==B[i]||B[j]<3||l!=q&&l!=p)for(r=0;r<=B[i];r++)if(r==B[i]||B[j]<4||r!=l&&r!=q&&r!=p)
				{
					if(q&&B[j]<2)continue;
					if(l&&B[j]<3)continue;
					if(r&&B[j]<4)continue;
					z[1]=p+1;z[2]=q+1;z[3]=l+1;z[4]=r+1;D=(A[i][0]==z[A[j][0]])+(A[i][1]==z[A[j][1]])+(A[i][2]==z[A[j][2]])+(A[i][3]==z[A[j][3]])+(A[j][0]==A[j][1])+(A[j][0]==A[j][2])+(A[j][1]==A[j][3])+(A[j][2]==A[j][3]);
					for(k=0;k+D<=K;k++)x.f[k][i][k+D][j]=(0ll+SELECT(C-B[i],(p==B[i])+(q==B[i])+(l==B[i])+(r==B[i]))+x.f[k][i][k+D][j])%P;
				}
			}
			for(i=0;i<=K;i++)for(j=0;j<15;j++)x.f[i][j][8][0]=1;x.f[8][0][8][0]=1;
			for(j=0;j<15;j++)s.f[0][0][(A[j][0]==A[j][1])+(A[j][0]==A[j][2])+(A[j][1]==A[j][3])+(A[j][2]==A[j][3])][j]=SELECT(C,B[j]);
			for(;H;H/=2,x=MULT(x,x))if(H&1)s=MULT(s,x);
			return s.f[0][0][8][0];
		}
};//.
