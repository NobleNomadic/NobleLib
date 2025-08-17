// noblelib.h - Definitions for main noblelib
#ifndef noblelib_h
#define noblelib_h

// Linux syscall numbers for x86_64
#define SYS_EXIT  60
#define SYS_WRITE 1
#define SYS_OPENAT 257
#define SYS_CLOSE  3
#define AT_FDCWD   -100

// File descriptors
#define STDIN  0
#define STDOUT 1
#define STDERR 2

// Function definitions
void exit(int status);                            // Quit program with status
long strlen(const char *s);                       // Return the lengeth of a string
void print(int fd, const char *s);                // Print a string to a fd 
long open(const char *path, int flags, int mode); // Open a file and return fd
long close(int fd);                               // Close fd

#endif // noblelib_h
