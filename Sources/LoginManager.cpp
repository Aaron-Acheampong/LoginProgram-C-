#include "LoginManager.h"



LoginManager::LoginManager() 
{
	m_accessGranted = 0;
}

LoginManager::~LoginManager() {}

//Login with Credentials
void LoginManager::login() 
{
	std::cout << "Hey. A username is required.\nUsername:";
	std::cin >> m_userNameAttempt;

	int userID = checkFile(m_userNameAttempt, "Sources/Assets/users.dat");
	if (userID != 0)
	{
		std::cout << "\nPassword:";
		std::cin >> m_passWordAttempt;

		int pwdID = checkFile(m_passWordAttempt, "Sources/Assets/pswds.dat");
		if (pwdID == userID)
		{
			std::cout << "Hey, that's right.\n";
			std::cin.get();
		}
		else 
		{
			std::cout << "Error!!!  Wrong Password." << std::endl;
			login();
		}
	}
	else 
	{
		std::cout << "Wrong email!!!!!!" << std::endl;
		login();
	}
}

//Check credentials
int LoginManager::checkFile(std::string attempt, const char* p_fileName) 
{
	std::string line;
	std::fstream file;

	std::string currentChar;
	long long eChar;

	file.open(p_fileName, std::ios::in);
	while(1)
	{
		//getline(file, eChar);
		file  >> currentChar;
		if (currentChar.find("#ID:") != std::string::npos)
		{
			if (attempt == line)
			{
				file.close();
				currentChar.erase(0, 4);
				int id;
				std::istringstream(currentChar) >> id;
				return id;
			}
			else 
			{
				line.erase(line.begin(), line.end());
			}
		}
		else
		{
			std::istringstream(currentChar) >> eChar;
			line += (char)decrypt(eChar);
			currentChar = "";
		}

		if (file.peek() == EOF)
		{
			file.close();
			return false;
		}
	}

}

//Encrypt Credentials
long long LoginManager::encrypt(int p_letter)
{
	return (long long)powf(p_letter, 5) * 4 - 14;
}

//Decrypt Credentials
int LoginManager::decrypt(long long p_letter)
{
	return powf((p_letter + 14 )/ 4, 1/5.f);
}

//Save Credentials
void LoginManager::saveFile(std::string p_line, const char* p_fileName, const int& id)
{
	std::fstream file;
	file.open(p_fileName, std::ios::app);
	file.seekg(0, std::ios::end);

	if (file.tellg() != 0) { file << "\n"; }

	file.seekg(0, std::ios::beg);

	for (int i = 0; i < p_line.length(); i++)
	{
		file << encrypt(p_line[i]);
		file << "\n";
	}

	file << "#ID:" << id;
	file.close();

	std::cout << "Credential saved." << std::endl;
}

//Add User
void LoginManager::addUser(const std::string username, const std::string password) 
{
	if (checkFile(username, "Sources/Assets/users.dat") != 0)
	{
		std::cout << "That username is not available." << std::endl;
		return;
	}

	int id = 1 + getLastID();
	saveFile(username, "Sources/Assets/users.dat", id);
	saveFile(password, "Sources/Assets/pswds.dat", id);
}

int LoginManager::getLastID()
{
	std::fstream file;
	file.open("Sources/Assets/users.dat", std::ios::in);
	file.seekg(0, std::ios::end);

	if (file.tellg() == -1)
	{
		return 0;
	}

	std::string s;

	for(int i = -1; s.find("#") == std::string::npos; i--)
	{
		file.seekg(i, std::ios::end);
		file >> s;
	}

	file.close();
	s.erase(0, 4);

	int id;
	std::istringstream(s) >> id;
	return id;
}