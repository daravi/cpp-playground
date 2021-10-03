cmake --build . --config debug
rr ./bin/test-core-clients --gtest_filter=$1.*
rr replay -s 50505 -k
sleep 3