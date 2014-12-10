#include "burner.h"
#include "kailleraclient.h"

bool KailleraGetInput(void *values, int size)
{
	// Send the control block to the Kaillera DLL & retrieve all controls
	if (kailleraModifyPlayValues(values, size) == -1) {
		kNetGame = 0;
		return false;
	}
   return true;
}
