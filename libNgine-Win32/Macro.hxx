#pragma once
#if defined _DLL
	#define NAPI __declspec(dllexport)
#else
	#define NAPI __declspec(dllimport)
#endif