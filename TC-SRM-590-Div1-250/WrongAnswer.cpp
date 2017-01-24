#include <string>
using namespace std;
class FoxAndChess{
public:
	string ableToMove(string begin, string target){
		begin.push_back('X');
		target.push_back('X');
		for(int i=0,j=0,c;;i++)if(begin[i]!='.'){
			while(target[j]=='.')++j;
			if((c=begin[i])!=target[j]||c=='L'&&j>i||c=='R'&&j<i)return"Impossible";
			if(c=='X')return"Possible";++j;
		}
	}
};
