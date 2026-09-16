/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** main
*/

#include "Parsing_client.hpp"
#include "Handle_output.hpp"

#include <poll.h>
#include <unistd.h>
#include <iostream>

int main(int ac, char **av)
{
    Parsing_client parse;
    Handle_output handler;

    try {
        if (parse.parse_args(ac, av) == 84)
            return 84;
        int fd = parse.connect_to_server();
        std::cout << parse.recover_output(fd);
        struct pollfd poll_fd[2];
        poll_fd[0] = {STDIN_FILENO, POLLIN, 0};
        poll_fd[1] = {fd, POLLIN, 0};
        while (true) {
            if (poll(poll_fd, 2, -1) < 0)
                throw std::runtime_error("poll failed");
            if (poll_fd[1].revents & (POLLHUP | POLLERR | POLLNVAL))
                break;
            if (poll_fd[1].revents & POLLIN) {
                std::string output = parse.recover_output(fd);
                handler.parse_output(output);
            }
            if (poll_fd[0].revents & POLLIN) {
                std::string msg;
                if (!std::getline(std::cin, msg))
                    break;
                parse.send_command(fd, msg);
            }
        }
        close(fd);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}