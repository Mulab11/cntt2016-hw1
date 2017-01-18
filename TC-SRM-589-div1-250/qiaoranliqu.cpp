#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>

using namespace std;

#define N 55

int i,fa[N],Max[N],A[N];
int get(int x) {return fa[x]==x?x:fa[x]=get(fa[x]); }
class GooseTattarrattatDiv1{
	  public:
	  	int getmin(string s)
	  	{
	  		 int len=s.length();
	  		 for (i=0;i<len;++i) A[s[i]-'a']++;
	  		 for (i=0;i<26;++i) fa[i]=i;
	  		 for (i=0;i<len;++i)
	  		   if (i<len-1-i) fa[get(s[i]-'a')]=get(s[len-i-1]-'a');
	  	     for (i=0;i<26;++i)
	  	       Max[get(i)]=max(Max[get(i)],A[i]);
	  	     for (i=0;i<26;++i) len-=Max[i];
	  		   return len;
	  	}
};
