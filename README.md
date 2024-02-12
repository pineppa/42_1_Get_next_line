# Get next line

This set of functions allows to read a part of a file to return the next line of a file, given its file descriptor. The bonus part allows to manage a series of different file descriptors.

## Main concept - Static Variables

These variables are initiated at compile time, before the program is executed and not automatically (stack memory) or dynamically (heap memory) as the program is executed. More info in [Wikipedia](https://en.wikipedia.org/wiki/Static_variable)

Static variable are defined via the keyword `static`

`Get_next_line` works like a generator function, which returns the next is a function is called multiple times, the functions may re-initialise their value. When I have a static variable, the variable is alive for the whole execution and multiple calls of the same function, build on the already existing value. The value doesn't get destroyed or modified when the function that calls it is finished. Moreover, the memory is already allocated, the initialisation is ignored.

The variable works as "a global variable" with a scope limited to the function and are variables whose values persist through different function calls.

Initializasion of a static variable only happens once

```
const char *ptr;

ptr = read(fd, str, 1);
```

## Secondary concepts - open / close / read / write

Working with files was already present in earlier projects, but it is good to refresh the memory on its behaviour as it is central to this project.

All the functions are included in the `<unistd.h>` library apart from `open` that is from `<fcntl.h>`

* `int open(const char* path, int flags)` returns an integer value referred to as <u>***file descriptor (fd)***</u>. In case of error it returns a value of -1.

* `size_t read(int fd, void* buffer, size_t count);` stores in `buffer` a maximum of `size_t count` characters. In case of a EOF signal it stops and returns the amount of characters that have been successfully read. Read mantains memory of the last position read. It returns:

  * `n_bytes` - Number of bytes read on success
  * `0` on reaching the end of file
  * `-1` on error
  * `-1` on signal interrupt

* `size_t write(int fd, void* buffer, size_t count);` writes in `int fd` a `size_t count` characters from `void* buffer`. It returns:

  * `n_bytes` - The number of bytes written on success.
  * `0` on reaching the End of File.
  * `-1` on error.
  * `-1` on signal interrupts.

* `int close(int fd);` closes the file initiated with open and returns 0 on success, and -1 on error.

### File descriptors (fd)

There are 3 standard values that are reserved:
- `0 - STDIN` or Standard Input: ;
- `1 - STDOUT` or Standard Output: ;
- `2 - STDERR` or Standard Error: ;

## Working structure for get_next_line()

### Prototype

```
char *get_next_line(int fd);
```

### Step 1 - Initial input check & sanitization

* `int fd` must be a valid file descriptor with `fd >= 0`.
* `BUFFER_SIZE` must be `BUFFER_SIZE > 0`. The value must be checked as it can be imposed by the user.
* Check that the given file descriptor corresponds to a readable file `read (fd, 0, 0);` is sufficient (passes NULL as buffer).
  * In case of error, this needs to free the static variable as well;

### Step 2 - Variables definition

* `static char *text`: stores the static string with the text already read;
* `char *buffer`: sized based on `BUFFER_SIZE` defined in the header file, defines the size of the reading;
* `char *line`: stores the output line that the function returns;

### Step 3 - Read the input file in buffer

> * <u>**EOL**</u> means <u>End Of Line</u> and is associated to an <u>ASCII value equal to 10</u> or a `char '\n'`
> * <u>**EOF**</u> means <u>End Of File</u> and it is not associated to a character, therefore it does not have an ASCII correspondent. Each operating system (OS) represents it differently, although it is usually associate with a negative value.

The reading will only get `BUFFER_SIZE` characters, therefore:

* **Option 1**: The buffer is empty, we reached the EOF -> Return the str, with the required size;
* **Option 2**: The buffer contains '\n' -> return the str, with the required size;
* **Option 3**: The buffer does not contain EOL nor EOF signals -> repeat the cycle;
* **Option 4**: The read function failed (Ex. the file was closed) -> Free arrays and reinit text to NULL;

At each cycle repetition the chars read and stored in the buff array is joined with the previous text. In case of a char `'/n'` or a read output of 0 we return the text. The EOF can only be catched as a ***read output equal to 0***. In case of errors in fact, read returns a value of -1.

### Step 4 - Add content to line and return the desired line

The next step is a simplified split function that separates the saved text in the output line and the text to be saved. Although this could be achieved with a single function, we split it in two parts to simplify both the logic and the understanding. This requires to be careful in freeing the string only in the text update function.

# ‼️ Things to be careful of ‼️

### Malloc & free - Memory leaks

#### Malloc usage

* `char *buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))`: It is initialised and freed in the same function to avoid possible leaks and complex management. The +1 is added to close the buffer after a read with the `'\0'` in order to have a proper closure of the array;
* `ft_strjoin()` and `ft_update_text()` return a new malloc'd array and should be properly managed. Since it is re-assigned, the input `char *text` must be freed internally.

So, as a general strategy:

* Read part of the text and allocate it to buffer;
* `buffer` is joined to a `char *string` via `ft_strjoin(char *text, char *buff)`;
  * `ft_strjoin` allocates a new memory space, copies text + buff and frees the necessary memories;
* `string` is divided in two parts at the first `'\n'` or in case of EOF, `string` is returned;
  * The first part copies the beginning of `string` to `line`;
  * The second part copies the ending part of `string` returning a new `str` with a new memory allocated and frees the static variable `text` so that at return it is assigned;

#### Bonus: Handling more file descriptors

In order to be able to keep a storage of all the arrays already checked, the function must be supplied with an array of array (pointers) to the different file descriptors previously passed to the function. Risky pitfalls:

* Malloc cannot be used to allocate the array of arrays -> Dynamic allocation only happens at runtime, while the static variable is inizialised at compile time;
* The initial array will have a fixed size. This should ideally allow each `fd` to be saved in memory, although the maximum value may change through different OS; Nice explaination in [stackoverflow](https://stackoverflow.com/questions/35442414/dynamic-vs-static-array-in-c)
* To check on the same PC what are the limitations for file descriptors `fd` run in the terminal `ulimit -Sn` for the soft limit and `ulimit -Hn` for the hard limit;
  * In general, the maximum amount of openable amounts of files is usually set at 10240. This value is also present in the `<limits.h>` library and it is what its used for this project
