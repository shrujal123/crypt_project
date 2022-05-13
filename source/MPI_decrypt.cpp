#include<iostream>
#include<thread>
#include<mutex>
#include<functional>
#include<mpi.h>

using namespace std;

const int NUM_KEYS = 10;
const string SECRET_MESSAGE = "secret message";
const string ENCRYPTED_MESSAGE = "Xjhwjy%Rjxxflj";

bool cipher(int key)
{
	string decrypt;
	for(int i = 0; i < SECRET_MESSAGE.size(); i++)
        {
		int temp = (ENCRYPTED_MESSAGE[i] - key);
		decrypt[i] = char(temp);
                if (decrypt.compare(SECRET_MESSAGE)==0)
                {
                        return true;
                }
	}
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

	if(world_size != 2)
        {
                cout << "num processors must be two" <<endl;
                MPI_Abort(MPI_COMM_WORLD, 1);
        }

	int j;
	MPI_Request request;
	if(world_rank == 0) //master
	{

		for(int i = 1; i <= world_size; i++)
		{

			for(j = 0; j < NUM_KEYS; j++)
			{

				MPI_Irecv(&world_rank, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);
				if(world_rank == -1)
				{
					for(int k = 1; k <= world_size; k++)
					{
						MPI_Send(&world_rank, 1, MPI_INT, k, 0, MPI_COMM_WORLD);
					}
					break;
				}
				MPI_Send(&j, 1, MPI_INT, world_rank, 1, MPI_COMM_WORLD); //send keys to slave nodes
			}

		}
	}

	else //slave	
	{
		while(1)
		{
			MPI_Send(&world_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			if(world_rank < 0)
			{
				break;
			}
			MPI_Irecv(&j, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
			if(cipher(j))
			{
				world_rank = -1;
			}
		}
	}

	MPI_Finalize();
	return 0;

}
