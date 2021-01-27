#!/usr/bin/bash

printf "\n\n========= Starting test run ==========\n\n"

ls

printf "===== Build test =====\n\n"
make test

makefile_res=$?
echo $makefile_res

printf "\n"

tests=$(find ./test/compile/ -type f -name "*.out")

# create valgrind_logs folder

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

EXIT_STATUS=0

# 0 - No error
# 1 - Test failed
# 2 - Mem leak


for e in $tests
do
	# first, run the test

	TEST_COUNTER="($counter/$max)"
	./$e
	EXIT_CODE_1=$?

	if (($EXIT_CODE_1 == 0));
	then
		# now, run valgrind tests

		echo -e "[${GREEN}Success${NC}] ${e} - ${GREEN}Test passed${NC} ${TEST_COUNTER}"

		log_name="$e-log.log"
		valgrind $valgrind_args --log-file=$log_name $e
		VALGRIND_EXIT_CODE=$?

		if (($VALGRIND_EXIT_CODE == 1)); #error found
		then
			EXIT_STATUS=2
			echo -e "[${RED}X${NC}]  ${e} - ${RED}Valgrind detected memory leak${NC} ${TEST_COUNTER}"
		else
			echo -e "[${GREEN}Success${NC}] ${e} - ${GREEN}Valgrind detected no memory leaks${NC} ${TEST_COUNTER}"
		fi
	else
		EXIT_STATUS=1
		echo -e "[${RED}X${NC}] ${e} - ${RED}Test failed${NC} ${TEST_COUNTER}"
		echo "Valgrind test for $e were not performed"
		printf "\n"
	fi

	counter=$(($counter + 1))
done

exit $EXIT_STATUS
