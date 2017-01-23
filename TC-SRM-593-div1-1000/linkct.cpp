#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007, MAXN = 2000005;

class WolfDelaymasterHard{
public:
	int hd, nxt[MAXN], st[MAXN], ed[MAXN], linkSize, s[MAXN], f[MAXN], prev0, prev1;
	int countWords(int n, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd){
		int i, j, prv;
		memset(s, -1, sizeof(s));
		for(i = 0, j = w0; i < wlen; ++ i, j = (j * 1LL * wmul + wadd) % n)
			s[j + 1] = 0;
		for(i = 0, j = o0; i < olen; ++ i, j = (j * 1LL * omul + oadd) % n)
			s[j + 1] = 1;
		memset(f, 0, sizeof(f));
		f[0] = 1;
		for(i = 1, prev0 = prev1 = 0; i <= n; ++ i){
			if(s[i] == 0) prev0 = i;
			else if(s[i] == 1) prev1 = i;
			if(prev1 < i - 1){
				nxt[++ linkSize] = hd;
				st[hd = linkSize] = prev1 + 1;
				ed[linkSize] = i - 1;
			}
			f[i] = f[i - 1];
			if(i % 2 == 0){
				for(j = hd; j && ed[j] >= prev0; prv = j, j = nxt[j]){
					//[st[j], ed[j]] can take 0
					if(st[j] % 2 == 0) ++ st[j];
					if(ed[j] - (i - ed[j]) < st[j] - 1){
						if(j == hd) hd = nxt[hd];
						else nxt[prv] = nxt[j];
					}else{
						f[i] = f[i] + f[ed[j] - (i - ed[j])] - (max(st[j] - 1, prev0 - (i - prev0)) ? f[max(st[j] - 1, prev0 - (i - prev0)) - 1] : 0);
						if(f[i] >= MOD) f[i] -= MOD;
						else if(f[i] < 0) f[i] += MOD;
					}
				}
			}
			if(prev1 < i - 1 && hd == linkSize)
				hd = nxt[hd], -- linkSize;
			if(s[i] != 1 && i < n && s[i + 1] == 1){
				nxt[++ linkSize] = hd;
				st[hd = linkSize] = prev1 + 1;
				ed[linkSize] = i;
			}
		} return (f[n] - f[n - 1] + MOD) % MOD;
	}
};
