#include <bits/stdc++.h>

using namespace std; 

class UndoHistory{
	public:
		int n,ans;
		int minPresses(vector<string> s){
			n = s.size();
			ans = s[0].size();
			for (int i = 1;i < n;i++){
				int tot = 0,mn = 52;
				for (int j = 0;j < i;j++){
					tot = 0;
					while (s[j][tot] == s[i][tot] && tot < s[j].size() && tot < s[i].size()) tot++;
					mn = min(mn,(int)s[i].size()-tot+2);
				//	cout << mn << endl;
					if (j+1 == i && (tot == s[j].size())) mn = min(mn,(int)s[i].size()-tot);
				//	cout << mn << endl;
				}
				ans += mn;
			}
			return ans+n;
		}
};
