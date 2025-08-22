// noblelib.c - Implementation for noblelib
#include "noblelib.h" // Include the header that defines syscalls, types, and function prototypes

// Syscall wrapper function supporting up to 5 arguments
// Provides a general interface to call Linux syscalls directly from C
long syscall(long number, long arg1, long arg2, long arg3, long arg4, long arg5) {
    long ret; // Variable to store the return value from the syscall

    // Inline assembly to perform the syscall
    __asm__ volatile (
        "mov %1, %%rax\n"   // Move syscall number into rax register (syscall code)
        "mov %2, %%rdi\n"   // Move first argument into rdi register
        "mov %3, %%rsi\n"   // Move second argument into rsi register
        "mov %4, %%rdx\n"   // Move third argument into rdx register
        "mov %5, %%r10\n"   // Move fourth argument into r10 register
        "mov %6, %%r8\n"    // Move fifth argument into r8 register
        "syscall\n"         // Trigger the syscall instruction
        "mov %%rax, %0\n"   // Store syscall return value from rax into ret
        : "=r"(ret)         // Output operand (ret)
        : "r"(number), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5) // Input operands
        : "rax", "rdi", "rsi", "rdx", "r10", "r8" // Clobbered registers (tells compiler these are overwritten)
    );

    return ret; // Return the result of the syscall
}

// Exit program with status code
void exit(int status) {
    // Calls the SYS_EXIT syscall with the provided exit status
    // Other args are 0 because SYS_EXIT only needs one argument
    syscall(SYS_EXIT, status, 0, 0, 0, 0);
}

// Return the length of a null-terminated string
long strlen(const char *s) {
    long len = 0;          // Counter for string length
    while (s[len])          // Iterate until null terminator '\0'
        len++;             // Increment length for each character
    return len;            // Return total length
}

// Print string to a file descriptor
void print(int fd, const char *s) {
    long len = strlen(s);                 // Get string length
    syscall(SYS_WRITE, fd, (long)s, len, 0, 0); // Call SYS_WRITE to write string to fd
}

// Print a string and then print a newline
void println(int fd, const char *s) {
  print(fd, s);
  print(fd, "\n");
}

// Open file and get file descriptor (returns -1 on error)
long open(const char *path, int flags, int mode) {
    // Calls SYS_OPENAT on current working directory (AT_FDCWD)
    return syscall(SYS_OPENAT, AT_FDCWD, (long)path, (long)flags, (long)mode, 0);
}

// Close file descriptor
long close(int fd) {
    // Calls SYS_CLOSE to release the file descriptor
    return syscall(SYS_CLOSE, fd, 0, 0, 0, 0);
}

// Read a line from fd into buffer, up to bufferSize-1 chars, null-terminated
size_t fgets(char *buffer, size_t bufferSize, int fd) {
    if (bufferSize == 0) return 0;  // If buffer has no space, return 0

    size_t i = 0;                   // Index for buffer
    while (i < bufferSize - 1) {    // Leave space for null terminator
        char c;                     // Temp variable to store each character
        long n = syscall(SYS_READ, fd, (long)&c, 1, 0, 0); // Read 1 byte from fd
        if (n <= 0) {               // Check for EOF or error
            break;                  // Stop reading if no more bytes
        }
        buffer[i++] = c;            // Store read character in buffer
        if (c == '\n') {            // Stop reading if newline
            break;
        }
    }
    buffer[i] = '\0';               // Null-terminate the string
    return i;                       // Return number of characters read
}

// Get entries in a directory using SYS_GETDENTS
long getdents(int fd, linuxDirent *dirent, size_t count) {
    // fd: directory file descriptor
    // dirent: buffer to store directory entries
    // count: size of buffer in bytes
    return syscall(SYS_GETDENTS, fd, (long)dirent, count, 0, 0);
}

// Create a directory with given path and mode
long mkdir(const char *path, unsigned int mode) {
    return syscall(SYS_MKDIR, (long)path, (long)mode, 0, 0, 0);
}

// Unlink (delete) file from file system
long deletefd(const char *path) {
    return syscall(SYS_UNLINK, (long)path, 0, 0, 0, 0);
}

// Compare 2 strings, return 0 if equal, <0 if s1<s2, >0 if s1>s2
long stringCompare(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) { // Loop until end of s1 or mismatch
        s1++;                     // Move pointer to next char in s1
        s2++;                     // Move pointer to next char in s2
    }
    return (unsigned char)*s1 - (unsigned char)*s2; // Difference of first non-matching char
}

// Convert string to long integer
long atoi(const char *s) {
    long result = 0;  // Store numeric value
    int sign = 1;     // Track positive or negative

    // Skip whitespace characters
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;

    // Handle optional '+' or '-' sign
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    // Convert digits '0'-'9' to numeric value
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0'); // Shift previous digits left and add new digit
        s++;
    }

    return (result * sign); // Apply sign and return
}

// Convert a long integer to a null-terminated string
// num: the number to convert
// str: buffer to store the resulting string (must be large enough to hold the number and null terminator)
void itoa(long num, char *str) {
    int i = 0;           // Index for str buffer
    int isNegative = 0;  // Flag to handle negative numbers

    // Handle special case of 0 explicitly
    if (num == 0) {
        str[i++] = '0';   // Store '0' as the only digit
        str[i] = '\0';    // Null-terminate the string
        return;
    }

    // If the number is negative, record that and make it positive
    if (num < 0) {
        isNegative = 1;   // Set negative flag
        num = -num;       // Make number positive for conversion
    }

    // Convert each digit to a character (in reverse order)
    while (num > 0) {
        int digit = num % 10;         // Extract last digit
        str[i++] = '0' + digit;       // Convert digit to ASCII and store in buffer
        num = num / 10;               // Remove the last digit from number
    }

    // Add minus sign if the number was negative
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';  // Null-terminate the string

    // Reverse the string in-place to get correct order
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];   // Swap characters at start and end
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

