#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct KeyDungeonDiv1
{
	int f[4100][131];
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys)
	{
		int n=doorR.size();
		memset(f,0xef,sizeof(f));
		f[0][keys[0]]=keys[2];
		int i,j,k,ans=keys[0]+keys[1]+keys[2];
		for(k=0;k<(1<<n);k++)
		{
			int tot=keys[0]+keys[1]+keys[2];
			for(i=0;i<n;i++)
			if(k&(1<<i)) tot+=(roomR[i]+roomG[i]+roomW[i]-doorR[i]-doorG[i]);
			for(j=0;j<=(n+1)*10;j++)
			if(f[k][j]>=0)
			{
				ans=max(ans,tot);
				int totr=j,totw=f[k][j],totg=tot-totr-totw;
				for(i=0;i<n;i++)
				if(!(k&(1<<i)))
				{
					int tmpr=(doorR[i]>totr?0:(totr-doorR[i]));
					int tmpw=totw-((doorR[i]>totr?(doorR[i]-totr):0)+(doorG[i]>totg?(doorG[i]-totg):0));
					if(tmpw<0) continue;
					f[k+(1<<i)][tmpr+roomR[i]]=max(f[k+(1<<i)][tmpr+roomR[i]],tmpw+roomW[i]);
				}
			}
		}
		return ans;
	} 
};
/*int main()
{
	KeyDungeonDiv1 P;
	vector<int>a,b,c,d,e,f;
	a.push_back(1);a.push_back(2);a.push_back(3);
	b.push_back(0);b.push_back(4);b.push_back(9);
	c.push_back(0);c.push_back(0);c.push_back(10);
	d.push_back(0);d.push_back(8);d.push_back(9);
	e.push_back(1);e.push_back(0);e.push_back(8);
	f.push_back(3);f.push_back(1);f.push_back(2);
	a.push_back(0);a.push_back(0);a.push_back(0);
	b.push_back(0);b.push_back(0);b.push_back(0);
	c.push_back(10);c.push_back(10);c.push_back(10);
	d.push_back(10);d.push_back(10);d.push_back(10);
	e.push_back(10);e.push_back(10);e.push_back(10);
	f.push_back(10);f.push_back(10);f.push_back(10);
	cout<<P.maxKeys(a,b,c,d,e,f);
}*/