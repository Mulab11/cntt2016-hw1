#include <bits/stdc++.h>

using namespace std;

class EllysBulls {
		public:
				int K, cnt;
				string res;
				vector <string> guesses;
				vector <int> bulls;
				void next(string & s)
				{
						int len = s.size();
						int k = 0;
						while (k < len && '9' == s[k]) {
								s[k] = '0' ;
								++k;
						}
						if (k >= len) {
								s = "";
						} else {
								++s[k];
						}
				}
				int countMatches(const string & s, const string & g)
				{
						int res = 0;
						for (int i = 0; i < s.size(); i++) {
								if (s[i] == g[i]) {
										++res;
								}
						}
						return res;
				}
				string getNumber(vector <string> guesses, vector <int> bulls) {
						string res = "Liar";
						K = guesses[0].size();
						this->guesses = guesses;
						this->bulls = bulls;
						int n = guesses.size();
						// left half
						map <vector<int>, string> left_half;
						for (string s(K / 2, '0'); s != ""; next(s)) {
								bool good = true;
								vector <int> matches(n);
								for (int i = 0; i < n; i++) {
										int m = countMatches(s, guesses[i]);
										if (m > bulls[i]) {
												good = false;
												break;
										} else {
												matches[i] = m;
										}
								}
								if (good) {
										if (left_half[matches] != "") {
												left_half[matches] = "Ambiguity";
										} else {
												left_half[matches] = s;
										}
								}
						}
						// right half
						for (string s(K - K / 2, '0'); s != ""; next(s)) {
								bool good = true;
								vector <int> required(n);
								for (int i = 0; i < n; i++) {
										int m = bulls[i] - countMatches(s, guesses[i].substr(K / 2));
										if (m < 0) {
												good =false;
												break;
										} else {
												required[i] = m;
										}
								}
								if (good) {
										if (left_half.find(required) != left_half.end()) {
												if (left_half[required] == "Ambiguity") {
														return "Ambiguity";
												} else {
														if (res != "Liar") {
																if (res != left_half[required] + s) {
																		return "Ambiguity";
																}
														} else {
																res = left_half[required] + s;
														}
												}
										}
								}
						}
						return res;
				}

};
