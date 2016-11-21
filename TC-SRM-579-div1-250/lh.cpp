#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

class point{
	public:
		point *nxt[26];
};

class UndoHistory{
	private:
		static const int maxn=55;
		point nod[maxn*maxn],*cnt,*root,*last;
		
		int insert(string &s){
			int ret1=2,ret2=10000000;// 复制，  继承 
			point *p=root;
			for (int i=0;i<s.length();++i){
				if (last==p) ret2=0;// 可以继承 
				if (!p->nxt[s[i]-'a']){
					++ret1;
					p->nxt[s[i]-'a']=cnt++;
				}
				p=p->nxt[s[i]-'a'];
				++ret2;
			}
			if (last==p) return 0;
			last=p;
			return min(ret1,ret2);
		}
		
	 public:
	 	int minPresses(vector <string> lines){
	 		last=root=nod;
	 		cnt=root+1;
	 		int ans=0;
			for (int i=0;i<lines.size();++i){
	 			ans++;// 回车键 
	 			ans+=insert(lines[i]);
//	 			printf("i=%d,ans=%d\n",i,ans);
	 		}
	 		return ans;
	 	}
};
