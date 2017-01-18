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

#define N 305
#define M 15
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans=Mo,fa[N],one[N],zer[N];
const int inf=(int)1e9;

char c[N],s[N];

void check(int S)
{
	  int i;
	  for (i=1;i<=n;++i) 
	  {
	    s[i]=c[i],fa[i]=i;
	    one[i]=zer[i]=0;
	    if (s[i]=='0') zer[i]++;
	    else one[i]++;
	  }
	  for (i=1;i<=n-m;++i) 
	  {
	        fa[i]=m+i; 
			zer[m+i]+=zer[i];
			one[m+i]+=one[i];
	  }
	  for (i=1;i<=n;++i) if (fa[i]==i) S+=min(zer[i],one[i]);
	  if (S==1)
	   S=1;
	  ans=min(ans,S);
}
void dfs(int x,int y)
{
	 if (x>n/m) check(y);
	 else 
	 {
	 	   dfs(x+1,y);
	 	   int i;
	 	   for (i=1;i<=x*m;++i) c[i]=(char)(((c[i]-'0')^1)+'0');
	 	   dfs(x+1,y+1);
	 	   for (i=1;i<=x*m;++i) c[i]=(char)(((c[i]-'0')^1)+'0');
	}
}
int f[N][1<<M]; 
void up(int &x,int y) { x=min(x,y); }
void workb()
{
         int Maxn=(1<<m)-1;
	     memset(f,60,sizeof(f));
         f[0][0]=0;
		 for (i=1;i<=n;++i)
		 {
		   for (j=0;j<=Maxn;++j)
		     if (f[i-1][j]<inf)
			 {
			 	   if (i<=m)
			 	   {
			 	   	    up(f[i][(j>>1)+(c[i]-'0')*(1<<(m-1))],f[i-1][j]);
			 	   	    up(f[i][(j>>1)+abs(c[i]-'1')*(1<<(m-1))],f[i-1][j]+1);
			 	   }
			 	   else
			 	   {
			 	   	         k=j&1;
						     if (k==c[i]-'0') up(f[i][(j>>1)+k*(1<<(m-1))],f[i-1][j]);
							 else up(f[i][(j>>1)+k*(1<<(m-1))],f[i-1][j]+1);
				   }
			 }
		   if (i%m==0)
		   for (j=0;j<=Maxn;++j) f[i][j]=min(f[i][j],f[i][j^Maxn]+1); 
		 } 
		 for(i=0;i<=Maxn;++i) ans=min(ans,f[n][i]); 
}
class FlippingBitsDiv1{
	public:
		int getmin(vector<string>s,int mc)
		{
			 m=mc;
			 for (i=0;i<s.size();++i)
			  for (j=0;j<s[i].length();++j)
			    c[++n]=s[i][j];
			 if (n/m<=20) dfs(1,0);
			 else workb();
			 return ans;
		}
}A;
int main()
{
	  vector<string> v;
	  v.push_back("00111000");
	  printf("%d\n",A.getmin(v,1));
}
