#include "ResponseRouter.h"


using Poco::Net::SocketReactor;


namespace kademlia {
namespace detail {


	ResponseRouter::ResponseRouter(SocketReactor &io_service): timer_(io_service)
	{
	}


	void ResponseRouter::handle_new_response(endpoint_type const &sender, Header const &h,
											 buffer::const_iterator i, buffer::const_iterator e)
	{
		// Try to forward the message to its associated callback.
		auto failure = response_callbacks_.dispatch_response(sender, h, i, e);
		if (failure == UNASSOCIATED_MESSAGE_ID)// Unknown or unassociated responses discarded.
			LOG_DEBUG(ResponseRouter, this) << "dropping unknown response." << std::endl;
	}

} }
