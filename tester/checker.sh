# rem @echo off
# rem g++ -std=c++17 -o test.exe test.cpp
# rem g++ -std=c++17 -o soln.exe soln.cpp
# rem g++ -std=c++17 -o brute.exe brute.cpp
# rem for /l %%x in (1, 1, 100) do (
# rem     test > input.in
# rem     soln < input.in > output.out 
# rem     brute < input.in > output2.out
# rem     fc output.out output2.out > diagnostics || exit /b
# rem     echo %%x
# rem )
# rem echo all tests passed
# rem pause
set -e
g++ -std=c++17 -O2 -Wshadow -Wall -Wextra -Wshift-overflow=2 -fno-sanitize-recover -fstack-protector -o "%e" -g -D_GLIBCXX_DEBUG a.cpp -o a
g++ -std=c++17 test.cpp -o test
g++ -std=c++17 brute.cpp -o brute
for((i = 1; i < 1000; ++i)); do
    ./test $i > input_file
    ./a < input_file > myAnswer
    ./brute < input_file > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer

echo "finished"