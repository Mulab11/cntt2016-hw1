#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

#define mp make_pair

const LL inf=1LL<<40;

class YamanoteLine
{
	public:
	
	struct Dist
	{
		LL di,lv;
		Dist(const LL &a=0,const LL &b=0):di(a),lv(b){}
		Dist operator+(const Dist &o)const
		{return Dist(di+o.di,lv+o.lv);}
	}d[55];
	
	//There is an edge from adj[i][k].first to i whose weight is adj[i][k].second
	vector<pair<int,Dist> > adj[55];
	
	pair<bool,LL> check(LL len,int n,vector<int> s1,vector<int> t1,vector<int> l1,vector<int> s2,vector<int> t2,vector<int> l2)
	{
		//Build the graph with the value length.
		for(int i=0;i<=n;i++)adj[i].clear();
		for(int i=0;i<n;i++)adj[i+1].push_back(mp(i,Dist(-1,0)));
		adj[0].push_back(mp(n,Dist(len,1)));
		adj[n].push_back(mp(0,Dist(-len,-1)));
		for(int i=0;i<l1.size();i++)
			if(s1[i]<t1[i])adj[t1[i]].push_back(mp(s1[i],Dist(-l1[i],0)));
			else adj[t1[i]].push_back(mp(s1[i],Dist(len-l1[i],1)));
		for(int i=0;i<l2.size();i++)
			if(s2[i]<t2[i])adj[s2[i]].push_back(mp(t2[i],Dist(l2[i],0)));
			else adj[s2[i]].push_back(mp(t2[i],Dist(l2[i]-len,-1)));
		d[0]=Dist(0,0);
		for(int i=1;i<=n;i++)d[i]=Dist(inf,0);
		Dist t,ls;
		bool flag=1;
		//Use Bellman-Ford to check.
		for(int tim=n*n;tim--&&flag;)//flag means if there are still any successful updates.
		{
			flag=0;
			for(int u=0,v;u<=n;u++)
				if(d[u].di<inf)
				{
					for(int i=0;i<adj[u].size();i++)
					{
						v=adj[u][i].first;
						t=d[u]+adj[u][i].second;
						if(d[v].di>t.di)
						{
							d[v]=t;
							if(d[v].di<0)return mp(0,d[v].lv);
							flag=1;
							//Store the last value that you used to update.
							ls=t;
						}
					}
				}
		}
		if(!flag)return mp(1,0);//Impossible.
		else return mp(0,ls.lv);
	}
	
	long howMany(int n,vector<int> s1,vector<int> t1,vector<int> l1,vector<int> s2,vector<int> t2,vector<int> l2)
	{
		LL L,R,low,high,mid;
		L=-1,R=inf;
		//Determine the upper bound.
		low=n,high=inf;
		while(low<=high)
		{
			mid=low+high>>1;
			pair<bool,LL> tmp=check(mid,n,s1,t1,l1,s2,t2,l2);
			if(tmp.first||tmp.second>0)
			{
				if(tmp.first)R=mid;
				low=mid+1;
			}
			else high=mid-1;
		}
		//Determine the lower bound.
		low=n,high=inf;
		while(low<=high)
		{
			mid=low+high>>1;
			pair<bool,LL> tmp=check(mid,n,s1,t1,l1,s2,t2,l2);
			if(tmp.first||tmp.second<0)
			{
				if(tmp.first)L=mid;
				high=mid-1;
			}
			else low=mid+1;
		}
		if(L>=n&&R==inf)return -1;
		else if(L==-1)return 0;
		return R-L+1;
	}
};
