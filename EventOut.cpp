#include "EventOut.h"
#include "LogManager.h"
namespace df {
	EventOut::EventOut() {
		setType(OUT_EVENT);
		LM.writeLog(0, "EventOut created");
	}

}