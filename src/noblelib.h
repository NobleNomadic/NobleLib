// noblelib.h - Definitions for main noblelib
#ifndef noblelib_h
#define noblelib_h

// Linux syscall numbers for x86_64
#define SYS_EXIT     60  // Program exit
#define SYS_READ     0   // Read from file descriptor
#define SYS_WRITE    1   // Write to a file descriptor
#define SYS_GETDENTS 78  // Get directory entries
#define SYS_MKDIR    83  // Create a directory
#define SYS_UNLINK   87  // Unlink node from filesystem
#define SYS_OPENAT   257 // Open a file
#define SYS_CLOSE    3   // Close a file

#define AT_FDCWD     -100 // Value used to find working directory

// File descriptors
#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define O_WRONLY 1
#define O_CREAT  0100
#define O_EXCL   0200
#define O_RDONLY    0
#define O_DIRECTORY 0200000

// Define types
typedef unsigned long size_t; // Size in bytes data type

// Directory reading
typedef struct {
    unsigned long  d_ino;
    unsigned long  d_off;
    unsigned short d_reclen;
    char           d_name[];
} linuxDirent;

// Function definitions
void exit(int status);                                         // Quit program with status
long strlen(const char *s);                                    // Return the lengeth of a string
void print(int fd, const char *s);                             // Print a string to a fd 
void println(int fd, const char *s);                           // Use print twice to print a string then a new line
long open(const char *path, int flags, int mode);              // Open a file and return fd
long close(int fd);                                            // Close file descriptor
size_t fgets(char *buffer, size_t bufferSize, int fd);         // Get a line of input into buffer
long getdents(int fd, linuxDirent *buf, size_t count);  // Read directory entries
long mkdir(const char *path, unsigned int mode);               // Create new directory
long deletefd(const char *path);                               // Unlink node from file system
long stringCompare(const char *s1, const char *s2);            // String comparison
long atoi(const char *s);                                      // String to int
void itoa(long num, char *str);                                // Convert num to string and put in *str buffer


#endif // noblelib_h
