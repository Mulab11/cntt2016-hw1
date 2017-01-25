// FST:DP转移时忘记判断是否合法FST了一次，f的初值应设为1却设为0又FST了一次 
#include <vector>
#include <algorithm>
using namespace std;
class AstronomicalRecords{
public:
	int minimalPlanets(vector <int> A, vector <int> B){
		long long As[55][55],Bs[55][55];
		int Ac[55]={0},Bc[55]={0},f[55][55],ans=0,tmp;
		for(int i=A.size();i--;){
			for(int j=A.size()-1;j>i;j--)As[i][Ac[i]++]=A[j]*64ll|j;
			sort(As[i],As[i]+Ac[i]);
		}
		for(int i=B.size();i--;){
			for(int j=B.size()-1;j>i;j--)Bs[i][Bc[i]++]=B[j]*64ll|j;
			sort(Bs[i],Bs[i]+Bc[i]);
		}
		for(int i=A.size();i--;){
			for(int j=B.size();j--;){
				if(i==A.size()-1||j==B.size()-1)f[i][j]=1;
				else for(int i2=!(f[i][j]=1),j2=0;i2<Ac[i];i2++){
					while(j2<Bc[j]&&A[i]*(Bs[j][j2]>>6)<B[j]*(As[i][i2]>>6))j2++;
					if(j2<Bc[j]&&A[i]*(Bs[j][j2]>>6)==B[j]*(As[i][i2]>>6)&&(tmp=1+f[As[i][i2]&63][Bs[j][j2]&63])>f[i][j])f[i][j]=tmp;
				}
				if(f[i][j]>ans)ans=f[i][j];
			}
		}
		return A.size()+B.size()-ans;
	}
};
