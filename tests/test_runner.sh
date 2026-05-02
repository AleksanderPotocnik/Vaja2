#!/bin/bash

COMPILER=${COMPILER:-g++}
PASS=0
FAIL=0

$COMPILER -o program Vaja2/main.cpp 2>&1
if [ $? -ne 0 ]; then
    echo "BUILD FAILED s kompilatorjem $COMPILER" >&2
    exit 1
fi

run_test() {
    local ime=$1
    local vhod=$2
    local pricakovano=$3

    echo "$vhod" > test_input.txt
    ./program test_input.txt
    rezultat=$(cat out.txt | tr -s ' ' '\n' | grep -v '^$' | tr '\n' ' ' | sed 's/ $//')

    if [ "$rezultat" = "$pricakovano" ]; then
        echo "PASS: $ime"
        PASS=$((PASS+1))
    else
        echo "FAIL: $ime: pricakovano '$pricakovano', dobljeno '$rezultat'" >&2
        FAIL=$((FAIL+1))
    fi
}

run_test "Ze sortirano"      "1 2 3 4 5"        "1 2 3 4 5"
run_test "Obratno sortirano" "5 4 3 2 1"        "1 2 3 4 5"
run_test "Enaka stevila"     "3 3 3 3"           "3 3 3 3"
run_test "Eno stevilo"       "42"                "42"
run_test "Mesano"            "200 15 8 99 1 128" "1 8 15 99 128 200"

rm -f test_input.txt out.txt program

echo ""
echo "Rezultat: $PASS uspesnih, $FAIL neuspesnih"

if [ $FAIL -gt 0 ]; then
    exit 1
fi
exit 0