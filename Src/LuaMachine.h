#pragma once

#define JASS2LUA "JASS2LUA_WRAPPER"

namespace LuaMachine {
	extern std::map<std::string, bool> handlemetatypes;

	lua_State* GetMainState(bool init = true,bool game = false);

	void DestroyLua();
	void StartLuaGame();
	void StartLuaConfig();
	BOOL __stdcall StartLuaThread();

	void HandleMetatablesReset();
	// Returns TRUE if table exists and FALSE if table was created
	BOOL GetGlobalTable(lua_State* l, LPCSTR name, bool weakKey, bool weakValue);

	DWORD PushFunctionByKey(lua_State* l, int index, DWORD key);
	void GetFunctionByKey(lua_State* l, DWORD key);

	BOOL GetUserdataByHandle(lua_State* l, DWORD handle, LPCSTR tname);
	void DeleteUserdataByHandle(lua_State* l, DWORD handle);

	void lua_throwerr(lua_State* l);
	void lua_throwerrChat(lua_State* l);

	void lua_throwWarning(lua_State* l, std::string msg);
}