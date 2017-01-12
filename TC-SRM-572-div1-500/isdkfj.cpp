#include <bits/stdc++.h>

using namespace std;


class EllysBulls {
public:
	string getNumber(vector <string> guesses, vector <int> bulls) {
		int m=guesses.size(),n=guesses[0].size(),n1=n/2,n2=n-n1;//折半 
		int pw=1,w[11];
		for(int i=1;i<=n1;++i)pw*=10;
		map<vector<int>,int>mp,sz;
		for(int i=0;i<pw;++i){
			int x=i;
			for(int j=0;j<n1;++j)w[j]=x%10,x/=10;
			vector<int>tmp;
			bool flag=1;
			for(int j=0;j<m;++j){
				int cnt=0;
				for(int k=0;k<n1;++k)if(w[k]+'0'==guesses[j][n1-k-1])++cnt;
				if(bulls[j]<cnt){flag=0;break;}
				tmp.push_back(bulls[j]-cnt);//差多少存起来 
			}
			if(!flag)continue;
			++mp[tmp];//出现次数 
			sz[tmp]=i;//对应数字 
		}
		pw=1;
		for(int i=1;i<=n2;++i)pw*=10;
		int res=0,ans=0;
		for(int i=0;i<pw;++i){
			int x=i;
			for(int j=0;j<n2;++j)w[j]=x%10,x/=10;
			vector<int>tmp;
			for(int j=0;j<m;++j){
				int cnt=0;
				for(int k=0;k<n2;++k)if(w[k]+'0'==guesses[j][n-k-1])++cnt;
				tmp.push_back(cnt);//后半部分有多少 
			}
			if(mp.find(tmp)==mp.end())continue;
			res+=mp[tmp];
			ans=sz[tmp]*pw+i;
			if(res>1)return "Ambiguity";//多于一种 
		}
		if(!res)return "Liar";//没有 
		string ret;
		for(int i=0;i<n;++i)ret=char(ans%10+'0')+ret,ans/=10;
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
