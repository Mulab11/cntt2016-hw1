#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int mov[4][2]={{1,0},{0,-1},{-1,0},{0,1}};

class RobotHerb{
	long long abs(long long a){return (a<0)?-a:a;}
	
	public:
	long long getdist(int T, vector<int> a){
		int n=a.size();
		long long px=0,py=0,x=0,y=0;
		int now=0;
		
		for (int i=0;i<4;++i){
			for (int j=0;j<n;++j){
				px+=mov[now][0]*a[j];
				py+=mov[now][1]*a[j];
				now=(now+a[j])%4;
			}
		}
		x=(T/4)*px;
		y=(T/4)*py;
		now=0;
		T%=4;
		cout<<T<<endl;
		while(T--){
			for (int j=0;j<n;++j){
				x+=mov[now][0]*a[j];
				y+=mov[now][1]*a[j];
				now=(now+a[j])%4;
			}
		}
		return (abs(x)+abs(y));
	}
};
