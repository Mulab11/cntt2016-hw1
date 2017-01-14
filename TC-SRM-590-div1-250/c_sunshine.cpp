#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class FoxAndChess
{
	public:
	string ableToMove(string begin,string target)
	{
		//I had nothing to say regarding this problem (fog) 
		//OK, just say something 
		int i=0,j=0;
		for(;i<begin.size();i++)
			if(begin[i]!='.')
			{
				//Make sure that target do contain enough pawns
				for(;j<target.size();j++)
					if(target[j]!='.')break;
				if(j==target.size())return "Impossible";
				//Make sure the pawns are of the same kind
				if(begin[i]!=target[j])return "Impossible";
				//Make sure that the pawn in begin can reach its position in target
				if(begin[i]=='L'&&i<j)return "Impossible";
				if(begin[i]=='R'&&i>j)return "Impossible";
				j++;
			}
		//Make sure that target do not contain extra pawns
		for(;j<target.size();j++)
			if(target[j]!='.')return "Impossible";
		return "Possible";
	}
};

