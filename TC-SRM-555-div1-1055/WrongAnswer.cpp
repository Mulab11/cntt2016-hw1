#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class MapGuessing{
public:
	int n,m;
	long long S[40];
	long long dfs(int i,long long s){
		long long cnt=1ll<<__builtin_popcountll(s);
		while(++i<m)cnt-=dfs(i,s&S[i]);
		return cnt;
	}
	long long T[36<<16];
	int make(int l,int r,int L){
		if(r-l==1){
			long long s=S[l];int R=L+(1<<__builtin_popcountll(s));
			for(int i=R-1;i>=L;i--)T[i]=s,s=(s-1)&S[l];
			return R;
		}
		int M=make(l,l+r>>1,L),R=make(l+r>>1,r,M);
		std::inplace_merge(T+L,T+M,T+R);
		R=std::unique(T+L,T+R)-T;
		return R;
	}
	long long countPatterns(string goal, vector<string> code){
		int l=0,r=0,p=0,pos[555],ch[555],opcnt=0;
		for(int i=0;i<code.size();i++)
			for(int j=0,c;j<code[i].length();j++)
				((c=code[i][j])=='<'?--p:c=='>'?++p:(ch[opcnt]=code[i][j],pos[opcnt++]=p))<l?l=p:p>r?r=p:1;
		n=goal.length();m=0;
		for(int i=0;i<n;i++)if(i+l>=0&&i+r<n){
			long long V=0,W=0;S[m]=0;
			for(int j=0;j<opcnt;j++){
				V|=1ll<<i+pos[j];
				if(goal[i+pos[j]]==ch[j])W&=~(1ll<<i+pos[j]);
				else W|=1ll<<i+pos[j];
				if(!W)S[m]=V;
			}
			m++;
		}
		if(m<=20){
			long long ans=0;
			for(int i=0;i<m;i++)ans+=dfs(i,S[i]);
			return ans;
		}
		return make(0,m,0);
	}
};
