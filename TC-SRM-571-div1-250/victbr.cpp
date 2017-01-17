#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
class FoxAndMp3{
	public:
		int cnt,N;
		string ss;
		vector <string> ans;
		vector <string> playList(int n){
			cnt = 0;N = n;
			for (char i = '1';i <= '9';i++){
				string s = "";s += i;
				dfs(s,i-'0');
				if (cnt >= 50) break;
			}
			return ans;
		}
		void dfs(string s,ll val){
			if (val > N) return;
			if (cnt < 50) {
				ss = s + ".mp3";
				ans.push_back(ss);cnt++;
			}
			if (cnt >= 50) return; 
			for (char i = '0';i <= '9';i++){
				dfs(s+i,val*10+i-'0');
				if (cnt >= 50) return;
			}
			
		}
		
};
