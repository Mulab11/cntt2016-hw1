#include<map>
#include<set>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class EllysBulls{
	private:
		int n,len;
		vector<string> G;
		vector<int> bul;
		map<vector<int>,string> mp;
		typedef map<vector<int>,string>::iterator mit;
		set<vector<int> > ab;
		int cal(string a,string b){
			int ret=0;
			for (int i=0;i<a.length();++i) if (a[i]==b[i]) ++ret;
			return ret;
		}
		
		void search1(int l){
			char s[100],use[100];
			int lim=pow(10,l);
			sprintf(use,"%%0%dd",l);
//			printf("%s\n",use);
			for (int i=0;i<lim;++i){
				sprintf(s,use,i);
				vector<int> tt;
//				printf("guess %s:\n",s);
				for (int j=0;j<n;++j){
					int tmp=cal(s,G[j].substr(0,l));
//					printf("%d ",tmp);
					tt.push_back(tmp);
				}
//				puts("");
				if (mp.find(tt)!=mp.end()) ab.insert(tt);
				else mp[tt]=s;
			}
			return;
		}
		
		string search2(int l){
			char s[100],use[100];
			int lim=pow(10,l);
			sprintf(use,"%%0%dd",l);
			bool fl=false;
			string ret;
			for (int i=0;i<lim;++i){
				sprintf(s,use,i);
				vector<int> tt;
//				printf("guess %s:\n",s);
				for (int j=0;j<n;++j){
					int tmp=bul[j]-cal(s,G[j].substr(len-l,l));
//					printf("%d ",tmp);
					tt.push_back(tmp);
				}
//				puts("");
				mit it=mp.find(tt);
				if (it!=mp.end()){
					if (fl||ab.find(tt)!=ab.end()) return "Ambiguity";
					fl=true;
					ret=it->second+s;
				}
			}
			if (fl) return ret;
			else return "Liar";
		}
	public:
		string getNumber(vector <string> g, vector <int> num){
			G=g;
			bul=num;
			n=g.size();
			len=g[0].size();
			search1(len/2);
			return search2(len-len/2);
		}
};
