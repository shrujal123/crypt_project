while  getopts 'n:' flag;
do 
	case "$flag" in
		n) 
			numProcessors = "$OPTARG";;
	esac
done


echo $1
echo $OPTARG

(time mpirun -n $1 ./exe) &>> benchmark_file;
