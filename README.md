# 42_1_Get_next_line

Program that allows to read and return the next line from a file.

Main concepts:

## Static Variables

These variables are initiated at compile time, before the program is executed and not automatically (stack memory) or dynamically (heap memory) as the program is executed. More info in [Wikipedia](https://en.wikipedia.org/wiki/Static_variable)

Static variable are defined via the keyword `static`

If a function is called multiple times, the functions may re-initialise their value. When I have a static variable, the variable is alive for the whole execution and multiple calls of the same function, build on the already existing value. The value doesn't get destroyed or modified when the function that calls it is finished. Moreover, the memory is already allocated, the initialisation is ignored.

The variable works as "a sort of a global variable" with a limited scope
Variables whose values persist through different function calls.

Initializasion of a static variable only happens once

const char *ptr;

ptr = read(fd, str, 1);

## Working structure for get_next_line()

### Prototype

```
char *get_next_line(int fd);
```

### Step 1 - Initial input check & sanitization

* `int fd` must be a valid file descriptor with `fd > 0`.<br>`fd = 0 || 1 || 2` are reserved values for STD_INPUT, STD_ERROR, STD_OUTPUT (double check)
* `BUFFER_SIZE` must be `BUFFER_SIZE > 0`. The value must be checked as it can be imposed by the user.
* Check that the given file descriptor corresponds to a readable file `read (fd, 0, 0);` is sufficient (passes NULL as buffer).

### Step 2 - Variables definition

* `char *buffer`: sized based on `BUFF_SIZE` defined in the header file, defines the size of the reading;
* `static char *line`: pointer to the begin of the line;

### Step 3 - Read the input file in buffer

The reading will only get `BUFF_SIZE` characters, therefore:

* **Option 1**: The buffer is empty -> Return NULL
* **Option 2**: The buffer does not contain EOL nor EOF signals -> repeatthe cyle;
* **Option 3**: The buffer contains '\n' or EOF -> return the str, with the required size;

### Step 4 - Add content to line and return the desired line


