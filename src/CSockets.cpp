/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CSockets.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mycomputer <mycomputer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:17:16 by belam             #+#    #+#             */
/*   Updated: 2023/06/07 13:17:46 by mycomputer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CSockets.hpp>
#define BUFFER_SIZE 5

using namespace std;

CSockets::CSockets()
{
    _nbSockets = 0;
    _mainSocketFd = -1;
}

CSockets::~CSockets()
{
    destroy();
}

CSockets::CSockets(const CSockets & ref)
{
    *this = ref;
}

CSockets & CSockets::operator=(const CSockets & rhs)
{
    (void) rhs;
    return (*this);
}

CSockets::CSockets(int port)
{
    _nbSockets = 0;
    _mainSocketFd = -1;
    init(port);
}

void CSockets::init(int port)
{
    int             opt = 1;
    
    if (_mainSocketFd != -1)
        cerr << "Double Init, use destroy() first" << endl;
    _mainSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(_mainSocketFd, F_SETFL, O_NONBLOCK);
    if (_mainSocketFd == -1)
    {
        perror("Socket creation error");
        return ;
    }
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(port);
    if (setsockopt(_mainSocketFd, SOL_SOCKET,
                   SO_REUSEADDR, &opt,
                   sizeof(opt)))
        perror("Setsockopt error");
    if (bind(_mainSocketFd, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr)))
        perror("Binding error");
    if (listen(_mainSocketFd, 5))
        perror("listen error");
    _sockets.push_back((pollfd){_mainSocketFd, POLLIN, 0});
    _nbSockets++;
}

void CSockets::update()
{
    socklen_t   len;
    int         new_socket;
    char        buffer[BUFFER_SIZE];
    int         ret;
    size_t      pos;
    
    poll(&_sockets[0], _nbSockets, 10);
    if (_sockets[0].revents)
    {
        len = sizeof(_addr);
        new_socket = accept(_mainSocketFd, reinterpret_cast<sockaddr *>(&_addr), &len);
        _sockets.push_back((pollfd){new_socket, POLLIN | POLLRDHUP, 0});
        fcntl(new_socket, F_SETFL, O_NONBLOCK);
        cout << "Connexion on fd :" << new_socket << endl;
        _nbSockets++;
    }
    _resp.clear();
    for (int i = 1; i < _nbSockets; i++)
    {
        if (_sockets[i].revents & POLLRDHUP)
        {
            disconnect(_sockets[i].fd);
            i--;
        }
        else if (_sockets[i].revents & POLLIN)
        {
            ret = read(_sockets[i].fd, buffer, BUFFER_SIZE - 1);
            if (ret == -1)
                cout << "ERROR" << endl;
            buffer[ret] = '\0';
            // printf("BUFFER = %s\n", buffer);
            _buffers[_sockets[i].fd] += buffer;
            pos = _buffers[_sockets[i].fd].find("\r\n");
            if (pos != string::npos)
            {
                _resp.push_back((Response){_sockets[i].fd, MESSAGE, _buffers[_sockets[i].fd].substr(0, pos)});
                _buffers[_sockets[i].fd] = _buffers[_sockets[i].fd].substr(pos + 2);
            }
        }
    }
}

std::vector<Response> & CSockets::getMsg()
{
    return (_resp);
}

void CSockets::disconnect(int fd)
{
    unsigned int i = 0;

    while (i < _sockets.size() && _sockets[i].fd != fd)
        ++i;
    if (i == _sockets.size())
    {
        cerr << "CSockets : Incorrect Disconnect" << endl;
        return ;
    }
    cout << "Deconnexion on fd :" << fd << endl;
    _nbSockets--;
    _buffers.erase(fd);
    _sockets.erase(_sockets.begin() + i);
}


void CSockets::destroy()
{
    for (int i = 1; i < _nbSockets; i++)
    {
        close(_sockets[i].fd);
    }
    _sockets.clear();
    if (_mainSocketFd != -1)
        shutdown(_mainSocketFd, SHUT_RDWR);
    _mainSocketFd = -1;
    _nbSockets = 0;
    _buffers.clear();
}