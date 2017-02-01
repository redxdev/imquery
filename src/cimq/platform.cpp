#include "platform.h"

#include <imq/platform.h>

const imqString imqGetVersion()
{
	return imq::getIMQVersion();
}