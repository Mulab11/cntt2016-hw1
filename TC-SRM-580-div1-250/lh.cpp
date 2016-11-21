#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class EelAndRabbit{
	private:
		static const int maxn=55;
		int use[maxn<<1],top;
		int L[maxn],R[maxn];
	public:
		int getmax(vector<int> l, vector<int> t){
			int n=l.size();
			for (int i=0;i<n;++i){
				L[i]=t[i];
				R[i]=l[i]+t[i];
				use[++top]=L[i];
				use[++top]=R[i];
			}
			sort(use+1,use+1+top);
			top=unique(use+1,use+1+top)-use;
			int ans=0;
			for (int i=0;i<top;++i)
			for (int j=0;j<top;++j){
				int ret=0;
				for (int k=0;k<n;++k) if (L[k]<=use[i]&&R[k]>=use[i]) ++ret;
				else if (L[k]<=use[j]&&R[k]>=use[j]) ++ret;
				ans=max(ans,ret);
			}
			return ans;
		}
};

