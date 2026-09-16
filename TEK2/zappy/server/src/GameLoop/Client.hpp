/*
** EPITECH PROJECT, 2026
** Client
** File description:
** Client class
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_


};

class Client {
    private:
        int _fd;
        int _state;
        std::string _teamName;
        std::string _readBuffer;
        std::optional<PlayerData> _playerData;
    public:
        explicit Client(int fd);

        int getFd() const;
        int getState() const;
        const std::string &getTeamName() const;
        std::string &getReadBuffer();
        void setState(int newState);
        void setTeamName(const std::string &newTeamName);
        void invalidate();
        bool isDead() const;
        std::optional<PlayerData> &getPlayerData();
        const std::optional<PlayerData> &getPlayerData() const;
        void initPlayerData();
};

}

#endif /* !CLIENT_HPP_ */
