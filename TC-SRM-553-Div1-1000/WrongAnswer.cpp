// FST:无解时check不一定有单调性（负权环系数正负不确定），二分时误判成有解
#include <vector>
#include <cstring>
using namespace std;
class YamanoteLine{
public:
	int N;
	vector<int> S1,T1,L1,S2,T2,L2;
	struct edge{int to,k;long long len;edge*next;}E[210],*ne,*first[60];
	void link(int a,int b,long long l,int k){*ne=(edge){b,k,l,first[a]};first[a]=ne++;}
	int Q[2510],pos[60],S[60],fr[2510],K[2510];
	long long D[2510];
	bool vis[60];
	int check(long long M){ // 判断环长能否等于M，M太小返回-1，太大返回1，否则返回0 
		// 差分约束建图 
		ne=E;memset(first,0,sizeof(first));
		link(0,N,M,1);link(N,0,-M,-1); // 环长等于M 
		for(int i=0;i<N;i++)link(i+1,i,-1,0); // 相邻距离不小于1 
		for(int i=0;i<S1.size();i++)link(T1[i],S1[i],S1[i]<T1[i]?-L1[i]:M-L1[i],S1[i]<T1[i]?0:1); // S1[i]到T1[i]距离至少L1[i] 
		for(int i=0;i<S2.size();i++)link(S2[i],T2[i],S2[i]<T2[i]?L2[i]:L2[i]-M,S2[i]<T2[i]?0:-1); // S2[i]到T2[i]距离至多L2[i]
		// 判断是否存在负权环 
		memset(D,63,sizeof(D));
		memset(vis,0,sizeof(vis));
		int head=*Q=*D=*S=0,tail=1;
		for(int x;head<tail;head++){
			vis[x=Q[head]]=0;
			for(edge*e=first[x];e;e=e->next)if(D[x]+e->len<D[e->to]){
				D[e->to]=D[x]+e->len,S[e->to]=S[x]+1;
				if(!vis[e->to])pos[e->to]=tail,vis[Q[tail++]=e->to]=1;
				fr[pos[e->to]]=head,K[pos[e->to]]=e->k;
				if(S[e->to]>N){ // 找到负权环，判断M是太小还是太大 
					int top=1,sum=0;
					memset(vis,0,sizeof(vis));vis[Q[*S=pos[e->to]]]=1;
					for(int i=*S;;i=fr[i]){
						S[top++]=fr[i],sum+=K[i];
						if(vis[Q[fr[i]]]){
							int old_sum=sum;
							do vis[Q[S[--top]]]=0,sum-=K[S[top-1]];
							while(Q[S[top-1]]!=Q[fr[i]]);
							return sum>old_sum?1:-1;
						}
						vis[Q[fr[i]]]=1;
					}
				}
			}
		}
		return 0; // 不存在负权环 
	}
	long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2){
		N=n;S1=s1;T1=t1;L1=l1;S2=s2;T2=t2;L2=l2;
		int tmp=check(1ll<<40);
		if(!tmp)return -1;
		if(tmp==-1||check(n-1)==1)return 0;
		long long left=n-1,right=1ll<<40,mid,ans=0;
		while(right-left>1)check(mid=left+right>>1)>0?right=mid:left=mid;
		if(check(left)==-1)return 0;
		ans=right;left=n-1;
		while(right-left>1)check(mid=left+right>>1)<0?left=mid:right=mid;
		return ans-right;
	}
};
