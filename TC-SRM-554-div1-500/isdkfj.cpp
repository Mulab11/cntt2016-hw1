#include <bits/stdc++.h>

using namespace std;

bool v[100005];

class TheBrickTowerMediumDivOne {
public:
	vector <int> find(vector <int> heights) {
		vector<int>ans;
		vector<pair<int,int> >tmp;
		ans.push_back(0);
		v[0]=1;
		int n=heights.size();
		for(int i=1;i<=n;++i){
			int p=-1;
			for(int j=0;j<n;++j)
			if(!v[j]&&heights[j]<=heights[ans[i-1]]){p=j;break;}//选择递减且字典序最小的 
			if(p==-1)break;
			ans.push_back(p);
			v[p]=1;
		}
		for(int i=0;i<n;++i)if(!v[i])tmp.push_back(make_pair(heights[i],i));
		if(tmp.size())sort(tmp.begin(),tmp.end());//排序 
		for(int i=0;i<tmp.size();++i)ans.push_back(tmp[i].second);//递增放入 
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
