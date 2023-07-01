/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mim.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:04 by iel-amra          #+#    #+#             */
/*   Updated: 2023/06/19 14:56:50 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    new_socket = accept(_mainSocketFd, reinterpret_cast<sockaddr *>(&_addr), &len);