#include<cstdio>
		#include<algorithm>
		#include<cstring>
		#include<vector>
		#include<string>
		#include<iostream>
		#include<set>
		
		#define N 10005
		
		using namespace std;
		class FoxAndFencing{
		public:
		string WhoCanWin(int A,int C,int B,int D,int E)
		{ 
		     if (A+B>=E) return "Ciel";
		     if (C+D>=A+E) return "Liss";
			 if (C+D>A+B) 
			 {
			 	if (A>=C||A+A+B>=C+D) return "Draw"; 
			    return "Liss";
			 }
			 if (C+D==A+B) return "Draw";
			 if (C>=A||C+C+D>=A+B) return "Draw";
			 return "Ciel"; 
		}
		};
