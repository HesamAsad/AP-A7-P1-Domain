#include <iostream>
#include "Utrip.h"
#include "Interface.h"
using namespace std;


int main(int argc, char** argv)
{
	string assets_path = string(argv[1]);
	Utrip utrip;
	Interface _interface(&utrip);
	utrip.load_hotels(assets_path);

	string command;
	while (getline(cin, command))
	{
		try
		{
			_interface.handle_command(command);
		}
		catch (exception& err)
		{
			cout << err.what() << endl;
		}
	}
	return 0;
}