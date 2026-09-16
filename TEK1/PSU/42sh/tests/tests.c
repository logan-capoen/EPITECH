#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "exec.h"
#include "format.h"
#include "globbings.h"
#include "input.h"
#include "parser.h"
#include "utilities.h"
#include "builtins.h"

/////////////////////////////////////////////////
///////////////////ALIASES///////////////////////
/////////////////////////////////////////////////
shell_t *init_shell(void)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->history = malloc(sizeof(char *));
    shell->history_size = 0;
    shell->aliases = malloc(sizeof(aliases_t *));
    shell->env = malloc(sizeof(shell_t));
    return shell;
}

Test(alias, display_no_aliases)
{
    shell_t *shell = init_shell();

    cr_redirect_stdout();
    interpret_alias(shell, (char *[]){"alias", NULL}, 0);
    cr_assert_stdout_eq_str("", "Expected no aliases, but got: '%s'", cr_get_redirected_stdout());
}

Test(alias, update_existing_alias)
{
    shell_t *shell = init_shell();

    interpret_alias(shell, (char *[]){"alias", "ls", "list", NULL}, 0);
    interpret_alias(shell, (char *[]){"alias", "ls", "long_list", NULL}, 0);

    cr_redirect_stdout();
    interpret_alias(shell, (char *[]){"alias", NULL}, 0);
    cr_assert_stdout_eq_str("ls\tlong_list\n", "Expected: 'ls\tlong_list\n', but got: '%s'", cr_get_redirected_stdout());
}

Test(alias, insufficient_arguments)
{
    shell_t *shell = init_shell();

    int result = interpret_alias(shell, (char *[]){"alias", "ls", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result: 0, but got: %d", result);
}

Test(alias, no_arguments)
{
    shell_t *shell = init_shell();

    cr_redirect_stdout();
    int result = interpret_alias(shell, (char *[]){"alias", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result: 0, but got: %d", result);
    cr_assert_stdout_eq_str("", "Expected no output, but got: '%s'", cr_get_redirected_stdout());
}

aliases_t *create_alias(const char *original, const char *new_name)
{
    aliases_t *node = malloc(sizeof(aliases_t));
    cr_assert_not_null(node, "Failed to allocate memory for alias node");

    node->original = strdup(original);
    cr_assert_not_null(node->original, "Failed to allocate memory for alias original");

    node->new_name = strdup(new_name);
    cr_assert_not_null(node->new_name, "Failed to allocate memory for alias new_name");

    node->next = NULL;
    return node;
}

Test(handle_alias, add_node)
{
    aliases_t *aliases = NULL;

    aliases_t *node1 = create_alias("ls", "list");
    aliases_t *node2 = create_alias("rm", "remove");
    aliases_t *node3 = create_alias("cd", "change_directory");

    add_node(&aliases, node1);
    add_node(&aliases, node2);
    add_node(&aliases, node3);

    cr_assert_not_null(aliases, "Aliases list should not be NULL");
    cr_assert_str_eq(aliases->original, "cd", "First alias should be 'cd'");
    cr_assert_str_eq(aliases->next->original, "ls", "Second alias should be 'ls'");
    cr_assert_str_eq(aliases->next->next->original, "rm", "Third alias should be 'rm'");
}

Test(handle_alias, delete_node)
{
    aliases_t *aliases = NULL;

    aliases_t *node1 = create_alias("ls", "list");
    aliases_t *node2 = create_alias("rm", "remove");
    aliases_t *node3 = create_alias("cd", "change_directory");

    add_node(&aliases, node1);
    add_node(&aliases, node2);
    add_node(&aliases, node3);

    delete_node(&aliases, aliases, NULL);
    cr_assert_str_eq(aliases->original, "ls", "First alias should now be 'ls'");

    delete_node(&aliases, aliases->next, aliases);
    cr_assert_str_eq(aliases->original, "ls", "Only 'ls' should remain");

    delete_node(&aliases, aliases, NULL);
    cr_assert_null(aliases, "Aliases list should now be empty");
}

Test(handle_alias, free_node)
{
    aliases_t *node = create_alias("ls", "list");

    cr_assert_not_null(node, "Node should not be NULL before freeing");
    cr_assert(1, "Node should be freed without crashing");
}

aliases_t **init_aliases(void)
{
    aliases_t **aliases = malloc(sizeof(aliases_t *));
    cr_assert_not_null(aliases, "Failed to allocate memory for aliases list");

    *aliases = NULL;
    add_node(aliases, create_alias("ls", "list"));
    add_node(aliases, create_alias("rm", "remove"));
    add_node(aliases, create_alias("cd", "change_directory"));

    return aliases;
}

Test(unalias, too_few_arguments)
{
    shell_t sh = {0};
    sh.aliases = init_aliases();

    cr_redirect_stderr();
    int result = interpret_unalias(&sh, (char *[]){"unalias", NULL}, 0);
    cr_assert_eq(result, 1, "Expected result to be 1, but got %d", result);
    cr_assert_stderr_eq_str("unalias: Too few arguments.\n");
}

Test(unalias, valid_alias)
{
    shell_t sh = {0};
    sh.aliases = init_aliases();

    int result = interpret_unalias(&sh, (char *[]){"unalias", "ls", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);

    aliases_t *current = *(sh.aliases);
    while (current) {
        cr_assert_str_neq(current->original, "ls", "Alias 'ls' was not removed");
        current = current->next;
    }
}

Test(unalias, non_existent_alias)
{
    shell_t sh = {0};
    sh.aliases = init_aliases();

    int result = interpret_unalias(&sh, (char *[]){"unalias", "nonexistent", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);

    cr_assert_str_eq((*(sh.aliases))->original, "cd", "Aliases list was unexpectedly modified");
    cr_assert_str_eq((*(sh.aliases))->next->original, "ls", "Aliases list was unexpectedly modified");
    cr_assert_str_eq((*(sh.aliases))->next->next->original, "rm", "Aliases list was unexpectedly modified");
}

Test(unalias, multiple_aliases)
{
    shell_t sh = {0};
    sh.aliases = init_aliases();

    int result = interpret_unalias(&sh, (char *[]){"unalias", "ls", "rm", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);

    aliases_t *current = *(sh.aliases);
    while (current) {
        cr_assert_str_neq(current->original, "ls", "Alias 'ls' was not removed");
        cr_assert_str_neq(current->original, "rm", "Alias 'rm' was not removed");
        current = current->next;
    }
}

Test(unalias, no_aliases)
{
    shell_t sh = {0};
    sh.aliases = malloc(sizeof(aliases_t *));
    cr_assert_not_null(sh.aliases, "Failed to allocate memory for aliases list");
    *(sh.aliases) = NULL;

    cr_redirect_stderr();
    int result = interpret_unalias(&sh, (char *[]){"unalias", "ls", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);
    cr_assert_null(*(sh.aliases), "Aliases list should still be NULL");
}

Test(add_node, add_to_empty_list)
{
    aliases_t *aliases = NULL;
    aliases_t *new_node = malloc(sizeof(aliases_t));
    new_node->original = strdup("ls");
    new_node->new_name = strdup("list");
    new_node->next = NULL;

    add_node(&aliases, new_node);

    cr_assert_not_null(aliases, "Expected aliases list to not be NULL");
    cr_assert_str_eq(aliases->original, "ls", "Expected alias original to be 'ls', but got '%s'", aliases->original);
    cr_assert_str_eq(aliases->new_name, "list", "Expected alias new_name to be 'list', but got '%s'", aliases->new_name);

    free_node(aliases);
}

Test(add_node, add_to_non_empty_list)
{
    aliases_t *aliases = malloc(sizeof(aliases_t));
    aliases->original = strdup("ls");
    aliases->new_name = strdup("list");
    aliases->next = NULL;

    aliases_t *new_node = malloc(sizeof(aliases_t));
    new_node->original = strdup("cd");
    new_node->new_name = strdup("change_dir");
    new_node->next = NULL;

    add_node(&aliases, new_node);

    cr_assert_not_null(aliases, "Expected aliases list to not be NULL");
    cr_assert_str_eq(aliases->original, "cd", "Expected first alias original to be 'cd', but got '%s'", aliases->original);
    cr_assert_str_eq(aliases->next->original, "ls", "Expected second alias original to be 'ls', but got '%s'", aliases->next->original);

    free_node(aliases->next);
    free_node(aliases);
}

Test(free_node, free_valid_node)
{
    aliases_t *node = malloc(sizeof(aliases_t));
    node->original = strdup("ls");
    node->new_name = strdup("list");
    node->next = NULL;

    free_node(node);

    cr_assert(1, "Freeing a valid node should not crash");
}

Test(delete_node, delete_head_node)
{
    aliases_t *aliases = malloc(sizeof(aliases_t));
    aliases->original = strdup("ls");
    aliases->new_name = strdup("list");
    aliases->next = NULL;

    delete_node(&aliases, aliases, NULL);

    cr_assert_null(aliases, "Expected aliases list to be NULL after deleting the head node");
}

Test(delete_node, delete_middle_node)
{
    aliases_t *aliases = malloc(sizeof(aliases_t));
    aliases->original = strdup("ls");
    aliases->new_name = strdup("list");
    aliases->next = malloc(sizeof(aliases_t));
    aliases->next->original = strdup("cd");
    aliases->next->new_name = strdup("change_dir");
    aliases->next->next = NULL;

    delete_node(&aliases, aliases->next, aliases);

    cr_assert_not_null(aliases, "Expected aliases list to not be NULL");
    cr_assert_null(aliases->next, "Expected aliases list to have no next node after deletion");

    free_node(aliases);
}

Test(interpret_unalias, too_few_arguments)
{
    shell_t shell = {0};
    shell.aliases = malloc(sizeof(aliases_t *));
    *(shell.aliases) = NULL;

    cr_redirect_stderr();
    int result = interpret_unalias(&shell, (char *[]){"unalias", NULL}, 0);
    cr_assert_eq(result, 1, "Expected result to be 1 for too few arguments");
    cr_assert_stderr_eq_str("unalias: Too few arguments.\n");

    free(shell.aliases);
}

Test(interpret_unalias, delete_existing_alias)
{
    shell_t shell = {0};
    shell.aliases = malloc(sizeof(aliases_t *));
    *(shell.aliases) = malloc(sizeof(aliases_t));
    (*(shell.aliases))->original = strdup("ls");
    (*(shell.aliases))->new_name = strdup("list");
    (*(shell.aliases))->next = NULL;

    int result = interpret_unalias(&shell, (char *[]){"unalias", "ls", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result to be 0 for successful alias deletion");
    cr_assert_null(*(shell.aliases), "Expected aliases list to be NULL after deletion");

    free(shell.aliases);
}

Test(interpret_unalias, delete_non_existing_alias)
{
    shell_t shell = {0};
    shell.aliases = malloc(sizeof(aliases_t *));
    *(shell.aliases) = malloc(sizeof(aliases_t));
    (*(shell.aliases))->original = strdup("ls");
    (*(shell.aliases))->new_name = strdup("list");
    (*(shell.aliases))->next = NULL;

    int result = interpret_unalias(&shell, (char *[]){"unalias", "cd", NULL}, 0);
    cr_assert_eq(result, 0, "Expected result to be 0 even if alias does not exist");
    cr_assert_not_null(*(shell.aliases), "Expected aliases list to remain unchanged");

    free_node(*(shell.aliases));
    free(shell.aliases);
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

char **init_fake_env(void)
{
    char **env = malloc(4 * sizeof(char *));
    env[0] = strdup("USER=logan");
    env[1] = strdup("HOME=/home/logan");
    env[2] = strdup("PATH=/usr/bin:/bin");
    env[3] = NULL;
    return env;
}

Test(cd_tilde, handle_tilde_home)
{
    char **env = init_fake_env();

    char *result = handle_tilde("~", env, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "/home/logan", "Expected '/home/logan', but got '%s'", result);
}

Test(cd_tilde, handle_tilde_home_with_subdir)
{
    char **env = init_fake_env();

    char *result = handle_tilde("~/subdir", env, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "/home/logan/subdir", "Expected '/home/logan/subdir', but got '%s'", result);
}

Test(cd_tilde, handle_tilde_username)
{
    char **env = init_fake_env();

    char *result = handle_tilde("~logan", env, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "/home/logan", "Expected '/home/logan', but got '%s'", result);
}

Test(cd_tilde, handle_tilde_previous_dir)
{
    char **env = init_fake_env();

    char *result = handle_tilde("-", env, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "/previous/dir", "Expected '/previous/dir', but got '%s'", result);
}

Test(cd_tilde, handle_tilde_normal_directory)
{
    char **env = init_fake_env();

    char *result = handle_tilde("/normal/dir", env, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "/normal/dir", "Expected '/normal/dir', but got '%s'", result);
}

Test(cd_tilde, handle_tilde_null_directory)
{
    char **env = init_fake_env();

    char *result = handle_tilde(NULL, env, "/previous/dir");
    cr_assert_null(result, "Expected NULL, but got a valid result");
}

Test(cd_tilde, handle_tilde_missing_home)
{
    char **env = malloc(3 * sizeof(char *));
    env[0] = strdup("USER=logan");
    env[1] = strdup("PATH=/usr/local/bin:/usr/bin:/bin");
    env[2] = NULL;

    char *result = handle_tilde("~", env, "/previous/dir");
    cr_assert_null(result, "Expected NULL, but got a valid result");
}

Test(get_home_user, valid_user)
{
    char *result = get_root_home("root");
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "/root");
}

Test(get_home_user, invalid_user)
{
    char *result = get_root_home("nonexistentuser");
    cr_assert_null(result);
}

Test(get_home_user, null_user)
{
    char *result = get_root_home(NULL);
    cr_assert_null(result);
}

Test(get_home_user, empty_user)
{
    char *result = get_root_home("");
    cr_assert_null(result);
}

Test(my_cd, too_many_arguments)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    cr_redirect_stderr();
    int result = my_cd(&shell, (char *[]){"cd", "arg1", "arg2", NULL}, 0);
    cr_assert_eq(result, 1);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
}

Test(my_cd, valid_directory)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.owd = malloc(512);

    int result = my_cd(&shell, (char *[]){"cd", "/tmp", NULL}, 0);
    cr_assert_eq(result, 0);
}

Test(my_cd, invalid_directory)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.owd = malloc(512);

    cr_redirect_stderr();
    int result = my_cd(&shell, (char *[]){"cd", "/nonexistent", NULL}, 0);
    cr_assert_eq(result, 1);
    cr_assert_stderr_eq_str("/nonexistent: No such file or directory.\n");
}

Test(my_cd, not_a_directory)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.owd = malloc(512);

    cr_redirect_stderr();
    int result = my_cd(&shell, (char *[]){"cd", "/etc/hosts", NULL}, 0);
    cr_assert_eq(result, 1);
    cr_assert_stderr_eq_str("/etc/hosts: Not a directory.\n");
}

Test(my_cd, tilde_expansion)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.owd = malloc(512);

    int result = my_cd(&shell, (char *[]){"cd", "~", NULL}, 0);
    cr_assert_eq(result, 0);
}

Test(my_getenv, valid_key)
{
    char **env = init_fake_env();
    char *result = get_value_key("HOME", env);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "/home/logan");
}

Test(my_getenv, invalid_key)
{
    char **env = init_fake_env();
    cr_redirect_stderr();
    char *result = get_value_key("INVALID", env);
    cr_assert_null(result);
    cr_assert_stderr_eq_str("INVALID: Undefined variable.\n");
}

Test(my_getenv, null_key)
{
    char **env = init_fake_env();
    char *result = get_value_key(NULL, env);
    cr_assert_null(result);
}

Test(my_getenv, empty_key)
{
    char **env = init_fake_env();
    char *result = get_value_key("", env);
    cr_assert_null(result);
}

Test(handle_tilde, null_directory)
{
    char *result = handle_tilde(NULL, NULL, "/previous/dir");
    cr_assert_null(result, "Expected NULL for a NULL directory, but got a valid result");
}

Test(handle_tilde, tilde_only)
{
    char *env[] = {"HOME=/home/user", NULL};
    char *result = handle_tilde("~", env, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result for '~', but got NULL");
    cr_assert_str_eq(result, "/home/user", "Expected '/home/user', but got '%s'", result);
    free(result);
}

Test(handle_tilde, tilde_with_path)
{
    char *env[] = {"HOME=/home/user", NULL};
    char *result = handle_tilde("~/documents", env, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result for '~/documents', but got NULL");
    cr_assert_str_eq(result, "/home/user/documents", "Expected '/home/user/documents', but got '%s'", result);
    free(result);
}

Test(handle_tilde, tilde_with_username)
{
    char *result = handle_tilde("~root", NULL, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result for '~root', but got NULL");
    cr_assert_str_eq(result, "/root", "Expected '/root', but got '%s'", result);
    free(result);
}

Test(handle_tilde, previous_directory)
{
    char *result = handle_tilde("-", NULL, "/previous/dir");
    cr_assert_not_null(result, "Expected a valid result for '-', but got NULL");
    cr_assert_str_eq(result, "/previous/dir", "Expected '/previous/dir', but got '%s'", result);
    free(result);
}

// Tests pour get_root_home
Test(get_root_home, valid_user)
{
    char *result = get_root_home("root");
    cr_assert_not_null(result, "Expected a valid result for 'root', but got NULL");
    cr_assert_str_eq(result, "/root", "Expected '/root', but got '%s'", result);
    free(result);
}

Test(get_root_home, invalid_user)
{
    char *result = get_root_home("nonexistent_user");
    cr_assert_null(result, "Expected NULL for a nonexistent user, but got a valid result");
}

Test(my_cd, too_many_arguments_case1)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    cr_redirect_stderr();
    int result = my_cd(&shell, (char *[]){"cd", "arg1", "arg2", NULL}, 0);
    cr_assert_eq(result, 1);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
}

Test(my_cd, valid_directory_case1)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.owd = malloc(512);

    int result = my_cd(&shell, (char *[]){"cd", "/tmp", NULL}, 0);
    cr_assert_eq(result, 0);
}

Test(my_cd, invalid_directory_case1)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.owd = malloc(512);

    cr_redirect_stderr();
    int result = my_cd(&shell, (char *[]){"cd", "/nonexistent", NULL}, 0);
    cr_assert_eq(result, 1);
    cr_assert_stderr_eq_str("/nonexistent: No such file or directory.\n");
}

Test(my_cd, not_a_directory_case1)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.owd = malloc(512);

    cr_redirect_stderr();
    int result = my_cd(&shell, (char *[]){"cd", "/etc/hosts", NULL}, 0);
    cr_assert_eq(result, 1);
    cr_assert_stderr_eq_str("/etc/hosts: Not a directory.\n");
}

// Tests pour get_value_key
Test(get_value_key, valid_key)
{
    char *env[] = {"HOME=/home/user", "PATH=/usr/bin", NULL};
    char *result = get_value_key("HOME", env);
    cr_assert_not_null(result, "Expected a valid result for 'HOME', but got NULL");
    cr_assert_str_eq(result, "/home/user", "Expected '/home/user', but got '%s'", result);
    free(result);
}

Test(get_value_key, invalid_key)
{
    char *env[] = {"HOME=/home/user", "PATH=/usr/bin", NULL};
    char *result = get_value_key("NONEXISTENT", env);
    cr_assert_null(result, "Expected NULL for a nonexistent key, but got a valid result");
}

Test(get_value_key, null_env)
{
    char *result = get_value_key("HOME", NULL);
    cr_assert_null(result, "Expected NULL for a NULL environment, but got a valid result");
}

Test(get_value_key, null_key)
{
    char *env[] = {"HOME=/home/user", "PATH=/usr/bin", NULL};
    char *result = get_value_key(NULL, env);
    cr_assert_null(result, "Expected NULL for a NULL key, but got a valid result");
}

Test(my_env, invalid_argument)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    cr_redirect_stderr();
    int result = my_env(&shell, (char *[]){"env", "invalid_arg", NULL}, 0);
    cr_assert_eq(result, 0);
    cr_assert_stderr_eq_str("env: invalid_arg: No such file or directory\n");
    cr_assert_eq(shell.exit_status, 127);
}

Test(my_env, empty_global_env)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = malloc(sizeof(char *));
    shell.env->global[0] = NULL;

    cr_redirect_stdout();
    int result = my_env(&shell, (char *[]){"env", NULL}, 0);
    cr_assert_eq(result, 0);
    cr_assert_stdout_eq_str("");
}

Test(my_setenv, invalid_variable_name)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    cr_redirect_stderr();
    int result = my_setenv(&shell, (char *[]){"setenv", "1INVALID", "value", NULL}, 0);
    cr_assert_eq(result, 0);
    cr_assert_stderr_eq_str("setenv: Variable name must begin with a letter.\n");
    cr_assert_eq(shell.exit_status, 1);
}

Test(my_setenv, valid_variable)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    int result = my_setenv(&shell, (char *[]){"setenv", "NEW_VAR", "new_value", NULL}, 0);
    cr_assert_eq(result, 0);

    char **env = shell.env->global;
    int found = 0;
    for (int i = 0; env[i]; i++) {
        if (strcmp(env[i], "NEW_VAR=new_value") == 0) {
            found = 1;
            break;
        }
    }
    cr_assert_eq(found, 1);
}

Test(my_setenv, overwrite_variable)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    int result = my_setenv(&shell, (char *[]){"setenv", "HOME", "/new/home", NULL}, 0);
    cr_assert_eq(result, 0);

    char **env = shell.env->global;
    int found = 0;
    for (int i = 0; env[i]; i++) {
        if (strcmp(env[i], "HOME=/new/home") == 0) {
            found = 1;
            break;
        }
    }
    cr_assert_eq(found, 1);
}
Test(my_unsetenv, too_few_arguments)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    cr_redirect_stderr();
    int result = my_unsetenv(&shell, (char *[]){"unsetenv", NULL}, 0);
    cr_assert_eq(result, 0);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
    cr_assert_eq(shell.exit_status, 1);
}

Test(my_unsetenv, valid_variable)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    int result = my_unsetenv(&shell, (char *[]){"unsetenv", "HOME", NULL}, 0);
    cr_assert_eq(result, 1);

    char **env = shell.env->global;
    for (int i = 0; env[i]; i++) {
        cr_assert_str_neq(env[i], "HOME=/home/logan", "HOME was not removed from the environment");
    }
}

Test(my_unsetenv, non_existent_variable)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    int result = my_unsetenv(&shell, (char *[]){"unsetenv", "NON_EXISTENT", NULL}, 0);
    cr_assert_eq(result, 0);

    char **env = shell.env->global;
    cr_assert_str_eq(env[0], "USER=logan", "Environment was unexpectedly modified");
    cr_assert_str_eq(env[1], "HOME=/home/logan", "Environment was unexpectedly modified");
    cr_assert_str_eq(env[2], "PATH=/usr/local/bin:/usr/bin:/bin", "Environment was unexpectedly modified");
}

Test(my_unsetenv, multiple_variables)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    int result = my_unsetenv(&shell, (char *[]){"unsetenv", "HOME", "PATH", NULL}, 0);
    cr_assert_eq(result, 1);

    char **env = shell.env->global;
    for (int i = 0; env[i]; i++) {
        cr_assert_str_neq(env[i], "HOME=/home/logan", "HOME was not removed from the environment");
        cr_assert_str_neq(env[i], "PATH=/usr/local/bin:/usr/bin:/bin", "PATH was not removed from the environment");
    }
}

Test(my_unsetenv, empty_environment)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = malloc(sizeof(char *));
    shell.env->global[0] = NULL;

    int result = my_unsetenv(&shell, (char *[]){"unsetenv", "HOME", NULL}, 0);
    cr_assert_eq(result, 0);
    cr_assert_null(shell.env->global[0], "Environment should still be empty");
}

Test(my_exit, no_arguments)
{
    shell_t shell = {0};
    shell.exit_status = 0;
    shell.run = true;

    cr_redirect_stdout();
    int result = my_exit(&shell, (char *[]){"exit", NULL}, 0);
    cr_assert_eq(result, 0, "Expected exit code to be 0, but got %d", result);
    //cr_assert_stdout_eq_str("exit\n", "Expected 'exit' message, but got something else");
    cr_assert_eq(shell.run, false, "Expected shell.run to be false, but it is true");
}

Test(my_exit, with_exit_code)
{
    shell_t shell = {0};
    shell.exit_status = 0;
    shell.run = true;

    cr_redirect_stdout();
    int result = my_exit(&shell, (char *[]){"exit", "42", NULL}, 0);
    cr_assert_eq(result, 42, "Expected exit code to be 42, but got %d", result);
    //cr_assert_stdout_eq_str("exit\n", "Expected 'exit' message, but got something else");
    cr_assert_eq(shell.run, false, "Expected shell.run to be false, but it is true");
}

Test(my_exit, invalid_exit_code)
{
    shell_t shell = {0};
    shell.exit_status = 0;
    shell.run = true;

    cr_redirect_stdout();
    int result = my_exit(&shell, (char *[]){"exit", "invalid", NULL}, 0);
    cr_assert_eq(result, 0, "Expected exit code to default to 0, but got %d", result);
    //cr_assert_stdout_eq_str("exit\n", "Expected 'exit' message, but got something else");
    cr_assert_eq(shell.run, false, "Expected shell.run to be false, but it is true");
}

Test(history, display_history)
{
    shell_t shell = {0};
    shell.history = malloc(2 * sizeof(char *));
    shell.history[0] = strdup("ls -l");
    shell.history[1] = strdup("cd ..");
    shell.history_size = 2;

    cr_redirect_stdout();
    display_history(&shell, NULL, 0);
    cr_assert_stdout_eq_str("1 ls -l\n2 cd ..\n");
}

Test(history, exec_history_valid_index)
{
    shell_t shell = {0};
    shell.history = malloc(2 * sizeof(char *));
    shell.history[0] = strdup("ls -l");
    shell.history[1] = strdup("cd ..");
    shell.history_size = 2;

    char *result = exec_history(&shell, "!1");
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "ls -l");
}

Test(history, get_history_from_file)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    FILE *fd = fopen("/tmp/.42sh_history", "w");
    fprintf(fd, "ls -l\ncd ..\n");
    fclose(fd);

    cr_redirect_stdout();
    get_history(&shell);
    cr_assert_eq(shell.history_size, 2);
    cr_assert_str_eq(shell.history[0], "ls -l");
    cr_assert_str_eq(shell.history[1], "cd ..");
}

Test(free_history, free_non_empty_history)
{
    char **history = malloc(3 * sizeof(char *));
    history[0] = strdup("ls -l");
    history[1] = strdup("cd ..");
    history[2] = NULL;

    free_history(history, 2);
    cr_assert(1, "Freeing a valid history should not crash");
}

Test(free_history, free_empty_history)
{
    char **history = NULL;
    free_history(history, 0);
    cr_assert(1, "Freeing an empty history should not crash");
}

// Test pour display_history avec un historique contenant des commandes vides
Test(display_history, empty_commands)
{
    shell_t shell = {0};
    shell.history = malloc(2 * sizeof(char *));
    shell.history[0] = strdup("");
    shell.history[1] = strdup("");
    shell.history_size = 2;

    cr_redirect_stdout();
    display_history(&shell, NULL, 0);
    cr_assert_stdout_eq_str("1 \n2 \n", "Expected empty commands to be displayed");

    free_history(shell.history, shell.history_size);
}

// Test pour exec_history avec une commande invalide
Test(exec_history, invalid_command)
{
    shell_t shell = {0};
    shell.history = malloc(2 * sizeof(char *));
    shell.history[0] = strdup("ls -l");
    shell.history[1] = strdup("cd ..");
    shell.history_size = 2;

    cr_redirect_stdout();
    char *result = exec_history(&shell, "!invalid");
    cr_assert_null(result, "Expected NULL for an invalid command");
    cr_assert_stdout_eq_str("invalid: Event not found.\n", "Expected error message for invalid command");

    free_history(shell.history, shell.history_size);
}

// Test pour free_history avec un historique partiellement rempli
Test(free_history, partially_filled_history)
{
    char **history = malloc(3 * sizeof(char *));
    history[0] = strdup("ls -l");
    history[1] = NULL;
    history[2] = NULL;

    free_history(history, 1);
    cr_assert(1, "Freeing a partially filled history should not crash");
}

Test(get_cmd_path, valid_command_in_path)
{
    char **env = init_fake_env();

    char *result = get_cmd_path("ls", env);
    cr_assert_not_null(result, "Expected a valid path for 'ls', but got NULL");
    cr_assert_str_neq(result, "ls", "Expected a full path for 'ls', but got the command itself");
    free(result);
}

Test(get_cmd_path, command_not_in_path)
{
    char **env = init_fake_env();

    char *result = get_cmd_path("nonexistent_command", env);
    cr_assert_null(result, "Expected NULL for a nonexistent command, but got a valid result");
}

Test(get_cmd_path, command_with_absolute_path)
{
    char **env = init_fake_env();

    char *result = get_cmd_path("/bin/ls", env);
    cr_assert_not_null(result, "Expected a valid result for '/bin/ls', but got NULL");
    cr_assert_str_eq(result, "/bin/ls", "Expected '/bin/ls', but got something else");
    free(result);
}

Test(get_cmd_path, empty_command)
{
    char **env = init_fake_env();

    char *result = get_cmd_path("", env);
    cr_assert_null(result, "Expected NULL for an empty command, but got a valid result");
}

Test(get_cmd_path, null_env)
{
    char *result = get_cmd_path("ls", NULL);
    cr_assert_null(result, "Expected NULL for a NULL environment, but got a valid result");
}

Test(get_cmd_path, empty_path_variable)
{
    char **env = malloc(2 * sizeof(char *));
    env[0] = strdup("PATH=");
    env[1] = NULL;

    char *result = get_cmd_path("ls", env);
    cr_assert_null(result, "Expected NULL for an empty PATH variable, but got a valid result");

    free(env[0]);
    free(env);
}

Test(format_input, alias_replacement)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.aliases = malloc(sizeof(aliases_t *));
    *(shell.aliases) = NULL;

    aliases_t *alias = malloc(sizeof(aliases_t));
    alias->original = strdup("ls");
    alias->new_name = strdup("list");
    alias->next = NULL;
    *(shell.aliases) = alias;

    char *result = format_input("ls", &shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "list", "Expected 'list', but got '%s'", result);
}

Test(format_input, environment_variable_expansion)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    char *result = format_input("$HOME", &shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "/home/logan", "Expected '/home/logan', but got '%s'", result);
}

// Test(format_input, globbing_expansion)
// {
//     shell_t shell = {0};
//     shell.env = malloc(sizeof(env_t));
//     shell.env->global = init_fake_env();

//     cr_redirect_stdout();
//     char *result = format_input("*.c", &shell);
//     cr_assert_not_null(result, "Expected a valid result, but got NULL");

//     // Vérifie que la sortie standard contient quelque chose
//     const char *stdout_content = cr_get_redirected_stdout();
//     cr_assert(strlen(stdout_content) > 0, "Expected globbing output, but got empty stdout");

//     free(result);
//     free(shell.env->global);
//     free(shell.env);
// }

Test(format_input, history_expansion)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.history = malloc(2 * sizeof(char *));
    shell.history[0] = strdup("ls -l");
    shell.history[1] = NULL;
    shell.history_size = 1;

    char *result = format_input("!1", &shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "ls -l", "Expected 'ls -l', but got '%s'", result);
}

Test(format_input, no_formatting_needed)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();

    char *result = format_input("echo Hello", &shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "echo Hello", "Expected 'echo Hello', but got '%s'", result);
}

Test(get_globbings, valid_pattern_with_matches)
{
    system("touch test_file1.c test_file2.c");
    char *result = get_globbings("*.c");
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert(strlen(result) > 0, "Expected non-empty result, but got an empty string");
    free(result);
    system("rm -f test_file1.c test_file2.c");
}

Test(get_globbings, valid_pattern_no_matches)
{
    char *result = get_globbings("*.nonexistent");
    cr_assert_null(result, "Expected NULL for a pattern with no matches, but got a valid result");
}

Test(get_globbings, invalid_pattern)
{
    char *result = get_globbings("[invalid_pattern");
    cr_assert_null(result, "Expected NULL for an invalid pattern, but got a valid result");
}

Test(get_globbings, empty_pattern)
{
    char *result = get_globbings("");
    cr_assert_null(result, "Expected NULL for an empty pattern, but got a valid result");
}

Test(get_globbings, null_pattern)
{
    char *result = get_globbings(NULL);
    cr_assert_null(result, "Expected NULL for a NULL pattern, but got a valid result");
}

Test(is_gobbling, contains_globbing_characters)
{
    char *str = "file*.c";
    int result = is_gobbling(str);
    cr_assert_eq(result, 1, "Expected 1 for a string containing globbing characters, but got %d", result);
}

Test(is_gobbling, no_globbing_characters)
{
    char *str = "file.c";
    int result = is_gobbling(str);
    cr_assert_eq(result, 0, "Expected 0 for a string without globbing characters, but got %d", result);
}

Test(is_gobbling, empty_string)
{
    char *str = "";
    int result = is_gobbling(str);
    cr_assert_eq(result, 0, "Expected 0 for an empty string, but got %d", result);
}

Test(is_gobbling, multiple_globbing_characters)
{
    char *str = "file[abc]?.c";
    int result = is_gobbling(str);
    cr_assert_eq(result, 1, "Expected 1 for a string containing multiple globbing characters, but got %d", result);
}

Test(check_shortcut, ctrl_a_move_to_start)
{
    input_t input = {
        .str_input = strdup("Hello, World!"),
        .input_len = strlen("Hello, World!"),
        .cursor_pos = 5,
        .char_input = 1 // CTRL-A
    };

    check_shortcut(&input);
    cr_assert_eq(input.cursor_pos, 0, "Expected cursor position to be 0, but got %d", input.cursor_pos);

    free(input.str_input);
}

Test(check_shortcut, ctrl_e_move_to_end)
{
    input_t input = {
        .str_input = strdup("Hello, World!"),
        .input_len = strlen("Hello, World!"),
        .cursor_pos = 5,
        .char_input = 5 // CTRL-E
    };

    check_shortcut(&input);
    cr_assert_eq(input.cursor_pos, input.input_len, "Expected cursor position to be %d, but got %d", input.input_len, input.cursor_pos);

    free(input.str_input);
}

Test(check_shortcut, ctrl_b_move_backward)
{
    input_t input = {
        .str_input = strdup("Hello, World!"),
        .input_len = strlen("Hello, World!"),
        .cursor_pos = 5,
        .char_input = 2 // CTRL-B
    };

    check_shortcut(&input);
    cr_assert_eq(input.cursor_pos, 4, "Expected cursor position to be 4, but got %d", input.cursor_pos);

    free(input.str_input);
}

Test(check_shortcut, ctrl_f_move_forward)
{
    input_t input = {
        .str_input = strdup("Hello, World!"),
        .input_len = strlen("Hello, World!"),
        .cursor_pos = 5,
        .char_input = 6 // CTRL-F
    };

    check_shortcut(&input);
    cr_assert_eq(input.cursor_pos, 6, "Expected cursor position to be 6, but got %d", input.cursor_pos);

    free(input.str_input);
}

Test(check_shortcut, ctrl_t_transpose_characters)
{
    input_t input = {
        .str_input = strdup("Helllo"),
        .input_len = strlen("Helllo"),
        .cursor_pos = strlen("Helllo"),
        .char_input = 20 // CTRL-T
    };

    check_shortcut(&input);
    cr_assert_str_eq(input.str_input, "Hello", "Expected string to be 'Hello', but got '%s'", input.str_input);

    free(input.str_input);
}

Test(check_shortcut, ctrl_l_clear_screen)
{
    input_t input = {
        .str_input = strdup("Hello, World!"),
        .input_len = strlen("Hello, World!"),
        .cursor_pos = 5,
        .char_input = 12 // CTRL-L
    };

    cr_redirect_stdout();
    check_shortcut(&input);
    cr_assert_stdout_eq_str("\033[2J\033[H", "Expected terminal to be cleared, but got something else");

    free(input.str_input);
}

Test(get_input, valid_input)
{
    shell_t shell = {0};
    cr_redirect_stdin();
    cr_redirect_stdout();

    // Simule une entrée utilisateur
    fputs("Hello, World!\n", stdin);
    rewind(stdin);

    char *result = get_input(&shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "Hello, World!", "Expected 'Hello, World!', but got '%s'", result);

    free(result);
}

Test(get_input, ctrl_d_exit)
{
    shell_t shell = {0};
    cr_redirect_stdin();
    cr_redirect_stdout();

    // Simule une entrée utilisateur avec Ctrl+D (EOF)
    fputs("\x04", stdin);
    rewind(stdin);

    char *result = get_input(&shell);
    cr_assert_null(result, "Expected NULL for Ctrl+D input, but got a valid result");
}

Test(get_input, empty_input)
{
    shell_t shell = {0};
    cr_redirect_stdin();
    cr_redirect_stdout();

    // Simule une entrée utilisateur vide
    fputs("\n", stdin);
    rewind(stdin);

    char *result = get_input(&shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "", "Expected an empty string, but got '%s'", result);

    free(result);
}

Test(get_input, input_with_backspace)
{
    shell_t shell = {0};
    cr_redirect_stdin();
    cr_redirect_stdout();

    // Simule une entrée utilisateur avec un backspace
    fputs("Helloo\b\n", stdin); // "Helloo\b" devient "Hello"
    rewind(stdin);

    char *result = get_input(&shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "Hello", "Expected 'Hello', but got '%s'", result);

    free(result);
}

Test(get_input, input_with_shortcuts)
{
    shell_t shell = {0};
    cr_redirect_stdin();
    cr_redirect_stdout();

    // Simule une entrée utilisateur avec des raccourcis (CTRL-A, CTRL-E)
    fputs("\x01Hello\x05, World!\n", stdin); // CTRL-A (début), CTRL-E (fin)
    rewind(stdin);

    char *result = get_input(&shell);
    cr_assert_not_null(result, "Expected a valid result, but got NULL");
    cr_assert_str_eq(result, "Hello, World!", "Expected 'Hello, World!', but got '%s'", result);

    free(result);
}

// Test(handle_sequences, handle_arrow_up)
// {
//     shell_t shell = {0};
//     shell.history = malloc(3 * sizeof(char *));
//     shell.history[0] = strdup("ls");
//     shell.history[1] = strdup("cd ..");
//     shell.history[2] = strdup("pwd");
//     shell.history_size = 3;

//     input_t input = {
//         .str_input = NULL,
//         .input_len = 0,
//         .cursor_pos = 0,
//         .history_pos = 3,
//         .char_input = '\033'
//     };

//     char seq[] = "[A"; // Arrow up sequence
//     int result = handle_sequences(&input, &shell);
//     cr_assert_eq(result, 1, "Expected result to be 1, but got %d", result);
//     cr_assert_str_eq(input.str_input, "pwd", "Expected 'pwd', but got '%s'", input.str_input);

//     free(input.str_input);
//     for (int i = 0; i < shell.history_size; i++)
//         free(shell.history[i]);
//     free(shell.history);
// }

// Test(handle_sequences, handle_arrow_down)
// {
//     shell_t shell = {0};
//     shell.history = malloc(3 * sizeof(char *));
//     shell.history[0] = strdup("ls");
//     shell.history[1] = strdup("cd ..");
//     shell.history[2] = strdup("pwd");
//     shell.history_size = 3;

//     input_t input = {
//         .str_input = strdup("cd .."),
//         .input_len = strlen("cd .."),
//         .cursor_pos = strlen("cd .."),
//         .history_pos = 1,
//         .char_input = '\033'
//     };

//     char seq[] = "[B"; // Arrow down sequence
//     int result = handle_sequences(&input, &shell);
//     cr_assert_eq(result, 1, "Expected result to be 1, but got %d", result);
//     cr_assert_str_eq(input.str_input, "pwd", "Expected 'pwd', but got '%s'", input.str_input);

//     free(input.str_input);
//     for (int i = 0; i < shell.history_size; i++)
//         free(shell.history[i]);
//     free(shell.history);
// }

// Test(handle_sequences, handle_arrow_left)
// {
//     input_t input = {
//         .str_input = strdup("Hello"),
//         .input_len = strlen("Hello"),
//         .cursor_pos = 5,
//         .char_input = '\033'
//     };

//     char seq[] = "[D"; // Arrow left sequence
//     int result = handle_sequences(&input, NULL);
//     cr_assert_eq(result, 1, "Expected result to be 1, but got %d", result);
//     cr_assert_eq(input.cursor_pos, 4, "Expected cursor position to be 4, but got %d", input.cursor_pos);

//     free(input.str_input);
// }

// Test(handle_sequences, handle_arrow_right)
// {
//     input_t input = {
//         .str_input = strdup("Hello"),
//         .input_len = strlen("Hello"),
//         .cursor_pos = 0,
//         .char_input = '\033'
//     };

//     char seq[] = "[C"; // Arrow right sequence
//     int result = handle_sequences(&input, NULL);
//     cr_assert_eq(result, 1, "Expected result to be 1, but got %d", result);
//     cr_assert_eq(input.cursor_pos, 1, "Expected cursor position to be 1, but got %d", input.cursor_pos);

//     free(input.str_input);
// }

// Test(handle_sequences, handle_delete_key)
// {
//     input_t input = {
//         .str_input = strdup("Hello"),
//         .input_len = strlen("Hello"),
//         .cursor_pos = 2,
//         .char_input = '\033'
//     };

//     char seq[] = "[3~"; // Delete key sequence
//     int result = handle_sequences(&input, NULL);
//     cr_assert_eq(result, 1, "Expected result to be 1, but got %d", result);
//     cr_assert_str_eq(input.str_input, "Helo", "Expected 'Helo', but got '%s'", input.str_input);

//     free(input.str_input);
// }

Test(handle_sequences, no_sequence_detected)
{
    input_t input = {
        .str_input = strdup("Hello"),
        .input_len = strlen("Hello"),
        .cursor_pos = 0,
        .char_input = 'a' // Not an escape sequence
    };

    int result = handle_sequences(&input, NULL);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);

    free(input.str_input);
}

Test(init_input, successful_initialization)
{
    shell_t shell = {0};
    shell.history_size = 5;

    input_t *input = NULL;
    int result = init_input(&input, &shell);

    cr_assert_eq(result, 0, "Expected initialization to succeed, but got %d", result);
    cr_assert_not_null(input, "Expected input to be initialized, but got NULL");
    cr_assert_eq(input->char_input, '\0', "Expected char_input to be '\\0', but got '%c'", input->char_input);
    cr_assert_eq(input->cursor_pos, 0, "Expected cursor_pos to be 0, but got %d", input->cursor_pos);
    cr_assert_eq(input->input_len, 0, "Expected input_len to be 0, but got %d", input->input_len);
    cr_assert_null(input->str_input, "Expected str_input to be NULL, but got a valid pointer");
    cr_assert_eq(input->history_pos, shell.history_size, "Expected history_pos to match shell.history_size, but got %d", input->history_pos);
    cr_assert_null(input->stock_history, "Expected stock_history to be NULL, but got a valid pointer");

    free_input(input);
}

Test(init_input, memory_allocation_failure)
{
    shell_t shell = {0};
    input_t *input = NULL;

    // Simule un échec d'allocation mémoire
    cr_redirect_stderr();
    int result = init_input(&input, &shell);
    cr_assert_eq(result, 1, "Expected initialization to fail, but got %d", result);
    cr_assert_null(input, "Expected input to be NULL on failure, but got a valid pointer");
}

Test(free_input, free_null_pointer)
{
    free_input(NULL);
    cr_assert(1, "Freeing a NULL pointer should not crash");
}

Test(free_input, free_valid_input)
{
    shell_t shell = {0};
    shell.history_size = 5;

    input_t *input = NULL;
    init_input(&input, &shell);

    input->str_input = strdup("Test input");
    input->stock_history = strdup("Test history");

    free_input(input);
    cr_assert(1, "Freeing a valid input structure should not crash");
}

Test(manage_input, insert_printable_character)
{
    shell_t shell = {0};
    input_t input = {
        .str_input = strdup("Hello"),
        .input_len = strlen("Hello"),
        .cursor_pos = 5,
        .char_input = '!'
    };

    int result = manage_input(&input, &shell);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);
    cr_assert_str_eq(input.str_input, "Hello!", "Expected 'Hello!', but got '%s'", input.str_input);
    cr_assert_eq(input.input_len, 6, "Expected input_len to be 6, but got %d", input.input_len);
    cr_assert_eq(input.cursor_pos, 6, "Expected cursor_pos to be 6, but got %d", input.cursor_pos);

    free(input.str_input);
}

Test(manage_input, handle_backspace)
{
    shell_t shell = {0};
    input_t input = {
        .str_input = strdup("Hello!"),
        .input_len = strlen("Hello!"),
        .cursor_pos = 6,
        .char_input = 127 // Backspace
    };

    int result = manage_input(&input, &shell);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);
    cr_assert_str_eq(input.str_input, "Hello", "Expected 'Hello', but got '%s'", input.str_input);
    cr_assert_eq(input.input_len, 5, "Expected input_len to be 5, but got %d", input.input_len);
    cr_assert_eq(input.cursor_pos, 5, "Expected cursor_pos to be 5, but got %d", input.cursor_pos);

    free(input.str_input);
}

Test(manage_input, insert_character_in_middle)
{
    shell_t shell = {0};
    input_t input = {
        .str_input = strdup("Helo"),
        .input_len = strlen("Helo"),
        .cursor_pos = 2,
        .char_input = 'l'
    };

    int result = manage_input(&input, &shell);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);
    cr_assert_str_eq(input.str_input, "Hello", "Expected 'Hello', but got '%s'", input.str_input);
    cr_assert_eq(input.input_len, 5, "Expected input_len to be 5, but got %d", input.input_len);
    cr_assert_eq(input.cursor_pos, 3, "Expected cursor_pos to be 3, but got %d", input.cursor_pos);

    free(input.str_input);
}

Test(manage_input, handle_non_printable_character)
{
    shell_t shell = {0};
    input_t input = {
        .str_input = strdup("Hello"),
        .input_len = strlen("Hello"),
        .cursor_pos = 5,
        .char_input = '\n' // Non-printable character
    };

    int result = manage_input(&input, &shell);
    cr_assert_eq(result, 0, "Expected result to be 0, but got %d", result);
    cr_assert_str_eq(input.str_input, "Hello", "Expected 'Hello', but got '%s'", input.str_input);
    cr_assert_eq(input.input_len, 5, "Expected input_len to remain 5, but got %d", input.input_len);
    cr_assert_eq(input.cursor_pos, 5, "Expected cursor_pos to remain 5, but got %d", input.cursor_pos);

    free(input.str_input);
}

Test(manage_input, handle_memory_allocation_failure)
{
    shell_t shell = {0};
    input_t input = {
        .str_input = NULL,
        .input_len = 0,
        .cursor_pos = 0,
        .char_input = 'H'
    };

    // Simule un échec d'allocation mémoire
    cr_redirect_stderr();
    int result = manage_input(&input, &shell);
    cr_assert_eq(result, 1, "Expected result to be 1 (failure), but got %d", result);
    cr_assert_null(input.str_input, "Expected str_input to remain NULL on failure, but got a valid pointer");
}

Test(open_input_fd, valid_file)
{
    commands_t cmd = { .fd_input = -1 };
    char *filename = "/tmp/test_input_file";

    // Crée un fichier temporaire pour le test
    FILE *file = fopen(filename, "w");
    fprintf(file, "Test input data\n");
    fclose(file);

    int fd = open_input_fd(&cmd, filename);
    cr_assert_neq(fd, -1, "Expected a valid file descriptor, but got -1");
    cr_assert_eq(cmd.fd_input, fd, "Expected cmd.fd_input to match the returned file descriptor");

    close(fd);
    remove(filename); // Nettoie le fichier temporaire
}

Test(open_input_fd, invalid_file)
{
    commands_t cmd = { .fd_input = -1 };
    char *filename = "/tmp/nonexistent_file";

    int fd = open_input_fd(&cmd, filename);
    cr_assert_eq(fd, -1, "Expected -1 for an invalid file, but got %d", fd);
}

Test(open_outputfd, valid_file_truncate)
{
    commands_t cmd = { .fd_output = -1 };
    char *filename = "/tmp/test_output_file";

    int fd = open_output_fd(&cmd, true, filename);
    cr_assert_neq(fd, -1, "Expected a valid file descriptor, but got -1");
    cr_assert_eq(cmd.fd_output, fd, "Expected cmd.fd_output to match the returned file descriptor");

    // Vérifie que le fichier est vide (truncation)
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    cr_assert_eq(size, 0, "Expected file to be empty, but its size is %ld", size);

    fclose(file);
    close(fd);
    remove(filename); // Nettoie le fichier temporaire
}

Test(open_outputfd, valid_file_append)
{
    commands_t cmd = { .fd_output = -1 };
    char *filename = "/tmp/test_output_file";

    // Crée un fichier temporaire avec du contenu
    FILE *file = fopen(filename, "w");
    fprintf(file, "Existing data\n");
    fclose(file);

    int fd = open_output_fd(&cmd, false, filename);
    cr_assert_neq(fd, -1, "Expected a valid file descriptor, but got -1");
    cr_assert_eq(cmd.fd_output, fd, "Expected cmd.fd_output to match the returned file descriptor");

    // Vérifie que le contenu existant n'est pas tronqué
    file = fopen(filename, "r");
    char buffer[256] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, file);
    cr_assert_str_eq(buffer, "Existing data\n", "Expected 'Existing data\\n', but got '%s'", buffer);

    fclose(file);
    close(fd);
    remove(filename); // Nettoie le fichier temporaire
}

Test(open_outputfd, invalid_file)
{
    commands_t cmd = { .fd_output = -1 };
    char *filename = "/invalid_path/test_output_file";

    int fd = open_output_fd(&cmd, true, filename);
    cr_assert_eq(fd, -1, "Expected -1 for an invalid file path, but got %d", fd);
}

Test(open_inputfd, valid_file)
{
    commands_t cmd = { .fd_input = -1 };
    char *filename = "/tmp/test_input_file";

    // Crée un fichier temporaire pour le test
    FILE *file = fopen(filename, "w");
    fprintf(file, "Test input data\n");
    fclose(file);

    int fd = open_input_fd(&cmd, filename);
    cr_assert_neq(fd, -1, "Expected a valid file descriptor, but got -1");
    cr_assert_eq(cmd.fd_input, fd, "Expected cmd.fd_input to match the returned file descriptor");

    close(fd);
    remove(filename); // Nettoie le fichier temporaire
}

Test(open_inputfd, invalid_file)
{
    commands_t cmd = { .fd_input = -1 };
    char *filename = "/tmp/nonexistent_file";

    int fd = open_input_fd(&cmd, filename);
    cr_assert_eq(fd, -1, "Expected -1 for an invalid file, but got %d", fd);
}

Test(open_output__fd, valid_file_truncate)
{
    commands_t cmd = { .fd_output = -1 };
    char *filename = "/tmp/test_output_file";

    int fd = open_output_fd(&cmd, true, filename);
    cr_assert_neq(fd, -1, "Expected a valid file descriptor, but got -1");
    cr_assert_eq(cmd.fd_output, fd, "Expected cmd.fd_output to match the returned file descriptor");

    // Vérifie que le fichier est vide (truncation)
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    cr_assert_eq(size, 0, "Expected file to be empty, but its size is %ld", size);

    fclose(file);
    close(fd);
    remove(filename); // Nettoie le fichier temporaire
}

Test(open_outputfdescriptor, valid_file_append)
{
    commands_t cmd = { .fd_output = -1 };
    char *filename = "/tmp/test_output_file";

    // Crée un fichier temporaire avec du contenu
    FILE *file = fopen(filename, "w");
    fprintf(file, "Existing data\n");
    fclose(file);

    int fd = open_output_fd(&cmd, false, filename);
    cr_assert_neq(fd, -1, "Expected a valid file descriptor, but got -1");
    cr_assert_eq(cmd.fd_output, fd, "Expected cmd.fd_output to match the returned file descriptor");

    // Vérifie que le contenu existant n'est pas tronqué
    file = fopen(filename, "r");
    char buffer[256] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, file);
    cr_assert_str_eq(buffer, "Existing data\n", "Expected 'Existing data\\n', but got '%s'", buffer);

    fclose(file);
    close(fd);
    remove(filename); // Nettoie le fichier temporaire
}

Test(open_outputfiled, invalid_file)
{
    commands_t cmd = { .fd_output = -1 };
    char *filename = "/invalid_path/test_output_file";

    int fd = open_output_fd(&cmd, true, filename);
    cr_assert_eq(fd, -1, "Expected -1 for an invalid file path, but got %d", fd);
}

Test(change_separator, update_to_column)
{
    sep_t current_separator = NONE;
    char *line = "echo hello; echo world";
    int index = 11; // Position du ';'

    sep_t result = change_separator(current_separator, line, index);
    cr_assert_eq(result, COLUMN, "Expected COLUMN separator, but got %d", result);
}

Test(change_separator, update_to_and_or)
{
    sep_t current_separator = NONE;
    char *line = "echo hello && echo world";
    int index = 11; // Position du '&&'

    sep_t result = change_separator(current_separator, line, index);
    cr_assert_eq(result, AND_OR, "Expected AND_OR separator, but got %d", result);
}

Test(change_separator, update_to_pipe)
{
    sep_t current_separator = NONE;
    char *line = "echo hello | grep world";
    int index = 11; // Position du '|'

    sep_t result = change_separator(current_separator, line, index);
    cr_assert_eq(result, PIPE, "Expected PIPE separator, but got %d", result);
}

Test(get_highest_separator, column_separator)
{
    char *line = "echo hello; echo world";
    sep_t result = get_highest_separator(line);
    cr_assert_eq(result, COLUMN, "Expected COLUMN separator, but got %d", result);
}

Test(get_highest_separator, and_or_separator)
{
    char *line = "echo hello && echo world";
    sep_t result = get_highest_separator(line);
    cr_assert_eq(result, AND_OR, "Expected AND_OR separator, but got %d", result);
}

Test(get_highest_separator, pipe_separator)
{
    char *line = "echo hello | grep world";
    sep_t result = get_highest_separator(line);
    cr_assert_eq(result, PIPE, "Expected PIPE separator, but got %d", result);
}

Test(get_highest_separator, no_separator)
{
    char *line = "echo hello world";
    sep_t result = get_highest_separator(line);
    cr_assert_eq(result, NONE, "Expected NONE separator, but got %d", result);
}

Test(is_simple_separator, valid_simple_separator)
{
    char current_character = ';';
    sep_t separator = COLUMN;

    int result = is_simple_separator(current_character, separator);
    cr_assert_eq(result, 1, "Expected 1 for a valid simple separator, but got %d", result);
}

Test(is_simple_separator, invalid_simple_separator)
{
    char current_character = '|';
    sep_t separator = COLUMN;

    int result = is_simple_separator(current_character, separator);
    cr_assert_eq(result, 0, "Expected 0 for an invalid simple separator, but got %d", result);
}

Test(is_double_separator, valid_double_separator)
{
    char *line = "echo hello && echo world";
    int current = 11; // Position du '&&'
    sep_t separator = AND_OR;

    int result = is_double_separator(line, &current, separator, true);
    cr_assert_eq(result, 1, "Expected 1 for a valid double separator, but got %d", result);
    cr_assert_eq(current, 12, "Expected current index to be incremented to 12, but got %d", current);
}

Test(is_double_separator, invalid_double_separator)
{
    char *line = "echo hello | grep world";
    int current = 11; // Position du '|'
    sep_t separator = AND_OR;

    int result = is_double_separator(line, &current, separator, true);
    cr_assert_eq(result, 0, "Expected 0 for an invalid double separator, but got %d", result);
    cr_assert_eq(current, 11, "Expected current index to remain 11, but got %d", current);
}

Test(create_command_node, successful_creation)
{
    commands_t *cmd = create_command_node();

    cr_assert_not_null(cmd, "Expected a valid command node, but got NULL");
    cr_assert_eq(cmd->separator, NONE, "Expected separator to be NONE, but got %d", cmd->separator);
    cr_assert_eq(cmd->fd_input, STDIN_FILENO, "Expected fd_input to be STDIN_FILENO, but got %d", cmd->fd_input);
    cr_assert_eq(cmd->fd_output, STDOUT_FILENO, "Expected fd_output to be STDOUT_FILENO, but got %d", cmd->fd_output);

    free(cmd);
}

Test(create_command_node, memory_allocation_failure)
{
    // Simule un échec d'allocation mémoire
    commands_t *cmd = create_command_node();
    cr_assert_null(cmd, "Expected NULL on memory allocation failure, but got a valid pointer");
}

Test(check_input_redirection, valid_redirection)
{
    commands_t cmd = { .fd_input = -1 };
    char *line = strdup("cat < input.txt");
    int index = 4;

    commands_t *result = check_input_redirection(line, &cmd, index);
    cr_assert_not_null(result, "Expected a valid command node, but got NULL");
    cr_assert_neq(cmd.fd_input, -1, "Expected a valid input file descriptor, but got -1");

    free(line);
    close(cmd.fd_input);
}

Test(check_input_redirection, missing_filename)
{
    commands_t cmd = { .fd_input = -1 };
    char *line = strdup("cat < ");
    int index = 4;

    cr_redirect_stderr();
    commands_t *result = check_input_redirection(line, &cmd, index);
    cr_assert_null(result, "Expected NULL due to missing filename, but got a valid pointer");
    cr_assert_stderr_eq_str("Missing name for redirect.\n", "Expected 'Missing name for redirect.' error message");

    free(line);
}

Test(check_output_redirection, valid_redirection_truncate)
{
    commands_t cmd = { .fd_output = -1 };
    char *line = strdup("echo Hello > output.txt");
    int index = 11;

    commands_t *result = check_output_redirection(line, &cmd, &index);
    cr_assert_not_null(result, "Expected a valid command node, but got NULL");
    cr_assert_neq(cmd.fd_output, -1, "Expected a valid output file descriptor, but got -1");

    free(line);
    close(cmd.fd_output);
}

Test(check_output_redirection, valid_redirection_append)
{
    commands_t cmd = { .fd_output = -1 };
    char *line = strdup("echo Hello >> output.txt");
    int index = 11;

    commands_t *result = check_output_redirection(line, &cmd, &index);
    cr_assert_not_null(result, "Expected a valid command node, but got NULL");
    cr_assert_neq(cmd.fd_output, -1, "Expected a valid output file descriptor, but got -1");

    free(line);
    close(cmd.fd_output);
}

Test(check_output_redirection, missing_filename)
{
    commands_t cmd = { .fd_output = -1 };
    char *line = strdup("echo Hello > ");
    int index = 11;

    cr_redirect_stderr();
    commands_t *result = check_output_redirection(line, &cmd, &index);
    cr_assert_null(result, "Expected NULL due to missing filename, but got a valid pointer");
    cr_assert_stderr_eq_str("Missing name for redirect.\n", "Expected 'Missing name for redirect.' error message");

    free(line);
}

Test(handle_no_separator_command, valid_command)
{
    commands_t cmd = {0};
    char *line = strdup("echo Hello, World!");

    commands_t *result = handle_no_separator_command(line, &cmd);
    cr_assert_not_null(result, "Expected a valid command node, but got NULL");
    cr_assert_not_null(result->command, "Expected command array to be initialized, but got NULL");
    cr_assert_str_eq(result->command[0], "echo", "Expected 'echo', but got '%s'", result->command[0]);
    cr_assert_str_eq(result->command[1], "Hello,", "Expected 'Hello,', but got '%s'", result->command[1]);
    cr_assert_str_eq(result->command[2], "World!", "Expected 'World!', but got '%s'", result->command[2]);

    free_array(result->command);
    free(line);
}

Test(handle_no_separator_command, command_with_redirections)
{
    commands_t cmd = {0};
    char *line = strdup("cat < input.txt > output.txt");

    commands_t *result = handle_no_separator_command(line, &cmd);
    cr_assert_not_null(result, "Expected a valid command node, but got NULL");
    cr_assert_neq(cmd.fd_input, -1, "Expected a valid input file descriptor, but got -1");
    cr_assert_neq(cmd.fd_output, -1, "Expected a valid output file descriptor, but got -1");

    close(cmd.fd_input);
    close(cmd.fd_output);
    free(line);
}

Test(nesting_matched_01, valid_parentheses)
{
    char *line = "(echo hello)";
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, true, "Expected true for valid parentheses, but got false");
}

Test(nesting_matched_02, unmatched_closing_parenthesis)
{
    char *line = "echo hello)";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched closing parenthesis, but got true");
    cr_assert_stderr_eq_str("Too many )'s.\n", "Expected 'Too many )'s.' error message, but got something else");
}

Test(nesting_matched_03, unmatched_opening_parenthesis)
{
    char *line = "(echo hello";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched opening parenthesis, but got true");
    cr_assert_stderr_eq_str("Too many ('s.\n", "Expected 'Too many ('s.' error message, but got something else");
}

Test(nesting_matched_04, valid_quotes)
{
    char *line = "'echo hello'";
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, true, "Expected true for valid quotes, but got false");
}

Test(nesting_matched_05, unmatched_single_quote)
{
    char *line = "'echo hello";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched single quote, but got true");
    cr_assert_stderr_eq_str("Unmatched '.\n", "Expected 'Unmatched '.' error message, but got something else");
}

Test(nesting_matched_06, unmatched_double_quote)
{
    char *line = "\"echo hello";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched double quote, but got true");
    cr_assert_stderr_eq_str("Unmatched \".\n", "Expected 'Unmatched \"' error message, but got something else");
}

Test(nesting_matched_07, mixed_valid_nesting)
{
    char *line = "(echo 'hello \"world\"')";
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, true, "Expected true for valid mixed nesting, but got false");
}

Test(nesting_matched_08, mixed_invalid_nesting)
{
    char *line = "(echo 'hello \"world\")'";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for invalid mixed nesting, but got true");
    cr_assert_stderr_eq_str("Too many )'s.\n", "Expected 'Too many )'s.' error message, but got something else");
}

Test(nesting_matched_09, valid_parentheses)
{
    char *line = "(echo hello)";
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, true, "Expected true for valid parentheses, but got false");
}

Test(nesting_matched_10, unmatched_closing_parenthesis)
{
    char *line = "echo hello)";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched closing parenthesis, but got true");
    cr_assert_stderr_eq_str("Too many )'s.\n", "Expected 'Too many )'s.' error message, but got something else");
}

Test(nesting_matched_11, unmatched_opening_parenthesis)
{
    char *line = "(echo hello";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched opening parenthesis, but got true");
    cr_assert_stderr_eq_str("Too many ('s.\n", "Expected 'Too many ('s.' error message, but got something else");
}

Test(nesting_matched_12, valid_quotes)
{
    char *line = "'echo hello'";
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, true, "Expected true for valid quotes, but got false");
}

Test(nesting_matched_13, unmatched_single_quote)
{
    char *line = "'echo hello";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched single quote, but got true");
    cr_assert_stderr_eq_str("Unmatched '.\n", "Expected 'Unmatched '.' error message, but got something else");
}

Test(nesting_matched_14, unmatched_double_quote)
{
    char *line = "\"echo hello";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for unmatched double quote, but got true");
    cr_assert_stderr_eq_str("Unmatched \".\n", "Expected 'Unmatched \"' error message, but got something else");
}

Test(nesting_matched_15, mixed_valid_nesting)
{
    char *line = "(echo 'hello \"world\"')";
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, true, "Expected true for valid mixed nesting, but got false");
}

Test(nesting_matched_16, mixed_invalid_nesting)
{
    char *line = "(echo 'hello \"world\")'";
    cr_redirect_stderr();
    bool result = is_nesting_matched(line);
    cr_assert_eq(result, false, "Expected false for invalid mixed nesting, but got true");
    cr_assert_stderr_eq_str("Too many )'s.\n", "Expected 'Too many )'s.' error message, but got something else");
}

Test(is_valid_pipe_syntax, valid_pipe_syntax)
{
    char *line = "echo hello | grep world";
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 1, "Expected 1 for valid pipe syntax, but got %d", result);
}

Test(is_valid_pipe_syntax, pipe_at_start)
{
    char *line = "| echo hello";
    cr_redirect_stderr();
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for pipe at the start, but got %d", result);
    cr_assert_stderr_eq_str("Invalid null command.\n", "Expected 'Invalid null command.' error message, but got something else");
}

Test(is_valid_pipe_syntax, pipe_at_end)
{
    char *line = "echo hello |";
    cr_redirect_stderr();
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for pipe at the end, but got %d", result);
    cr_assert_stderr_eq_str("Invalid null command.\n", "Expected 'Invalid null command.' error message, but got something else");
}

Test(is_valid_pipe_syntax, consecutive_pipes)
{
    char *line = "echo hello || grep world";
    cr_redirect_stderr();
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for consecutive pipes, but got %d", result);
    cr_assert_stderr_eq_str("Invalid null command.\n", "Expected 'Invalid null command.' error message, but got something else");
}

Test(is_valid_pipe_syntax, valid_pipes_with_quotes)
{
    char *line = "echo 'hello | world' | grep world";
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 1, "Expected 1 for valid pipes with quotes, but got %d", result);
}

Test(is_valid_pipe_syntax, invalid_pipes_with_quotes)
{
    char *line = "echo 'hello | world |' | grep world";
    cr_redirect_stderr();
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for invalid pipes with quotes, but got %d", result);
    cr_assert_stderr_eq_str("Invalid null command.\n", "Expected 'Invalid null command.' error message, but got something else");
}

Test(is_valid_pipe_syntax, empty_line)
{
    char *line = "";
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for an empty line, but got %d", result);
}

Test(is_valid_pipe_syntax, null_line)
{
    char *line = NULL;
    int result = is_valid_pipe_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for a NULL line, but got %d", result);
}

Test(is_valid_syntax, valid_syntax)
{
    char *line = "echo hello | grep world";
    int result = is_valid_syntax(line);
    cr_assert_eq(result, 1, "Expected 1 for valid syntax, but got %d", result);
}

Test(is_valid_syntax, invalid_pipe_syntax)
{
    char *line = "| echo hello";
    cr_redirect_stderr();
    int result = is_valid_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for invalid pipe syntax, but got %d", result);
    cr_assert_stderr_eq_str("Invalid null command.\n", "Expected 'Invalid null command.' error message, but got something else");
}

Test(is_valid_syntax, unmatched_parentheses)
{
    char *line = "(echo hello";
    cr_redirect_stderr();
    int result = is_valid_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for unmatched parentheses, but got %d", result);
    cr_assert_stderr_eq_str("Too many ('s.\n", "Expected 'Too many ('s.' error message, but got something else");
}

Test(is_valid_syntax, unmatched_quotes)
{
    char *line = "'echo hello";
    cr_redirect_stderr();
    int result = is_valid_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for unmatched quotes, but got %d", result);
    cr_assert_stderr_eq_str("Unmatched '.\n", "Expected 'Unmatched '.' error message, but got something else");
}

Test(is_valid_syntax, valid_with_quotes_and_pipes)
{
    char *line = "echo 'hello | world' | grep world";
    int result = is_valid_syntax(line);
    cr_assert_eq(result, 1, "Expected 1 for valid syntax with quotes and pipes, but got %d", result);
}

Test(is_valid_syntax, empty_line)
{
    char *line = "";
    int result = is_valid_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for an empty line, but got %d", result);
}

Test(is_valid_syntax, null_line)
{
    char *line = NULL;
    int result = is_valid_syntax(line);
    cr_assert_eq(result, 0, "Expected 0 for a NULL line, but got %d", result);
}

Test(change_depth, increase_depth)
{
    parsing_state_t state = {0};
    change_depth(&state, '(');
    cr_assert_eq(state.current_depth, 1, "Expected depth to be 1, but got %d", state.current_depth);
}

Test(change_depth, decrease_depth)
{
    parsing_state_t state = { .current_depth = 1 };
    change_depth(&state, ')');
    cr_assert_eq(state.current_depth, 0, "Expected depth to be 0, but got %d", state.current_depth);
}

Test(change_depth, no_change)
{
    parsing_state_t state = { .current_depth = 1 };
    change_depth(&state, 'a');
    cr_assert_eq(state.current_depth, 1, "Expected depth to remain 1, but got %d", state.current_depth);
}

Test(is_nested, not_nested)
{
    parsing_state_t state = {0};
    int result = is_nested(state);
    cr_assert_eq(result, 0, "Expected not nested (0), but got %d", result);
}

Test(is_nested, nested_in_parentheses)
{
    parsing_state_t state = { .current_depth = 1 };
    int result = is_nested(state);
    cr_assert_eq(result, 1, "Expected nested (1), but got %d", result);
}

Test(is_nested, nested_in_quotes)
{
    parsing_state_t state = { .in_single_quote = true };
    int result = is_nested(state);
    cr_assert_eq(result, 1, "Expected nested (1), but got %d", result);
}

Test(change_backtick_and_quotes, toggle_backtick)
{
    parsing_state_t state = {0};
    change_backtick_and_quotes(&state, '`');
    cr_assert_eq(state.in_backtick, true, "Expected in_backtick to be true, but got false");
    change_backtick_and_quotes(&state, '`');
    cr_assert_eq(state.in_backtick, false, "Expected in_backtick to be false, but got true");
}

Test(change_backtick_and_quotes, toggle_single_quote)
{
    parsing_state_t state = {0};
    change_backtick_and_quotes(&state, '\'');
    cr_assert_eq(state.in_single_quote, true, "Expected in_single_quote to be true, but got false");
    change_backtick_and_quotes(&state, '\'');
    cr_assert_eq(state.in_single_quote, false, "Expected in_single_quote to be false, but got true");
}

Test(change_backtick_and_quotes, toggle_double_quote)
{
    parsing_state_t state = {0};
    change_backtick_and_quotes(&state, '\"');
    cr_assert_eq(state.in_double_quote, true, "Expected in_double_quote to be true, but got false");
    change_backtick_and_quotes(&state, '\"');
    cr_assert_eq(state.in_double_quote, false, "Expected in_double_quote to be false, but got true");
}

Test(is_command_inside_parenthesis, valid_parentheses)
{
    char *line = "(echo hello)";
    int result = is_command_inside_parenthesis(line);
    cr_assert_eq(result, 1, "Expected 1 for valid parentheses, but got %d", result);
}

Test(is_command_inside_parenthesis, invalid_parentheses)
{
    char *line = "(echo (hello))";
    int result = is_command_inside_parenthesis(line);
    cr_assert_eq(result, 0, "Expected 0 for invalid parentheses, but got %d", result);
}

Test(is_command_inside_parenthesis, no_parentheses)
{
    char *line = "echo hello";
    int result = is_command_inside_parenthesis(line);
    cr_assert_eq(result, 0, "Expected 0 for no parentheses, but got %d", result);
}

Test(cut_parenthesis, no_outer_parentheses)
{
    char *line = "echo hello";
    char *result = cut_parenthesis(line);
    cr_assert_null(result, "Expected NULL for no outer parentheses, but got a valid result");
}

Test(get_number_subcommands, single_command_no_separator)
{
    char *line = "echo hello";
    int result = get_number_subcommands(NONE, line);
    cr_assert_eq(result, 1, "Expected 1 subcommand, but got %d", result);
}

Test(get_number_subcommands, multiple_commands_with_separator)
{
    char *line = "echo hello; echo world";
    int result = get_number_subcommands(COLUMN, line);
    cr_assert_eq(result, 2, "Expected 2 subcommands, but got %d", result);
}

Test(get_number_subcommands, nested_commands)
{
    char *line = "(echo hello; echo world)";
    int result = get_number_subcommands(COLUMN, line);
    cr_assert_eq(result, 1, "Expected 1 subcommand due to nesting, but got %d", result);
}

Test(get_number_subcommands, empty_line)
{
    char *line = "";
    int result = get_number_subcommands(NONE, line);
    cr_assert_eq(result, 0, "Expected 0 for an empty line, but got %d", result);
}

Test(is_a_builtin_command_which, valid_builtin_command)
{
    cr_redirect_stdout();
    int result = is_a_builtin_command_which("echo");
    cr_assert_eq(result, 1, "Expected 1 for a valid built-in command, but got %d", result);
    cr_assert_stdout_eq_str("echo: shell built-in command.\n", "Expected built-in command message.");
}

Test(is_a_builtin_command_which, invalid_builtin_command)
{
    int result = is_a_builtin_command_which("invalid_command");
    cr_assert_eq(result, 0, "Expected 0 for an invalid built-in command, but got %d", result);
}

// Tests pour interpret_which
Test(interpret_which, too_few_arguments)
{
    shell_t shell = {0};
    char *command[] = {"which", NULL};

    cr_redirect_stderr();
    int result = interpret_which(&shell, command, 0);
    cr_assert_eq(result, 1, "Expected 1 for too few arguments, but got %d", result);
    cr_assert_stderr_eq_str("which: Too few arguments\n", "Expected error message for too few arguments.");
}

// Tests pour is_a_builtin_command_where
Test(is_a_builtin_command_where, valid_builtin_command_case2)
{
    cr_redirect_stdout();
    int result = is_a_builtin_command_where("echo");
    cr_assert_eq(result, 1, "Expected 1 for a valid built-in command, but got %d", result);
    cr_assert_stdout_eq_str("echo is a shell built-in\n", "Expected built-in command message.");
}

Test(is_a_builtin_command_where, invalid_builtin_command_case2)
{
    int result = is_a_builtin_command_where("invalid_command");
    cr_assert_eq(result, 0, "Expected 0 for an invalid built-in command, but got %d", result);
}

// Tests pour interpret_where
Test(interpret_where, too_few_arguments_case2)
{
    shell_t shell = {0};
    char *command[] = {"where", NULL};

    cr_redirect_stderr();
    int result = interpret_where(&shell, command, 0);
    cr_assert_eq(result, 1, "Expected 1 for too few arguments, but got %d", result);
    cr_assert_stderr_eq_str("where: Too few arguments\n", "Expected error message for too few arguments.");
}

Test(interpret_where, command_with_multiple_aliases_and_paths_case2)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.aliases = malloc(sizeof(aliases_t *));
    *(shell.aliases) = NULL;

    aliases_t *alias1 = malloc(sizeof(aliases_t));
    alias1->original = strdup("cmd");
    alias1->new_name = strdup("alias1");
    alias1->next = NULL;
    *(shell.aliases) = alias1;

    aliases_t *alias2 = malloc(sizeof(aliases_t));
    alias2->original = strdup("cmd");
    alias2->new_name = strdup("alias2");
    alias2->next = alias1;
    *(shell.aliases) = alias2;

    char *command[] = {"where", "cmd", NULL};

    cr_redirect_stdout();
    int result = interpret_where(&shell, command, 0);
    cr_assert_eq(result, 0, "Expected 0 for a valid command, but got %d", result);
    cr_assert_stdout_neq_str("", "Expected output for multiple aliases and paths.");

    free(alias1->original);
    free(alias1->new_name);
    free(alias1);
    free(alias2->original);
    free(alias2->new_name);
    free(alias2);
    free(shell.aliases);
    free(shell.env->global);
    free(shell.env);
}

Test(is_a_builtin_command_which, valid_builtin_command_case2)
{
    cr_redirect_stdout();
    int result = is_a_builtin_command_which("echo");
    cr_assert_eq(result, 1, "Expected 1 for a valid built-in command, but got %d", result);
    cr_assert_stdout_eq_str("echo: shell built-in command.\n", "Expected built-in command message.");
}

Test(is_a_builtin_command_which, invalid_builtin_command_case2)
{
    int result = is_a_builtin_command_which("invalid_command");
    cr_assert_eq(result, 0, "Expected 0 for an invalid built-in command, but got %d", result);
}

Test(interpret_which, alias_and_path_command_case2)
{
    shell_t shell = {0};
    shell.env = malloc(sizeof(env_t));
    shell.env->global = init_fake_env();
    shell.aliases = malloc(sizeof(aliases_t *));
    *(shell.aliases) = NULL;

    aliases_t *alias = malloc(sizeof(aliases_t));
    alias->original = strdup("cmd");
    alias->new_name = strdup("alias_cmd");
    alias->next = NULL;
    *(shell.aliases) = alias;

    char *command[] = {"which", "cmd", NULL};

    cr_redirect_stdout();
    int result = interpret_which(&shell, command, 0);
    cr_assert_eq(result, 0, "Expected 0 for a valid alias and path command, but got %d", result);
    cr_assert_stdout_neq_str("", "Expected output for alias and path command.");

    free(alias->original);
    free(alias->new_name);
    free(alias);
    free(shell.aliases);
    free(shell.env->global);
    free(shell.env);
}

Test(is_a_builtin_command_which_case3, valid_builtin_command)
{
    cr_redirect_stdout();
    int result = is_a_builtin_command_which("echo");
    cr_assert_eq(result, 1, "Expected 1 for a valid built-in command, but got %d", result);
    cr_assert_stdout_eq_str("echo: shell built-in command.\n", "Expected built-in command message.");
}

Test(is_a_builtin_command_which_case3, invalid_builtin_command)
{
    int result = is_a_builtin_command_which("invalid_command");
    cr_assert_eq(result, 0, "Expected 0 for an invalid built-in command, but got %d", result);
}

Test(interpret_which_case3, too_few_arguments)
{
    shell_t shell = {0};
    char *command[] = {"which", NULL};

    cr_redirect_stderr();
    int result = interpret_which(&shell, command, 0);
    cr_assert_eq(result, 1, "Expected 1 for too few arguments, but got %d", result);
    cr_assert_stderr_eq_str("which: Too few arguments\n", "Expected error message for too few arguments.");
}

