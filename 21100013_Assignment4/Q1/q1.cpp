#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;
string line = "", ext = "";
int arr_size = 0;
/*
recurrence relation  is max((high[n] + fun(n-2), low[n] + fun(n-1))
the base case for this would be func(0) = max(high[0], low[0])
the time complexity of this is O(n)
*/
int	revenue(int x, int order[], int values[], int high[], int low[])
{
	int highval, lowval;
	if(values[x] > -1)
		return values[x];
	else
		if(x > 1)
			highval = high[x] + revenue(x-2, order, values, high, low);
		else
			highval = high[x];

		lowval = low[x] + revenue(x-1, order, values, high, low);
		if(highval < lowval)
		{
			order[x] = 0;
			values[x] = lowval;
		}
		else
		{
			order[x] = 1;
			values[x] = highval;
		}
		return values[x];
}

int main(int argc, char** argv)
{
	ifstream infile;
	string f = argv[1];
	infile.open(f);
	if (!infile) 
	{
		cout << "Unable to open file";
		return 0;
	}
	getline(infile, line);
	ext = line.substr(2);
	stringstream str(ext);
	str >> arr_size;

	getline(infile, line);
	ext = line.substr(3);
	int i = 0, j = 0;
	int high[arr_size], low[arr_size], order[arr_size], values[arr_size];
	
	for(int x = 0; x < arr_size; x++)
	{
		high[x] = 0;
		low[x] = 0;
		order[x] = 0;
		values[x] = -1;
	}

	istringstream extracted(ext);
	while(extracted)
	{
		string x;
		int num;
		extracted >> x;

		stringstream to_num(x);
		to_num >> num;
		high[i] = num;
		i++;
		//cout<<num<<endl;
	}
	getline(infile, line);
	ext = line.substr(3);

	istringstream extracted2(ext);
	while(extracted2)
	{
		string x;
		int num;
		extracted2 >> x;

		stringstream to_num2(x);
		to_num2 >> num;
		low[j] = num;
		j++;
		//cout<<num<<endl;
	}

	if (high[0] < low[0])
	{
		values[0] = low[0];
		order[0] = 0;
	}
	else
	{
		values[0] = high[0];
		order[0] = 1;
	}

	int maxrev = revenue(arr_size-1, order, values, high, low);
	for(int i = arr_size-1; i>=0; i--)
	{
		if(order[i] == 1)
		{
			order[i-1] = 2;
			i--;
		}
	}
	string ans = "";
	for(int i = 0; i < arr_size; i++){
		ans += "Week " +  to_string(i+1) + ": ";
		if(order[i] == 0)
			ans += "Low " + to_string(low[i])  + "\n";
		else if(order[i] == 1)
			ans += "High " + to_string(high[i])  + "\n";
		else if(order[i] == 2)
			ans += "Priming\n";
	}
	ans += "Total Revenue: " + to_string(maxrev) + "\n";
	cout <<ans;
	// for(int x = 0; x < arr_size; x++)
	// 	cout <<high[x]<<endl;

	// string ans = "";
	// ans+="Week 1 : Priming\n";
	// ans+="Week 2 : High 1\n";
	// ans+="Week 3 : Priming\n";
	// ans+="Week 4 : Low 6\n";
	// ans+="Total Revenue : 7\n";	
	// cout<<ans;	

	return 0;
}