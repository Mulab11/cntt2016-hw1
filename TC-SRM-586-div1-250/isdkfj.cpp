#include <bits/stdc++.h>

using namespace std;

int work(vector<int>Y,double t){
	int tmp=0;
	for(int j=1;j<Y.size();++j)
	if(Y[j-1]<Y[j])tmp+=Y[j-1]<t&&t<Y[j];
	else if(Y[j-1]>Y[j])tmp+=Y[j]<t&&t<Y[j-1];//中间 
	for(int j=0;j<Y.size();++j)tmp+=fabs(Y[j]-t)<1e-6;//端点 
	return tmp;
}

class PiecewiseLinearFunction {
public:
	int maximumSolutions(vector <int> Y) {
		int ans=0;
		for(int i=1;i<Y.size();++i)
			if(Y[i]==Y[i-1])return -1;//有两个相等 
		for(int i=0;i<Y.size();++i)
			for(int j=0;j<Y.size();++j)
			ans=max(ans,work(Y,(Y[i]+Y[j])/2.));//中点 
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
