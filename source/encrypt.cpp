#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

int main(int argc, char** argv)
{
	int key;
	string file = "text.txt";
	char c;

	if(argc == 1)
	{
		cout << "key: ";
		cin >> key;
	}
	else
	{
		stringstream s;
		s << argv[1];
		s >> key;
	}
	fstream fin,fout;

	fin.open(file, fstream::in);
	fout.open("encrypt.txt", fstream::out);

	string line;

	while(getline(fin, line))
	{
		for(int i = 0; i < line.size(); i++)
		{
			int temp = (line[i] + key);
			fout << char(temp);
		}
		fout << '\n';
	}


	fin.close();
	fout.close();


	return 0;
}
