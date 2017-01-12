#include <bits/stdc++.h>

using namespace std;

int f[55][55];

class TravelOnMars {
public:
	int minTimes(vector <int> range, int startCity, int endCity) {
		memset(f,0x3f,sizeof f);
		int n=range.size();
		for(int i=0;i<n;++i)f[i][i]=0;
		for(int i=0;i<n;++i)
			for(int j=1;j<=range[i];++j){
				f[i][(i+j)%n]=1;
				f[i][(i-j+n)%n]=1;//按题意建图 
			}
		for(int k=0;k<n;++k)
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//floyd
		return f[startCity][endCity];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
