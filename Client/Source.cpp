#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/connect.hpp>

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::redirect_error;
using boost::asio::use_awaitable;



class client_chat
	: public std::enable_shared_from_this<client_chat>
{
public:
	client_chat(boost::asio::io_context& io_context)
		: resolver_{ io_context }
		, socket_{ io_context }
	{
	}

	~client_chat()
	{
		stop();
	}

	boost::asio::ip::tcp::socket& getSocket() { return socket_; }

	void connect(const std::string& ip, const std::string& port)
	{
		tcp::resolver::results_type endpoints = resolver_.resolve("127.0.0.1", "6000");
		boost::asio::connect(socket_, endpoints);
		start();
	}

	void start()
	{
		co_spawn(socket_.get_executor(),
			[self = shared_from_this()] { return self->writer(); },
			detached);

		co_spawn(socket_.get_executor(),
			[self = shared_from_this()] { return self->reader(); },
			detached);
	}

	awaitable<void> writer()
	{
		try
		{
			while (socket_.is_open())
			{
				std::string message { "Hello my dear server. "};
				//std::cin >> message;
				co_await boost::asio::async_write(socket_,
					boost::asio::buffer(message), use_awaitable);
			}
		}
		catch (std::exception&)
		{
			stop();
		}
	}

private:
	awaitable<void> reader()
	{
		try
		{
			for (std::string read_msg;;)
			{
				std::size_t n = co_await boost::asio::async_read_until(socket_,
					boost::asio::dynamic_buffer(read_msg, 1024), "\n", use_awaitable);

				std::cout << "message size [" << n << "]: " << read_msg << "\n";
				read_msg.erase(0, n);
			}
		}
		catch (std::exception&)
		{
			stop();
		}
	}


	void stop()
	{
		socket_.close();
	}

	tcp::resolver resolver_;
	tcp::socket socket_;
};

int main(int argc, char* argv[])
{
	try
	{
// 		boost::asio::io_context io_context;
// 
// 		tcp::resolver resolver{ io_context };
// 
// 		tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "6000");
// 
// 		tcp::socket socket{ io_context };
// 
// 		boost::asio::connect(socket, endpoints);


		boost::asio::io_context io_context(1);
		std::shared_ptr<client_chat> client = std::make_shared<client_chat>(io_context);
		client->connect("127.0.0.1", "6000");

		io_context.run();


// 		while (true)
// 		{
// 			// Listen for messages
// 			std::array<char, 128> buffer;
// 			boost::system::error_code errorCode;
// 
// 			size_t len = socket.read_some(boost::asio::buffer(buffer), errorCode);
// 
// 			if (errorCode == boost::asio::error::eof)
// 			{
// 				// clean connection cut off
// 				t1.join();
// 				break;
// 			}
// 			else if(errorCode)
// 			{
// 				throw boost::system::system_error(errorCode);
// 			}
// 
// 			std::cout.write(buffer.data(), len);
// 		}
	}

	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}

	std::cin.get();
	return 0;
}