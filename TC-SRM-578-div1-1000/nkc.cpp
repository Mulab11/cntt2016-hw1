#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#define N 110
using namespace std;
struct mcf
{
	int s,e;
	int to[N*N],nxt[N*N],w[N*N],c[N*N],pre[N],ti[N],cnt,T,Ti;
	void reset()
	{
		T++;cnt=1;
	}
	void AE(int ff,int tt,int ww,int cc)
	{
	    cnt++;
	    to[cnt]=tt;
	    if(ti[ff]==T) nxt[cnt]=pre[ff];
	    else nxt[cnt]=0;
	    w[cnt]=ww;
	    c[cnt]=cc;
	    pre[ff]=cnt;
	    ti[ff]=T;
	}
	void ae(int ff,int tt,int ww,int cc)
	{
		AE(ff,tt,ww,cc);
		AE(tt,ff,0,-cc);
	}
	int q[20*N],t;
	int td[N],d[N],bef[N];
	bool zai[N];
	bool spfa()
	{
	    int h=1,t=1;
	    d[s]=0;q[1]=s;
	    Ti++;
	    td[s]=Ti;
	    int i,j,x;
	    while(h<=t)
	    
	{
	        x=q[h];h++;zai[x]=false;
	        for(i=pre[x];i;i=nxt[i])
	        if(w[i])
	        
	{
	            j=to[i];
	            if(td[j]!=Ti||d[j]<d[x]+c[i])
	            
	{
	            	td[j]=Ti;
	                d[j]=d[x]+c[i];
	                bef[j]=i;
	                if(!zai[j])
	                
	{
	                    t++;q[t]=j;
	                    zai[j]=true;
	                }
	            }
	        }
	    }
	 //   cout<<td[e];
	    if(td[e]!=Ti) return false;
	    return true;
	}
	int doit()
	{
	    int minn=1e9,x=e,ans=0,i;
	    while(x!=s)
	    
	{
	        i=bef[x];
	        minn=min(minn,w[i]);
	        x=to[i^1];
	    }
	    x=e;
	    while(x!=s)
	    
	{
	        i=bef[x];
	        ans+=c[i]*minn;
	        w[i]-=minn;
	        w[i^1]+=minn;
	        x=to[i^1];
	    }
	    return ans;
	}
	int fyl()
	{
		int ret=0;
		while(spfa())
		ret+=doit();
	//	cout<<"ret"<<ret<<endl;
		return ret;
	}
}P;
struct DeerInZooDivOne
{
	int n;
	int to[N],nxt[N],pre[N],num[N],cnt,cut;
	int ans;
	void ae(int ff,int tt,int nn)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
		num[cnt]=nn;
	}
	bool can[N];
	int f[N][N];
	void prego(int x,int fa)
	{
		can[x]=true;
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa||num[i]==cut) continue;
			prego(j,x);
		}
	}
	void dp(int x,int y,int fx,int fy)
	{
		int i,j,ii,jj;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fx||num[i]==cut) continue;
			for(ii=pre[y];ii;ii=nxt[ii])
			{
				jj=to[ii];
				if(jj==fy||num[ii]==cut) continue;
				dp(j,jj,x,y);
			}
		}
		P.reset();
		P.s=0;P.e=2*n+1;
		set<int>S;
		set<int>::iterator it;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fx||num[i]==cut) continue;
			P.ae(P.s,j,1,0);
			for(ii=pre[y];ii;ii=nxt[ii])
			{
				jj=to[ii];
				if(jj==fy||num[ii]==cut) continue;
				P.ae(j,n+jj,1,f[j][jj]);
				S.insert(n+jj);
			}
		}
		for(it=S.begin();it!=S.end();it++)
		P.ae((*it),P.e,1,0);
	//	cout<<x<<' '<<y<<' '<<'!'<<endl;
		f[x][y]=P.fyl()+1;
	}
	void devide(int x,int fa)
	{
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa) continue;
			cut=num[i];
			memset(can,0,sizeof(can));
			prego(j,0);
			for(j=1;j<=n;j++)
			if(can[j])
			{
			//	cout<<x<<' '<<j<<endl;
				memset(f,0,sizeof(f));
				dp(x,j,0,0);
				ans=max(f[x][j],ans);
			}
		}
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa) continue;
			devide(j,x);
		}
	}
	int getmax(vector <int> a, vector <int> b)
	{
		n=a.size();
		cnt=1;
		int i,j,x,y;
		for(i=0;i<n;i++)
		ae(a[i]+1,b[i]+1,i+1),ae(b[i]+1,a[i]+1,i+1);
		n++;
		devide(1,0);
		return ans;
	}
};
/*int main()
{
	DeerInZooDivOne PP;
	vector<int>V1,V2;
	V1.push_back(0);V1.push_back(1);V1.push_back(2);
	V2.push_back(1);V2.push_back(2);V2.push_back(3);
	cout<<PP.getmax(V1,V2);
}*/