#include<iostream>
#include<string>
class FullName {
private:
	std::string firstName, middleName, lastName;
public:
	FullName() {   }
	void setFirstName(std::string fn) {
		firstName = fn;
	}
	std::string getFirstName() {
		return firstName;
	}
	void setMiddleName(std::string mn) {
		middleName = mn;
	}
	std::string getMiddleName() {
		return middleName;
	}
	void setLastName(std::string ln) {
		lastName = ln;
	}
	std::string getLastName() {
		return lastName;
	}

};
class Player {
private:
	std::string playerID;
	FullName playerName;
	int matchesPlayed, goalsScored;
public:
	Player() {}
	void setPlayerId(std::string playerId) {
		this->playerID = playerId;
	}
	 std::string getPlayerId() {
		return playerID;
	}
	 void setMatchesPlayed(int mp) {
		 matchesPlayed = mp;
	 }
	 int getMatchesPlayed() {
		 return matchesPlayed;
	 }
	 void setGoalsScored(int gs) {
		 goalsScored = gs;
	 }
	 int getGoalsScored() {
		 return goalsScored;
	 }
	 void setPlayerName(FullName fn) {
		 playerName = fn;
	 }
	 FullName getPlayerName() {
		 return playerName;
	 }
	 friend void increaseGoalsScored(Player &player, int score);
};
void increaseGoalsScored(Player &player, int score) {
	player.goalsScored += score;
}
int main() {
	Player *player = new Player;
	FullName fullName;
	int intTemp;
	std::string strTemp;
	std::cout << "Enter goals scored" << std::endl;
	std::cin >> intTemp;
	player->setGoalsScored(intTemp);
	std::cout << "Enter matches played" << std::endl;
	std::cin >> intTemp;
	player->setMatchesPlayed(intTemp);
	std::cout << "Enter player id" << std::endl;
	std::cin >> strTemp;
	player->setPlayerId(strTemp);
	std::cout << "Enter first name" << std::endl;
	std::cin >> strTemp;
	fullName.setFirstName(strTemp);
	std::cout << "Enter last name" << std::endl;
	std::cin >> strTemp;
	fullName.setLastName(strTemp);
	std::cout << "Enter middle name" << std::endl;
	std::cin >> strTemp;
	fullName.setMiddleName(strTemp);
	player->setPlayerName(fullName);
	std::cout << "Enter additional score" << std::endl;
	std::cin >> intTemp;
	increaseGoalsScored(*player, intTemp);
	std::cout << "goals scored: " << player->getGoalsScored() << std::endl;
	std::cout << "matches played: " << player->getMatchesPlayed() << std::endl;
	std::cout << "player id: " << player->getPlayerId() << std::endl;
	std::cout << "first name: " << fullName.getFirstName() << std::endl;
	std::cout << "last name: " << fullName.getLastName() << std::endl;
	std::cout << "middle name: " << fullName.getMiddleName() << std::endl;
	delete player;
	system("pause");
	return 0;
}