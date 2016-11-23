#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class CheckerExpansion{
	int calc(long long a){
		if (a<=1) return 0;
		return (a/2)+calc(a/2);
	}
	
	bool C(long long a,long long b){
		if (a<b) return false;
		if (calc(a)-calc(b)-calc(a-b)>0) return false;
		return true;
	}
	
	char clac(long long t,long long x,long long y){
		if (x+y<0) return '.';
		if ((x+y)&1) return '.';
		if ((x+y)/2>=t) return '.';
		if (y<0) return '.';
		long long g=(x+y)/2;
		if (g&1){
			if (C(g,y)) return 'B';
			else return '.';
		}
		else{
			if (C(g,y)) return 'A';
			else return '.';
		}
	}
	
	public:
		vector<string> resultAfter(long long t,long long x0,long long y0, int w, int h){
			vector<string> ret;
			for (int i=0;i<h;++i){
				string tmp;
				for (int j=0;j<w;++j) tmp+=clac(t,x0+j,y0+h-i-1);
				ret.push_back(tmp);
			}
			return ret;
		}
};
