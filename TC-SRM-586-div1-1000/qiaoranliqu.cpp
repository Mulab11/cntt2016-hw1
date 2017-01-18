#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define N 55

using namespace std;
const int inf=(int)1e9;
int f[N][27][27],i,j,k,pi,pj,pk,L[N],n,sumt;
void up(int &x,int y) { x=min(x,y); } 
class StringWeight{
	public:
		int getMinimum(vector<int> v)
		{
			n=v.size();
			for (i=1;i<=n;++i) L[i]=v[i-1];
			memset(f,60,sizeof(f));
			f[0][0][0]=0;
			for (i=1;i<=n;++i)
			{
			  int Need=min(L[i],26);
			  for (j=0;j<27;++j)
			    for (k=0;k<=j;++k)
			      if (f[i-1][j][k]<inf)
			      {
			      	int now=f[i-1][j][k];
			        for (pi=0;pi<=j-k;++pi)
			          for (pj=0;pj+pi<=j-k&&pi+pj<=Need;++pj)
			            if (Need-pi-pj<=26-j) 
					      for (pk=0;pk<=26-j;++pk)
						{
						      int pl=Need-pi-pj-pk,rest=L[i]-pi-pj-pk-pl;
							  if (pl<0) break;
							  int val=now+(sumt+1+sumt+pi)*pi/2;
							  val-=(sumt+L[i]+sumt+L[i]-pl+1)*pl/2;
							  if (!pj) val+=L[i]-Need;
							  if (j+pk+pl>26||k+pi+pk>26)
							    puts("cao"); 
							  up(f[i][j+pk+pl][k+pi+pk],val);
					    }
				  }
			  sumt+=L[i];
			}
			int ans=inf;
			for (i=0;i<=26;++i) 
			   up(ans,f[n][i][i]);
			return ans;
	    }
}A;
int main()
{
      vector<int>v;
      v.push_back(26); v.push_back(2); v.push_back(2); 
	  //for (i=1;i<=27;++i) v.push_back(1);
	  printf("%d\n",A.getMinimum(v));
}
