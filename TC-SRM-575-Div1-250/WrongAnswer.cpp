#include <string>
class TheNumberGameDivOne{
public:
	std::string find(long long n){
		for(int i=1;i<62;i+=2)if(n==(1ll<<i))return"Brus";
		return n%2?"Brus":"John";
	}
};
