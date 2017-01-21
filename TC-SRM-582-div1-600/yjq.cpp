#include <bits/stdc++.h>

#define MOD 1000000009
using namespace std ;

int n ;

const int MAXN = 1310 ;

int c[MAXN], sv[MAXN][MAXN], c_id = 0, a[MAXN], Fac[MAXN], Inv[MAXN], p[MAXN], tot[MAXN] ; 

bool cmp(int a, int b) {
		return c[a] < c[b] ; 
}
int qpow(int a, int b) { 
		int tmp = a, ret = 1; 
		for (; b; b >>= 1, tmp = 1LL * tmp * tmp % MOD) if (b & 1) ret = 1LL * ret * tmp % MOD ;
		return ret ; 
}

class ColorfulBuilding { 
		public :
			   int count(vector<string> c1, vector<string> c2, int L) {
						int sz = c1.size() ;
						for (int i = 0; i < sz; i ++) { 
								int len = c1[i].length() ;
								for (int j = 0; j < len; j ++) { 
										c[++n] =  c1[i][j] * 256 + c2[i][j] ;
								}
						}
						for (int i = 1; i <= n; i ++) p[i] = i ; 
						sort(p + 1, p + n + 1, cmp) ; 
						for (int i = 1; i <= n; i ++) {
							   if (i == 1 || (c[p[i]] != c[p[i - 1]])) c_id ++ ;
							   a[p[i]] = c_id ; 
						}
						for (int i = 1; i <= n; i ++) c[i] = a[i] ;
						Fac[n] = 1;  
						Fac[n - 1] = n - 1; 
						for (int i = n - 1; i > 1; i --) Fac[i - 1] = 1LL * Fac[i] * (i - 1) % MOD ; 
						for (int i = 1; i <= n - 1; i ++) Inv[i] = qpow(Fac[i], MOD - 2) ; 
						tot[1] = Fac[1], sv[c[n]][1] = Fac[1];   
						for (int i = n - 1; i; i --) {
								for (int j = (n - i) ; j; j --) { 
										int tmp = 1LL * (tot[j] - sv[c[i]][j] + MOD) * Inv[n - i] % MOD ;
										tmp = 1LL * tmp * Fac[n - i + 1] % MOD ; 
										(sv[c[i]][j + 1] += tmp) %= MOD ; (tot[j + 1] += tmp) %= MOD;  
										tmp = 1LL * sv[c[i]][j] * Inv[n - i] % MOD; 
										tmp = 1LL * tmp * Fac[n - i + 1] % MOD; 
										(sv[c[i]][j] += tmp) %= MOD; (tot[j] += tmp) %= MOD ; 
								}
						}
						return tot[L] ; 
			   }
} solution; 

vector<string> s1, s2;  

string g[1110]  = 	
{"SJXcabKTWeUXhwxGixFepQaQlFxrAedNAtVP",
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
 "FAsbuzrLVIgaryqXBfuBRAbReleXSSgEKSvt"} ; 

string g2[1110] = 
{"XAhlUHtfjOpOlQlowWppQcodMGUiqoLobxnD",
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
 "thkgVflJYmbUYbIlafNUMGePQWiZyYzYXvUR"} ;
int main() {
	   for (int i = 0; i < 36; i ++) s1.push_back(g[i]), s2.push_back(g2[i]) ;	
		printf("%d\n", solution.count(s1, s2, 1200)) ; 
}		
