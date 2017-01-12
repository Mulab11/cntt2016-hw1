#include <bits/stdc++.h>

using namespace std;


class SurveillanceSystem {
public:
	string getContainerInfo(string containers, vector <int> reports, int L) {
		int n=containers.size();
		vector<pair<int,int> >seg[55];
		int cnt[55]={0};
		for(int i=0;i<n;++i)if(i+L-1<n){
			int k=0;
			for(int j=i;j<i+L;++j)k+=containers[j]=='X';
			seg[k].push_back(make_pair(i,i+L));//统计一段区间L内的X个数 
		}
		for(int i=0;i<reports.size();++i)++cnt[reports[i]];
		string ret;
		for(int i=0;i<n;++i){
			int flag=0,flag2=1;
			for(int j=0;j<=n;++j)if(cnt[j]){//有监视器 
				int s=0;
				for(int k=0;k<seg[j].size();++k)
					if(seg[j][k].first<=i&&i<seg[j][k].second)++s;//在覆盖区间内 
				if(s+cnt[j]>seg[j].size()){flag=1;break;}//至少有一个能监视到 
				if(s)flag2=0;//可能监视到 
			}
			if(flag)ret+="+";
			else if(flag2)ret+="-";
			else ret+="?";
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
