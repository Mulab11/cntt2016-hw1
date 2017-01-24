#include <vector>
#include <string>
#include <cmath>
using namespace std;
class TheSwapsDivOne{
public:
	int a[2510];
	double find(vector <string> sequence, int k){
		int n=0,S=0;
		for(int i=0;i<sequence.size();i++)
			for(int j=0;j<sequence[i].length();j++)S+=(a[n++]=sequence[i][j]-'0');
		double E=0,P=1.0/n+(1-1.0/n)*pow(1-2.0/(n-1),k);
		for(int i=0;i<n;i++)E+=(a[i]*P+(S-a[i])*(1-P)/(n-1))*(i+1)*(n-i)*2/n/(n+1);
		return E;
	}
};
