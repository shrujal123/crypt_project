module load cmake/3.19.5 mpich/3.4 gcc/7.5.0

echo $1
(time mpirun -n $1 ./exe) &>> benchmark_file;
