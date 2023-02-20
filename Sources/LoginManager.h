#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>

class LoginManager {

public:
	LoginManager();
	~LoginManager();

	void login();
	int checkFile(std::string attempt, const char* p_fileName);
	long long encrypt(int p_letter);
	int decrypt(long long p_letter);
	void saveFile(std::string p_text, const char* p_fileName, const int& id);
	void addUser(const std::string username, const std::string password);
	int getLastID();

private:
	std::string m_passWord;
	std::string m_userName;
	std::string m_userNameAttempt;
	std::string m_passWordAttempt;
	bool m_accessGranted;
};