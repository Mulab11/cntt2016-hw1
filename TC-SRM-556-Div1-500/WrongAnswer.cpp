#include <string>
using namespace std;
class LeftRightDigitsGame2{
public:
	// 倒过来将digits拼在串s的首尾
	string f[52][52][2]; // f[l][r][k]:剩下[l,r)未确定，s[0,l)=lowerBound[0,l)，s[r,n)<lowerBound[r,n)（k=0）或s[r,n)>=lowerBound[r,n)，s[l,r)的最小字典序，不存在则为空串
	string g[52]; // g[i]:用digits的前i个字符构成最小字典序
	// 特判空串为不存在方案
	string min(string a,string b){return a==""||b==""?a+b:a<b?a:b;}
	string con(string a,string b){return a==""||b==""?"":a+b;}
	string minNumber(string digits, string lowerBound){
		g[0]="";
		for(int i=0;i<digits.length();i++)g[i+1]=min(g[i]+digits[i],digits[i]+g[i]);
		for(int l=digits.length()-1;l>=0;l--){
			for(int r=l+1;r<=digits.length();r++){
				for(int k=0;k<2;k++){
					char c=digits[r-l-1],L=lowerBound[l],R=lowerBound[r-1];
					string d;d.push_back(c);
					if(r-l==1)f[l][r][k]=c<L||(c==L&&!k)?"":d; // 边界为只含一个字符
					else f[l][r][k]=min(con(f[l][r-1][c!=R?c>R:k],d),c>L?d+g[r-l-1]:c==L?con(d,f[l+1][r][k]):""); // 转移时枚举放左边还是右边
				}
			}
		}
		return f[0][digits.length()][1];
	}
};
