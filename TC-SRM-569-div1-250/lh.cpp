#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TheDevice{
	int cnt[3];
	int num[100][2];
	int n,m;
	public:
		int minimumAdditional(vector<string> plates){
			m=plates[0].length();
			for (auto &x:plates)
			for (int i=0;i<m;++i) ++num[i+1][x[i]-'0'];
			int ans=0;
			for (int i=1;i<=m;++i){
				int tmp=0;
				if (num[i][0]<1) tmp+=1-num[i][0];
				if (num[i][1]<2) tmp+=2-num[i][1];
				if (tmp>ans) ans=tmp;
			}
			return ans;
		}
};
