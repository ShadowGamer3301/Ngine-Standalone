#pragma once
#ifdef _WIN32
	#ifdef DLL_EXPORT
		#define NAPI __declspec(dllexport)
	#else
		#define NAPI __declspec(dllimport)
	#endif
#endif