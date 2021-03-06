#include "Server.hpp"

int main(int argc, char *argv[])
{
	Server		*server;
	int			portIndex;
	int			passIndex;
	int			networkIndex;

	if (argc == 3 || argc == 4)
	{
		networkIndex = 1;
		portIndex = argc - 2;
		passIndex = argc - 1;
		if (isActualPort(std::string(argv[portIndex])))
		{
			server = new Server(argv[passIndex], argv[portIndex]);
			try
			{
				server->init(argv[portIndex]);
				if (argc == 4)
					server->connectServer(argv[networkIndex]);
				server->start();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			delete server;
		}
		else
			std::cerr << ERROR_PORT << std::endl;
	}
	else
		std::cerr << ERROR_ARG_NUM << std::endl;
	return (0);
}
