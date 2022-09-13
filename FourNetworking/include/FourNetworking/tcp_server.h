#pragma once
#include <boost/asio.hpp>

namespace four::net {

	class TCPServer {
	public:
		TCPServer(int port);

		// run io_context
		void Run();

	private:
		void StartAccept();

	private:
		int m_port;
		boost::asio::io_context m_io_context;
		boost::asio::ip::tcp::acceptor m_acceptor;
	};
}