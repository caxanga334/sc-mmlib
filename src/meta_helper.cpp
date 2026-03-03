#include "meta_helper.h"
#include "misc_utils.h"

// keep in sync with the angelscript plugin
enum custom_key_types {
	KEY_TYPE_INTEGER,
	KEY_TYPE_FLOAT,
	KEY_TYPE_STRING,
	KEY_TYPE_VECTOR,
};

void hook_angelscript(std::string hook, std::string cmdname, void (*callback)()) {
	REG_SVR_COMMAND((char*)cmdname.c_str(), callback);
	g_engfuncs.pfnServerCommand(("as_command .RegisterHook \"" + hook + "\" \"" + cmdname + "\";").c_str());
	g_engfuncs.pfnServerExecute();
}

int readCustomKeyvalueInteger(edict_t* ent, std::string keyName) {
	int oldVal = ent->v.iuser4;

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyRead " + std::to_string(ENTINDEX(ent)) + " " + keyName + " 0;").c_str());
	g_engfuncs.pfnServerExecute();
	int retVal = ent->v.iuser4;

	ent->v.iuser4 = oldVal;

	return retVal;
}

float readCustomKeyvalueFloat(edict_t* ent, std::string keyName) {
	float oldVal = ent->v.fuser4;

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyRead " + std::to_string(ENTINDEX(ent)) + " " + keyName + " 1;").c_str());
	g_engfuncs.pfnServerExecute();
	float retVal = ent->v.fuser4;

	ent->v.iuser4 = oldVal;

	return retVal;
}

std::string readCustomKeyvalueString(edict_t* ent, std::string keyName) {
	string_t oldVal = ent->v.noise3;

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyRead " + std::to_string(ENTINDEX(ent)) + " " + keyName + " 2;").c_str());
	g_engfuncs.pfnServerExecute();
	std::string retVal = STRING(ent->v.noise3);

	ent->v.noise3 = oldVal;

	return retVal;
}

Vector readCustomKeyvalueVector(edict_t* ent, std::string keyName) {
	Vector oldVal = ent->v.vuser4;

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyRead " + std::to_string(ENTINDEX(ent)) + " " + keyName + " 3;").c_str());
	g_engfuncs.pfnServerExecute();
	Vector retVal = ent->v.vuser4;

	ent->v.vuser4 = oldVal;

	return retVal;
}

void writeCustomKeyvalue(edict_t* ent, std::string keyName, int value) {
	std::string args = std::to_string(ENTINDEX(ent)) + " " + std::to_string(KEY_TYPE_INTEGER) + " " + keyName + " " + std::to_string(value);

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void writeCustomKeyvalue(edict_t* ent, std::string keyName, float value) {
	std::string args = std::to_string(ENTINDEX(ent)) + " " + std::to_string(KEY_TYPE_FLOAT) + " " + keyName + " " + std::to_string(value);

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void writeCustomKeyvalue(edict_t* ent, std::string keyName, std::string value) {
	std::string args = std::to_string(ENTINDEX(ent)) + " " + std::to_string(KEY_TYPE_STRING) + " " + keyName + " " + value;

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void writeCustomKeyvalue(edict_t* ent, std::string keyName, Vector value) {
	std::string args = std::to_string(ENTINDEX(ent)) + " " + std::to_string(KEY_TYPE_VECTOR) + " " + keyName + " \"" + vecToString(value) + "\"";

	g_engfuncs.pfnServerCommand(("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

bool customKeyvalueExists(edict_t* ent, std::string keyName) {
	std::string args = std::to_string(ENTINDEX(ent)) + " " + keyName;

	int oldVal = ent->v.iuser4;
	g_engfuncs.pfnServerCommand(("as_command .CustomKeyExists " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
	int retVal = ent->v.iuser4;

	ent->v.iuser4 = oldVal;

	return retVal != 0;
}

void TakeDamage(edict_t* victim, edict_t* inflictor, edict_t* attacker, float damage, int damageType) {
	std::string s_victim = std::to_string(ENTINDEX(victim));
	std::string s_inflictor = std::to_string(ENTINDEX(inflictor));
	std::string s_attacker = std::to_string(ENTINDEX(attacker));
	std::string s_damage = std::to_string(damage);
	std::string s_damageType = std::to_string(damageType);
	std::string args = s_victim + " " + s_inflictor + " " + s_attacker + " " + s_damage + " " + s_damageType;
	
	g_engfuncs.pfnServerCommand(("as_command .EntTakeDamage " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void Killed(edict_t* victim, edict_t* attacker, int gibMode) {
	std::string s_victim = std::to_string(ENTINDEX(victim));
	std::string s_attacker = std::to_string(ENTINDEX(attacker));
	std::string s_gibMode = std::to_string(gibMode);
	std::string args = s_victim + " " + s_attacker + " " + s_gibMode;

	g_engfuncs.pfnServerCommand(("as_command .EntKill " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void Revive(edict_t* target) {
	g_engfuncs.pfnServerCommand(("as_command .EntRevive " + std::to_string(ENTINDEX(target)) + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void Use(edict_t* target, edict_t* activator, edict_t* caller, int useType) {
	std::string s_target = std::to_string(ENTINDEX(target));
	std::string s_activator = std::to_string(ENTINDEX(activator));
	std::string s_caller = std::to_string(ENTINDEX(caller));
	std::string s_useType = std::to_string(useType);
	std::string args = s_target + " " + s_activator + " " + s_caller + " " + s_useType;

	g_engfuncs.pfnServerCommand(("as_command .Use " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void PrecacheSound(const std::string& snd) {
	g_engfuncs.pfnServerCommand(("as_command .PrecacheSound " + snd + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void PrecacheModel(const std::string& mdl) {
	g_engfuncs.pfnServerCommand(("as_command .PrecacheModel " + mdl + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void PrecacheGeneric(const std::string& mdl) {
	g_engfuncs.pfnServerCommand(("as_command .PrecacheGeneric " + mdl + ";").c_str());
	g_engfuncs.pfnServerExecute();
}