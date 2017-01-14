#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
using namespace std;
template<class T>inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T>inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}

class WallGameDiv1
{
	public:
	int n,m;
	int S[55][55],sS[55][55];
	
	map<pair<pair<int,int>,pair<int,int> >, int> fR,fE;
	
	//int fR[55][55][55][55];
	//int fE[55][55][55][55];
	
	int sum(int x,int l,int r)
	{return sS[x][r]-sS[x][l-1];}
	
	int Rabbit(int x,int y,int yl,int yr)
	{
		if(fR.count(make_pair(make_pair(x,y),make_pair(yl,yr))))
			return fR[make_pair(make_pair(x,y),make_pair(yl,yr))];
		int &res=fR[make_pair(make_pair(x,y),make_pair(yl,yr))];
		if(x==n)return res=S[x][y];//In the last row. 
		//We can prove the rabbit must go down if it can.
		if(y<yl||y>yr)return res=S[x][y]+Eel(x+1,y,m+1,0);
		res=1<<20;
		if(yl>1)ten(res,Eel(x,yl-1,yl,yr)+sum(x,yl,y));//Go left
		if(yr<m)ten(res,Eel(x,yr+1,yl,yr)+sum(x,y,yr));//Go right
		return res;
	}
	
	int Eel(int x,int y,int yl,int yr)
	{
		if(fE.count(make_pair(make_pair(x,y),make_pair(yl,yr))))
			return fE[make_pair(make_pair(x,y),make_pair(yl,yr))];
		int &res=fE[make_pair(make_pair(x,y),make_pair(yl,yr))];
		if(x==n)return res=Rabbit(x,y,yl,yr);
		res=Rabbit(x,y,yl,yr);//Do not place any walls.
		if(yr-yl+1<m-1&&m>1)//To prevent the rabbit from going down.
			rel(res,Rabbit(x,y,min(yl,y),max(yr,y)));
		return res;
	}
	
	int play(vector<string> costs)
	{
		n=costs.size();
		m=costs[0].size();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				S[i][j]=costs[i-1][j-1]-'0',sS[i][j]=sS[i][j-1]+S[i][j];
		//memset(fR,-1,sizeof(fR));
		//memset(fE,-1,sizeof(fE));
		int ans=1<<20;
		//fR/fE[((i,j),(l,r))]: Rabbit/Eel play first now the token is in the cell (i,j), and walls between the current row and next are from l to r.
		for(int j=1;j<=m;j++)
			ans=min(ans,Eel(1,j,m+1,0));
		return ans;
	}
};

