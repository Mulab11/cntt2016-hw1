#include <bits/stdc++.h>
using namespace std;

class LittleElephantAndString{
public:
	int cnt[26];
	int getNumber(string a, string b){
		int i, j, n = a.length();
		memset(cnt, 0, sizeof(cnt));
		for(i = 0; i < n; ++ i) ++ cnt[a[i] - 'A'], -- cnt[b[i] - 'A'];
		for(i = 0; i < 26; ++ i) if(cnt[i]) return -1;
		for(i = j = n - 1; i >= 0 && j >= 0; -- i, -- j){
			while(j && a[j] != b[i]) -- j;
			if(a[j] != b[i]) break;
		} return i + 1;
	}
};
