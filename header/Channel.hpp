#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <iostream>
# include <map>
# include "./User.hpp" 
// Format :    [{:}{prefix} {SP} ]{COMMANDE}[{SP}{PARAMETRES}]{CRLF}
/*
TO DO :
Channel Message:
	JOIN Message
	PART Message
	TOPIC Message
	NAMES Message
	LIST Message
	INVITE Message
*/
class Channel {
	public:
	// canonical
		Channel();
		Channel(std::string name); // constructors
		Channel(std::string name, std::string key); // constructors
		Channel(std::string name, std::string key, User *admin); // constructors
		Channel(std::string name, User *admin); // constructors
		Channel( Channel const &src);
		Channel &	operator=( Channel const &rhs);
		~Channel(void);

	// getters
		std::string						getName( void ) const;
		std::string						getKey( void ) const;
		std::string						getTopic( void ) const;
		bool							getInviteOnly( void ) const;
		bool							getRestricted( void ) const;
		int								getUserLimit( void ) const;
		std::map<std::string, User *>	&getUsers (void );
		std::map<std::string, User *>	&getAdmins( void );
		std::map<std::string, User *>	&getInvited( void );
		std::map<std::string, User *>	getUsers2 (void ) const;
		std::map<std::string, User *>	getAdmins2( void )const;
		std::map<std::string, User *>	getInvited2( void )const;
		bool							getIsKey(void) const;

	// setters
		void			setName( std::string name );
		void			setKey( std::string key );
		void			setTopic( std::string topic );
		void			setInviteOnly( bool invite_only );
		void			setRestricted( bool restricted );
		void			setUserLimit( int user_limit );
		void			setIsKey(bool iskey);
		// on a peut etre pas besoin de ces deux fonctions dans le sens ou on va juste faire admin.push() etc
		// void			setUsers( std::list<User> users);
		// void			setAdmin( std::list<User> admin );

	// specific functions

	protected:
	private:
		std::string		_name; /*	begins with a valid channel type prefix character;
									no spaces " ", ctrlG "0x07", comma ","
									 */

		std::string		_key; // mode +k
		std::string		_topic; // command TOPIC
		bool			_invite_only; // mode +i
		bool			_restricted; // mode +t
		int				_user_limit; // mode +l
		bool			_iskey; // mode +k

		std::map<std::string, User *>	_admins; // mode +o to give/take
		std::map<std::string, User *>	_users; // users within the channel
		std::map<std::string, User *>	_invited; // users invited to the channel
};
#endif
