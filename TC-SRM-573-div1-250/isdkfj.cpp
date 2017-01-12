#include <bits/stdc++.h>

using namespace std;


class TeamContest {
public:
	int worstRank(vector <int> strength) {
		int sum=max(strength[0],max(strength[1],strength[2]))+min(strength[0],min(strength[1],strength[2]));
		//自己的值 
		if(strength.size()==3)return 1;//只有3个人 
		sort(strength.begin()+3,strength.end());//排序 
		int ret=1;
		for(int i=strength.size()-1,j=3;i>j;--i){
			while(strength[i]+strength[j]<=sum&&j<i)++j;//枚举最大，找一个能用的最小的 
			if(j+1<i)j+=2,++ret;else break;
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
