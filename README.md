# Week 10 Formative 2: System Programming & Multithreading Challenges  

---

## Question 1: Strace Analysis  
**Objective**: Analyze system calls for file and process operations in a C program.  
**Code File**: `file_process_ops.c`  

**Compilation & Execution**:  


**Strace Command**:  


**Key System Calls**:  
- **File Operations**: `open`, `read`, `write`, `close`  
- **Process Operations**: `fork`, `execve`, `wait4`  

**Purpose**: Demonstrates kernel-level management of processes and files.  

---

## Question 2: Buffered vs. Unbuffered Copiers  
**Objective**: Compare performance of buffered (`FILE*`) and unbuffered (`read`/`write`) I/O.  

**Code Files**:  
- Buffered: `buffered_copy.c`  
- Unbuffered: `unbuffered_copy.c`  

**Compilation**:  


**Performance Test**:  
1. Generate a 100MB test file:  

2. Measure system calls:  

3. Time execution:  

**Findings**:  
- **Buffered I/O**: Fewer syscalls (batched operations), ~30% faster.  
- **Unbuffered I/O**: More syscalls (per-byte operations), slower due to kernel-mode overhead.  

---

## Question 3: Multi-threaded Prime Counter  
**Objective**: Count primes between 0-10,000 using 20 threads.  

**Code File**: `prime_counter.c`  

**Compilation**:  

**Execution**:  

**Key Features**:  
- **Thread Safety**: Mutex-protected global prime count.  
- **Efficiency**: Divides range into 20 chunks for parallelism.  
- **Prime Check**: Optimized with square-root termination.  

---

## Question 4: Multi-threaded File Copier  
**Objective**: Copy large files using parallel threads.  

**Code File**: `threaded_copy.c`  

**Compilation**:  

### Usage:

Example:

### Key Features:
- **Chunk Division**: Splits files into equal-sized chunks.  
- **Thread Safety**: Uses `lseek` for safe concurrent writes.  
- **Performance**: Optimal thread count is between 4–8 for most systems.

### Performance Analysis:
| Thread Count | Characteristics                          |  
|--------------|------------------------------------------|  
| 1–2          | Minimal overhead, no parallel gain       |  
| 4–8          | Best speed/resource balance              |  
| 16+          | Overhead outweighs benefits              |  

---

## Dependencies:
- GCC compiler.  
- `pthread` library for multithreading.  
- `strace` for syscall analysis.  
- Test file (`big.txt`). 
