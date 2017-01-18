#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<string> 

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,cnt;
class FoxAndChess{
	public:
		string ableToMove(string a,string b)
		{
			 n=a.length();
			 for (i=0;i<n;++i)
			 {
			   if (a[i]!='.') ++cnt;
			   if (b[i]!='.') cnt--;
		     }
		     if (cnt) return "Impossible";
		     j=-1;
		     for (i=0;i<n;++i)
		       if (a[i]!='.')
		       {
		       	    for (++j;j<n;++j)
					     if (b[j]!='.') break; 
					if (a[i]!=b[j]) return "Impossible";
					if (a[i]=='L'&&i<j) return "Impossible";
					if (a[i]=='R'&&i>j) return "Impossible";
			   }
			   return "Possible";
		}
};

