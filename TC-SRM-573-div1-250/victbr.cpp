#include <bits/stdc++.h>

using namespace std;
bool cmp(int x,int y){return x > y;}
class TeamContest{
	public:
		int ss[60];
		int worstRank(vector <int> st){
			int n = st.size(),ans = 0,s;
			for (int i = 0;i < n;i++) ss[i] = st[i];
			s = max(max(ss[0],ss[1]),ss[2])+min(min(ss[0],ss[1]),ss[2]);
			sort(ss+3,ss+n,cmp);
			int t = 3,w = n-1;
			while (w-t+1 >= 3){
				if (ss[w]+ss[t] <= s) w--;
				else{
					ans++;
					t++;w--;w--;
				}
			}
			return ans+1;
		}
};
