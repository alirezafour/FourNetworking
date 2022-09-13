#include "FourNetworking/tcp_connection.h"
#include <iostream>

namespace four::net {
	using boost::asio::ip::tcp;

	TCPConnection::TCPConnection(boost::asio::io_context& io_context)
		: m_socket(io_context)
	{

	}

	void TCPConnection::Start()
	{
// 		auto strongThis = shared_from_this();
// 		boost::asio::write(m_socket, boost::asio::buffer(m_message),
// 			[strongThis](const boost::system::error_code& ec, size_t byteTransferred)
// 			{
// 
// 			});
	}

}