#include <bits/stdc++.h>

using namespace std;


class FoxAndHandle {
public:
	string lexSmallestName(string S) {
		int n=S.size(),cnt[55][26],nxt[55][26],res[26];
		memset(cnt,0,sizeof cnt);
		memset(nxt,-1,sizeof nxt);
		for(int i=n-1;i>=0;--i){
			for(int j=0;j<26;++j)cnt[i][j]=cnt[i+1][j],nxt[i][j]=nxt[i+1][j];
			++cnt[i][S[i]-97];
			nxt[i][S[i]-97]=i;//统计下一个字母位置和字母出现次数 
		}
		for(int i=0;i<26;++i)res[i]=cnt[0][i]/2;
		string ret;int now=0;//当前位置 
		for(int i=0;i<n/2;++i){
			for(int j=0;j<26;++j)if(res[j]){//从小到大贪心 
				int x=nxt[now][j];
				if(x==-1)continue;
				bool flag=1;
				for(int k=0;k<26;++k)if(cnt[x][k]<res[k]){flag=0;break;}//判断是否还能凑出来 
				if(flag){
					ret+=j+'a';
					--res[j];
					now=x+1;
					break;
				}
			}
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
