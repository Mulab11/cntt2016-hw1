#include<bits/stdc++.h>
using namespace std;
vector<int> a;
vector<string> e;
int s,v[55][1024],n;
void D(int x,int y){v[x][y]=1;s=max(s,y);for(int i=0;i<n;i++)if(e[x][i]=='Y'&&!v[i][y^a[i]])D(i,y^a[i]);}
class XorTravelingSalesman//搜索
{
	public:
		int maxProfit(vector<int> A,vector<string> E){return n=A.size(),a=A,e=E,D(0,a[0]),s;}
};
