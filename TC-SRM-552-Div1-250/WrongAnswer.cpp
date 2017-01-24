#define min(a,b) ((a)<(b)?(a):(b))
class FoxPaintingBalls{
public:
	long long theMax(long long R, long long G, long long B, int N){
		long long x=N*(N+1ll)/2,y=x/3;
		return y?min(min(R/y,G/y),min(B/y,(R+G+B)/x)):R+G+B;
	}
};
