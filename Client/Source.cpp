#include <boost/asio.hpp>
#include <iostream>
#include <array>

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_context io_context;

		boost::asio::ip::tcp::resolver resolver{ io_context };

		boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "13");

		boost::asio::ip::tcp::socket socket{ io_context };
		boost::asio::connect(socket, endpoints);

		while (true)
		{
			// Listen for messages
			std::array<char, 128> buffer;
			boost::system::error_code errorCode;

			size_t len = socket.read_some(boost::asio::buffer(buffer), errorCode);

			if (errorCode == boost::asio::error::eof)
			{
				// clean connection cut off
				break;
			}
			else if(errorCode)
			{
				throw boost::system::system_error(errorCode);
			}

			std::cout.write(buffer.data(), len);
		}
	}

	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}

	std::cin.get();
	return 0;
}