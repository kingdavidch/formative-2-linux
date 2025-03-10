gcc file_process_ops.c -o file_process_ops
strace -o trace.txt -e trace=file,process ./file_process_ops
