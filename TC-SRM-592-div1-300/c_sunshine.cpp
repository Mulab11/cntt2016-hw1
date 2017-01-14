#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class LittleElephantAndBalls
{
	public:
	int c[256];
	int getNumber(string S)
	{
		int ans=0,t=0;
		//We can imagine two sets there. One is on left and another is on right.
		//We can add each color first in Left ,second in Right ,and then in middle. 
		for(int i=0;i<S.size();i++)
		{
			ans+=t;
			if(++c[S[i]]<=2)
				t++;
		}
		return ans;
	}
};

