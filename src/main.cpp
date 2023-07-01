/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mycomputer <mycomputer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:17:58 by iel-amra          #+#    #+#             */
/*   Updated: 2023/06/07 12:37:01 by mycomputer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <CSockets.hpp>
#include <DMap.hpp>
#include <Message.hpp>
#include <Server.hpp>
#include <Channel.hpp>
#include <User.hpp>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{

	std::cout << "test" << std::endl;
    if (argc != 3)
    {
        cerr << "Usage : "  << argv[0] << " [port number] [password]" << endl;
        return (1);
    }
    Server server(atoi(argv[1]), argv[2]);

    server.start();
    return (0);
}