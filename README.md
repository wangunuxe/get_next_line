# get_next_line

> *Reading files line by line — because the whole buffer at once is cheating.*

## 📖 About

**get_next_line** is a 42 School project that challenges you to implement
a function that reads a file descriptor line by line, one call at a time.

It sounds simple. It isn't.

Between managing a static buffer across multiple calls, handling multiple
file descriptors simultaneously, and dealing with edge cases like empty
lines or files with no newline at the end — this project teaches you
some of the most important lessons in C:

- How **static variables** persist between function calls
- How **file descriptors** work at a low level
- How to think carefully about **memory management**
- How to handle **edge cases** like a professional

The function you build here will follow you through the rest of the 42 cursus.

---

## 📁 Project Structure

```
get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c        # handles multiple file descriptors
├── get_next_line_utils_bonus.c
└── Makefile                     # (optional, often included in libft)
```

---

## ⚙️ Function Prototype

```c
char *get_next_line(int fd);
```

| Parameter | Description |
|---|---|
| `fd` | The file descriptor to read from |

**Return value:**
- The next line read from `fd`, including the `\n` if present
- `NULL` if there is nothing more to read, or if an error occurred

---

## 🔍 How It Works

The function relies on a **static variable** to retain leftover data
between successive calls — what wasn't part of the current line
gets saved and prepended to the next read.

Here's the general flow:

1. Read from `fd` in chunks of `BUFFER_SIZE` bytes
2. Append each chunk to the static leftover buffer
3. Once a `\n` is found (or EOF is reached), extract the current line
4. Save everything after `\n` into the static buffer for the next call
5. Return the extracted line

```
First call  → reads chunks → finds '\n' → returns line 1, saves the rest
Second call → uses saved rest → finds '\n' → returns line 2
...
Last call   → no more data → returns NULL
```

---

## 🧠 Key Concepts

### BUFFER_SIZE
Defined at compile time, it controls how many bytes are read per
`read()` call. It can be any positive integer:

```bash
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The function must work correctly for any `BUFFER_SIZE`,
from `1` to `10000` and beyond.

---

## 🎯 Bonus — Multiple File Descriptors

The bonus part requires handling **multiple file descriptors at the same time**
without mixing up their respective buffers.

```c
char *line_a = get_next_line(fd1);
char *line_b = get_next_line(fd2);
char *line_c = get_next_line(fd1); // must continue where fd1 left off
```

This is solved by using a **static array** indexed by file descriptor:

```c
static char *leftover[OPEN_MAX];
```

---

## 🛠️ Usage

### Clone the repository
```bash
git clone git@github.com:wangunuxe/get_next_line.git
cd get_next_line
```

### Compile with a custom BUFFER_SIZE
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c -o gnl
```

### Example
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## 🧪 Testing

Community testers to validate your implementation:

- [gnlTester](https://github.com/Tripouille/gnlTester) — the reference tester
- [42cursus-gnl-tests](https://github.com/mrjvs/42cursus-gnl-tests)
- [Francinette](https://github.com/xicodomingues/francinette) — supports GNL too

---

## ⚠️ Edge Cases to Handle

- `BUFFER_SIZE` of `1` or very large values
- Empty file (returns `NULL` on first call)
- File with no newline at the end
- Reading from `stdin` (`fd = 0`)
- Multiple file descriptors open simultaneously (bonus)
- Memory leaks on every path

---

## 📌 Notes

- Compiled with `cc -Wall -Wextra -Werror`
- `BUFFER_SIZE` is defined at compile time with `-D BUFFER_SIZE=n`
- No use of `lseek()` or global variables
- All allocated memory is properly freed — no leaks
- Norm compliant (Norminette)

---

## 👤 Author

**jili** — 42 School
# get_next_line
