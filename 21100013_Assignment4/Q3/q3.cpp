#include <iostream> 
#include <string.h>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <climits>
using namespace std; 
/*
the base cases are fun(len, cut{}) = 0 and fun(len, cut{x}) = len
the recurrence elation will be for all n in {x:xs} fun(len, cut{x:xs}) = min(len+fun(n, {y} for all y<n)+fun(len-n, {(y)-n} for all y>n))
the time complexity will be O(mlog(m))
*/

string line, ext;
vector<int> memo[10000];
struct mystruct
{
	vector<int> myv;
	int x;
	int y;
};
//int length;
vector<mystruct> myvec;

vector<int> Cutter(int length, vector<int> cut){
	vector<int> v1;
	vector<int> v2;
	vector <int> greaterthan;
	vector <int> lesserthan;
	int minimum = INT_MAX;
	int total;
	
	if(cut.size() == 0)
	{
		v1.push_back(0);
		//memo[v1[0]+v1[v1.size()-1]] = v1;
		return v1;
	}
	for(int i = 0; i < myvec.size(); i++)
	{
		if(myvec[i].x == cut[0] && myvec[i].y == cut[cut.size()-1])
			return myvec[i].myv;
	}
	if(cut.size() == 1)
	{
		v2.push_back(length);
		v2.push_back(cut[0]);
		mystruct s;
		s.myv = v2;
		s.x = v2[0];
		s.y = v2[v2.size()-1];
		//memo[v2[0]+v2[v2.size()-1]] = v2;
		myvec.push_back(s);
		return v2;
	}
	for(int i=0; i<cut.size(); i++)
	{
		int currentlength = cut[i];
		vector<int> lesser;
		vector<int> greater;
		
		for(int j = 0; j < cut.size(); j++)
		{
			if(j != i)
			{
				if(cut[j] < currentlength)
					lesser.push_back(cut[j]);
				else
					greater.push_back(cut[j]-currentlength);
			}

		}
		lesserthan = Cutter(length-currentlength, greater);
		greaterthan = Cutter(currentlength, lesser);
		total = length + greaterthan[0] + lesserthan[0];
		
		if(total < minimum)
		{
			vector<int> v3;
			minimum = total;
			v3.push_back(total);
			v3.push_back(currentlength);

			for(int x = 0; x < greaterthan.size(); x++)
			{
				if(x == 0)
					continue;
				v3.push_back(greaterthan[x]);
			}
			for(int x = 1; x < lesserthan.size(); x++)
				v3.push_back(lesserthan[x]+currentlength);
			v1 = v3;
		}
	}
	mystruct s;
	s.myv = v1;
	s.x = v1[0];
	s.y = v1[v1.size()-1];
	//memo[v1[0]+v1[v1.size()-1]];
	myvec.push_back(s);

	return v1;
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
    int length;
    str >> length;
    // cout<<length;
    int x;
    getline(infile, line);
	ext = line.substr(2);
	vector<int> cut;
	istringstream extracted(ext);
	while(extracted)
	{
		string x;
		int num;
		extracted >> x;

		stringstream to_num(x);
		to_num >> num;
		cut.push_back(num);
		// cout<<num<<endl;
	}
	cut.pop_back();
	// for (int i = 0; i < cut.size(); i++)
	// {
	// 	cout<<cut[i]<<endl;
	// }
	// cout<<length;
	vector<int> v = Cutter(length, cut);
	// for (int i = 0; i < v.size(); i++)
	// {
	// 	cout<<v[i]<<endl;
	// }
	string answer = "Optimal cut ordering: ";
	for (int i = 1; i < v.size(); i++)
	{
		answer += to_string(v[i]) + " ";
	}
	answer = answer.substr(0, answer.length()-1) + "\nLeast cost " + to_string(v[0]) + "\n";
	cout<<answer;
	//Answering Format
	//Grader is not Endline or Space Sensitive
	// string ans;
	// ans +="Optimal cut ordering: 5 3 10     \n";
	// ans +="Least Cost: 30 \n\n";

   	//cout<<ans<<endl;
    return 0; 
} 
