#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct RandomPaintingOnABoard
{
	int n,m;
	int a[21][21],b[21][21],sum[12],f[21][1351];
	void rotate()
	{
		int i,j;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		b[j][i]=a[i][j];
		swap(n,m);
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		a[i][j]=b[i][j];
	}
	int p[21];
	double expectedSteps(vector <string> prob)
	{
		n=prob.size();m=prob[0].size();
		int i,j,k,tot=0;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		{
			a[i][j]=prob[i][j]-48;
			tot+=a[i][j];
		}
		if(n>m) rotate();
		for(i=0;i<n;i++)
		{
			sum[i]=0;
			for(j=0;j<m;j++)
			sum[i]+=a[i][j];
		}
		double ans=0;
		for(k=0;k<(1<<n);k++)
		{
			int tmp=0,o=0;
			for(i=0;i<n;i++)
			if(k&(1<<i)) tmp+=sum[i],o++;
			for(i=0;i<m;i++)
			{
				p[i]=0;
				for(j=0;j<n;j++)
				if(!(k&(1<<j)))
				p[i]+=a[j][i];
			//	cout<<p[i]<<'!';
			}
			for(i=0;i<=tot;i++)
			f[0][i]=0;
			if(o&1) f[0][tmp]+=1,f[0][tmp+p[0]]-=1;
			else f[0][tmp]-=1,f[0][tmp+p[0]]+=1;
			for(i=1;i<m;i++)
			for(j=0;j<=tot;j++)
			{
				f[i][j]=f[i-1][j];
				if(j>=p[i]) f[i][j]-=f[i-1][j-p[i]];
			//	cout<<i<<' '<<j<<' '<<f[i][j]<<endl;
			}
			for(j=1;j<=tot;j++)
			ans+=(double)tot/j*f[m-1][j];
			//ans+=((double)tot/j-1)*f[m-1][j];
		}
		return ans;
	}
};
/*int main()
{
	RandomPaintingOnABoard P;
	vector<string> V;
	V.push_back("000000000000001000000");
	V.push_back("888999988889890999988");
	V.push_back("988889988899980889999");
	V.push_back("889898998889980999898");
	V.push_back("988889999989880899999");
	V.push_back("998888998988990989998");
	V.push_back("998988999898990889899");
	/*V.push_back(3);
	V.push_back(1);
	cout<<P.expectedSteps(V);
}*/