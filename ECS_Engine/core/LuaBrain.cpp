#include "LuaBrain.h"
#include <iostream>

LuaBrain::LuaBrain()
{
	this->m_pLuaState = luaL_newstate();

	luaL_openlibs(this->m_pLuaState);

	lua_pushcfunction(this->m_pLuaState, playsound);
	lua_setglobal(this->m_pLuaState, "playsound");
	std::cout << "load lua" << std::endl;
	//int error = luaL_loadfile(this->m_pLuaState, LUASCRIPT_PATH);
	////lua_newtable(this->m_pLuaState);
	////lua_pushstring(this->m_pLuaState, "area");
	//lua_pushstring(this->m_pLuaState, "woods");
	////lua_rawset(this->m_pLuaState, -3);
	//lua_setglobal(this->m_pLuaState, "args");
	//lua_pcall(this->m_pLuaState, 0, 1, 0);
	//lua_pop(this->m_pLuaState, 1);
}

LuaBrain::~LuaBrain()
{
	lua_close(this->m_pLuaState);
}

void LuaBrain::LoadScript(std::string param)
{
	int error = luaL_loadfile(this->m_pLuaState, LUASCRIPT_PATH);
	lua_pushstring(this->m_pLuaState, param.c_str());
	lua_setglobal(this->m_pLuaState, "param");
	lua_pcall(this->m_pLuaState, 0, 1, 0);
}

void LuaBrain::RunScriptImmediately(std::string script)
{
	int error = luaL_loadstring(this->m_pLuaState, script.c_str());
	
	if (error != 0)
	{
		std::cout << "Lua "<<script << "Error: " << m_decodeLuaErrorToString(error) << std::endl;
		return;
	}

	error = lua_pcall(this->m_pLuaState, 0, 0, 0);

	if (error != 0)
	{
		std::cout << "Lua: There was an error..." << std::endl;
		std::cout << this->m_decodeLuaErrorToString(error) << std::endl;

		std::string luaError;
		// Get error information from top of stack (-1 is top)
		luaError.append(lua_tostring(this->m_pLuaState, -1));

		// Make error message a little more clear
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Error running Lua script: ";
		std::cout << luaError << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
		// We passed zero (0) as errfunc, so error is on stack)
		lua_pop(this->m_pLuaState, 1);  /* pop error message from the stack */
	}
}

std::string LuaBrain::m_decodeLuaErrorToString(int error)
{
	switch (error)
	{
	case 0:
		return "Lua: no error";
		break;
	case LUA_ERRSYNTAX:
		return "Lua: syntax error";
		break;
	case LUA_ERRMEM:
		return "Lua: memory allocation error";
		break;
	case LUA_ERRRUN:
		return "Lua: Runtime error";
		break;
	case LUA_ERRERR:
		return "Lua: Error while running the error handler function";
		break;
	}


	return "Lua: UNKNOWN error";
}
