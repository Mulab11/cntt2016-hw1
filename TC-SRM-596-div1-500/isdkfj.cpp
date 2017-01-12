#include <bits/stdc++.h>

using namespace std;

int cnt[60],w[60];
bool flag[60];

class BitwiseAnd {
public:
	vector<long long> lexSmallest(vector<long long> subset, int N) {
		for(int i=0;i<subset.size();++i)
			for(int j=0;j<60;++j)if((subset[i]>>j)&1)++cnt[j],w[j]=i;//每个位的出现次数和对应哪个数 
		vector<long long>ret,kk;
		for(int i=0;i<subset.size();++i)
			for(int j=0;j<subset.size();++j)
			if(!(subset[i]&subset[j]))return kk;//判断给定集合是否合法 
		for(int i=0;i<60;++i)if(cnt[i]>2)return kk;//是否三个&=0 
		ret=subset;
		while(ret.size()<N){
			memset(flag,0,sizeof flag);
			long long t=0;
			int tmp=0;
			for(int i=0;i<60;++i)if(cnt[i]==1&&!flag[w[i]]){
				t|=1ll<<i;++cnt[i];flag[w[i]]=1;++tmp;
			}//贪心加最小的位 
			if(tmp!=subset.size())return kk;//不能全部都有 
			ret.push_back(t);
		}
		for(int i=subset.size(),k=0;i<ret.size();++i)
			for(int j=i+1;j<ret.size();++j){//补上后面新加的数的公共位 
				while(k<60&&cnt[k])++k;
				if(k==60)return kk;
				ret[i]|=1ll<<k;
				ret[j]|=1ll<<k;
				cnt[k]=2;
			}
		sort(ret.begin(),ret.end());
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
