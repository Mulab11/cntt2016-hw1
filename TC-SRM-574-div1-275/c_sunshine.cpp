#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<sstream>
using namespace std;

class TheNumberGame
{
	public:
	string to_str(int x)
	{
		ostringstream os;
		os<<x;
		return os.str();
	}
	
	string determineOutcome(int A,int B)
	{
		//Manao wins if and only if A contains B as a substring. 
		string s=to_str(A);
		string x=to_str(B);
		string y=x;reverse(y.begin(),y.end());
		if(s.find(x)!=string::npos||s.find(y)!=string::npos)
			return "Manao wins";
		return "Manao loses";
	}
};

