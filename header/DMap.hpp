/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DMap.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:31:36 by iel-amra          #+#    #+#             */
/*   Updated: 2023/06/08 10:00:43 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DMAP_HPP
# define DMAP_HPP

#include <map>

template <typename T, typename U, typename V>
class DMap : public std::map<T, V>
{
public:
    DMap();
    ~DMap();
    DMap(const DMap &ref);
    DMap &operator=(const DMap &rhs);

    V &operator[](const T &key);
    V &operator[](const U &key);
    void erase(const T &key);
    void erase(const U &key);
    bool exist(const T &key);
    bool exist(const U &key);
    void addKey(const T &value, const U &key);
    void rmKey(const U &key);
    std::map<U, T> &getKeys() const;
private:
    std::map<U, T> _keys;
};

#include "DMap.tpp"

#endif