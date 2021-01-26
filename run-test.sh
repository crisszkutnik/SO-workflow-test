printf "\n\n========= Starting test run ==========\n\n"

printf "===== Build test =====\n\n"
make test
printf "\n"

tests=$(find ./test/compile/ -type f -name "*.out")

if [ ! -d valgrind-logs ]; 
then
	mkdir valgrind-logs
fi

valgrind_args="--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1"
counter=1
max=${#valgrind_args[@]}

RED="\033[0;31m"
NC="\033[0m"
GREEN="\033[0;32m"

for e in $tests
do
	log_name="$e-log.log"
	valgrind $valgrind_args --log-file=$log_name $e
	exit_code=$?

	TEST_COUNTER="($counter/$max)"

	if (($exit_code == 1)); #error found
	then
		echo -e "[${RED}X${NC}]  ${e} - ${RED}Test failed${NC} ${TEST_COUNTER}"
	else
		echo -e "[${GREEN}✔${NC}] ${e} - ${GREEN}Test passed${NC} ${TEST_COUNTER}"
	fi

	counter=$(($counter + 1))
done
