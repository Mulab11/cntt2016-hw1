// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulBuilding.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000009;
int n,m,ans;
int a[1310],f[1310][1310],fac[1310],ifac[1310],b[20010];

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

void update(int &i,int x)
{i=(i+x)%mod;
}

class ColorfulBuilding
{	public:
	int count(vector <string> color1, vector <string> color2, int L)
	{	int i,j,s;
		
		n=0;
		for(i=0;i<color1.size();i++)
			for(j=0;j<color1[i].length();j++)
				a[++n]=color1[i][j]*100;
		n=0;
		for(i=0;i<color2.size();i++)
			for(j=0;j<color2[i].length();j++)
				a[++n]+=color2[i][j];
		
		//cout<<n<<endl;
		//for(i=1;i<=n;i++) cout<<a[i]<<" ";
	 	//cout<<endl;			
				
		m=L;
		fac[0]=1;
		for(i=1;i<=n;i++) fac[i]=(ll)fac[i-1]*i%mod;
		ifac[n]=fpow(fac[n],mod-2);
		for(i=n-1;i>=0;i--) ifac[i]=(ll)ifac[i+1]*(i+1)%mod; //预处理阶乘，阶乘的逆元 
		memset(f,0,sizeof(f));
		f[0][1]=1;
		for(i=1;i<=n;i++) //预处理f[i][1]的答案 
		{	for(j=0;j<i;j++)
			{	if(j && a[j]!=a[i]) continue;
				update(f[i][1],(ll)f[j][1]*fac[n-j-1]%mod*ifac[n-i]%mod);
			}
		}
		for(j=2;j<=m;j++) //f[i][j]表示1~i的楼房有j个颜色段 
		{	s=0;
			for(i=1;i<=n;i++) b[a[i]]=0;
			for(i=1;i<=n;i++)
			{	f[i][j]=(ll)(s+b[a[i]])*ifac[n-i]%mod;
				update(s,(ll)f[i][j-1]*fac[n-i-1]%mod);
				update(b[a[i]],(ll)(f[i][j]+mod-f[i][j-1])*fac[n-i-1]%mod);
			}
		}
		ans=f[n][m];
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"aaba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"aaaa"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 6; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"aaba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"aaba"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; int Arg3 = 0; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"ab", "ba", "a", "aab"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"bb", "ba", "a", "aba"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; int Arg3 = 432; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"xxxxxxxxxxxxxxxxxxxx",
 "xxxxxxxxxxxxxxxxxxxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOxxxxxxxxxxxxxxxx",
 "xxOOxxxxxxxxxxxxxxxx",
 "xxOOxxxxxxxxxxxxxxxx",
 "xxOOxxxxxxxxxxxxxxxx",
 "xxOOxxxxxxxxxxxxxxxx",
 "xxOOxxxxxxxxxxxxxxxx",
 "xxOOxxxxxxxxxxxxxxxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxxxxxxxxxxxxxxxOOxx",
 "xxxxxxxxxxxxxxxxOOxx",
 "xxxxxxxxxxxxxxxxOOxx",
 "xxxxxxxxxxxxxxxxOOxx",
 "xxxxxxxxxxxxxxxxOOxx",
 "xxxxxxxxxxxxxxxxOOxx",
 "xxxxxxxxxxxxxxxxOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxxxxxxxxxxxxxxxxxxx",
 "xxxxxxxxxxxxxxxxxxxx"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"xxxxxxxxxxxxxxxxxxxx",
 "xxxxxxxxxxxxxxxxxxxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOxxxxxxxxxxxxOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxOOOOOOOOOOOOOOOOxx",
 "xxxxxxxxxxxxxxxxxxxx",
 "xxxxxxxxxxxxxxxxxxxx"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 58; int Arg3 = 619787617; verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"SJXcabKTWeUXhwxGixFepQaQlFxrAedNAtVP",
 "gorBIkcTlOFbLDbFeElYAyAqszQdMbpxSRdE",
 "SQVHPehlNtesbJDflyGxMqvgzjXisRnqDcQO",
 "pIAEBwbmpPWCooQAujbGXFGLvXxTmExLARkf",
 "AFnWyWKVObfxDGCjTxdZaObgwdxlPKtIxaAd",
 "uznMpJVNjAofbHJjOrZeSHgSagOCUMGbvkVR",
 "LBRrDbTAyKfVnedKiRfzgRzECpcsziqaTwdo",
 "JrJHvsEVVGDkNVGqLbpxyLDPloBuNDQKnReI",
 "SSYpbjKHSCnQhuyYrVauWDHDyhAoGyecrZMv",
 "UdetQfWEUWHHuAxRSdkJOOJSixKpQXpCFZHO",
 "KXVsQbuQtIgsULOMsTvPFNUqkBldMTLCipYK",
 "hoXConjnDWQkZVtyZlwSedvdVrNWqQhGUClQ",
 "TpsvvyoXsXmQpBAGGVDrXCkodoRHQZmpoQDW",
 "csiJspzTqeFBRmPgeEtTAzfrfCGlTZqcPuyO",
 "vsPDVBJVaJmUAtDdcsKoUkPEbDmAwtZKwjjP",
 "MOfoMhMiKIvGQoeIJXHzyClWRtRuKXMqxUAF",
 "KyyUCkRBjsYvmPFFEGBqqVhIUdtvIyyLacfu",
 "BfuwfSajSlcuTzhMufHSQLudvGEGlyHsEmBD",
 "PLpIXZkdyXveTMfSvqnDGKWOZrTBMUIlZrqF",
 "dzVMCqrSLbanRJTYpDJNHAOLPSzmvSEPQJYm",
 "rAjRkrSjouJyFaCSPPLYSzqDmMoADyWAbobJ",
 "eOCBrJNoyFnGpXpxiExXcoOHnVsaEPXhPfLe",
 "XMjRksnxWssPEINhdhbiLBSYpCLtwNshFjXS",
 "HnnDeUAbuswsgsYQuAaXySLkFYUwFXwYTreM",
 "uqLnwOEGbwZZDgAAWEdLRZxFlogDmlhjhgHM",
 "NcfaQsgPQfirkYDRFrLQpySmBGfRHumKULZf",
 "mOpmmgclsxRzXskEywfryqCRyATNoJwnlHiD",
 "AnoKoKAjrasttjNlHCROnvTJMhEHlVPVoVMo",
 "yegLyIuRkkENFAjwzDoPLKjgUHHEkfzYDIpo",
 "EcxRGGfuaBXUFXkSxctJWOLmmVbvoMkWtTvV",
 "nBMkOBHgaltEVzfyGxseGhmBscfGIbxFbqRn",
 "GvkEcLtqdOofGtsbWDafVMbNdJxsffKDzSiR",
 "jhZQUVzTzalrZcebvyqPWtOUUyniBKTWdyLi",
 "ODJLQPMdjDdTlxrfGsNmBfeGYjzeXApqKDhJ",
 "vlJkWMzdVQujKdLViQClOrJXMTBkuZEasFgg",
 "FAsbuzrLVIgaryqXBfuBRAbReleXSSgEKSvt"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"XAhlUHtfjOpOlQlowWppQcodMGUiqoLobxnD",
 "IDzGlKrHiVGdBjZxIcoxjwagbWieKvUwZrjg",
 "SkpkTVeIFeoNQzUUgmYAYskKONNZdgXxSiWd",
 "rXBGhTmqnvxkmqiutoDzPusDiOUggEFXGCzm",
 "fzrxVuTbFXunGbeEavjshmrIRlDorTuISCxn",
 "LsvIaxTkOBjcskiekmrKNNFEXqnfMNXLWqqu",
 "ekzxGIlbJPVEQPYAbTuMtZKsCiubDXDiBVzU",
 "hZuOCJxvBOYENGSFcUiKKAKfCdebutVmnyvB",
 "UveNkKRQmHnedrROQOpHJfrHjwcNLUShlDbn",
 "ptUkvbaGDryHRkYfHKLkSgVpjWCEcgazyxGK",
 "nVPYEqTTJsRPjzjfdOiULhnZPFeNcnbXaQlk",
 "IPXBXRhMQIkxpygsgbcRfMuvIcuzUPPHGOWX",
 "yWWlNyEyqZSIOXBFAybIuFpVqpvmKRaRFrAE",
 "EvBJVtHvKhjrFcmtpdBbFTdTVtXXZQKAglKT",
 "bCVjHzUvyINFkxXageZQMzCyNhcifACdJVDh",
 "lZITYcDSeIbLweyFtoMAfOQyBNupKlhcNpgo",
 "BduslNrJdWOUukYFFidEkMFaghfofpxVgvJd",
 "YrJpDZKqdjEPzdLsOQEdkcrBfNHPemXHokCW",
 "GjeUKSGjDlgKTyUGNrMQbBLxRUcgrWpkAwOD",
 "wgxTcswqdJHaDugNIRMvrhBsdDaJAssVbSRW",
 "qmVmqFEpvgGioMXDSFqEoQcDOAaUoGPEovSO",
 "KrukPlpfOhawaovCfteTSCIdLMrtImVtiMyQ",
 "ykwmxHsKMFzFHwcbyyedLvhZPnaNGqJMMCxd",
 "HUNYCXjNLQIFCLLGpCXHBCHLTxLynBxnHFbx",
 "uwjzbNbJepVFgMPUXVirxYHzExquBEtPmKju",
 "xXAxAbJePyUsVHeLytDvAxBGMRtnvCEiZZqe",
 "xMkQoIVxWPXPgaOYmDjTOXiMImVdzojERNxS",
 "dwICFwMAmdOIUxyAdXdshasnzwyhfnVWVqZJ",
 "etypXNVvSTEQvriGBZdSGmDEHhvpSqkFklCS",
 "YkxpFBCRYUueRcKaJUXVdaMoYMYEooPQVMOr",
 "DTrexDqclZNKdPuTRFHualJSFziCLPCZjpxo",
 "TfEijcAsSJPikkmBSbXMqYHAhPTcpcKVSkIX",
 "xKXHYPYMJxFpSbxltDKYuRiTkOLxpQKnXZPs",
 "YFYuvuYHfpFJcrLNIdlNfBxRnWdppsdalBkx",
 "NFTysBvNFjejdnlhRTclbcfGipNCxpFEOriY",
 "thkgVflJYmbUYbIlafNUMGePQWiZyYzYXvUR"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1200; int Arg3 = 396065426; verify_case(4, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ColorfulBuilding ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
