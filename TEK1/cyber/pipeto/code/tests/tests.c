#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pipeto.h"


void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(activate_emergency_protocols, stdin_correct_password_fmemopen)
{
    IS_ADMIN = false;

    FILE *input_stream = fmemopen("admin123\n", 9, "r");
    cr_assert_not_null(input_stream, "fmemopen failed");

    FILE *original_stdin = stdin;
    stdin = input_stream;

    activate_emergency_protocols();

    cr_assert(IS_ADMIN, "IS_ADMIN should be true after entering the correct password from stdin.");
    stdin = original_stdin;
    fclose(input_stream);
}

Test(activate_emergency_protocols, empty_password)
{
    IS_ADMIN = false;

    FILE *input_stream = fmemopen("\n", 1, "r");
    cr_assert_not_null(input_stream, "fmemopen failed");

    FILE *original_stdin = stdin;
    stdin = input_stream;

    activate_emergency_protocols();

    cr_assert_not(IS_ADMIN, "IS_ADMIN should remain false after entering an incorrect password.");
    stdin = original_stdin;
    fclose(input_stream);
}

Test(activate_emergency_protocols, incorrect_password)
{
    IS_ADMIN = false;

    FILE *input_stream = fmemopen("wrongpassword\n", 14, "r");
    cr_assert_not_null(input_stream, "fmemopen failed");

    FILE *original_stdin = stdin;
    stdin = input_stream;

    activate_emergency_protocols();

    cr_assert_not(IS_ADMIN, "IS_ADMIN should remain false after entering an incorrect password.");
    stdin = original_stdin;
    fclose(input_stream);
}

Test(check_cooling_pressure, valid_pressure_status, .init = redirect_all_std)
{
    check_cooling_pressure();

    fflush(stdout);

    FILE *output = cr_get_redirected_stdout();
    char buffer[1024] = {0};
    fread(buffer, sizeof(char), sizeof(buffer) - 1, output);

    cr_assert(strstr(buffer, "Cooling pressure check in progress...\n") != NULL,
        "Expected 'Cooling pressure check in progress...' in the output.");
    cr_assert(strstr(buffer, "Simulating sensor reading...\n") != NULL,
        "Expected 'Simulating sensor reading...' in the output.");
    cr_assert(strstr(buffer, "Cooling pressure status: Pressure OK\n") != NULL,
        "Expected 'Cooling pressure status: Pressure OK' in the output.");
    cr_assert(strstr(buffer, "Cooling pressure check complete.\n") != NULL,
        "Expected 'Cooling pressure check complete.' in the output.");
}

Test(check_reactor_status, capture_and_inspect_stdout, .init = redirect_all_std)
{
    check_reactor_status();

    fflush(stdout);

    FILE *output = cr_get_redirected_stdout();
    char buffer[1024] = {0};
    fread(buffer, sizeof(char), sizeof(buffer) - 1, output);

    cr_assert(strstr(buffer, "Reactor status: OK") != NULL,
        "Expected 'Reactor status: OK' in the output.");
}

// Test(encrypt_message, encryption_verification)
// {
//     const char *input = "ReactorStatusOK";
//     char output[50] = {0};
//     encrypt_message(input, output, 3);

//     cr_assert_str_eq(output, "UhdfwruVwdwxvRN", "The encryption result is incorrect.");
// }

// Test(encrypt_message, no_shift)
// {
//     const char *input = "ReactorStatusOK";
//     char output[50] = {0};
//     encrypt_message(input, output, 0);

//     cr_assert_str_eq(output, input, "The encryption result with no shift should match the input.");
// }

// Test(encrypt_message, wrap_around)
// {
//     const char *input = "XYZ";
//     char output[50] = {0};
//     encrypt_message(input, output, 3);

//     cr_assert_str_eq(output, "ABC", "The encryption result with wrap-around is incorrect.");
// }

// Test(configure_cooling_system, file_not_found, .init = redirect_all_std)
// {
//     rename("Data/cooling_config.txt", "Data/cooling_config_backup.txt");
//     configure_cooling_system();
//     const char *expected_output = "Error: Unable to open configuration file: Data/cooling_config.txt\n";
//     cr_assert_stdout_eq_str(expected_output, "The output does not match when the configuration file is missing.");
//     rename("Data/cooling_config_backup.txt", "Data/cooling_config.txt");
// }

// Test(configure_cooling_system, valid_configuration, .init = redirect_all_std)
// {
//     FILE *file = fopen("Data/cooling_config.txt", "w");
//     cr_assert_not_null(file, "Failed to create the configuration file.");
//     fprintf(file, "echo 'Cooling system configured!'");
//     fclose(file);

//     configure_cooling_system();

//     const char *expected_output =
//         "Reading configuration file: Data/cooling_config.txt\n"
//         "Applying configuration: echo 'Cooling system configured!'\n"
//         "Cooling system configured!\n"
//         "Configuration applied successfully.\n";
//     cr_assert_stdout_eq_str(expected_output, "The output does not match for a valid configuration.");
// }

// Test(configure_cooling_system, invalid_configuration, .init = redirect_all_std)
// {
//     FILE *file = fopen("Data/cooling_config.txt", "w");
//     cr_assert_not_null(file, "Failed to create the configuration file.");
//     fprintf(file, "invalid_command");
//     fclose(file);

//     configure_cooling_system();

//     const char *expected_output =
//         "Reading configuration file: Data/cooling_config.txt\n"
//         "Applying configuration: invalid_command\n"
//         "Failed to apply configuration. Command returned: 127\n";
//     cr_assert_stdout_eq_str(expected_output, "The output does not match for an invalid configuration.");
// }

// Test(enable_remote_access, enable_access, .init = redirect_all_std)
// {
//     enable_remote_access();

//     const char *expected_output =
//         "Initializing remote access procedure...\n\n"
//         "Enabling remote access...\n"
//         "Performing network call to: http://example.com/api/enable\n"
//         "Network call to http://example.com/api/enable completed.\n"
//         "[...] Remote access status: ENABLED\n"
//         "Remote access successfully enabled.\n\n"
//         "Performing status check...\n"
//         "Performing network call to: http://example.com/api/status\n"
//         "Network call to http://example.com/api/status completed.\n"
//         "Status check complete.\n\n";

//     cr_assert_stdout_eq_str(expected_output, "The output does not match when enabling remote access.");
// }

// Test(enable_remote_access, disable_access, .init = redirect_all_std)
// {
//     enable_remote_access();
//     enable_remote_access();

//     const char *expected_output =
//         "Initializing remote access procedure...\n\n"
//         "Enabling remote access...\n"
//         "Performing network call to: http://example.com/api/enable\n"
//         "Network call to http://example.com/api/enable completed.\n"
//         "[...] Remote access status: ENABLED\n"
//         "Remote access successfully enabled.\n\n"
//         "Performing status check...\n"
//         "Performing network call to: http://example.com/api/status\n"
//         "Network call to http://example.com/api/status completed.\n"
//         "Status check complete.\n\n"
//         "Initializing remote access procedure...\n\n"
//         "Disabling remote access...\n"
//         "Performing network call to: http://example.com/api/disable\n"
//         "Network call to http://example.com/api/disable completed.\n"
//         "[...] Remote access status: DISABLED\n"
//         "Remote access successfully disabled.\n\n";

//     cr_assert_stdout_eq_str(expected_output, "The output does not match when disabling remote access.");
// }

// Test(log_access_attempt, log_enabled_status, .init = redirect_all_std)
// {
//     log_access_attempt("ENABLED");

//     time_t now = time(NULL);
//     char *timestamp = ctime(&now);
//     timestamp[strlen(timestamp) - 1] = '\0';

//     char expected_output[256];
//     snprintf(expected_output, sizeof(expected_output), "[%s] Remote access status: ENABLED\n", timestamp);

//     cr_assert_stdout_eq_str(expected_output, "The log output for ENABLED status does not match.");
// }

// Test(log_access_attempt, log_disabled_status, .init = redirect_all_std)
// {
//     log_access_attempt("DISABLED");

//     time_t now = time(NULL);
//     char *timestamp = ctime(&now);
//     timestamp[strlen(timestamp) - 1] = '\0';

//     char expected_output[256];
//     snprintf(expected_output, sizeof(expected_output), "[%s] Remote access status: DISABLED\n", timestamp);

//     cr_assert_stdout_eq_str(expected_output, "The log output for DISABLED status does not match.");
// }

// Test(help, output_verification, .init = redirect_all_std)
// {
//     help();

//     const char *expected_output =
//         "Available commands :\n"
//         "- init_reactor: Initialize the reactor for operation.\n"
//         "- check_reactor_status: Check the current status of the reactor.\n"
//         "- activate_emergency_protocols: Activate emergency protocols (requires admin).\n"
//         "- simulate_meltdown: Simulate a reactor meltdown for testing purposes.\n"
//         "- check_cooling_pressure: Check the pressure in the cooling system.\n"
//         "- send_status_report: Send a status report to the control center.\n"
//         "- monitor_radiation_levels: Monitor radiation levels in the reactor.\n"
//         "- set_reactor_power: Adjust the reactor's power output.\n"
//         "- run_diagnostic: Run a full diagnostic on the reactor systems.\n"
//         "- enable_remote_access: Enable or disable remote access to the reactor.\n"
//         "- quit: Exit the console.\n"
//         "- help: Display this help message.\n"
//         "- load_fuel_rods: Load fuel rods into the reactor.\n"
//         "- log_system_event: Log a system event.\n"
//         "- history: Display command history.\n"
//         "- !n: Execute command number n from history.\n"
//         "- load_config: Load configuration from a file.\n"
//         "- configure_cooling_system: Configure the cooling system.\n"
//         "---- External libraries ----\n"
//         "- init_steam_turbine: Initialize the turbine.\n"
//         "- read_turbine_config: Read the turbine configuration.\n"
//         "- run_turbine: Run the turbine.\n"
//         "- turbine_temperature: Change the turbine temperature.\n"
//         "- turbine_remote_access: Remote access to the turbine.\n"
//         "\n"
//         "Configuration:\n"
//         "- .pipetorc: Create this file in your home directory or current directory\n"
//         "  to automatically execute commands at startup.\n"
//         "  Use 'exec <command>' to execute shell commands.\n"
//         "\n";

//     cr_assert_stdout_eq_str(expected_output, "The output of help() does not match the expected output.");
// }

// Test(history, init_and_add_commands, .init = redirect_all_std)
// {
//     history_init();

//     history_add("command1");
//     history_add("command2");
//     history_add("command3");

//     cr_assert_eq(history_count_get(), 3, "History count should be 3 after adding 3 commands.");
//     cr_assert_str_eq(history_get(0), "command1", "First command in history should be 'command1'.");
//     cr_assert_str_eq(history_get(1), "command2", "Second command in history should be 'command2'.");
//     cr_assert_str_eq(history_get(2), "command3", "Third command in history should be 'command3'.");

//     history_free();
// }

// Test(history, prevent_duplicate_commands, .init = redirect_all_std)
// {
//     history_init();

//     history_add("command1");
//     history_add("command1");
//     history_add("command2");

//     cr_assert_eq(history_count_get(), 2, "History count should be 2 after adding a duplicate command.");
//     cr_assert_str_eq(history_get(0), "command1", "First command in history should be 'command1'.");
//     cr_assert_str_eq(history_get(1), "command2", "Second command in history should be 'command2'.");

//     history_free();
// }

// Test(history, clear_history, .init = redirect_all_std)
// {
//     history_init();

//     history_add("command1");
//     history_add("command2");
//     history_clear();

//     cr_assert_eq(history_count_get(), 0, "History count should be 0 after clearing history.");

//     history_free();
// }

// Test(history, show_history, .init = redirect_all_std)
// {
//     history_init();

//     history_add("command1");
//     history_add("command2");
//     history_add("command3");

//     history_show();

//     const char *expected_output =
//         " 1  command1\n"
//         " 2  command2\n"
//         " 3  command3\n";

//     cr_assert_stdout_eq_str(expected_output, "The output of history_show() does not match the expected output.");

//     history_free();
// }

// Test(history, get_invalid_index, .init = redirect_all_std)
// {
//     history_init();

//     history_add("command1");
//     history_add("command2");

//     const char *result = history_get(5);
//     cr_assert_null(result, "history_get() should return NULL for an invalid index.");

//     history_free();
// }
