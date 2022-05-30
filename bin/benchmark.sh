while getopts 'n:' flag;
do
	case "$flag" in
		n)
			num_processors = "$OPTARG";;
	esac
done

(time mpirun ($num_processors ./exe)) &>> benchmark_file;
