/*
** EPITECH PROJECT, 2024
** error ouptus tab
** File description:
** my_constants definition
*/

#ifndef MY_CONSTANTS
    #define MY_CONSTANTS
    #include <errno.h>
    #include <stdlib.h>

typedef struct errno_outputs {
    int errnum;
    const char *errmsg;
} errno_outputs_t;

errno_outputs_t const errno_table[] = {
    {E2BIG, "Argument list too long."},
    {EACCES, "Permission denied."},
    {EFAULT, "Bad address."},
    {EINVAL, "Invalid argument."},
    {EIO, "Input/output error."},
    {EISDIR, "Is a directory."},
    {ELIBBAD, "ELF interpreter format error."},
    {ELOOP, "Too many levels of symbolic links."},
    {EMFILE, "Too many open files."},
    {ENAMETOOLONG, "File name too long."},
    {ENFILE, "Too many open files in system."},
    {ENOENT, "No such file or directory."},
    {ENOEXEC, "Exec format error. Binary file not executable."},
    {ENOMEM, "Not enough memory."},
    {ENOTDIR, "Not a directory."},
    {EPERM, "Operation not permitted."},
    {ETXTBSY, "Text file busy."},
    {-1, NULL}
};

#endif /* !MY_CONSTANTS */
