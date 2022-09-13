#include "FourNetworking/tcp_server.h"
#include <iostream>
#include "FourNetworking/tcp_connection.h"

namespace four::net {
	using boost::asio::ip::tcp;

	TCPServer::TCPServer(int port)
		: m_port(port)
		, m_acceptor(m_io_context, tcp::endpoint(tcp::v4(), port))
	{

	}

	void TCPServer::Run()
	{
		try {
			m_io_context.run();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
			std::exit(-1);
		}
	}

	void TCPServer::StartAccept()
	{
		// create connection
		// async accept connection
		auto connection = TCPConnection::Create(m_io_context);

		m_acceptor.async_accept(connection->GetSocket(),
			[connection, this](const boost::system::error_code& ec)
			{
				if (!ec)
				{
					connection->Start();
				}
				else
				{
					std::cerr << "[Error StartAccept] " << ec.message() << "\n";
				}
			});

	}

}