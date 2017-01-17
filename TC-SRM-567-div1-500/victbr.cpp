#include <bits/stdc++.h>

using namespace std;

const int N = 60;

class StringGame{
	public:
		bool bo[N],ch[N];
		int a[N][27],n;
		vector <int> getWinningStrings(vector <string> S){
			memset(a,0,sizeof(a));
			vector <int> ans;ans.clear();
			n = S.size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < S[i].size();j++)
					a[i][S[i][j]-'a']++;
			for (int i = 0;i < n;i++)
				if (check(i)) ans.push_back(i);
			return ans;
		}
		bool check(int p){
			memset(ch,1,sizeof(ch));
			memset(bo,1,sizeof(bo));
			while (1){	
				bool flag = 0,win = 0;//如果每一位都少则win = 0否则有可能赢 
				for (int i = 0;i < 26;i++) flag |= ch[i];
				if (!flag) return 0;
				 
				for (int i = 0;i < 26;i++)
					if (ch[i]){
						int opt = 3;
						for (int j = 0;j < n;j++)
							if (j != p && bo[j]){
								if (a[p][i] < a[j][i]) opt = 1;
								if (a[p][i] == a[j][i]) opt = min(opt,2);
							}
						if (opt == 3) return 1;
						if (opt == 1) continue;
						ch[i] = 0;win = 1;
						for (int j = 0;j < n;j++)
							if (j != p && bo[j])
								if (a[p][i] > a[j][i]) bo[j] = 0;
					}
				flag = 0;
				for (int i = 0;i < n;i++)
					if (i != p) flag |= bo[i];
					
				if (!flag) return 1;
				if (!win) return 0;
			}
		}
};
