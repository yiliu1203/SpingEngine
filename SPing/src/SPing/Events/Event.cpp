
#include "SPingPre.h"
#include "Event.h"

namespace SPing {

	std::ostream& operator<<(std::ostream& os, const Event& event) {
		return os << event.ToString();
	}



}
