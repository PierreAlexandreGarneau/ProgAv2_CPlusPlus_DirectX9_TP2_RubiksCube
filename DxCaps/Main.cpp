#include <fstream>
#include <iostream>
#include <d3d9.h>
#include <dxerr.h>

void main()
{
	IDirect3D9* d3dObject = nullptr;
	d3dObject = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	HRESULT hr = d3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (FAILED(hr))
	{
		DXTrace(__FILE__, __LINE__, hr, "GetDeviceCaps -- Failed!", true);
	}

	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		std::cout << "Peut fonctionner avec T&L" << std::endl;
	}

	int modeCnt = 0;
	D3DDISPLAYMODE mode;
	std::ofstream file;

	file.open("AdapaterMode.txt");

	for (UINT i = 0; i < d3dObject->GetAdapterCount(); i++)
	{
		modeCnt = d3dObject->GetAdapterModeCount(i, D3DFMT_X8R8G8B8);
		for (int j = 0; j < modeCnt; j++)
		{
			d3dObject->EnumAdapterModes(i, D3DFMT_X8R8G8B8, j, &mode);
		
			file	<< "Width: " << mode.Width << std::endl
					<< "Height: " << mode.Height << std::endl
					<< "Format: " << mode.Format << std::endl
					<< "RefreshRate: " << mode.RefreshRate << std::endl << std::endl;
		}
	}

	file.close();
}