#!/bin/bash

MYSHELL="$PWD/../42sh"
REFER="/bin/tcsh -f"
TRAPSIG=0

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

for i in `env | grep BASH_FUNC_ | cut -d= -f1`; do
    f=`echo $i | sed s/BASH_FUNC_//g | sed s/%%//g`
    unset -f $f
done

if [ $# -lt 1 ]; then
    echo "Usage: $0 <test_file> [test_id]" >&2
    exit 1
fi

TEST_FILE="$1"

if [ ! -f "$TEST_FILE" ]; then
    echo "Test file '$TEST_FILE' not found" >&2
    exit 1
fi

if [ ! -f "$MYSHELL" ]; then
    echo "$MYSHELL not found" >&2
    exit 1
fi

disp_test()
{
  id=$1
  $CAT "$TEST_FILE" | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script()
{
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test()
{
  local testfn="/tmp/.tester.$$"
  local runnerfn="/tmp/.runner.$$"
  local refoutfn="/tmp/.refer.$$"
  local shoutfn="/tmp/.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > \"$shoutfn\" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  echo "/bin/bash -c '$testfn | /bin/tcsh -f ; echo Shell exit with code \$?' > \"$refoutfn\" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

test_passed=0
test_failed=0

load_test()
{
  id=$1
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
  TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
  prepare_test
  $WRAPPER
  nb=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT /tmp/.shell.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $ok -eq 1 ]
  then
    echo "Test $id ($NAME) : ✅"
    test_passed=$((test_passed + 1))
  else
    echo "Test $id ($NAME) : ❌ - Check output in /tmp/test.$$/$id/"
    test_failed=$((test_failed + 1))
    $MKDIR -p /tmp/test.$$/$id 2>/dev/null
    $CP /tmp/.shell.$$ /tmp/test.$$/$id/42sh.out
    $CP /tmp/.refer.$$ /tmp/test.$$/$id/tcsh.out
  fi
}

if [ $# -eq 1 ]; then
  for lst in $(grep "^\[.*\]$" "$TEST_FILE" | grep -vi END | sed 's/\[//' | sed 's/\]//'); do
    path_backup=$PATH
    load_test "$lst"
    export PATH=$path_backup
  done
else
  load_test "$2"
fi

rm -f coucou output.txt
echo "Résumé des tests :"
echo "Tests réussis ✅: $test_passed"
echo "Tests échoués ❌: $test_failed"
