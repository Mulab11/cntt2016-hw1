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
int i,j,m,n,p,k,Q[N],ans;
struct Node{int time,note;}A[N];
inline bool cmp(Node a,Node b)
{
	 return a.note<b.note;
}
class GUMIAndSongsDiv1{
	  public:
	  	int maxSongs(vector<int> AA,vector<int> BB,int T)
	  	{
	  		   n=AA.size();
	  		   for (i=1;i<=n;++i) A[i]=(Node){AA[i-1],BB[i-1]};
	  		   sort(A+1,A+n+1,cmp);
               for (i=1;i<=n;++i)
                 for (j=i;j<=n;++j)
				   if (A[j].note-A[i].note<=T)
				   {
				   	    int now=T-(A[j].note-A[i].note);
				   	    for (k=i;k<=j;++k) Q[k]=A[k].time;
				   	    sort(Q+i,Q+j+1);
				   	    for (k=i;k<=j;++k)
				   	    {
				   	    	   if (now<Q[k]) break;
				   	    	   now-=Q[k];
				   	    }
				   	    ans=max(ans,k-i);
				   }
			    return ans;
	  	}
};
