#pragma once

extern "C" {
#include <Lua5.4.4/lua.h>
#include <Lua5.4.4/lualib.h>
#include <Lua5.4.4/lauxlib.h>
}

#include <string>
#include <map>
#include "FMODManager.h"

#define LUASCRIPT_PATH "assets/script/script.lua"

extern FModManager* g_FMODManager;
static int playsound(lua_State* L)
{
	const char* soundName = lua_tostring(L, 1);
	printf("playing sound: %s\n", soundName);

	g_FMODManager->stop_sound(FX1_CH);
	g_FMODManager->play_sound(soundName, FX1_CH);

	return 0;
}

class LuaBrain
{
public:
	LuaBrain();
	~LuaBrain();

	void LoadScript(std::string param);
	void RunScriptImmediately(std::string script);

private:

	lua_State* m_pLuaState;
	std::map<std::string, std::string> m_mapScript;
	std::string m_decodeLuaErrorToString(int error);
};
