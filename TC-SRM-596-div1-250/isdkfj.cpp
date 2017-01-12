#include <bits/stdc++.h>

using namespace std;


class IncrementAndDoubling {
public:
	int getMin(vector <int> desiredArray) {
		int ret=0,mx=0;
		for(int i=0;i<desiredArray.size();++i){
			int x=desiredArray[i],cnt=0,flag=0;
			while(x){
				ret+=x&1;//1的个数 
				x>>=1;
				if(flag)++cnt;//乘以2的操作次数 
				else flag=1;
			}
			mx=max(mx,cnt);
		}
		return ret+mx;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
