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

const int N=55,inf=1e9+7;
int dis[N][N],n;

class TravelOnMars{
public:
	int minTimes(vector<int> range, int startCity, int endCity){
	n=range.size();
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++) dis[i][j]=inf;
			for(int j=1;j<=range[i];j++)
				dis[i][(i+j)%n]=1,dis[i][(i-j+n*N)%n]=1;
		}
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		return dis[startCity][endCity];
	}
};

