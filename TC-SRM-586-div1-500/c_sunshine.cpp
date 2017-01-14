#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int inf=1000000000;
class History
{
	public:
	int n;
	
	int f[30][30],g[30][30],f_[30][30],g_[30][30];
	
	vector<pair<int,int> > range[30];
	
	vector<pair<int,int> > tr1(string inp)//get input
	{
		vector<int> tm;
		int t=0;
		for(int i=0;i<=inp.size();i++)
			if(i==inp.size()||inp[i]==' ')
				tm.push_back(t),t=0;
			else
				t=t*10+inp[i]-'0';
		vector<pair<int,int> > res;
		for(int i=0;i+1<tm.size();i++)
			res.push_back(make_pair(tm[i],tm[i+1]-1));
		return res;
	}
	
	void addbattle(int a,int i,int b,int j)
	{
		for(int kk=0;kk<2;kk++)//the relation of battle is bidirectional 
		{
			f[a][b]=min(f[a][b],range[a][i].second-range[b][j].first);//p=range[a][i].second-range[b][j].first
			//country b cannot be more than p years later than a
			g[a][b]=min(g[a][b],range[b][j].second-range[a][i].first);//q=range[b][j].second-range[a][i].first
			//country b cannot be more than q years ealier than a
			swap(a,b),swap(i,j);
		}
	}
	
	char check(int a,int x,int b,int y)
	{
		memcpy(f,f_,sizeof(f));
		memcpy(g,g_,sizeof(g));
		addbattle(a,x,b,y);//add the new relation
		//use Floyd to check the consistency
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					f[i][j]=max(-inf,min(f[i][j],f[i][k]+f[k][j])),
					g[i][j]=max(-inf,min(g[i][j],g[i][k]+g[k][j]));
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				{//It is impossible if a negative cycle exists or the feasible inteval of delta is empty
					if(f[i][j]+g[i][j]<0)return 'N';
					for(int k=0;k<n;k++)
							if(f[i][j]>f[i][k]+f[k][j]||g[i][j]>g[i][k]+g[k][j])
								return 'N';
				}
		return 'Y';
	}
	
	string verifyClaims(vector<string> dynasties,vector<string> battles,vector<string> queries)
	{
		n=dynasties.size();
		for(int i=0;i<dynasties.size();i++)
			range[i]=tr1(dynasties[i]);
		string bb;
		for(int i=0;i<battles.size();i++)
			bb+=battles[i];
		vector<string> bt;
		string bs="";
		for(int i=0;i<=bb.size();i++)
			if(i==bb.size()||bb[i]==' ')
				bt.push_back(bs),bs="";
			else
				bs+=bb[i];
		//Above is getting input
		memset(f,31,sizeof(f));
		memset(g,31,sizeof(g));
		//use triangle inequality in shortest path to represent the relation among delta of time
		for(int i=0;i<bt.size();i++)//build graph
		{
			bs=bt[i];
			addbattle(bs[0]-'A',bs[1]-'0',bs[3]-'A',bs[4]-'0');
		}
		memcpy(f_,f,sizeof(f));
		memcpy(g_,g,sizeof(g));
		string ans="";
		for(int i=0;i<queries.size();i++)//for each query
		{
			bs=queries[i];
			ans+=check(bs[0]-'A',bs[1]-'0',bs[3]-'A',bs[4]-'0');
		}
		return ans;
	}
};

