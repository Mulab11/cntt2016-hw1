#include <bits/stdc++.h>

using namespace std;


class TrafficCongestion {
public:
	static const int mo=1000000007;
	int f[1000005];
	int theMinCars(int treeHeight) {
		f[0]=1;
		f[1]=1;//初始化 
		for(int i=2;i<=treeHeight;++i){
			f[i]=f[i-1];
			if((f[i]+=f[i-2])>=mo)f[i]-=mo;
			if((f[i]+=f[i-2])>=mo)f[i]-=mo;//递推f[i]=f[i-1]+2*f[i-2]
		}
		return f[treeHeight];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
