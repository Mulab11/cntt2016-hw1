#include <bits/stdc++.h>

using namespace std;


class KingdomAndTrees {
public:
	int minLevel(vector <int> heights) {
		int n=heights.size();
		int l=0,r=1000000000,mid;
		while(l<r){
			mid=(l+r)>>1;//二分答案 
			bool flag=1;
			int pre=0;
			for(int i=0;i<n;++i){
				if(heights[i]+mid<=pre){//不可行 
					flag=0;
					break;
				}
				pre=max(pre+1,heights[i]-mid);//让当前数尽量小 
			}
			//贪心判断是否可行 
			if(flag)r=mid;else l=mid+1;
		}
		return l;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
