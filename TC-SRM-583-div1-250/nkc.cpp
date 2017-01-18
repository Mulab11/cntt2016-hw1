#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 5010
using namespace std;
int s,e;
int to[N],nxt[N],pre[N],cnt;
void ae(int ff,int tt)
{
	cnt++;
	to[cnt]=tt;
	nxt[cnt]=pre[ff];
	pre[ff]=cnt;
}
int d[N];
int q[N],h,t;
void bfs()
{
	h=t=1;q[1]=s;
	d[s]=1;
	int i,j,x,y;
	while(h<=t)
	{
		x=q[h];h++;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(!d[j])
			{
				d[j]=d[x]+1;
				t++;q[t]=j;
			}
		}
	}
}
struct TravelOnMars
{
	int minTimes(vector <int> range, int startCity, int endCity)
	{
		int n=range.size();
		s=startCity,e=endCity;
		int i,j,x,y;
		for(i=0;i<n;i++)
		{
			for(j=-range[i];j<=range[i];j++)
			{
				x=((i+j)%n+n)%n;
				ae(i,x);
			}
		}
		bfs();
		return d[e]-1;
	}
};
/*int main()
{
	SpaceWarDiv1 P;
	vector<int> V1,V2;
	vector<long long>V3;
	V1.push_back(2);
	V1.push_back(3);
	V1.push_back(4);
	V2.push_back(1);
	V2.push_back(3);
	V2.push_back(4);
	V3.push_back(2);
	V3.push_back(9);
	V3.push_back(4);
	cout<<P.minimalFatigue(V1,V2,V3);
}*/