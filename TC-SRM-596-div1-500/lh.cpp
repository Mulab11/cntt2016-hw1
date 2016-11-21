#include<set>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class BitwiseAnd{
	static const int maxn=11;
	vector<long long> ans;
	set<int> canuse,doub;
	set<int> lft[maxn];
	
	int calc(int a){
		return a*(a-1)/2;
	}
	
	public:
		vector<long long> lexSmallest(vector<long long> s, int N){
			if (calc(N)>60) return ans;
			int now=s.size();
			for (int i=0;i<now;++i)
			for (int j=i+1;j<now;++j) if ((s[i]&s[j])==0) return ans;
			for (int i=0;i<now;++i)
			for (int j=i+1;j<now;++j)
			for (int k=j+1;k<now;++k) if (s[i]&s[j]&s[k]) return ans;
			for (auto i:s){
				for (int j=0;j<60;++j) if (i&(1LL<<j)){
					if (canuse.find(j)!=canuse.end()) doub.insert(j);
					canuse.insert(j);
//					printf("")
				}
			}
			for (auto i:doub) canuse.erase(i);
//			puts("xxxxxxxxxx");
			for (int i=0;i<now;++i){
				for (int j=0;j<60;++j) if (s[i]&(1LL<<j)){
					if (canuse.find(j)!=canuse.end())
						lft[i].insert(j);
				}
				if ((int)lft[i].size()<N-now) return ans;
			}
			for (auto i:canuse) doub.insert(i);
			for (int i=0;i<60;++i) canuse.insert(i);
			for (auto i:doub) canuse.erase(i);
			if ((int)canuse.size()<calc(N-now)) return ans;
			ans=s;
			for (int i=now;i<N;++i){ans.push_back(0);}
			for (int i=now;i<N;++i){
				for (int j=0;j<now;++j){
					int tmp=*lft[j].begin();
					lft[j].erase(tmp);
					ans[i]|=1LL<<tmp;
				}
				for (int j=i+1;j<N;++j){
					int tmp=*canuse.begin();
					canuse.erase(tmp);
					ans[i]|=1LL<<tmp;
					ans[j]|=1LL<<tmp;
				}
			}
			sort(ans.begin(),ans.end());
			return ans;
		}
};
