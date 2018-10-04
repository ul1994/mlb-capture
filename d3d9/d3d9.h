#pragma once

#define INITGUID

#include <d3d9.h>
#include <dxerr.h>
#include <d3dx9.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "..\Common\Wrapper.h"
#include "..\Common\Logging.h"

typedef HRESULT(WINAPI *Direct3DShaderValidatorCreate9Proc)();
typedef HRESULT(WINAPI *PSGPErrorProc)();
typedef HRESULT(WINAPI *PSGPSampleTextureProc)();
typedef int(WINAPI *D3DPERF_BeginEventProc)(D3DCOLOR, LPCWSTR);
typedef int(WINAPI *D3DPERF_EndEventProc)();
typedef DWORD(WINAPI *D3DPERF_GetStatusProc)();
typedef BOOL(WINAPI *D3DPERF_QueryRepeatFrameProc)();
typedef void(WINAPI *D3DPERF_SetMarkerProc)(D3DCOLOR, LPCWSTR);
typedef void(WINAPI *D3DPERF_SetOptionsProc)(DWORD);
typedef void(WINAPI *D3DPERF_SetRegionProc)(D3DCOLOR, LPCWSTR);
typedef HRESULT(WINAPI *DebugSetLevelProc)(DWORD);
typedef void(WINAPI *DebugSetMuteProc)();
typedef void(WINAPI *Direct3D9EnableMaximizedWindowedModeShimProc)();
typedef IDirect3D9 *(WINAPI *Direct3DCreate9Proc)(UINT);
typedef HRESULT(WINAPI *Direct3DCreate9ExProc)(UINT, IDirect3D9Ex **);

#include "IDirect3D9.h"
#include "IDirect3D9Ex.h"
#include "IDirect3DDevice9.h"
#include "IDirect3DDevice9Ex.h"
#include "IDirect3DCubeTexture9.h"
#include "IDirect3DIndexBuffer9.h"
#include "IDirect3DPixelShader9.h"
#include "IDirect3DQuery9.h"
#include "IDirect3DStateBlock9.h"
#include "IDirect3DSurface9.h"
#include "IDirect3DSwapChain9.h"
#include "IDirect3DTexture9.h"
#include "IDirect3DVertexBuffer9.h"
#include "IDirect3DVertexDeclaration9.h"
#include "IDirect3DVertexShader9.h"
#include "IDirect3DVolume9.h"
#include "IDirect3DVolumeTexture9.h"

// TODO: import custom here?
//#include "Vector.h"
//#include "UnicodeString.h"
//#include "String.h"
//#include "Asserts.h"
//
//#include "Plane.h"
//
//#include "RGBColor.h"
//#include "Stdhdr.h"
//#include "SpaceVector.h"
//
//#include "Matrix4.h"

extern m_IDirect3DVertexShader9 * CurVShader;

#include "Overlay.h"

extern Overlay* m_Overlay;

#include "RenderManager.h"

extern RenderManager renderManager;





