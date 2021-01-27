#!/usr/bin/bash

printf "\n\n========= Starting test run ==========\n\n"

printf "===== Build test =====\n\n"

GET_LINK="https://beto-bot.guidodipietro.repl.co/59332280-fe1d-42c9-8445-36f12ad241fd/"

make test
MAKEFILE_RES=$?

# 4 error code is that it did not compile
if (($MAKEFILE_RES != 0));
then
	if [ ! -z "$1" ] && [ "$1" == "github" ];
	then
		wget --spider "${GET_LINK}$2/$3/&3"
	fi

	exit 3
fi

printf "\n"

tests=$(find ./test/compile/ -type f -name "*.out")

valgrind_args="--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1"
counter=1

max=0


# This is not a good way to do this but it wokrks
for e in ${tests[@]} 
do
	max=$(($max + 1))
done

# No tests to perform. Exit now
if ((max == 0));
then
	exit 0
fi

RED="\033[0;31m"
NC="\033[0m"
GREEN="\033[0;32m"

EXIT_STATUS=0

# 0 - No error
# 1 - Test failed
# 2 - Mem leak

declare -a MEM_LEAK
declare -a TEST_ERROR

#
#
# Start performing tests
#
#

printf "\n\n===== Perform tests =====\n\n"

for e in ${tests[@]}
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
			MEM_LEAK+=($e)
			EXIT_STATUS=2
			printf "[${RED}X${NC}]  ${e} - ${RED}Valgrind detected memory leak${NC} ${TEST_COUNTER}\n\n"
		else
			printf "[${GREEN}Success${NC}] ${e} - ${GREEN}Valgrind detected no memory leaks${NC} ${TEST_COUNTER}\n\n"
		fi
	else
		EXIT_STATUS=1
		TEST_ERROR+=($e)
		echo -e "[${RED}X${NC}] ${e} - ${RED}Test failed${NC} ${TEST_COUNTER}"
		printf "Valgrind test for $e were not performed\n\n"
	fi

	counter=$(($counter + 1))
done

#
# If on GitHub, make request to GitGariol
#

if [ ! -z "$1" ] && [ "$1" == "github" ];
then
	URL_DIR=""

	if ((${#TEST_ERROR[@]} > 0));
	then
		URL_DIR+="&1"

		for e in ${TEST_ERROR[@]}
		do
			PARSED_STR=${e##*/}
			URL_DIR+="*${PARSED_STR[${#PARSED_STR[@]} - 1]}"
		done
	fi

	if ((${#MEM_LEAK[@]} > 0));
	then
		URL_DIR+="&2"

		for e in ${MEM_LEAK[@]}
		do
			PARSED_STR=${e##*/}
			URL_DIR+="*${PARSED_STR[${#PARSED_STR[@]} - 1]}"
		done
	fi

	# $2 -> branch
	# $3 -> commit hash
	FINAL_LINK="${GET_LINK}$2/$3/${URL_DIR}"

	if ((${#URL_DIR} > 0));
	then
		wget --spider $FINAL_LINK
		printf "\n\nRequest: ${FINAL_LINK}\n\n"
	fi
fi

exit $EXIT_STATUS
