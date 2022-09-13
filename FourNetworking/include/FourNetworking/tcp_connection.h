#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>

namespace four::net {

	class TCPConnection : public std::enable_shared_from_this<TCPConnection>{

	public:
		static std::shared_ptr<TCPConnection> Create(boost::asio::io_context& io_context) { return std::shared_ptr<TCPConnection>(new TCPConnection(io_context)); }

		inline boost::asio::ip::tcp::socket& GetSocket() { return m_socket; }

		// send message
		void Start();

	private:
		TCPConnection(boost::asio::io_context& io_context);

	private:
		boost::asio::ip::tcp::socket m_socket;
		std::string m_message{"Hello client!\n"};
	};
}