#pragma once
#include "../../../../../Lib.h"


struct DialogData {
	HWND hwnd;
	int mode;
	const char *filter;
	char *selected_dir;
	char *selected_file;
	int unknown;
};
