#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const LL inf=0x3f3f3f3f3f3f3f3fll;
int n,q[100005],fst[55],nxt[200],to[200],tt,vis[55];
bool inq[55];
LL sb;
struct info{
	int x;LL y;//x:几个len y:剩下的长度 
	info(){}
	info(int x,LL y):x(x),y(y){}
	bool operator<(const info&rhs)const{return sb*x+y<sb*rhs.x+rhs.y;}
	bool operator>(const info&rhs)const{return sb*x+y>sb*rhs.x+rhs.y;}
	info operator+(const info&rhs)const{
		return info(x+rhs.x,y+rhs.y);
	}
}d[55],w[200];
void ad(int x,int y,info z){nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;w[tt]=z;}
int splay(LL len,vector<int>&s1,vector<int>&t1,vector<int>&l1,vector<int>&s2,vector<int>&t2,vector<int>&l2){
	memset(fst,0,sizeof fst);tt=0;sb=len;
	for(int i=0;i<s1.size();++i)ad(t1[i],s1[i],info(s1[i]>t1[i],-l1[i]));
	for(int i=0;i<s2.size();++i)ad(s2[i],t2[i],info(-(s2[i]>t2[i]),l2[i]));
	for(int i=0;i<n-1;++i)ad(i+1,i,info(0,-1));
	ad(0,n-1,info(1,-1));//根据不等式建图 
	for(int i=1;i<n;++i)d[i]=info(0,inf);
	d[0]=info(0,0);q[0]=0;
	for(int i=0;i<n;++i)vis[i]=inq[i]=0;vis[0]=inq[0]=1;//初始化 
	int l=0,r=0;
	while(l<=r){//spfa
		int x=q[l++];inq[x]=0;
		if(vis[x]>n){//找到负环 
			if(d[x].x>0)return 1; 
			return -1;//根据系数确定要上还是下 
		}
		for(int i=fst[x];i;i=nxt[i]){
			info tmp=d[x]+w[i];
			if(tmp<d[to[i]]){
				d[to[i]]=tmp;
				if(!inq[to[i]]){
					inq[to[i]]=1;
					q[++r]=to[i];
					++vis[to[i]];
				}
			}
		}
	}
	return 0;//没找到说明可以 
}

class YamanoteLine {
public:
	long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2) {
		::n=n;int fk;
		LL l,r,mid,lb=-1,ub=10000000000000ll;
		l=n;r=ub;
		while(l<=r){//二分答案求下界 
			mid=(l+r)>>1;
			fk=splay(mid,s1,t1,l1,s2,t2,l2);
			if(fk==-1)r=mid-1;
			else if(fk==1)l=mid+1;
			else r=(lb=mid)-1;
		}
		l=n;r=ub;
		while(l<=r){//二分答案求上界 
			mid=(l+r)>>1;
			fk=splay(mid,s1,t1,l1,s2,t2,l2);
			if(fk==-1)r=mid-1;
			else if(fk==1)l=mid+1;
			else l=(ub=mid)+1;
		}
		if(lb>=n&&ub>=10000000000000ll)return -1;//无穷多种 
		else if(lb==-1)return 0;//没有可行的解 
		else return ub-lb+1;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
