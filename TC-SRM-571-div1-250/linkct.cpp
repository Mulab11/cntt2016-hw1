#include <bits/stdc++.h>
using namespace std;

class FoxAndMp3{
public:
	vector <string> ans; int n;
	void dfs(int num){
		if(num > n || ans.size() == 50) return;
		if(num){
			stringstream tmp;
			tmp << num;
			tmp << ".mp3";
			ans.push_back("");
			tmp >> ans.back();
		}
		for(int i = 0; i < 10; ++ i)
			if(num * 10 + i)
				dfs(num * 10 + i);
	}
	vector <string> playList(int n_){
		n = n_, dfs(0);
		return ans;
	}
};
