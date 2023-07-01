/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DMap.tpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:48:07 by iel-amra          #+#    #+#             */
/*   Updated: 2023/06/08 10:01:35 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T, typename U, typename V>
DMap<T, U, V>::DMap() : std::map<T, V>()
{
}

template <typename T, typename U, typename V>
DMap<T, U, V>::~DMap()
{
}

template <typename T, typename U, typename V>
DMap<T, U, V>::DMap(const DMap<T, U, V> &ref) : std::map<T, V>(ref), _keys(ref._keys)
{
}

template <typename T, typename U, typename V>
DMap<T, U, V> &DMap<T, U, V>::operator=(const DMap<T, U, V> &rhs)
{
    static_cast<std::map<T, V> >(*this) = rhs;
    _keys = rhs.keys;
    return (*this);
}

template <typename T, typename U, typename V>
V &DMap<T, U, V>::operator[](const T &key)
{
    return ((*static_cast<std::map<T, V> *>(this))[key]);
}

template <typename T, typename U, typename V>
V &DMap<T, U, V>::operator[](const U &key)
{
    return ((*static_cast<std::map<T, V> *>(this))[_keys[key]]);
}

template <typename T, typename U, typename V>
bool DMap<T, U, V>::exist(const T &key)
{
    return (this->find(key) != this->end());
}

template <typename T, typename U, typename V>
bool DMap<T, U, V>::exist(const U &key)
{
    return (_keys.find(key) != _keys.end());
}

template <typename T, typename U, typename V>
void DMap<T, U, V>::erase(const T &key)
{
    std::map<T, V>::erase(key);
    _keys.erase(find(_keys.begin(), _keys.end(), key));
}

template <typename T, typename U, typename V>
void DMap<T, U, V>::erase(const U &key)
{
    std::map<T, V>::erase(_keys[key]);
    _keys.erase(key);
}

template <typename T, typename U, typename V>
void DMap<T, U, V>::addKey(const T &value, const U &key)
{
    _keys[key] = value;
}

template <typename T, typename U, typename V>
void DMap<T, U, V>::rmKey( const U &key)
{
    _keys.erase(key);
}

template <typename T, typename U, typename V>
std::map<U, T> &DMap<T, U, V>::getKeys() const
{
    return(_keys);
}