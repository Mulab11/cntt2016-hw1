#include <bits/stdc++.h>

using namespace std;


class FoxAndChess {
public:
	string ableToMove(string begin, string target) {
		int n=begin.size(),i=0,j=0;
		for(;i<n;++i)
		if(begin[i]!='.'){//找到一个 
			while(j<n&&target[j]=='.')++j;
			if(j>=n)return "Impossible";//找不到 
			if(begin[i]!=target[j])return "Impossible";//不相同 
			if(begin[i]=='L'&&j>i)return "Impossible";//在右边 
			if(begin[i]=='R'&&j<i)return "Impossible";//在左边 
			++j;
		}
		while(j<n&&target[j]=='.')++j;
		if(j<n)return "Impossible";//有多的 
		return "Possible";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
