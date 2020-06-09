#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv)
{
	string x = argv[0];
	vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(5);

	cout<<v.size()/2<<endl;
	for (int i = 0; i < v.size()/2; ++i)
	{
		cout<<"("<<v[i*2]<<","<<v[i*2+1]<<")"<<endl;
	}

	return 0;
}
