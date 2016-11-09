#include <bits/stdc++.h>
#define MEM(x,y) memset(x, y, sizeof(x))
/*
	lft[c] = count of character c left (in the answer)
	cnt[pos][c] = count of c after pos (in the input string)
	nxt[pos][c] = the next position that c appears after pos (in the input string)
*/ 
int nxt[100][255], cnt[100][255], lft[255], len;
class FoxAndHandle {
	public:
	string lexSmallestName(std::string S) {
		MEM(nxt, 0); MEM(cnt, 0); MEM(lft, 0);
		len = S.length(); S = ' ' + S;
		for (int i = 1; i <= len; ++i) ++lft[S[i]];
		for (char i = 'a'; i <= 'z'; ++i) lft[i] /= 2;
		for (char i = 'a'; i <= 'z'; ++i) nxt[len][i] = len + 1;
		for (int i = len; i >= 0; --i)
			for (char c = 'a'; c <= 'z'; c++){
				if (i < len) nxt[i][c] = S[i + 1] == c ? i + 1 : nxt[i + 1][c];
				cnt[i][c] = cnt[i + 1][c] + (S[i] == c);
			}
		string ret(""); char c = 233; int pos = 0;
		for (int s = 1; s <= len / 2; ++s){ // for each character (in the answer)
			for (char j = 'a'; j <= 'z'; ++j) if (lft[j]){ // if we take j
				bool ok = 1; int p = nxt[pos][j]; 
				for (char k = 'a'; k <= 'z'; ++k) 
					if (cnt[p][k] < lft[k]) {ok = 0; break;} // not enough k, shakalaka boom
				if (ok) {c = j; break;} // we take c as the next one
			}
			lft[c]--; pos = nxt[pos][c]; ret += c;
		}
		return ret;
	}
};
