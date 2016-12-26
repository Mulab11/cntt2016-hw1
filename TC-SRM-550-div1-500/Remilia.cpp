// by ξ
// program sky  :)

#include <bits/stdc++.h>

using namespace std;

struct CheckerExpansion{
	vector<string> resultAfter(long long t,long long x0,long long y0,int w,int h){
		vector<string> res{};
		--t;
		for(auto j=y0+h-1;j>=y0;--j){
			string ss="";
			for(auto i=x0;i<x0+w;++i)
				// 枚举点，搞一搞
				if((i+j&1)==0 && (i+j)/2<=t && (((i+j)/2)&j)==j)ss+=i+j&3?'B':'A';else ss+='.';
			res.push_back(ss);
		}
		return res;
	}
};