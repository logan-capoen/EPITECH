/*
** EPITECH PROJECT, 2025
** criterion_workshop
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

int print_star(void);
int open_utils(int *stdout_fd, int *output_fd);
int close_utils(const int *stdout_fd, const int *output_fd);
char *get_file_content(const char *filename);

Test(print_star, basic_test)
{
    int std_out = -1;
    int fd_out = -1;

    open_utils(&std_out, &fd_out);
    print_star();
    close_utils(&std_out, &fd_out);
    cr_assert_str_eq(get_file_content("test_file.txt"), get_file_content("star.txt"));
}