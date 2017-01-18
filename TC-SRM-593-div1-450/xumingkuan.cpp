#include <vector>
#include <bitset>
using namespace std;

class MayTheBestPetWin
{
private:
	bitset<1010101> f;//f(i)[j]: if there is a subset of {A[1] + B[1], A[2] + B[2], ..., A[i] + B[i]} whose sum is j
public:
	int calc(vector<int> A, vector<int> B)
	{
		f[0] = 1;
		int sumA = 0, sumB = 0;
		for(int i = 0; i < A.size(); i++)//dp
			f |= f << (A[i] + B[i]), sumA += A[i], sumB += B[i];
		for(int ans = (sumB - sumA + 1) >> 1; true; ans++)//get smallest maxdiff
			if(f[sumB - ans] || f[sumA + ans])
				return ans; 
	}
};

