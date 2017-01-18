#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;

int i,s[55];

class LittleElephantAndString{
  public:
  int getNumber(string A,string B)
  {
  	   int la=A.length(),lb=B.length();
  	   for (i=0;i<la;++i) s[A[i]-'A']++;
  	   for (i=0;i<lb;++i) s[B[i]-'A']--;
	   for (i=0;i<26;++i) if (s[i]) return -1;
	   int j=la-1;
	   for (i=lb-1;i>=0;--i)
	   {
	        while (j>=0&&B[i]!=A[j]) --j;
	        if (j==-1) break; --j;
	   }
	   return i+1;
  }
};
