#!/usr/bin/bash

printf "\n\n========= Starting test run ==========\n\n"

printf "===== Build test =====\n\n"

GET_LINK="https://beto-bot.guidodipietro.repl.co/59332280-fe1d-42c9-8445-36f12ad241fd/"

make test
MAKEFILE_RES=$?

# 4 error code is that it did not compile
if (($MAKEFILE_RES != 0));
then
	wget "${GET_LINK}4" 
fi

printf "\n"

tests=$(find ./test/compile/ -type f -name "*.out")

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

if [ ! -z "$1" ] && [ "$1" == "github" ];
then
	wget "${GET_LINK}${EXIT_STATUS}"
fi

exit $EXIT_STATUS
