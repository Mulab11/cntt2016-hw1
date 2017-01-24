#include <bits/stdc++.h>

using namespace std;


int		K, cnt;

string		res;

vector <string> tmp;

vector <int>	Bl;




int Calc( const string & s, const string & g )
{
	int res = 0;
	for ( int i = 0; i < s.size(); i++ )
	{
		if ( s[i] == g[i] )
		{
			++res;
		}
	}
	return(res);
}


void getInt( string & s )
{
	int	len	= s.size();
	int	k	= 0;
	while ( k < len && '9' == s[k] )
	{
		s[k] = '0';
		++k;
	}
	if ( k >= len )
	{
		s = "";
	} else {
		++s[k];
	}
}


map<vector<int>, string>	mpL;
class				EllysBulls {
public:

	string getNumber( vector <string> GA, vector <int> GB )
	{
		string res = "Liar";
		tmp	= GA, Bl = GB;
		K	= tmp[0].size();
		int n = tmp.size();
		for ( string s( K / 2, '0' ); s != ""; getInt( s ) )
		{
			bool good = true;
			vector <int> matches( n );


			for ( int i = 0; i < n; i++ )
			{
				int m = Calc( s, tmp[i] );
				if ( m > Bl[i] )
				{
					good = false;
					break;
				} else {
					matches[i] = m;
				}
			}
			if ( good )
			{
				if ( mpL[matches] != "" )
				{
					mpL[matches] = "Ambiguity";
				} else {
					mpL[matches] = s;
				}
			}
		}
		for ( string s( K - K / 2, '0' ); s != ""; getInt( s ) )
		{
			bool good = true;
			vector <int> required( n );


			for ( int i = 0; i < n; i++ )
			{
				int m = Bl[i] - Calc( s, tmp[i].substr( K / 2 ) );
				if ( m < 0 )
				{
					good = false;
					break;
				} else {
					required[i] = m;
				}
			}
			if ( good )
			{
				if ( mpL.find( required ) != mpL.end() )
				{
					if ( mpL[required] == "Ambiguity" )
					{
						return("Ambiguity");
					} else {
						if ( res != "Liar" )
						{
							if ( res != mpL[required] + s )
							{
								return("Ambiguity");
							}
						} else {
							res = mpL[required] + s;
						}
					}
				}
			}
		}
		return(res);
	}
} sol ;

string x[] = {"1234", "4321", "1111", "2222", "3333", "4444", "5555", "6666", "7777", "8888", "9999"} ; 

int a[] = {2, 1, 1, 0, 2, 0, 0, 0, 1, 0, 0} ; 


		vector<string> ga ;
		vector<int> gb ; 
int main() { 
		for (int i = 0; i < 11; i ++) ga.push_back(x[i]), gb.push_back(a[i]) ; 
		cout << sol.getNumber(ga, gb) << endl ; 
}




