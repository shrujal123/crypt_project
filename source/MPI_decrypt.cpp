#include<iostream>
#include<thread>
#include<mutex>
#include<functional>
#include<mpi.h>

void cipher(int rank, int )
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

	if(world_rank == 0) //master
	{
		for(int i = 1; i <= world_size; i++)
		{
			MPI_Send() //send keys to slave nodes
		}
	}

	else //slave	
	{
		
		MPI_Recv()
	}

}
