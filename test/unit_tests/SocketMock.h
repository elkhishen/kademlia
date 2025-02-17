// Copyright (c) 2014, David Keller
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the University of California, Berkeley nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY DAVID KELLER AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef KADEMLIA_SOCKET_MOCK_H
#define KADEMLIA_SOCKET_MOCK_H

#ifdef _MSC_VER
#   pragma once
#endif

#include <functional>
#include <cstdlib>
#include <deque>
#include <vector>
#include <cstdint>

#include <boost/asio/buffer.hpp>
#include "Poco/Net/SocketReactor.h"
#include "kademlia/SocketAdapter.h"
#include "Poco/Net/DatagramSocket.h"
#include "kademlia/error_impl.hpp"

namespace kademlia {
namespace test {

/**
 *
 */
class SocketMock
{
public:
    ///
    //using protocol_type = Poco::Net::IPAddress::Family;//boost::asio::ip::udp;

    ///
    using endpoint_type = Poco::Net::SocketAddress;//protocol_type::endpoint;

public:
    /**
     *
     */
    SocketMock
        ( Poco::Net::SocketReactor* io_service,
		const Poco::Net::SocketAddress& address, bool reuseAddress = true, bool ipV6Only = true )
    { }

    /**
     *
     */
    SocketMock
        ( SocketMock const& o )
        = delete;

    /**
     *
     */
    SocketMock
        ( SocketMock && o )
    { }

    /**
     *
     */
    SocketMock &
    operator=
        ( SocketMock const& o ) { return *this; }
        //= delete;

    /**
     *
     */
    ~SocketMock
        ( void )
    {
        boost::system::error_code ignored;
        close( ignored );
    }

	void setIOService(Poco::Net::SocketReactor& io_service)
	{
	}

	Poco::Net::SocketAddress address() const
	{
		return Poco::Net::SocketAddress();
	}
    /**
     *
     */
    template< typename Option >
    void
    set_option
        ( Option const& )
    { }

    /**
     *
     */
    endpoint_type
    local_endpoint
        ( void )
        const
    { return endpoint_type{}; }

    /**
     *
     */
    boost::system::error_code
    bind
        ( endpoint_type const& e )
    { return boost::system::error_code{}; }

    /**
     *
     */
    boost::system::error_code
    close
        ( boost::system::error_code & failure )
    { return failure; }

    /**
     *
     */
    template< typename Callback >
    void
    asyncReceiveFrom
        ( boost::asio::mutable_buffer const& buffer
        , endpoint_type & from
        , Callback && callback )
    { }

    /**
     *
     */
    template< typename Callback >
    void
    asyncSendTo
        ( boost::asio::const_buffer const& buffer
        , endpoint_type const& to
        , Callback && callback )
    { }
};

} // namespace test
} // namespace kademlia

#endif

