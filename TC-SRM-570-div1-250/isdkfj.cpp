#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

class RobotHerb {
public:
	long long getdist(int T, vector <int> a) {
		LL x=0,y=0;int f=0;
		for(int k=0;k<4;++k)//模拟4次 
			for(int i=0;i<a.size();++i){
				if(f==0)x+=a[i];
				else if(f==1)y-=a[i];
				else if(f==2)x-=a[i];
				else if(f==3)y+=a[i];//走 
				f=(f+a[i])%4;
			}
		x=x*(T/4);y=y*(T/4);//T/4次都是一样的 
		for(int k=0;k<T%4;++k)//模拟T%4次 
			for(int i=0;i<a.size();++i){
				if(f==0)x+=a[i];
				else if(f==1)y-=a[i];
				else if(f==2)x-=a[i];
				else if(f==3)y+=a[i];//走 
				f=(f+a[i])%4;
			}
		return abs(x)+abs(y);//答案 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
