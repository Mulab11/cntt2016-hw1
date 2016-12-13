#include<bits/stdc++.h>
using namespace std;
int i,v[128],k,S;
class LittleElephantAndBalls
{
	public:
		int getNumber(string s)
		{
			for(i=0;i<s.size();i++)S+=k,v[s[i]]++,k+=(v[s[i]]<3);//贪心			
			return S; 
		}
};
