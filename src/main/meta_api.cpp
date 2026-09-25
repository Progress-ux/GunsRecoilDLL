#include <extdll.h>			// always
#include <meta_api.h>		// of course

#include "config/config_manager.h"
#include "hooks/regame_loader.h"
#include "util/logger.h"

static ConfigManager g_config_manager;
#define GUNS_RECOIL_CONFIG "guns-recoil-config.cfg"

// Must provide at least one of these..
static META_FUNCTIONS gMetaFunctionTable = {
	NULL,			// pfnGetEntityAPI				HL SDK; called before game DLL
	NULL,			// pfnGetEntityAPI_Post			META; called after game DLL
	GetEntityAPI2,	// pfnGetEntityAPI2				HL SDK2; called before game DLL
	NULL,			// pfnGetEntityAPI2_Post		META; called after game DLL
	NULL,			// pfnGetNewDLLFunctions		HL SDK2; called before game DLL
	NULL,			// pfnGetNewDLLFunctions_Post	META; called after game DLL
	GetEngineFunctions,	// pfnGetEngineFunctions	META; called before HL engine
	NULL,			// pfnGetEngineFunctions_Post	META; called after HL engine
};

// Description of plugin
plugin_info_t Plugin_info = {
	META_INTERFACE_VERSION,	// ifvers
	"Guns Recoil",	// name
	"0.1",	// version
	"2026/08/20",	// date
	"Progress",	// author
	"",	// url
	"GUNS",	// logtag, all caps please
	PT_ANYTIME,	// (when) loadable
	PT_ANYPAUSE,	// (when) unloadable
};

meta_globals_t *gpMetaGlobals;		// metamod globals
gamedll_funcs_t *gpGamedllFuncs;	// gameDLL function tables
mutil_funcs_t *gpMetaUtilFuncs;		// metamod utility functions

C_DLLEXPORT int Meta_Query(char * /*ifvers */, plugin_info_t **pPlugInfo,
		mutil_funcs_t *pMetaUtilFuncs) 
{
	*pPlugInfo=&Plugin_info;
	gpMetaUtilFuncs=pMetaUtilFuncs;
	return(TRUE);
}

C_DLLEXPORT int Meta_Attach(PLUG_LOADTIME /* now */, 
		META_FUNCTIONS *pFunctionTable, meta_globals_t *pMGlobals, 
		gamedll_funcs_t *pGamedllFuncs) 
{
	if (!pFunctionTable) 
		return(FALSE);

	if (!pMGlobals) 
		return(FALSE);

    if (!pGamedllFuncs)
        return(FALSE);
	
	gpMetaGlobals  = pMGlobals;
	gpGamedllFuncs = pGamedllFuncs;
	
	memcpy(
        pFunctionTable, 
        &gMetaFunctionTable, 
        sizeof(META_FUNCTIONS)
    );

    LH_LogInit();
    LH_START("Guns Recoil %s attaching", Plugin_info.version);

    if (!Initialize())
    {
        LH_ERROR("[Meta_Attach()] ReGameDll initialization failed!");
        LH_LogShutdown();
        return(FALSE);
    }

    if (!ConfigManager_Load(&g_config_manager, GUNS_RECOIL_CONFIG))
    {
        LH_WARN("Failed load guns config");
    }

    LH_INFO("ReGameDLL initialization successful");
    LH_INFO("Guns Recoil attached successfully");

	return(TRUE);
}

// Metamod detaching plugin from the server.
// now		(given) current phase, ie during map, etc
// reason	(given) why detaching (refresh, console unload, forced unload, etc)
C_DLLEXPORT int Meta_Detach(PLUG_LOADTIME /* now */, 
		PL_UNLOAD_REASON /* reason */) 
{
    LH_START("Guns Recoil detaching");

    Shutdown();
    LH_LogShutdown();

	return(TRUE);
}
