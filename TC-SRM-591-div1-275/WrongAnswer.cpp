#include <vector>
using namespace std;
class TheTree{
public:
	int maximumDiameter(vector <int> cnt){
		int D=cnt.size(),L=D,S=0;for(int i=D;i--;)D+(L=cnt[i]==1?i:L)-2*i>S?S=D+L-2*i:1;return S;
	}
};
