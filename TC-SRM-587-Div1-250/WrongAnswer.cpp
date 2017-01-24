#include <cmath>
class JumpFurther{
public:
	int furthest(int N, int b){
		return N*(N+1)/2-(b<=N*(N+1)/2&&int(sqrt(8*b+1.5))*int(sqrt(8*b+1.5))==8*b+1);
	}
};
