#include <bits/stdc++.h>

using namespace std;


class TomekPhone {
public:
	int minKeystrokes(vector <int> frequencies, vector <int> keySizes) {
		vector<int>a=frequencies;
		vector<pair<int,int> >b;
		for(int i=0;i<keySizes.size();++i)b.push_back(make_pair(0,keySizes[i]));
		int n=a.size(),m=b.size();
		sort(a.begin(),a.end());//按出现次数排序 
		int ret=0;
		for(int i=n-1;i>=0;--i){
			int p=-1,v=9999;
			for(int j=0;j<m;++j)if(b[j].second&&b[j].first<v)v=b[j].first,p=j;
			//选出最小的 
			if(p==-1)return -1;
			++b[p].first; --b[p].second;
			ret+=(v+1)*a[i];//按上去 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
