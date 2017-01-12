#include <bits/stdc++.h>

using namespace std;


class TheDevice {
public:
	int minimumAdditional(vector <string> plates) {
		int m=plates[0].size(),cnt[2],ret=0;
		for(int i=0;i<m;++i){
			cnt[0]=cnt[1]=0;
			for(int j=0;j<plates.size();++j)++cnt[plates[j][i]-48];//每位0和1的个数 
			int ans=0;
			if(cnt[1]<2)ans+=2-cnt[1];//缺1 
			if(cnt[0]==0)++ans;//缺0 
			ret=max(ret,ans);
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
