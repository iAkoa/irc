#ifndef USER_HPP
# define USER_HPP
# include <iostream>

class User {
	public:
		User(std::string name);
		User(int fd);
		User(void);
		~User(void);
		User(User const & src);
		User &	operator=(User const &rhs);

		// getters 
		std::string	getUsername(void) const;
		std::string	getNickname(void) const;
		std::string	getPassword(void) const;
		std::string	getIP(void) const;
		bool	isOperator(void) const;
		int		getFd(void) const;
		int		getLevel(void) const;

		// setters 
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);
		void	setPassword(std::string password);
		void	setIP(std::string ip);
		void	setOperator(bool op);
		void	setFd(int fd);
		void	setLevel(int fd);
	protected:
	private:
		int			_fd;

		int			_level;
		std::string	_username;
		std::string	_nickname;
		std::string	_password;
		bool		_operator;
		std::string	_ip;
};
#endif
