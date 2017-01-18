	#include<cstdio>
	#include<algorithm>
	#include<cstring>
	using namespace std;
	int i,j,m,n,p,k,st,ed;
	char c[1001];
	int mp[102][102],mp1[102][102],dis[1001],que[1001];
	inline int bfs()
	 { int i,p,l,r;
	   memset(dis,-1,sizeof(dis));
	    l=r=1;
	    dis[st]=0;
	   que[1]=st;
	   while (l<=r)
	    { p=que[l];
	        for (i=0;i<=n+1;i++)
	         if (mp[p][i]>0)
	        if (dis[i]==-1)
	         { 
	           que[++r]=i;
	           dis[i]=dis[p]+1;
	           }
	      l++;
	}
	 if (dis[ed]==-1) return 0;
	 return 1;
	}
	int dfs(int num,int flow)
	 {  int i,a,nowans=0;
	   if (num==ed) return flow;
	     //for (i=fox[num];i&&flow;i=s[i].before)
	      for (i=0;i<=n+1&&flow;i++)
	       if (mp[num][i]>0&&dis[i]==dis[num]+1)
	        if(a=dfs(i,min(mp[num][i],flow)))
	         { mp[num][i]-=a;
	           mp[i][num]+=a;
	           flow-=a;nowans+=a;
	           }if (!nowans) dis[num]=(int)1e8;
	   return nowans;
	}       
	int dinic()
	  { int j;
	   int ans=0;
	    while (bfs())
	    { j=dfs(st,(int)1e8);  while (j) ans+=j,j=dfs(st,(int)1e8); }
	 return ans;
	}  
class OldBridges{
	public:
	string isPossible(vector <string> c, int a1, int a2, int an, int b1, int b2, int bn)
	{ 
	    n=c.size();
		memset(mp,0,sizeof(mp));
	    memset(mp1,0,sizeof(mp1));
	  for (i=0;i<n;i++)
	  { 
	    for (j=0;j<n;j++)
	      if (c[i][j]=='X') mp[i][j]=mp1[i][j]=0;
	      else if (c[i][j]=='O') mp[i][j]=mp1[i][j]=2;
	      else mp[i][j]=mp1[i][j]=10000000;
	 }
	 st=n;
	 ed=n+1;
	 mp[st][a1]=an*2;
	 mp[st][b1]=bn*2;
	 mp[a2][ed]=an*2;
	 mp[b2][ed]=bn*2;
	if (dinic()<2*(an+bn)) return "No";
	 swap(b1,b2);
	 memset(mp,0,sizeof(mp));
	 for (i=0;i<n;i++)
	   for (j=0;j<n;j++) mp[i][j]=mp1[i][j];
	 mp[st][a1]=an*2;
	 mp[st][b1]=bn*2;
	 mp[a2][ed]=an*2;
	 mp[b2][ed]=bn*2;
	 if (dinic()<2*(an+bn)) return "No"; 
	 return "Yes";
	}
};
