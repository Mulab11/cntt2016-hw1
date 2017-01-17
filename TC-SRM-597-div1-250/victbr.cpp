#include <bits/stdc++.h>

using namespace std;

class LittleElephantAndString{
	public:
		int n,cnt[26];
		int getNumber(string A, string B){
			n = A.size();
			for (int i = 0;i < n;i++)
				cnt[A[i]-'A']++;
			for (int i = 0;i < n;i++)
				cnt[B[i]-'A']--;
			for (int i = 0;i < 26;i++) 
				if (cnt[i] != 0) return -1;
			int u = n-1,tot = 0;
			for (int i = n-1;i >= 0;i--){
				while (A[u] != B[i]){
					u--;
					if (u < 0) break;
				}
				if (u >= 0) tot++;
				u--;
				if (u < 0) break;
			}
			return n-tot;
		}
};
