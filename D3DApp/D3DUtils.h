#pragma once

#include "stdafx.h"

// Macro
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
		#define HR(x)\
		{\
			if(x)\
			{\
				HRESULT hr = x;\
				if(FAILED(hr))\
				{\
					DXTrace(__FILE__, __LINE__, hr, L#x, true);\
				}\
			}\
		}
	#endif
#else
	#ifndef HR
		#define HR(x) x;
	#endif
#endif

#ifndef ReleaseCOM

#define ReleaseCOM(x)		\
{							\
	x->Release();			\
	x = nullptr;			\
}

#endif // !ReleaseCOM
