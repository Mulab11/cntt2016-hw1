#include <string>
class TheNumberGame{
public:
	bool check(int A,int B,int K){
		for(;A;A/=10)if(A%K==B)return 1;
		return 0;
	}
	std::string determineOutcome(int A, int B){
		int C=0,K=1;
		for(int x=B;x;x/=10)C=C*10+x%10,K*=10;
		return check(A,B,K)||check(A,C,K)?"Manao wins":"Manao loses";
	}
};
