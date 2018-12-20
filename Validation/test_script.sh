#!/bin/bash

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

CODE=../Vote
VALID=.
TEST=$VALID/fich_tests
LOG=$VALID/Log
RET=

rm -rf $LOG
mkdir $LOG
function test_command {
    RET=0

    if [ -x $CODE/scrutin ]
    then
	for i in "-i x" "-i" "-d" "-i -d" "-i -l" "-l" "-m" "-d $TEST/2012.txt -m uni1" "-d $TEST/TESTS/2012.txt -m uni2" "-d $TEST/2012.txt -m bidon";
	do
      $CODE/scrutin $i &> /dev/null
	    RET=$?
	    [ $RET -eq 1 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "scrutin $i"
	    [ $RET -ne 1 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "scrutin $i" && RET=2 && return;
	done
	RET=0
    else
	RET=2
    fi
}

function test_uni1 {
    RET=0

    if [ -x $CODE/scrutin ]
    then


    rm -rf $VALID/Res_Uni1/
    mkdir $VALID/Res_Uni1/

	while read i
	do
 	    $CODE/scrutin -i $TEST/$i  -l $LOG/log_uni1_${i} -m uni1 > $VALID/Res_Uni1/${i}.txt
	    diff $VALID/ref_uni1/$i.txt $VALID/Res_Uni1/${i}.txt  &>/dev/null
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <./$VALID/file_list_ballots.txt
    else
	RET=2
    fi

}

function test_uni2 {
    RET=0

    if [ -x $CODE/scrutin ]
    then


    rm -rf $VALID/Res_Uni2/
    mkdir $VALID/Res_Uni2/

	while read i
	do
 	    $CODE/scrutin -i $TEST/$i  -l $LOG/log_uni2_${i} -m uni2 > $VALID/Res_Uni2/${i}.txt
	    diff $VALID/ref_uni2/$i.txt $VALID/Res_Uni2/${i}.txt  &>/dev/null
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <./$VALID/file_list_ballots.txt
    else
	RET=2
    fi

}

function test {
    test_$1

    [ $RET -eq 0 ] && printf "===> %-12s [${ok}OK${wipe}]\n" "$1"
    [ $RET -ne 0 ] && printf "xxx> %-12s [${ko}KO${wipe}]\n" "$1"
}

test command;
test uni1;
test uni2;

exit 0
