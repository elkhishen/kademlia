// Copyright (c) 2013-2014, David Keller
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//	 * Redistributions of source code must retain the above copyright
//	   notice, this list of conditions and the following disclaimer.
//	 * Redistributions in binary form must reproduce the above copyright
//	   notice, this list of conditions and the following disclaimer in the
//	   documentation and/or other materials provided with the distribution.
//	 * Neither the name of the University of California, Berkeley nor the
//	   names of its contributors may be used to endorse or promote products
//	   derived from this software without specific prior written permission.
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


#include "SessionImpl.h"
#include "kademlia/error.hpp"
#include "error_impl.hpp"


namespace kademlia {
namespace detail {


SessionImpl::SessionImpl(endpoint const& ipv4, endpoint const& ipv6):
	_engine{ _ioService, ipv4, ipv6 }
{ }

SessionImpl::SessionImpl(endpoint const& initPeer, endpoint const& ipv4, endpoint const& ipv6): _ioService{},
	_engine{ _ioService, initPeer, ipv4, ipv6 }
{ }

std::error_code SessionImpl::run()
{
	// Protect against concurrent invocation of this method.
	detail::concurrent_guard::sentry s{ _concurrentGuard };
	if (!s) return make_error_code(ALREADY_RUNNING);
	_ioService.run();
	return make_error_code(RUN_ABORTED);
}


void SessionImpl::abort()
{
	_ioService.stop();
	_ioService.wakeUp();
}

} // namespace detail
} // namespace kademlia
