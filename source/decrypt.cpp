#include<iostream>
#include<thread>
#include<vector>
#include<fstream>
#include<sstream>
#include<mutex>

using namespace std;
mutex mtx;

int KEYS[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void cipher(int threadnum, stringstream &file, string encrypted, string message, string decrypt, int &key)
{
	
	for(int j = threadnum; j < 10; j +=3)
	{
		for(int i = 0; i < encrypted.size(); i++)
		{
			int temp = (encrypted[i] - j);
			decrypt[i] = char(temp);
		}
		if (decrypt.compare(message)==0)
		{
			key = j;
			break;
		}
	}
	
}

int main()
{

string encrypted = "Xjhwjy%Rjxxflj";
string message = "Secret Message";
string decrypt;
int key;
bool isFound = false;
stringstream fin;
fin << encrypted;

vector<thread> threads;
decrypt = encrypted;

for (int i = 0; i < 3; i++)
{
	threads.push_back(thread(cipher, i, ref(fin), encrypted, message, decrypt, ref(key)));
}

for(auto& th : threads) th.join();

for(int i = 0; i < decrypt.size(); i++)
{
	int temp = (encrypted[i] - key);
	decrypt[i] = char(temp);
}
cout << decrypt << endl;

return 0;
}
