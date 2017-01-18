#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,UM,DM,LM,RM,now=0,nowx,nowy;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
map<pair<int,int>,int>mp;
class RotatingBot{
	public:
	int minArea(vector <int> moves)
	{
			mp[mk(0,0)]=1;
			nowx=0; nowy=0;
			for (i=0;i<(int)moves.size()-1;++i) //计算前面的路径是否合法 
			{
					int steps=moves[i];
					for (j=0;j<steps;++j)
					{
						  nowx+=dx[now]; nowy+=dy[now];
						  if (mp[mk(nowx,nowy)]) return -1;
						  mp[mk(nowx,nowy)]=1;
					}
					if (now==0)
					{
							if (!mp[mk(nowx+1,nowy)])
							{
								  if (RM&&RM!=nowx) return -1;
								  RM=nowx;
							}
					}
					if (now==1)
					{
							if (!mp[mk(nowx,nowy+1)])
							{
								  if (UM&&UM!=nowy) return -1;
								  UM=nowy;
							}
					}
					if (now==2)
					{
							if (!mp[mk(nowx-1,nowy)])
							{
								  if (LM&&LM!=nowx) return -1;
								  LM=nowx;
							}
					}
					if (now==3)
					{
							if (!mp[mk(nowx,nowy-1)])
							{
								  if (DM&&DM!=nowy) return -1;
								  DM=nowy;
							}
					}
					(now+=1)%=4;
			}
					int steps=moves[i];//最后一步稍有些特殊,可以不贴在墙上. 
					for (j=0;j<steps;++j)
					{
						  nowx+=dx[now]; nowy+=dy[now];
						  if (mp[mk(nowx,nowy)]) return -1;
						  mp[mk(nowx,nowy)]=1;
					}
					if (now==0)
					{
							if (!mp[mk(nowx+1,nowy)])
							{
								  if (RM&&RM<nowx) return -1;
								  RM=max(RM,nowx);
							}
					}
					if (now==1)
					{
							if (!mp[mk(nowx,nowy+1)])
							{
								  if (UM&&UM<nowy) return -1;
								  UM=max(UM,nowy);
							}
					}
					if (now==2)
					{
							if (!mp[mk(nowx-1,nowy)])
							{
								  if (LM&&LM>nowx) return -1;
								  LM=min(LM,nowx);
							}
					}
					if (now==3)
					{
							if (!mp[mk(nowx,nowy-1)])
							{
								  if (DM&&DM>nowy) return -1;
								  DM=min(DM,nowy);
							}
					}
					(now+=1)%=4;
			if (DM>0||LM>0||RM<0||UM<0) return -1;
			return (RM-LM+1)*(UM-DM+1);
	}
};
