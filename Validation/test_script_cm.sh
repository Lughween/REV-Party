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

function test_minimaxb {
    RET=0

    if [ -x $CODE/scrutin ]
    then


    rm -rf $VALID/Res_Mini/
    mkdir $VALID/Res_Mini/

	while read i
	do
 	    $CODE/scrutin -i $TEST/$i  -l $LOG/log_${i} -m cm > $VALID/Res_Mini/${i}.txt
	    diff $VALID/ref_cm/$i.txt $VALID/Res_Mini/${i}.txt  &>/dev/null
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <$VALID/file_list_ballots.txt
    else
	RET=2
    fi

}

function test_minimaxd {
    RET=0

    if [ -x $CODE/scrutin ]
    then


    rm -rf $VALID/Res_Mini/
    mkdir $VALID/Res_Mini/

	while read i
	do
 	    $CODE/scrutin -d $TEST/$i  -l $LOG/log_${i} -m cm > $VALID/Res_Mini/${i}.txt
	    diff $VALID/ref_cm/$i.txt $VALID/Res_Mini/${i}.txt  &>/dev/null
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <$VALID/file_list_duels.txt
    else
	RET=2
    fi

}
function test {
    test_$1

    [ $RET -eq 0 ] && printf "===> %-12s [${ok}OK${wipe}]\n" "$1"
    [ $RET -ne 0 ] && printf "xxx> %-12s [${ko}KO${wipe}]\n" "$1"
}

test minimaxb;
test minimaxd;

exit 0
