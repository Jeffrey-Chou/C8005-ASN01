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
process_tests=("process_spawner" "process_spawner -i 100000" "process_spawner -i 250000" \
"process_spawner -t 5" "process_spawner -t 5 -i 100000" "process_spawner -t 5 -i 250000" \
"process_spawner -t 10" "process_spawner -t 10 -i 100000" "process_spawner -t 10 -i 250000")
process_folders=("process_test" "process_test_i100000" "process_test_i250000" \
 "process_test_t5" "process_test_t5_i100000" "process_test_t5_i250000" \
"process_test_t10" "process_test_t10_i100000" "process_test_t10_i250000")
thread_tests=("thread_spawner" "thread_spawner -i 100000" "thread_spawner -i 250000" \
"thread_spawner -t 5" "thread_spawner -t 5 -i 100000" "thread_spawner -t 5 -i 250000" \
"thread_spawner -t 10" "thread_spawner -t 10 -i 100000" "thread_spawner -t 10 -i 250000")
thread_folders=("thread_test" "thread_test_i100000" "thread_test_i250000" \
"thread_test_t5" "thread_test_t5_i100000" "thread_test_t5_i250000" \
"thread_test_t10" "thread_test_t10_i100000" "thread_test_t10_i250000")
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
