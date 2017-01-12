#include <bits/stdc++.h>

using namespace std;

char get(long long t,long long x,long long y){
	if(t==0)return '.';//全空 
	if(t==1){//走了一步 
		if(x==0&&y==0)return 'A';
		else return '.';
	}
	if(t==2){//走了两步 
		if(x==0&&y==0)return 'A';
		if(x==1&&y==1)return 'B';
		if(x==2&&y==0)return 'B';
		return '.';
	}
	long long u=1;
	while(u*2<t)u=u<<1;
	if(x<=2*u-2&&y<u)return get(u,x,y);
	if(x>=u&&x<=3*u-2&&y>=u&&y<=2*u-1)return get(t-u,x-u,y-u);
	if(x>=2*u&&x<=4*u-2&&y<u)return get(t-u,x-2*u,y);
	//递归查找 
	return '.';//为空 
}

class CheckerExpansion {
public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h) {
		vector<string>ret;
		for(int i=h-1;i>=0;--i){
			string s="";
			for(int j=0;j<w;++j)s+=get(t,x0+j,y0+i);
			ret.push_back(s);
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
