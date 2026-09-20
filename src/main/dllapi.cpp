#include <extdll.h>

#include <dllapi.h>
#include <meta_api.h>

C_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, 
		int *interfaceVersion)
{
	if(!pFunctionTable || !interfaceVersion) 
		return(FALSE);

	if(*interfaceVersion != INTERFACE_VERSION) 
    {
		*interfaceVersion = INTERFACE_VERSION;
		return(FALSE);
	}

	return(TRUE);
}
