#include <bits/stdc++.h>

using namespace std;


class FoxAndMountainEasy {
public:
	string possible(int n, int h0, int hn, string history) {
		int t=0,det=0,x;
		for(int i=0;i<history.size();++i){//求最低点和高度差 
			if(history[i]=='U')++det;
			else --det; t=min(t,det);
		}
		n-=history.size();
		if(h0+t<0){//高度不够先往上走 
			x=-t-h0;
			if(x>n)return "NO";
			n-=x;h0+=x;
		}
		h0+=det;
		if(abs(hn-h0)>n)return "NO";//超出步数 
		if((n-abs(hn-h0))&1)return "NO";//奇数 
		return "YES";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
