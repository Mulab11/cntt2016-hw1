#include <bits/stdc++.h>

using namespace std;


class BinPacking {
public:
	int minBins(vector <int> item) {
		sort(item.begin(),item.end());//排序 
		int n=item.size(),cnt=0,ret=0;
		for(int i=n-1;i>=0;--i)if(item[i]!=998244353){
			if(item[i]==100){++cnt;continue;}//为100的单独计算 
			for(int j=i-1;j>=0;--j)if(item[i]+item[j]<=300){//找另一个尽量大的 
				item[j]=998244353;
				break;
			}
			item[i]=998244353;
			++ret;
		}
		return ret+(cnt+2)/3;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
