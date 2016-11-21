#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TravelOnMars{
	private:
		static const int maxn=55,inf=10000000;
		int mp[maxn][maxn];
	
	public:
		int minTimes(vector <int> range, int startCity, int endCity){
			int n=range.size();
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (i==j) mp[i][j]=0;
			else mp[i][j]=inf;
			for (int i=0;i<n;++i){
				int t=range[i];
				while(t){
					mp[i][(i+t)%n]=1;
					mp[i][((i-t)%n+n)%n]=1;
					--t;
				}
			}
			for (int k=0;k<n;++k)
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
			return mp[startCity][endCity];
		}
};
