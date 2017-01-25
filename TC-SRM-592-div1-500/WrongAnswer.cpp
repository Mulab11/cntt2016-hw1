#define MOD 1000000007
class LittleElephantAndPermutationDiv1{
public:
	int N,f[52][52][2502];
	int F(int i,int c00,int c01,int s){
		if(s<0)s=0;
		if(i>N)return!s;
		int&g=f[c00][c01][s];
		if(g)return g-1;
		if(c00)g=(g+1ll*c00*F(i+1,c00-1,c01,s-i))%MOD;
		if(c00>1)g=(g+1ll*c00*(c00-1)*F(i+1,c00-2,c01+1,s))%MOD;
		if(c00&&c01)g=(g+2ll*c00*c01*F(i+1,c00-1,c01,s-i))%MOD;
		if(c01)g=(g+1ll*c01*c01*F(i+1,c00,c01-1,s-2*i))%MOD;
		return g++;
	}
	int getNumber(int N, int K){
		this->N=N;
		return F(1,N,0,K);
	}
};
