#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TheTree{
	public:
		int maximumDiameter(vector<int> cnt){
			int n=cnt.size(),ans=0;
			for (int i=-1;i<n;++i){
				int d1=0,d2=0;
				bool f1=true,f2=true;
				for (int j=i+1;j<n;++j){
					if (cnt[j]==1){
						f2=false;
						++d1;
					}
					else{
						if (f1) ++d1;
						if (f2) ++d2;
					}
				}
				ans=max(ans,d1+d2);
			}
			return ans;
		}
};
