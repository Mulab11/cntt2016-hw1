#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class KingdomAndTrees{
	private:
		bool judge(int lim,vector<int>&a){
			int last=0;
			for (auto i:a){
				int t=max(last+1,i-lim);
				if (t>i+lim) return false;
				last=t;
			}
			return true;
		}
	public:
		int minLevel(vector <int> heights){
			int l=0,r=1000000000,mid;
			while(l<r){
				mid=(l+r)>>1;
				if (judge(mid,heights)) r=mid;
				else l=mid+1;
			}
			return l;
		}
};
