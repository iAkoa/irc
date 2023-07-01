/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CSockets.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mycomputer <mycomputer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:40:53 by belam             #+#    #+#             */
/*   Updated: 2023/06/09 16:09:13 by mycomputer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSOCKETS_HPP
# define CSOCKETS_HPP
# include <poll.h>
# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdio.h> // Uniquement pour les perrors a retirer quand throw
# include <fcntl.h>
# include <map>
# include <vector>

// #ifndef POLLRDHUP
// #define POLLRDHUP 0x2000
// #endif

#define MESSAGE 1
struct Response
{
    int fd;
    int type;
    std::string msg;
};
class CSockets
{
public:

    class socketException : public std::exception
    {
        const char *what() const throw();
        const char *what(std::string) const throw();
    };

    CSockets();
    ~CSockets();
    CSockets(const CSockets & ref);
    CSockets & operator=(const CSockets & rhs);

    CSockets(int port);
    void                    init(int port);
    void                    update();
    std::vector<Response>   &getMsg();
    void                    disconnect(int fd);
    void                    destroy();

private:
    int                         _nbSockets;
    int                         _mainSocketFd;
    std::vector<struct pollfd>  _sockets;
    std::map<int, std::string>  _buffers;
    std::vector<Response>       _resp;
    struct sockaddr_in          _addr;
};

#endif