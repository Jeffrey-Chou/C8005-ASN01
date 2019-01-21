#!/bin/sh
make process_spawner
make thread_spawner
run_tests() {
    for i in {1..5}
    do
        echo Starting $testname number $i
        ./$execname
        echo Done Test
    done
    mkdir $testname
    mv *.txt $testname
    mv $testname Output
}
mkdir Output
process_tests=("process_spawner" "process_spawner -i 100000")
process_folders=("process_test" "process_test_i100000")
thread_tests=("thread_spawner" "thread_spawner -i 100000")
thread_folders=("thread_test" "thread_test_i100000")
len=${#process_tests[@]}
for((j=0; j<$len;++j))
do
    execname=${process_tests[$j]}
    testname=${process_folders[$j]}
    run_tests
    execname=${thread_tests[$j]}
    testname=${thread_folders[$j]}
    run_tests
done
#execname="process_spawner -i 100000"
#testname="process_spawner -i 100000"
#run_tests
#testname="thread_spawner -i 100000"
#run_tests
