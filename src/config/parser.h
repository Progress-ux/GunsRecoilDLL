#ifndef GUNS_RECOIL_PARSER_H
#define GUNS_RECOIL_PARSER_H

#include "config_node.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void Config_Trim(char* str);
int Config_ParseLine(const char* line, ConfigEntry* entry);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GUNS_RECOIL_PARSER_H
