// noblelib.c - Implementation for noblelib
#include "noblelib.h"

// Syscall wrapper function supporting up to 5 arguments
long syscall(long number, long arg1, long arg2, long arg3, long arg4, long arg5) {
    long ret;
    __asm__ volatile (
        "mov %1, %%rax\n"   // syscall number
        "mov %2, %%rdi\n"   // arg1
        "mov %3, %%rsi\n"   // arg2
        "mov %4, %%rdx\n"   // arg3
        "mov %5, %%r10\n"   // arg4
        "mov %6, %%r8\n"    // arg5
        "syscall\n"         // call kernel
        "mov %%rax, %0\n"   // store return value
        : "=r"(ret)
        : "r"(number), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5)
        : "rax", "rdi", "rsi", "rdx", "r10", "r8"
    );
    return ret;
}

// Exit program with status code
void exit(int status) {
    syscall(SYS_EXIT, status, 0, 0, 0, 0);
}

// Return the length of a string
long strlen(const char *s) {
    long len = 0;
    while (s[len]) len++;
    return len;
}

// Print string to file descriptor
void print(int fd, const char *s) {
    long len = strlen(s);
    syscall(SYS_WRITE, fd, (long)s, len, 0, 0);
}

// Open file and get file descriptor (return -1 on error)
long open(const char *path, int flags, int mode) {
    return syscall(SYS_OPENAT, AT_FDCWD, (long)path, (long)flags, (long)mode, 0);
}

// Close file descriptor
long close(int fd) {
    return syscall(SYS_CLOSE, fd, 0, 0, 0, 0);
}

// Read a line from fd into buffer, up to bufferSize-1 chars, null-terminated
size_t fgets(int fd, char *buffer, size_t bufferSize) {
    if (bufferSize == 0) return 0;  // no space for anything

    size_t i = 0;
    while (i < bufferSize - 1) {
        char c;
        long n = syscall(SYS_READ, fd, (long)&c, 1, 0, 0);
        if (n <= 0) {
            // EOF or error
            break;
        }
        buffer[i++] = c;
        if (c == '\n') {
            break;
        }
    }
    buffer[i] = '\0'; // null-terminate string
    return i;
}
