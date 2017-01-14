#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
const int inf=1000;
class MagicalHats
{
	public:
	int n,m,cn,hn,gn,p3[15];
	int cx[15],cy[15],hx[15],hy[15];
	char s[15][15];
	int f[2000000];
	
	int setbit(int st,int pos,int p)
	{return st/p3[pos+1]*p3[pos+1]+p*p3[pos]+st%p3[pos];}
	int getbit(int st,int pos)
	{return st/p3[pos]%3;}
	
	int dp(int st,int c,int h)
	{
		//the state is st now.
		//we can record some extra information to make it more convenience.
		if(hn-h<cn-c)return -inf;//There are not enough hats to cover coins.
		if(h==hn)
		{
			//if(c<cn)return -inf;
			for(int i=0;i<n;i++)
				if(cx[i]&1)return -inf;
			for(int i=0;i<m;i++)
				if(cy[i]&1)return -inf;
			return 0;//It satisfies the limit.
		}
		int &res=f[st];
		if(res!=-1)return res;
		res=-inf;
		
		for(int i=0;i<hn;i++)//choose an unopened hat.
		{
			int x=hx[i],y=hy[i],d=getbit(st,i),t,r1,r2;
			if(d==0)
			{
				//There is a coin under the hat.
				if(c<cn)
				{
					cx[x]+=2,cy[y]+=2;
					r1=(h<gn)+dp(setbit(st,i,1),c+1,h+1);
					cx[x]-=2,cy[y]-=2;
				}
				else r1=-inf;
				//There isn't a coin under the hat.
				cx[x]++,cy[y]++;
				r2=dp(setbit(st,i,2),c,h+1);
				cx[x]--,cy[y]--;
				if(r1<0)res=max(res,r2);
				else if(r2<0)res=max(res,r1);
				else res=max(res,min(r1,r2));//B can make the choice.
			}
		}
		return res;
	}
	
	int findMaximumReward(vector<string> board,vector<int> coins,int numGuesses)
	{
		n=board.size();
		m=board[0].size();
		gn=numGuesses;cn=coins.size();hn=0;
		//Find all hats' positions.
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				s[i][j]=board[i][j];
				if(s[i][j]=='H')
					hx[hn]=i,hy[hn]=j,hn++;
			}
		for(int i=p3[0]=1;i<=14;i++)
			p3[i]=p3[i-1]*3;
		memset(cx,0,sizeof(cx));
		memset(cy,0,sizeof(cy));
		memset(f,-1,sizeof(f));
		int res=dp(0,0,0);
		if(res<0)return -1;
		sort(coins.begin(),coins.end());
		int sum=0;
		//Of course B will give A the least valuable coins.
		for(int i=0;i<coins.size()&&i<res;i++)sum+=coins[i];
		return sum;
	}
	
};

