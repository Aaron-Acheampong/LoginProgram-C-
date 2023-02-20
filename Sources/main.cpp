#include "LoginManager.h"


int main() 
{
	LoginManager app;

	//app.addUser("user@email.com", "user");
	//app.addUser("aaron@email.com", "aaron");
	//app.addUser("mike@email.com", "mike");
	//app.addUser("bee@email.com", "bee");

	
    app.login();
	///std::cout << app.getFile("Sources/Assets/pswds.dat") << std::endl;

	std::cin.get();
};