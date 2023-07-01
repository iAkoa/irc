#ifndef SERVER_HPP
# define SERVER_HPP

# include "./Channel.hpp"
# include "./CSockets.hpp"
# include "./User.hpp"
# include <iostream>
# include <DMap.hpp>
# include <Message.hpp>
# include <cstdlib>
# include <sstream>
# include <cctype>
# include "NumericReplies.hpp"

class Server {
	public:
	// canonical
		Server(void);
		Server(int port, const std::string password); // constructors
		Server( Server const &src);
		Server &	operator=( Server const &rhs);
		~Server(void);

	// getters
		DMap<int, std::string, User>		getUsers( void ) const;
		std::map<std::string, Channel>	getChannels( void ) const;

	// specific functions
		std::vector<std::string> splitString(const std::string& str, const std::string& separator);
		void								init();
		void								start();
		void								pass(const Message &message);
		void								nick(const Message &message);
		// channel functions 
		void								join(const Message &message);
		std::list<std::string>				joinGetChannels(std::string parameters);
		std::list<std::string>				joinGetKeys(std::string parameters);

		std::string							topicGetTopic(std::string parameters);
		std::string							topicGetChannel(std::string parameters);
		void								topic(const Message &message);

		void								invite(const Message &message);
		std::string							inviteGetChannel(std::string parameters);
		std::string							inviteGetNickname(std::string parameters);

		void								kick(const Message &message);
		void								part(const Message &message);

		void								mode(const Message &message);
		int									isParsingModeOk(std::string modestring, std::map<std::string, Channel>::iterator it);
		// message functions
		std::string							word(const std::string &s, int n, bool all);
		std::string							getWord(std::string src, int word);
		std::string							getEndFrom(std::string src, int word);
		int									countWords(std::string src);
		bool								isInCharset(std::string charset, char c);
		bool								isUnique(std::string modestring, char c);
		bool								beginWith(std::string src, char c);
		bool								isStrAlNum(std::string src);
		bool								isValidString(std::string src);

		void								respond(std::string source, std::string answer, const int fd);
		void 								respondC(std::string source, std::string answer, Channel channel);
		void								user(const Message &message);
		void 								checkAuth(User &user);
		void								privmsg(const Message &message);
		void								notice(const Message &message);
		void								chooseCommand(const Message &message);
	protected:
	private:
		CSockets								_sockets;
		DMap<int, std::string, User>			_users;
		std::map<std::string, Channel>			_channels;
		std::string								_password;
		std::map<std::string, void (Server::*)(const Message &)> _commands;
		
};
#endif
