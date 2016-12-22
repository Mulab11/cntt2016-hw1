#include<bits/stdc++.h>
using namespace std;
int A[16][16],f[16][16][16][16],v[16][16][16][16],i,j;
int Cost(int a,int b,int c,int d,int e,int f,int g,int h)
{
	int r=0,x=a,y;
	for(;x<=c;x++)for(y=b;y<=d;y++)if(A[x][y])r+=max(max(abs(x-e),abs(x-g)),max(abs(y-f),abs(y-h)));
	return r;
}
int Work(int a,int b,int c,int d)//消完一个矩形的最小代价
{
	if(a==c&&b==d)return 0;
	if(v[a][b][c][d])return f[a][b][c][d];
	int t=1<<30;
	if(a<c)t=min(t,min(Work(a+1,b,c,d)+Cost(a,b,a,d,a,b,c,d),Work(a,b,c-1,d)+Cost(c,b,c,d,a,b,c,d)));
	if(b<d)t=min(t,min(Work(a,b+1,c,d)+Cost(a,b,c,b,a,b,c,d),Work(a,b,c,d-1)+Cost(a,d,c,d,a,b,c,d)));
	return v[a][b][c][d]=1,f[a][b][c][d]=t;
}
class EllysChessboard
{
	public:
		int minCost(vector<string> a)
		{
			for(;i<8;i++)for(j=0;j<8;j++)A[i+j][i+8-j]=(a[i][j]=='#');
			return Work(0,0,15,15); 
		}
};
