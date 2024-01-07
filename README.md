# 42_1_Get_next_lin

Program that allows to read and return the next line of a file given its file descriptor.

## Main concept - Static Variables

These variables are initiated at compile time, before the program is executed and not automatically (stack memory) or dynamically (heap memory) as the program is executed. More info in [Wikipedia](https://en.wikipedia.org/wiki/Static_variable)

Static variable are defined via the keyword `static`

If a function is called multiple times, the functions may re-initialise their value. When I have a static variable, the variable is alive for the whole execution and multiple calls of the same function, build on the already existing value. The value doesn't get destroyed or modified when the function that calls it is finished. Moreover, the memory is already allocated, the initialisation is ignored.

The variable works as "a sort of a global variable" with a limited scope
Variables whose values persist through different function calls.

Initializasion of a static variable only happens once

const char *ptr;

ptr = read(fd, str, 1);

## Secondary concepts - open / close / read / write

These concepts where already present in earlier projects, but it is good to refresh its behaviour as it is central to this project.

All the functions are included in the &lt;unistd.h&gt; library

* `int open(const char* path, int flags)` returns an integer value referred to as <u>***file descriptor (fd)***</u>. In case of error it returns a value of -1.

* `size_t read(int fd, void* buffer, size_t count);` stores in `buffer` a maximum of `size_t count` characters. In case of a EOF signal it stops and returns the amount of characters that have been successfully read. Read mantains memory of the last position read. It returns:

  * Number of bytes read on success
  * 0 on reaching the end of file
  * -1 on error
  * -1 on signal interrupt

* `size_t write(int fd, void* buffer, size_t count);` writes in `int fd` a `size_t count` characters from `void* buffer`. It returns:

  * The number of bytes written on success.
  * 0 on reaching the End of File.
  * -1 on error.
  * -1 on signal interrupts.

* `int close(int fd);` closes the file initiated with open and returns 0 on success, and -1 on error.

### File descriptors (fd)

There are 3 standard values that are reserved:
- 0 - STDIN or Standard Input: ;
- 1 - STDOUT or Standard Output: ;
- 2 - STDERR or Standard Error: ;

## Working structure for get_next_line()

### Prototype

```
char *get_next_line(int fd);
```

### Step 1 - Initial input check & sanitization

* `int fd` must be a valid file descriptor with `fd >= 0`.
* `BUFFER_SIZE` must be `BUFFER_SIZE > 0`. The value must be checked as it can be imposed by the user.
* Check that the given file descriptor corresponds to a readable file `read (fd, 0, 0);` is sufficient (passes NULL as buffer).

### Step 2 - Variables definition

* `char *buffer`: sized based on `BUFFER_SIZE` defined in the header file, defines the size of the reading;
* `static char *line`: pointer to the begin of the line;

### Step 3 - Read the input file in buffer

The reading will only get `BUFFER_SIZE` characters, therefore:

* **Option 1**: The buffer is empty -> Return NULL
* **Option 2**: The buffer does not contain EOL nor EOF signals -> repeat the cycle;
* **Option 3**: The buffer contains '\n' or EOF -> return the str, with the required size;

> * <u>**EOL**</u> means <u>End Of Line</u> and is associated to an <u>ASCII value equal to 10</u> or a `char '\n'`
> * <u>**EOF**</u> means <u>End Of File</u> and it is not part of the standards, therefore it does not have an ASCII correspondent. Each operating system (OS) represents it differently, although it is usually associate with a negative value.

### Step 4 - Add content to line and return the desired line

Steps description

## Things to be careful of

### Malloc & free - Memory leaks

#### Malloc usage

* `char *buffer = malloc(sizeof(char) * BUFFER_SIZE)`: At the end of each call of get_next_line() the memory allocated to the buffer must be freed;

As a general strategy:

* Read part of the text and allocate it to buffer;
* `buffer` is joined to a `char *string` via `ft_strjoin(char *s1, char *s2)`;
  * `ft_strjoin` allocates a new memory space, copies s1 + s2 and frees the necessary memories;
* `string` is divided in two parts at the first `'\n'` or in case of EOF, `string` is returned;
  * The first part copies the beginning of `string`;
  * The second part copies the ending part of `string` returning a new `str` with a new memory allocated;
  * A third process is used to free `string`;
