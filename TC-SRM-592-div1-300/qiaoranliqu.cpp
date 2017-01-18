#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>

#define N 55

using namespace std;
int i,j,m,n,p,k,A[10005],B[100005],ans;
class LittleElephantAndBalls{
   public:
    int getNumber(string s)
    {
    	  n=s.length(); int L=0,R=0;
          for (i=0;i<n;++i)
          {
          	     ans+=L+R;
          	     if (!A[s[i]]) ++L,A[s[i]]=1;
          	     else if (!B[s[i]]) ++R,B[s[i]]=1;
          }
          return ans;
    }
};

