#include<iostream>
#include<thread>
#include<mutex>
#include<functional>
#include<mpi.h>

using namespace std;

const int KEYS = 10;
const string SECRET_MESSAGE = "Secret Message";
const string ENCRYPTED_MESSAGE = "Xjhwjy%Rjxxflj";

bool cipher(int key, string &decrypt)
{
	for(int i = 0; i < ENCRYPTED_MESSAGE.size(); i++)
        {
		int temp = (ENCRYPTED_MESSAGE[i] - key);
		decrypt[i] = char(temp);
	}
	
	if(decrypt == SECRET_MESSAGE)
	{
		return true;
	}
	else
		return false;
}

int main()
{
	//Initialize MPI
	MPI_Init(NULL, NULL);
	
	int world_rank;
        int world_size;

        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if(world_size < 2)
        {
                cout << "num processors must be greater than two" <<endl;
                MPI_Abort(MPI_COMM_WORLD, 1);
        }

	int j = 0;
	int finished = 1;
	bool found = false;
	string decrypt = ENCRYPTED_MESSAGE;
	MPI_Request request;
	if(world_rank == 0) //master
	{

		while(finished != world_size)
		{
			MPI_Recv(&world_rank, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(world_rank < 0)
			{
				found = true;
				j = -1;
				world_rank = -world_rank;
			}			
			MPI_Ssend(&j, 1, MPI_INT, world_rank, 1, MPI_COMM_WORLD); //send keys to slave nodes
			if(!found)
				j++;
			else
				finished++;
		}
		
	}

	else //slave	
	{
		while(true)
		{
			MPI_Ssend(&world_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Recv(&j, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(j < 0) 
			{
				break;
			}	
			if(cipher(j, ref(decrypt)))
			{
				world_rank = -world_rank;
				cout << "The secret message is: " << decrypt << " , and the key is: " << j << endl;
			}
		}
	}

	MPI_Finalize();

	return 0;

}
