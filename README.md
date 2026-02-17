
*This project has been created as part of the 42 curriculum by esnavarr.*

## Description

Get Next Line is a project whose goal is to implement a function capable of reading and returning one line at a time from a file descriptor.

A line is defined as a sequence of characters ending with a newline character (\n), except when the end of file is reached without one.

This project focuses on essential C programming concepts, particularly:

- static variables
- dynamic memory management
- file descriptor handling

The function must behave correctly when reading from:

- Regular files
- Standard input
- Any valid file descriptor

And it must also work with any BUFFER_SIZE, including edge cases such as 1, very large values, or values defined at compile time.

## Instructions

### Compilation

Compile the project using:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=n get_next_line_utils.c get_next_line.c

## Mandatory files:

- get_next_line.c
- get_next_line_utils.c
- get_next_line.h

Bonus files (optional):

- get_next_line_bonus.c
- get_next_line_utils_bonus.c
- get_next_line_bonus.h

## Algorithm explanation & justification

The goal of the algorithm is to read a file one line at a time while respecting the project constraints:

- Reading only what is necessary
- Avoiding global variables
- Correctly managing memory
- Preserving unread data between function calls

### 1. Use of a static variable (stash)

The function get_next_line() uses a static pointer called stash:
```c
static char *stash;
```

This variable stores data that has been read from the file descriptor but not yet returned to the user.

This is required because:

- read() does not guarantee that a full line is read in one call
- A line may be split across multiple reads
- Leftover data must persist between function calls

Using a static variable allows the function to preserve this data without using global variables.

### 2. Reading from the file descriptor (read_buffer)

Data is read using a buffer of size BUFFER_SIZE inside a loop.

The helper function read_buffer():

1. Clears the buffer
2. Reads from the file descriptor
3. Appends the buffer content to stash using ft_strjoin

The reading loop stops as soon as:

- A newline character is found in stash
- read() returns 0 (end of file)
- An error occurs

This guarantees that the function never reads more data than necessary.

### 3. Extracting the next line (get_result)

Once stash contains a newline (or EOF is reached), the function:

1. Locates the first \n
2. Allocates a new string
3. Copies characters from the beginning of stash up to and including \n
4. Null-terminates the result

This newly allocated string is returned to the caller as the next line.

If no newline exists but stash still contains data (EOF case), the remaining content is returned as the final line.

### 4. Updating leftover data (remove_result)

After extracting the line, the remaining data in stash must be updated.

The function:

1. Creates a new string containing everything after the newline
2. Frees the old stash
3. Assigns the new string as the updated stash

If no data remains after the newline, stash is freed and set to NULL.

This ensures that:

- No memory is leaked
- Stash always reflects unread data only

### Memory safety and error handling

- Every memory allocation is checked for failure
- Every allocated block has a corresponding free
- The static stash is freed when no longer needed

The user is responsible for freeing the line returned by get_next_line()

The function safely handles:

- Invalid file descriptors
- BUFFER_SIZE <= 0
- Read errors
- End-of-file conditions

### 📌 Bonus (multiple file descriptors)

In the bonus version, stash becomes an array indexed by file descriptor:
```c
static char *stash[MAX_FILES_OPENED];
```

This allows get_next_line() to manage multiple file descriptors simultaneously, each with its own independent buffer.

### Resources

📚 References:

- https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line

- man 2 read

- man 2 open
