# Compile both
gcc buffered_copy.c -o buffered_copy
gcc unbuffered_copy.c -o unbuffered_copy

# Test with a large file (e.g., 100MB)
dd if=/dev/zero of=large.txt bs=1M count=100

# Measure system calls and time
strace -c ./buffered_copy large.txt buffered_copy.txt
strace -c ./unbuffered_copy large.txt unbuffered_copy.txt

time ./buffered_copy large.txt /dev/null
time ./unbuffered_copy large.txt /dev/null
