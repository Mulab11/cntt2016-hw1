#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f,dx[]={0,-1,0,1},dy[]={1,0,-1,0};
int s,t,q[3005],d[3005],a[3005],p[3005],fst[3005],to[100005],nxt[100005],w[100005],c[100005],tt,n,m;
bool inq[3005];
int gs(int x,int y){//点的标号 
	return x*m+y;
}
void ad(int x,int y,int z,int _c){
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;w[tt]=z;c[tt]=_c;
	nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;w[tt]=0;c[tt]=-_c;
}
bool spfa(int&flow,int&cost){//费用流 
	int l=0,r=1;q[0]=s;
	memset(d,0x3f,sizeof d);
	d[s]=0;inq[s]=1;a[s]=inf;
	while(l!=r){
		int x=q[l++];inq[x]=0;
		if(l==3005)l=0;
		for(int i=fst[x];i;i=nxt[i])
		if(w[i]&&d[to[i]]>d[x]+c[i]){
			d[to[i]]=d[x]+c[i];
			a[to[i]]=min(a[x],w[i]);
			p[to[i]]=i;
			if(!inq[to[i]]){
				q[r++]=to[i];
				inq[to[i]]=1;
				if(r==3005)r=0;
			}
		}
	}
	if(d[t]==inf)return 0;
	flow+=a[t];
	cost+=a[t]*d[t];
	for(int i=t;i!=s;i=to[p[i]^1]){
		w[p[i]]-=a[t];
		w[p[i]^1]+=a[t];
	}
	return 1;
}

class CurvyonRails {
public:
	int getmin(vector <string> field) {
		tt=1;
		n=field.size(),m=field[0].size();
		s=n*m*3; t=s+1;
		int sum=0,ch=0;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)
			if(field[i][j]!='w'){
				if((i+j)&1){//黑 
					sum+=2;
					++ch;
					ad(gs(i,j),t,2,0);
					ad(gs(i,j)+n*m,gs(i,j),1,0);
					ad(gs(i,j)+n*m*2,gs(i,j),1,0);
					ad(gs(i,j)+n*m,gs(i,j),1,field[i][j]=='C');
					ad(gs(i,j)+n*m*2,gs(i,j),1,field[i][j]=='C');//建边 
				}else {//白 
					--ch;
					ad(s,gs(i,j),2,0);
					ad(gs(i,j),gs(i,j)+n*m,1,0);
					ad(gs(i,j),gs(i,j)+n*m*2,1,0);
					ad(gs(i,j),gs(i,j)+n*m,1,field[i][j]=='C');
					ad(gs(i,j),gs(i,j)+n*m*2,1,field[i][j]=='C');//建边 
					for(int k=0,x,y;k<4;++k){//往四个方向连边 
						x=i+dx[k];y=j+dy[k];
						if(0<=x&&x<n&&0<=y&&y<m&&field[x][y]!='w'){
							if(x==i)ad(gs(i,j)+n*m,gs(x,y)+n*m,1,0);
							else ad(gs(i,j)+n*m*2,gs(x,y)+n*m*2,1,0);
						}
					}
				}
			}
		if(ch)return -1;//点的个数不对 
		int flow=0,cost=0;
		while(spfa(flow,cost));//跑 
		if(flow!=sum)return -1;//没满流 
		return cost;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
