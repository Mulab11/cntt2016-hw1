#include<bits/stdc++.h>
using namespace std;
int x[128],i,j;
struct LittleElephantAndString
{
	public:
		int getNumber(string A,string B)
		{
			for(i=j=A.size()-1;~i;i--)x[A[i]]++,x[B[i]]--;
			for(i=j;~i;i--)if(x[A[i]])return -1;
			for(i=j;~i;i--)
			{
				while(~j&&A[j]!=B[i])j--;
				if(j--<0)break;
			}
			return i+1;
		}
};
