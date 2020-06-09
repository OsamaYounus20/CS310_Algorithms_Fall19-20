#include <iostream>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;
/*In this question we extracted the values from files and made two different arrays for rows and columns.
//To check for the not possible condition I have summed up values of rows and collumns and if it isnt equal then it isnt possible
otherwise it goes to the else loop where for each row it finds the maxiumum column and places the piece there. If the board already has a
piece than in that case it finds the other max. The board is implemented using array and the searching takes log(n) time so the total time
complexity is O(n^2 * log(n))
*/ 
string line = "", ext = "";
int arr_size = 0,  i = 0;

int max(int arr[], int n)
{
	int max = 0;
	int maxi = 0;
	for (int i = 0; i < n; i++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
			maxi = i;
		}
	}
	return maxi;
}
int max(int arr[], int n, int m)
{
	int max = 0;
	int maxi = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == m)
			continue;
		if(arr[i] > max)
		{
			max = arr[i];
			maxi = i;
		}
	}
	return maxi;
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
	int i = 0, j = 0;
	int row[arr_size], col[arr_size];
	getline(infile, line);
	ext = line.substr(4);
	for(int x = 0; x < arr_size; x++)
		row[x] = 0;
	for(int x = 0; x < arr_size; x++)
		col[x] = 0;

	istringstream extracted(ext);
	while(extracted)
	{
		string x;
		int num;
		extracted >> x;

		stringstream to_num(x);
		to_num >> num;
		row[i] = num;
		i++;
		//cout<<num<<endl;
	}

	getline(infile, line);
	ext = line.substr(4);
	//cout << ext2<<endl;


	
	istringstream extracted2(ext);
	while(extracted2)
	{
		string x;
		int num;
		extracted2 >> x;

		stringstream to_num2(x);
		to_num2 >> num;
		col[j] = num;
		j++;
		//cout<<num<<endl;
	}
	int sum1 = 0, sum2 = 0;
	// for(int x = 0; x < arr_size; x++)
	// 	cout<<row[x]<<endl;

	// cout << endl;
	// for(int x = 0; x < arr_size; x++)
	// 	cout<<col[x]<<endl;

	for(int x = 0; x < arr_size; x++)
		sum1 += row[x];

	for(int x = 0; x < arr_size; x++)
		sum2 += col[x];

	int board[arr_size][arr_size];
	// cout << sum1 << " " << sum2;
	if (sum1 != sum2)
	{
		string answer = "Not Possible\n";
		cout <<answer;
	}
	else
	{
		for (int i = 0; i < arr_size; i++)
			for (int j = 0; j < arr_size; j++)
				board[i][j] = 0;

		for (int i = 0; i < arr_size; i++)
		{
			int n = row[i];
			for (int j = 0; j < n; j++)
			{
				int m = max(col, arr_size);
				if (board[i][m] == 1)
				{
					m = max(col, arr_size, m);
					board[i][m] = 1;
					col[m]--;
				}
				else
				{	
					board[i][m] = 1;
					col[m]--;
				}
			}
		}
		string answer = "";
		for (int i = 0; i < arr_size; i++)
		{
			for (int j = 0; j < arr_size; j++)
			{

				if (board[i][j] == 1)
				{
					ostringstream convert;
					convert << i + 1;
					string conc_st = convert.str();
					answer += "("+ conc_st + ",";
					ostringstream convert2;
					convert2 << j + 1;
					string conc_str = convert2.str();
					answer += conc_str + ") ";
				}
			}
			answer = answer.substr(0, answer.length()-1);
			answer += "\n";
		}

		cout << answer;
	}

	
	// string ans ="";
	// if (argv[1][4]=='1'){
	// 	ans+="(3,1) (3,2) (3,2)\n";
	// 	ans+="(3,3)\n";
	// 	ans+="(2,2) (2,3) (2,4)\n";
	// 	ans+="(4,2) (4,3) (4,4)\n";
	// 	ans+="(2,1) (2,3) (2,2)\n";
	// }
	// else if (argv[1][4]=='2'){
	// 	ans+="Not Possible\n";
	// }
	// cout<<ans;
	return 0;
}