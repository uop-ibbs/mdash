#!/usr/bin/env bash
#
# $Id: test.sh 124 2017-10-23 13:55:21Z dw $
#
# dash test harness
#

MDASH=mdash
AMBER=no
INPUTS=../examples
EXPECTED=.

while [[ $1 == -* ]]; do
    case $1 in
	-mdash)
	    MDASH=$2
	    shift ;;
	-amber)
	    AMBER=yes ;;
	-inputs)
	    INPUTS=$2
	    shift ;;
	-expected)
	    EXPECTED=$2
	    shift ;;
	*)
	    echo "usage: test.sh [-mdash <exe>] [-amber] [-inputs <dir>] [-expected <dir>]"
	    exit 1 ;;
    esac
    shift
done

declare -A TESTS=(
    [hUII_test1]="-q -C -Z -p -i ${INPUTS}/hUII.in"
    [hUII_test2]="-q -C -Z -p -t 20 -i ${INPUTS}/hUII.in"
    [tzd_test1]="-q -C -Z -p -i ${INPUTS}/tzd.in.gz"
    [tzd_test2]="-q -C -Z -p -t 20 -i ${INPUTS}/tzd.in.gz"
    [repex_test1]="-q -x -i ${INPUTS}/repex.in.bz2"
)

if [[ "$AMBER" == "yes" ]]; then
    if [ -x "$(command -v cpptraj)" ]; then
	TESTS+=([avp_test1]="-q -P ${INPUTS}/avp.parm7 -T ${INPUTS}/avp.nc")
	TESTS+=([avp_test2]="-q -P ${INPUTS}/avp.parm7 -T ${INPUTS}/avp.nc -R 2-9 -D phi,psi")
	TESTS+=([avp_test3]="-q -P ${INPUTS}/avp.parm7 -T ${INPUTS}/avp.nc -R 2,3-5,6,7-9")
    else
	echo "Amber tests omitted: cpptraj not found"
    fi
fi

declare -A SIMTESTS=(
    [sim_test1]="-S ${EXPECTED}/hUII_test1.exp ${EXPECTED}/hUII_test2.exp"
    [sim_test2]="-S ${EXPECTED}/hUII_test1.exp ${EXPECTED}/tzd_test2.exp"
)

check() {
  test=$1

  # remove version number, time stamp, cpu times and filename
  tidy() { cat "$@" | head -n -3 | tail -n +3 | grep -v "^file"; }

  tidy ${test}.out > $test.out.$$
  tidy ${EXPECTED}/${test}.exp > $test.exp.$$

  diff ${test}.out.$$ ${test}.exp.$$ > ${test}.diff 2>&1

  if ( [ ! -e ${test}.out.$$ ] || [ ! -e ${test}.exp.$$ ]  || [ -s ${test}.diff ] ); then
      ((nfail++))
      echo "${test}: FAIL - see ${test}.diff for discrepancies"
  else
      ((npass++))
      echo "${test}: PASS"
      rm -f $test.out ${test}.diff
  fi

  rm -f $test.out.$$ $test.exp.$$
}

simcheck() {
  test=$1

  # path components of input files reported by mdash depend on the
  # relative location of the build directory, so remove them
  tidy() { cat "$@" | sed -s 's| [^ ]*/| |'; }

  tidy ${test}.out > $test.out.$$
  diff ${test}.out.$$ ${EXPECTED}/${test}.exp > ${test}.diff 2>&1

  if ( [ ! -e ${test}.out.$$ ] || [ -s ${test}.diff ] ); then
      ((nfail++))
      echo "${test}: FAIL - see ${test}.diff for discrepancies"
  else
      ((npass++))
      echo "${test}: PASS"
      rm -f $test.out ${test}.diff
  fi

  rm -f $test.out.$$
}

npass=0
nfail=0
((ntests=${#TESTS[@]}+${#SIMTESTS[@]}))

for test in "${!TESTS[@]}"; do
    echo "Running ${test}"
    echo "$MDASH ${TESTS[${test}]} -o ${test}.out"
    $MDASH ${TESTS[${test}]} -o ${test}.out
    check ${test}
done

for test in "${!SIMTESTS[@]}"; do
    echo "Running ${test}"
    echo "$MDASH ${SIMTESTS[${test}]} > ${test}.out 2>&1"
    $MDASH ${SIMTESTS[${test}]} > ${test}.out 2>&1
    simcheck ${test}
done

echo "*** PASSED $npass of $ntests tests ***"

if (($nfail > 0)); then
    echo "*** FAILED $nfail of $ntests tests ***"
fi
