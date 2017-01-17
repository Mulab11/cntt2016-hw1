#include <bits/stdc++.h>

using namespace std;

const int A = 26;

class GooseTattarrattatDiv1{
	public:
		int n,fa[A],mx[A],sum[A],ans;
		int getmin(string S){//并查集维护哪些字母最终要相同。 
			n = S.size();
			for (int i = 0;i < 26;i++) fa[i] = i;
			for (int i = 0;i < n;i++) {mx[S[i]-'a']++;sum[S[i]-'a']++;}
			for (int i = 0;i < n/2;i++){
				int x = S[i]-'a',y = S[n-i-1]-'a';
				fa[x] = getfa(fa[x]);
				fa[y] = getfa(fa[y]);
				if (fa[x] != fa[y]){
					mx[fa[x]] = max(mx[fa[x]],mx[fa[y]]);
					sum[fa[x]] += sum[fa[y]];
					fa[fa[y]] = fa[x];
				}
			}
			for (int i = 0;i < 26;i++) {
				fa[i] = getfa(fa[i]);
				if (fa[i] == i)
					ans += sum[i]-mx[i];
			}
			return ans;
		}
		int getfa(int x){
			if (fa[x] == x) return x;
			fa[x] = getfa(fa[x]);
			return fa[x];
		}
};
