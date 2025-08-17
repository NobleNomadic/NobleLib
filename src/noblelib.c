// noblelib.c - Implementation for noblelib
#include "noblelib.h"

// Syscall wrapper function
long syscall(long number, long arg1, long arg2, long arg3) {
    long ret;
    __asm__ volatile (
        "mov %1, %%rax\n"   // syscall number
        "mov %2, %%rdi\n"   // arg1
        "mov %3, %%rsi\n"   // arg2
        "mov %4, %%rdx\n"   // arg3
        "syscall\n"         // call kernel
        "mov %%rax, %0\n"   // store return value
        : "=r"(ret)
        : "r"(number), "r"(arg1), "r"(arg2), "r"(arg3)
        : "rax", "rdi", "rsi", "rdx"
    );
    return ret;
}

// Quit program with status code
void exit(int status) {
  syscall(SYS_EXIT, status, 0, 0);
}

// Return the length of a string
long strlen(const char *s) {
  long len = 0;
  while (s[len]) len++;
  return len;
}

// Print to file descriptor
void print(int fd, const char *s) {
  long len = strlen(s);
  syscall(SYS_WRITE, fd, (long)s, len);
}

// Open file and get file descriptor (return -1 on error)
long open(const char *path, int flags, int mode) {
    return syscall(SYS_OPENAT, AT_FDCWD, (long)path, (long)flags, (long)mode);
}

// Close file descriptor
long close(int fd) {
    return syscall(SYS_CLOSE, fd, 0, 0);
}
