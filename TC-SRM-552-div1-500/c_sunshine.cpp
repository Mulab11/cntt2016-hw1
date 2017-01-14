#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int B=1000;
int cval[256];
class FoxAndFlowerShopDivOne
{
	public:
	int n,m,D,MD;
	int fw[35][35],f[35][35],g[35][35];
	int w1[B+B],w2[B+B];
	
	int sumf(int x1,int x2,int y1,int y2)
	{
		if(D)swap(x1,y1),swap(x2,y2);
		return f[x2][y2]-f[x1-1][y2]-f[x2][y1-1]+f[x1-1][y1-1];
	}
	
	int sumg(int x1,int x2,int y1,int y2)
	{
		if(D)swap(x1,y1),swap(x2,y2);
		return g[x2][y2]-g[x1-1][y2]-g[x2][y1-1]+g[x1-1][y1-1];
	}
	
	int calc()
	{
		int ans=-1;
		for(int p=1;p<n;p++)
		{
			//w1/w2[i] : the maximum number of flowers in a rectangle,
			//while the number of 'L's minus the number of 'P's is equal to i. 
			int fs,gs,fmin1=B,fmax1=-B,fmin2=B,fmax2=-B;
			memset(w1,-20,sizeof(w1));
			//pick all possible rectangles above i-th row.
			for(int i1=1;i1<=p;i1++)
				for(int i2=i1;i2<=p;i2++)
					for(int j1=1;j1<=m;j1++)
						for(int j2=j1;j2<=m;j2++)
						{
							fs=sumf(i1,i2,j1,j2);
							gs=sumg(i1,i2,j1,j2);
							w1[fs+B]=max(w1[fs+B],gs);
							fmin1=min(fmin1,fs);
							fmax1=max(fmax1,fs);
						}
			//pick all possible rectangles below i-th row.
			memset(w2,-20,sizeof(w2));
			for(int i1=p+1;i1<=n;i1++)
				for(int i2=i1;i2<=n;i2++)
					for(int j1=1;j1<=m;j1++)
						for(int j2=j1;j2<=m;j2++)
						{
							fs=sumf(i1,i2,j1,j2);
							gs=sumg(i1,i2,j1,j2);
							w2[fs+B]=max(w2[fs+B],gs);
							fmin2=min(fmin2,fs);
							fmax2=max(fmax2,fs);
						}
			//merge two arrays to update the answer.
			for(int i=fmin1;i<=fmax1;i++)
				for(int j=fmin2;j<=fmax2;j++)
					if(max(i+j,-i-j)<=MD)
						ans=max(ans,w1[i+B]+w2[j+B]);
		}
		return ans;
	}
	
	int theMaxFlowers(vector<string> flowers,int maxDiff)
	{
		cval['L']=1,cval['P']=-1,cval['.']=0;MD=maxDiff;
		n=flowers.size(),m=flowers[0].size();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				f[i][j]=fw[i][j]=cval[flowers[i-1][j-1]];
				g[i][j]=cval[flowers[i-1][j-1]]!=0;
				f[i][j]+=f[i][j-1]+f[i-1][j]-f[i-1][j-1];
				g[i][j]+=g[i][j-1]+g[i-1][j]-g[i-1][j-1];
			}
		//f: the number of 'L's - the number of 'P's.
		//g: the number of flowers.
		int ans=-1;
		ans=calc();
		swap(n,m),D=1;//transposition
		ans=max(ans,calc());
		return ans;
	}
};

