#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int inf=100;
int dis[55][55];

class Egalitarianism{
public:
	int maxDifference(vector<string> isFriend, int d){
		int n=isFriend.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i==j) dis[i][j]=0; else if(isFriend[i][j]=='Y') dis[i][j]=1; else dis[i][j]=inf;
		for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		int ans=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++) ans=max(ans,dis[i][j]);
		if(ans<inf) return ans*d;
		return -1;
	}
};
