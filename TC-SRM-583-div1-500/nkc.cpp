#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 5010
using namespace std;
int a[N],siz[N],fa[N];
struct TurnOnLamps
{
	int minimize(vector <int> roads, string initState, string isImportant)
	{
		int n=roads.size();
		int i,j;
		for(i=0;i<n;i++)
		{
			fa[i+1]=roads[i];
			if(isImportant[i]=='1')
			{
				if(initState[i]=='0') a[i+1]=1;
				else a[i+1]=2;
			}
		}
		int tot=0;
		for(i=n;i>=1;i--)
		{
			if(a[i]==0)
			{
				tot+=siz[i]/2;
				if(siz[i]&1) siz[fa[i]]++;
			}
			if(a[i]==1)
			{
				tot+=siz[i]/2;
				siz[fa[i]]++;
			}
			if(a[i]==2)
			tot+=(siz[i]+1)/2;
		}
		tot+=(siz[0]+1)/2;
		return tot;
	}
};
/*int main()
{
	TurnOnLamps P;
	vector<int> V;
	V.push_back(0);
	V.push_back(0);
	V.push_back(1);
	V.push_back(1);
	V.push_back(3);
	V.push_back(1);
	V.push_back(6);
	V.push_back(3);
	V.push_back(1);
	cout<<P.minimize(V,"0001","0111");
}*/