#include "SPFIARParser.h"

bool spParserIsInt(const char* str) {
	int len = strlen(str);
	if (len == 0) { //str == ""
		return 0;
	}
	int i = 0;
	char c;
	if (str[0] == '-') {
		if (len == 1) { // str == '-'
			return 0;
		}
		i++;
	}
	for (; i < len; i++) {
		c = str[i];
		if (c < '0' || c > '9') {
			return 0;
		}
	}
	return 1;
}

int spPaserPraseInt(char* str) {
	int len = strlen(str);
	int x = 1;
	int base = 10;
	int ret = 0;
	while (len > 1) {
		ret += (str[len - 1] - '0') * x;
		x *= base;
		len--;
	}
	if (str[0] == '-') {
		return -ret;
	} else {
		return ret + (str[0] - '0') * x;
	}
}

SPCommand spParserPraseLine(const char* str) {
	char dest[1024];
	strcpy(dest, str);
//	char* number;
	SPCommand spcommand;
	char* delimeter = " ,.\n\t\r";
	char* token = strtok(dest, delimeter);
	spcommand.cmd = spPaserPraseCommand(token);
	if (spcommand.cmd == SP_INVALID_LINE)
	{
		spcommand.validArg = 0;
		return spcommand;
	}
	token = strtok(NULL, delimeter);
	spcommand.validArg = spParserIsInt(token);
	if (spcommand.validArg) {
		spcommand.arg = spPaserPraseInt(token);
	}
	return spcommand;
}

SP_COMMAND spPaserPraseCommand(char* str) {
	if (!str) { //if str is NULL
		return SP_INVALID_LINE;
	}
	if (strcmp(str, "undo_move") == 0) {
		return SP_UNDO_MOVE;
	} else if (strcmp(str, "add_disc") == 0) {
		return SP_ADD_DISC;
	} else if (strcmp(str, "suggest_move") == 0) {
		return SP_SUGGEST_MOVE;
	} else if (strcmp(str, "quit") == 0) {
		return SP_QUIT;
	} else if (strcmp(str, "restart") == 0) {
		return SP_RESTART;
	} else {
		return SP_INVALID_LINE;
	}
}

