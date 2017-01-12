#include <bits/stdc++.h>

using namespace std;

int mp[13][13],n,m;

int work(int s,int s0){
	int zt=0,ty=s0,ret=0;//上一行状态，上一行取了什么，总次数 
	for(int i=0;i<m;++i){
		ret+=(s0>>i)&1;
		int t=mp[0][i];
		if((s&s0)==s0)t^=(s0>>i)&1;
		if(i)t^=(s0>>(i-1))&1;
		if(i+1<m)t^=(s0>>(i+1))&1;
		if(t)zt|=1<<i;
	}
	for(int i=1;i<n;++i)
	if((zt&s)==0){//1号操作 
		int nt=0;
		for(int j=0;j<m;++j){
			ret+=(zt>>j)&1;
			int t=mp[i][j];
			t^=(ty>>j)&1;
			if(j)t^=(zt>>(j-1))&1;
			if(j+1<m)t^=(zt>>(j+1))&1;
			if(t)nt|=1<<j;
		}
		ty=zt;
		zt=nt;
	}else if((zt&s)==zt){//2号操作 
		int nt=0;
		for(int j=0;j<m;++j){
			ret+=(zt>>j)&1;
			int t=mp[i][j];
			t^=(ty>>j)&1;
			t^=(zt>>j)&1;
			if(j)t^=(zt>>(j-1))&1;
			if(j+1<m)t^=(zt>>(j+1))&1;
			if(t)nt|=1<<j;
		}
		ty=zt;
		zt=nt;
	}else return 99999;
	if(zt==0)return ret;//最后一行要是0 
	return 99999;
}

class YetAnotherBoardGame {
public:
	int minimumMoves(vector <string> board) {
		n=board.size(),m=board[0].size();
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)mp[i][j]=board[i][j]=='W'?1:0;
		int ans=99999;
		for(int s=0;s<1<<m;++s){
			for(int s0=s;s0;s0=s&(s0-1))ans=min(ans,work(s,s0));//枚举子集 
			int rs=(1<<m)-1-s;
			for(int s0=rs;s0;s0=rs&(s0-1))ans=min(ans,work(s,s0));//枚举子集 
			ans=min(ans,work(s,0));
		}
		return ans==99999?-1:ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
