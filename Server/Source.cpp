#include <boost/asio.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	try {
		boost::asio::io_context io_context;

		boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1337));

		while (true)
		{
			std::cout << "accepting connections! \n";
			boost::asio::ip::tcp::socket socket(io_context);
			acceptor.accept(socket);

			std::cout << "Client Connected! Sending message!\n";

			std::string hello_message = "Hello, my client!\n";
			boost::system::error_code errorCode;

			boost::asio::write(socket, boost::asio::buffer(hello_message), errorCode);
		}

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	
	return 0;
}