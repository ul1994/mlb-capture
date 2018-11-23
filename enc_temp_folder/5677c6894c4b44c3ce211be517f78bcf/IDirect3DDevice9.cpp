/**
* Copyright (C) 2018 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "d3d9.h"

RenderManager renderManager;
UINT ConstFloatRegisterCount = 256;
int frameCounter = 0;
int objCounter = 0;
boolean ingame = false;
std::vector<D3DXVECTOR4> vsConstants;

HRESULT m_IDirect3DDevice9::QueryInterface(REFIID riid, void** ppvObj)
{
	if ((riid == IID_IDirect3DDevice9 || riid == IID_IUnknown) && ppvObj)
	{
		AddRef();

		*ppvObj = this;

		return S_OK;
	}

	return ProxyInterface->QueryInterface(riid, ppvObj);
}

ULONG m_IDirect3DDevice9::AddRef()
{
	return ProxyInterface->AddRef();
}

ULONG m_IDirect3DDevice9::Release()
{
	ULONG count = ProxyInterface->Release();

	if (count == 0)
	{
		delete this;
	}

	return count;
}
HRESULT m_IDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	return ProxyInterface->Reset(pPresentationParameters);
}

HRESULT m_IDirect3DDevice9::EndScene()
{
	return ProxyInterface->EndScene();
}

void m_IDirect3DDevice9::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return ProxyInterface->SetCursorPosition(X, Y, Flags);
}

HRESULT m_IDirect3DDevice9::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap)
{
	if (pCursorBitmap)
	{
		pCursorBitmap = static_cast<m_IDirect3DSurface9 *>(pCursorBitmap)->GetProxyInterface();
	}

	return ProxyInterface->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

BOOL m_IDirect3DDevice9::ShowCursor(BOOL bShow)
{
	return ProxyInterface->ShowCursor(bShow);
}

HRESULT m_IDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **ppSwapChain)
{
	HRESULT hr = ProxyInterface->CreateAdditionalSwapChain(pPresentationParameters, ppSwapChain);

	if (SUCCEEDED(hr) && ppSwapChain)
	{
		*ppSwapChain = ProxyAddressLookupTable->FindAddress<m_IDirect3DSwapChain9>(*ppSwapChain);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::CreateCubeTexture(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);

	if (SUCCEEDED(hr) && ppCubeTexture)
	{
		*ppCubeTexture = ProxyAddressLookupTable->FindAddress<m_IDirect3DCubeTexture9>(*ppCubeTexture);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::CreateDepthStencilSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);

	if (SUCCEEDED(hr) && ppSurface)
	{
		*ppSurface = ProxyAddressLookupTable->FindAddress<m_IDirect3DSurface9>(*ppSurface);
	}

	return hr;
}

std::map<IDirect3DIndexBuffer9*, int> indexBufferSize;
HRESULT m_IDirect3DDevice9::CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);

	if (SUCCEEDED(hr) && ppIndexBuffer)
	{
		*ppIndexBuffer = ProxyAddressLookupTable->FindAddress<m_IDirect3DIndexBuffer9>(*ppIndexBuffer);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::CreateRenderTarget(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);

	if (SUCCEEDED(hr) && ppSurface)
	{
		*ppSurface = ProxyAddressLookupTable->FindAddress<m_IDirect3DSurface9>(*ppSurface);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::CreateTexture(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	if (SUCCEEDED(hr) && ppTexture)
	{
		*ppTexture = ProxyAddressLookupTable->FindAddress<m_IDirect3DTexture9>(*ppTexture);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateVertexBuffer(Length, 
		//Usage, 
		D3DUSAGE_SOFTWAREPROCESSING,
		FVF, Pool, ppVertexBuffer, pSharedHandle);

	if (SUCCEEDED(hr) && ppVertexBuffer)
	{
		*ppVertexBuffer = ProxyAddressLookupTable->FindAddress<m_IDirect3DVertexBuffer9>(*ppVertexBuffer);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::CreateVolumeTexture(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);

	if (SUCCEEDED(hr) && ppVolumeTexture)
	{
		*ppVolumeTexture = ProxyAddressLookupTable->FindAddress<m_IDirect3DVolumeTexture9>(*ppVolumeTexture);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::BeginStateBlock()
{
	return ProxyInterface->BeginStateBlock();
}

HRESULT m_IDirect3DDevice9::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	HRESULT hr = ProxyInterface->CreateStateBlock(Type, ppSB);

	if (SUCCEEDED(hr) && ppSB)
	{
		*ppSB = ProxyAddressLookupTable->FindAddress<m_IDirect3DStateBlock9>(*ppSB);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::EndStateBlock(THIS_ IDirect3DStateBlock9** ppSB)
{
	HRESULT hr = ProxyInterface->EndStateBlock(ppSB);

	if (SUCCEEDED(hr) && ppSB)
	{
		*ppSB = ProxyAddressLookupTable->FindAddress<m_IDirect3DStateBlock9>(*ppSB);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9 *pClipStatus)
{
	return ProxyInterface->GetClipStatus(pClipStatus);
}

HRESULT m_IDirect3DDevice9::GetDisplayMode(THIS_ UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return ProxyInterface->GetDisplayMode(iSwapChain, pMode);
}

HRESULT m_IDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue)
{
	return ProxyInterface->GetRenderState(State, pValue);
}

HRESULT m_IDirect3DDevice9::GetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	HRESULT hr = ProxyInterface->GetRenderTarget(RenderTargetIndex, ppRenderTarget);

	if (SUCCEEDED(hr) && ppRenderTarget)
	{
		*ppRenderTarget = ProxyAddressLookupTable->FindAddress<m_IDirect3DSurface9>(*ppRenderTarget);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix)
{
	return ProxyInterface->GetTransform(State, pMatrix);
}

HRESULT m_IDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9 *pClipStatus)
{
	return ProxyInterface->SetClipStatus(pClipStatus);
}

HRESULT m_IDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return ProxyInterface->SetRenderState(State, Value);
}

HRESULT m_IDirect3DDevice9::SetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	if (pRenderTarget)
	{
		pRenderTarget = static_cast<m_IDirect3DSurface9 *>(pRenderTarget)->GetProxyInterface();
	}

	return ProxyInterface->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT m_IDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix)
{
	return ProxyInterface->SetTransform(State, pMatrix);
}

void m_IDirect3DDevice9::GetGammaRamp(THIS_ UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	return ProxyInterface->GetGammaRamp(iSwapChain, pRamp);
}

void m_IDirect3DDevice9::SetGammaRamp(THIS_ UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	return ProxyInterface->SetGammaRamp(iSwapChain, Flags, pRamp);
}

HRESULT m_IDirect3DDevice9::DeletePatch(UINT Handle)
{
	return ProxyInterface->DeletePatch(Handle);
}

HRESULT m_IDirect3DDevice9::DrawRectPatch(UINT Handle, CONST float *pNumSegs, CONST D3DRECTPATCH_INFO *pRectPatchInfo)
{
	return ProxyInterface->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT m_IDirect3DDevice9::DrawTriPatch(UINT Handle, CONST float *pNumSegs, CONST D3DTRIPATCH_INFO *pTriPatchInfo)
{
	return ProxyInterface->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT m_IDirect3DDevice9::GetIndices(THIS_ IDirect3DIndexBuffer9** ppIndexData)
{
	HRESULT hr = ProxyInterface->GetIndices(ppIndexData);

	if (SUCCEEDED(hr) && ppIndexData)
	{
		*ppIndexData = ProxyAddressLookupTable->FindAddress<m_IDirect3DIndexBuffer9>(*ppIndexData);
	}

	return hr;
}

IDirect3DIndexBuffer9* validIndex = NULL;
HRESULT m_IDirect3DDevice9::SetIndices(THIS_ IDirect3DIndexBuffer9* pIndexData)
{
	if (pIndexData)
	{
		validIndex = pIndexData;
		pIndexData = static_cast<m_IDirect3DIndexBuffer9 *>(pIndexData)->GetProxyInterface();
	}

	return ProxyInterface->SetIndices(pIndexData);
}

UINT m_IDirect3DDevice9::GetAvailableTextureMem()
{
	return ProxyInterface->GetAvailableTextureMem();
}

HRESULT m_IDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return ProxyInterface->GetCreationParameters(pParameters);
}

HRESULT m_IDirect3DDevice9::GetDeviceCaps(D3DCAPS9 *pCaps)
{
	return ProxyInterface->GetDeviceCaps(pCaps);
}

HRESULT m_IDirect3DDevice9::GetDirect3D(IDirect3D9 **ppD3D9)
{
	if (!ppD3D9)
	{
		return D3DERR_INVALIDCALL;
	}

	if (m_pD3D)
	{
		m_pD3D->AddRef();

		*ppD3D9 = m_pD3D;
	}
	else if (m_pD3DEx)
	{
		m_pD3DEx->AddRef();

		*ppD3D9 = m_pD3DEx;
	}

	return D3D_OK;
}

HRESULT m_IDirect3DDevice9::GetRasterStatus(THIS_ UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return ProxyInterface->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT m_IDirect3DDevice9::GetLight(DWORD Index, D3DLIGHT9 *pLight)
{
	return ProxyInterface->GetLight(Index, pLight);
}

HRESULT m_IDirect3DDevice9::GetLightEnable(DWORD Index, BOOL *pEnable)
{
	return ProxyInterface->GetLightEnable(Index, pEnable);
}

HRESULT m_IDirect3DDevice9::GetMaterial(D3DMATERIAL9 *pMaterial)
{
	return ProxyInterface->GetMaterial(pMaterial);
}

HRESULT m_IDirect3DDevice9::LightEnable(DWORD LightIndex, BOOL bEnable)
{
	return ProxyInterface->LightEnable(LightIndex, bEnable);
}

HRESULT m_IDirect3DDevice9::SetLight(DWORD Index, CONST D3DLIGHT9 *pLight)
{

	return ProxyInterface->SetLight(Index, pLight);
}

HRESULT m_IDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9 *pMaterial)
{
	return ProxyInterface->SetMaterial(pMaterial);
}

HRESULT m_IDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix)
{
	return ProxyInterface->MultiplyTransform(State, pMatrix);
}

HRESULT m_IDirect3DDevice9::ProcessVertices(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	if (pDestBuffer)
	{
		pDestBuffer = static_cast<m_IDirect3DVertexBuffer9 *>(pDestBuffer)->GetProxyInterface();
	}

	if (pVertexDecl)
	{
		pVertexDecl = static_cast<m_IDirect3DVertexDeclaration9 *>(pVertexDecl)->GetProxyInterface();
	}

	return ProxyInterface->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT m_IDirect3DDevice9::TestCooperativeLevel()
{
	return ProxyInterface->TestCooperativeLevel();
}

HRESULT m_IDirect3DDevice9::GetCurrentTexturePalette(UINT *pPaletteNumber)
{
	return ProxyInterface->GetCurrentTexturePalette(pPaletteNumber);
}

HRESULT m_IDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries)
{
	return ProxyInterface->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT m_IDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return ProxyInterface->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT m_IDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY *pEntries)
{
	return ProxyInterface->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT m_IDirect3DDevice9::CreatePixelShader(THIS_ CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	HRESULT hr = ProxyInterface->CreatePixelShader(pFunction, ppShader);

	if (SUCCEEDED(hr) && ppShader)
	{
		*ppShader = ProxyAddressLookupTable->FindAddress<m_IDirect3DPixelShader9>(*ppShader);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::GetPixelShader(THIS_ IDirect3DPixelShader9** ppShader)
{
	HRESULT hr = ProxyInterface->GetPixelShader(ppShader);

	if (SUCCEEDED(hr) && ppShader)
	{
		*ppShader = ProxyAddressLookupTable->FindAddress<m_IDirect3DPixelShader9>(*ppShader);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::SetPixelShader(THIS_ IDirect3DPixelShader9* pShader)
{
	if (pShader)
	{
		pShader = static_cast<m_IDirect3DPixelShader9 *>(pShader)->GetProxyInterface();
	}

	return ProxyInterface->SetPixelShader(pShader);
}

HRESULT m_IDirect3DDevice9::Present(CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion)
{
	// NOTE: render texts here
	m_Overlay->RenderConsole();
	return ProxyInterface->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

std::string matrixString(float*matrix, int width, int height, std::string prefix="") {
	char buff[256];
	sprintf(buff, "%sMatrix: %d x %d\n", (char*)prefix.c_str(), width, height);
	
	std::string out = std::string(buff);

	for (int hh = 0; hh < height; hh++) {
		out += prefix;
		for (int ww = 0; ww < width; ww++) {
			int ind = height * hh + ww;
			sprintf(buff, "%f ", matrix[ind]);
			out += std::string(buff);
		}
		out += "\n";
	}

	return out;
}

void m_IDirect3DDevice9::identifyStride(
	IDirect3DVertexDeclaration9* ppDecl, 
	int *stride, int *postype, char* typeString,
	int *blendOffset) {

	std::string names[] = {
		"D3DDECLTYPE_FLOAT1",
		"D3DDECLTYPE_FLOAT2",
		"D3DDECLTYPE_FLOAT3",
		"D3DDECLTYPE_FLOAT4",
		"D3DDECLTYPE_D3DCOLOR",
		"D3DDECLTYPE_UBYTE4",
		"D3DDECLTYPE_SHORT2",
		"D3DDECLTYPE_SHORT4",
		"D3DDECLTYPE_UBYTE4N",
		"D3DDECLTYPE_SHORT2N",
		"D3DDECLTYPE_SHORT4N",
		"D3DDECLTYPE_USHORT2N",
		"D3DDECLTYPE_USHORT4N",
		"D3DDECLTYPE_UDEC3",
		"D3DDECLTYPE_DEC3N",
		"D3DDECLTYPE_FLOAT16_2",
		"D3DDECLTYPE_FLOAT16_4",
		"D3DDECLTYPE_UNUSED",
	};

	int typeSize[] = {
		/*
		"D3DDECLTYPE_FLOAT1",
		"D3DDECLTYPE_FLOAT2",
		"D3DDECLTYPE_FLOAT3",
		"D3DDECLTYPE_FLOAT4", */
		4, 4 * 2, 4 * 3, 4 * 4,
		/*
		"D3DDECLTYPE_D3DCOLOR",
		"D3DDECLTYPE_UBYTE4", */
		4, 4,
		/*
		"D3DDECLTYPE_SHORT2",
		"D3DDECLTYPE_SHORT4", */
		2 * 2, 2 * 4,
		/*
		"D3DDECLTYPE_UBYTE4N",
		"D3DDECLTYPE_SHORT2N",
		"D3DDECLTYPE_SHORT4N",
		"D3DDECLTYPE_USHORT2N",
		"D3DDECLTYPE_USHORT4N", */
		4, 2 * 2, 2 * 4, 2 * 2, 2 * 4,
		/*
		"D3DDECLTYPE_UDEC3",
		"D3DDECLTYPE_DEC3N",
		"D3DDECLTYPE_FLOAT16_2",
		"D3DDECLTYPE_FLOAT16_4",
		"D3DDECLTYPE_UNUSED" */
		0, 0,
		2 * 2, 2 * 4,
		0
	};

	std::string use_names[] = {
		"D3DDECLUSAGE_POSITION",
		"D3DDECLUSAGE_BLENDWEIGHT",
		"D3DDECLUSAGE_BLENDINDICES",
		"D3DDECLUSAGE_NORMAL",
		"D3DDECLUSAGE_PSIZE",
		"D3DDECLUSAGE_TEXCOORD",
		"D3DDECLUSAGE_TANGENT",
		"D3DDECLUSAGE_BINORMAL",
		"D3DDECLUSAGE_TESSFACTOR",
		"D3DDECLUSAGE_POSITIONT",
		"D3DDECLUSAGE_COLOR",
		"D3DDECLUSAGE_FOG",
		"D3DDECLUSAGE_DEPTH",
		"D3DDECLUSAGE_SAMPLE"
	};

	char buff[256];
	D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH];
	UINT numElements;
	HRESULT hr = ppDecl->GetDeclaration(decl, &numElements);

	if (FAILED(hr)) {
		Log() << " ! VTYPE FAILED";
		return;
	}

	std::vector<std::string> typeLog;
	sprintf(buff, "  Identifying declaration: %d", numElements);
	typeLog.push_back(std::string(buff));

	std::string debugStr = "";
	int dynStride = 0;
	bool foundBlend = false;
	for (int ii = 0; ii < numElements - 1; ii++) {
		int typei = 0;
		int usei = 0;

		for (typei = 0; typei < 18; typei++)
			if (static_cast<D3DDECLTYPE>(typei) == decl[ii].Type)
				break;
		for (usei = 0; usei < 14; usei++)
			if (static_cast<D3DDECLUSAGE>(usei) == decl[ii].Usage)
				break;

		if (typei == 18) goto CantIdentify;
		int amount = typeSize[typei];
		if (amount == 0) goto CantIdentify;

		if (!foundBlend && usei == 2) {
			*blendOffset = dynStride;
			foundBlend = true;
		}
		dynStride += amount;
		if (ii == 0) {
			if (typei == 2 || typei == 3) *postype = 0;
			else *postype = 1;
		}

		sprintf(buff, "   %d: %s  %s", ii, names[typei].c_str(), use_names[usei].c_str());
		typeLog.push_back(std::string(buff));
	}
	*stride = dynStride;

	
	for (int ii = 0; ii < typeLog.size(); ii++) {
		debugStr += "# ";
		debugStr += typeLog[ii];
		debugStr += "\n";
	}
	sprintf(typeString, "%s", debugStr.c_str());

	return;

CantIdentify:
	for (int ii = 0; ii < typeLog.size(); ii++)
		Log() << typeLog[ii];
	Log() << "^^^^^^^^^^^^ UNKNOWN DTYPE ^^^^^^^^^^^^";
	MessageBox(NULL, L"Unknown Type", L"DEBUG", MB_OK);
	return;

TODOType:
	for (int ii = 0; ii < typeLog.size(); ii++)
		Log() << typeLog[ii];
	Log() << "^^^^^^^^^^^^ SHORT POS VECTOR ^^^^^^^^^^^^";
	MessageBox(NULL, L"Short Dtype used...", L"DEBUG", MB_OK);
	return;
}

void m_IDirect3DDevice9::getProcessedVerts(FLOAT** pVerts, int MinVertexIndex, int NumVertices) {

	IDirect3DVertexBuffer9 *procBuff = NULL;
	int sizeInBytes = sizeof(FLOAT) * 4 * NumVertices * 4;
	HRESULT hr = CreateVertexBuffer(
		sizeInBytes, 
		D3DUSAGE_SOFTWAREPROCESSING,
		D3DFVF_XYZRHW, D3DPOOL_MANAGED, &procBuff, NULL);
	if (FAILED(hr)) Log() << "! PROC CREATE FAILED";

	VOID * pVoid; // move verts to buffer
	/*
	hr = procBuff->Lock(0, sizeInBytes, &pVoid, 0);
	memcpy(pVoid, *pVerts, sizeInBytes);
	procBuff->Unlock();
	*/
	
	D3DVERTEXELEMENT9 simple_decl[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
		D3DDECL_END()
	};
	IDirect3DVertexDeclaration9* outdec = NULL;
	hr = CreateVertexDeclaration(simple_decl, &outdec);
	if (FAILED(hr)) Log() << "! OUT DECL FAILED";

	hr = procBuff->Lock(0, sizeInBytes, &pVoid, 0);
	hr = ProcessVertices(MinVertexIndex, 0, NumVertices, procBuff, outdec, 0);
	outdec->Release();
	//hr = ProcessVertices(MinVertexIndex, 0, NumVertices, procBuff, outdec, 0);
	if (FAILED(hr)) Log() << "! VERTEX PROC FAILED";

	
	if (FAILED(hr)) Log() << "! PROC LOCK FAILED";
	memcpy(*pVerts, pVoid, sizeInBytes);
	procBuff->Unlock();
EndProc:
	procBuff->Release();
}

HRESULT m_IDirect3DDevice9::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	if (NumVertices > 50 && Type == D3DPT_TRIANGLELIST) {
		// Signifies that in-game rendering has begun
		ingame = true;
	}

	if (ingame && NumVertices > 100 && Type == D3DPT_TRIANGLESTRIP && frameCounter % 500 == 0) {
		Log() << "TriangleStrip  PCnt " << primCount << "  Nvs " << NumVertices << "  SInd " << startIndex << "  MinV "<< MinVertexIndex;

		IDirect3DIndexBuffer9* localIndex = NULL;
		GetIndices(&localIndex);

		VOID * pVoid;
		char buff[256];
		int startInBytes = sizeof(short) * startIndex;
		int range = primCount +2;
		int rangeInBytes = sizeof(short) * range;
		HRESULT hr = localIndex->Lock(startInBytes, rangeInBytes, &pVoid, 0);
		if (FAILED(hr)) {
			Log() << "! INDEX LOCK FAILED";
			localIndex->Release();
			goto EndDrawIndexedPrimitive;
		}	
		short* indices = new short[range];
		memcpy(indices, pVoid, rangeInBytes);
		localIndex->Unlock();
		localIndex->Release();

		short minInd = indices[0];
		short maxInd = indices[0];
		for (int ii = 0; ii < range; ii++) {
			if (indices[ii] < minInd) minInd = indices[ii];
			if (indices[ii] > maxInd) maxInd = indices[ii];
		}
			
		// TriangleStrip Contd.
		int dataStride = -1;
		int blendOffset = -1;
		int posType = -1;
		char typeString[512];
		identifyStride(vertexType, &dataStride, &posType, typeString, &blendOffset);
		if (dataStride == -1 || posType == 1) {
			// UNIDENTIFIED VERTEX TYPE
			delete indices;
			goto EndDrawIndexedPrimitive;
		}
		if (blendOffset == -1) {
			// non-blended mesh
			Log() << typeString;
			delete indices;
			goto EndDrawIndexedPrimitive;
		}
		if (dataStride != bufferStride) {
			Log() << typeString;
			Log() << " WARN: Stride Mismatch: Guessed " << dataStride << " vs  Stride " << bufferStride;
			MessageBox(NULL, L"Stride Mismatch", L"WARN", MB_OK);
			/*delete indices;
			goto EndDrawIndexedPrimitive;*/
			dataStride = bufferStride; // case when vdata is split across many buffers
		}
	
		int vertexStartInBytes = dataStride * (MinVertexIndex);
		int vertexRange = (maxInd - minInd) + 1;
		int vertexRangeInBytes = dataStride * vertexRange;
		if (vertexRange != NumVertices) {
			Log() << "! Index Range Inconsistent";
			Log() << "  " << indices[0] << " " << indices[range - 1];
			Log() << "  " << maxInd << " " << minInd << " " << vertexRange << " " << dataStride;
			delete indices; // only thing in use?
			goto EndDrawIndexedPrimitive;
		}
		hr = validVertex->Lock(vertexStartInBytes, vertexRangeInBytes, &pVoid, 0);
		if (FAILED(hr)) {
			Log() << "! VERTEX LOCK FAILED";
			delete indices; // only thing in use?
			goto EndDrawIndexedPrimitive;
		}
		VOID* verts = malloc(vertexRangeInBytes);
		memcpy(verts, pVoid, vertexRangeInBytes);
		validVertex->Unlock();
		
		std::ofstream myfile;
		sprintf(buff, "meshes/frame%d_strip_o%d_s%d_%d.obj", frameCounter, objCounter, dataStride, primCount);
		myfile.open(buff);

		// debug info
		sprintf(buff, "# STRIDE %d  BUFFSTRIDE %d  DTYPE %d\n", dataStride, bufferStride, posType);
		myfile << buff;

		myfile << "# Constants:\n";
		for (int reg = 0; reg < vsConstants.size(); reg++) {
			D3DXVECTOR4 vec = vsConstants[reg];
			sprintf(buff, "# %d %f %f %f %f\n", reg, vec.x, vec.y, vec.z, vec.w);
			myfile << buff;
		}
		myfile << typeString;

		for (int jj = 0; jj < vertexRange; jj++) {
			FLOAT* casted = NULL;
			VOID* vertexPointer = (char*)verts + dataStride * jj;
			unsigned char* blendInds = (unsigned char*)vertexPointer + blendOffset;
			
			if (posType == 0) {
				casted = (FLOAT*)vertexPointer;
			}
			else {
				casted = (FLOAT*)malloc(sizeof(FLOAT) * 3);
				D3DXFloat16To32Array(casted, (D3DXFLOAT16*)vertexPointer, 3);
			}

			float vert[] = { casted[0], casted[1], casted[2] };
			D3DXVECTOR4 vout = vert;
			
			sprintf(buff, "# w %f\n", vout.w);
			myfile << buff;

			sprintf(buff, "# o %f %f %f\n",
				vert[0],
				vert[1],
				vert[2]);
			myfile << buff;

			sprintf(buff, "# blend %d %d %d\n",
				(int) blendInds[0],
				(int) blendInds[1],
				(int) blendInds[2]);
			myfile << buff;

			sprintf(buff, "v %f %f %f\n",
				vout.x,
				vout.y,
				vout.z);
			myfile << buff;

			if (posType == 1) delete casted;
		}

		for (int ii = 2; ii < primCount; ii ++) {
			// FIXME: first index not necessarily the CCW triangle.. or is it always?
			// FIXME: Exclude degenerative (0 area) faces
			if (ii % 2 == 0) {
				sprintf(buff, "f %d %d %d\n",
					indices[ii - 2] - MinVertexIndex + 1,
					indices[ii - 1] - MinVertexIndex + 1,
					indices[ii - 0] - MinVertexIndex + 1);
			}
			else {
				// reverse for alternating triangles
				sprintf(buff, "f %d %d %d\n",
					indices[ii - 2] - MinVertexIndex + 1,
					indices[ii - 0] - MinVertexIndex + 1,
					indices[ii - 1] - MinVertexIndex + 1);
			}
			myfile << buff;
		}
		myfile.close();

		delete verts;
		delete indices;

		//MessageBox(NULL, L"TriangleStrip Once", L"DEBUG", MB_OK);
	}
	else if (ingame && NumVertices > 100 && Type == D3DPT_TRIANGLELIST && frameCounter % 500 == 0) {
	//if (false) {
		Log() << "TriangleList   PCnt " << primCount << "  Nvs " << NumVertices << "  SInd " << startIndex << "  MinV " << MinVertexIndex << "  BaseV " << BaseVertexIndex;

		IDirect3DIndexBuffer9* localIndex = NULL;
		GetIndices(&localIndex);

		VOID * pVoid;
		char buff[256];
		int startInBytes = sizeof(short) * startIndex;
		int range = 3 * primCount;
		int rangeInBytes = sizeof(short) * range;
		HRESULT hr = localIndex->Lock(startInBytes, rangeInBytes, &pVoid, 0);
		if (FAILED(hr)) {
			Log() << "! LOCK FAILED";
			localIndex->Release();
			goto EndDrawIndexedPrimitive;
		}
		short* indices = new short[range];
		memcpy(indices, pVoid, rangeInBytes);
		localIndex->Unlock();
		localIndex->Release();

		short minInd = indices[0];
		short maxInd = indices[0];
		for (int ii = 0; ii < range; ii++) {
			if (indices[ii] < minInd) minInd = indices[ii];
			if (indices[ii] > maxInd) maxInd = indices[ii];
		}

		int dataStride = -1;
		int posType = -1;
		char typeString[512];
		int blendOffset = -1;
		identifyStride(vertexType, &dataStride, &posType, typeString, &blendOffset);
		if (dataStride == -1 || posType == -1) {
			// UNIDENTIFIED VERTEX TYPE
			// TODO: SHORT2 positions 
			delete indices;
			goto EndDrawIndexedPrimitive;
		}
		
		int vertexStartInBytes = dataStride * (MinVertexIndex);
		int vertexRange = (maxInd - minInd) + 1;
		int vertexRangeInBytes = dataStride * vertexRange;
		if (vertexRange != NumVertices) {
			Log() << "! Index Range Inconsistent";
			Log() << "  " << indices[0] << " " << indices[range - 1];
			Log() << "  " << maxInd << " " << minInd << " " << vertexRange;
			delete indices; // only thing in use?
			goto EndDrawIndexedPrimitive;
		}
		if (blendOffset == -1) {
			// non-blended mesh
			Log() << typeString;
			delete indices;
			goto EndDrawIndexedPrimitive;
		}

		hr = validVertex->Lock(vertexStartInBytes, vertexRangeInBytes, &pVoid, 0);
		if (FAILED(hr)) {
			Log() << "! VERTEX LOCK FAILED";
			delete indices; // only thing in use?
			goto EndDrawIndexedPrimitive;
		}
		
		VOID* verts = malloc(vertexRangeInBytes);
		memcpy(verts, pVoid, vertexRangeInBytes);
		validVertex->Unlock();

		std::ofstream myfile;
		sprintf(buff, "meshes/frame%d_list_o%d_s%d_%d.obj", frameCounter, objCounter, dataStride, primCount);
		objCounter++;
		myfile.open(buff);

		sprintf(buff, "# STRIDE %d  BUFFSTRIDE %d  DTYPE %d\n", dataStride, bufferStride, posType);
		myfile << buff;

		myfile << typeString;

		// NOTE: strided skipping is resilient to inconsistent vertex fields
		//   unless stride itself is incorrect!
		for (int jj = 0; jj < vertexRange; jj++) {
			FLOAT* casted = NULL;
			VOID* vertexPointer = (char*)verts + dataStride * jj;
			unsigned char* blendInds = (unsigned char*)vertexPointer + blendOffset;

			if (posType == 0) {
				casted = (FLOAT*)vertexPointer;
			}
			else {
				casted = (FLOAT*)malloc(sizeof(FLOAT) * 3);
				D3DXFloat16To32Array(casted, (D3DXFLOAT16*)vertexPointer, 3);
			}

			sprintf(buff, "# blend %d %d %d\n",
				(int)blendInds[0],
				(int)blendInds[1],
				(int)blendInds[2]);
			myfile << buff;

			sprintf(buff, "v %f %f %f\n",
				casted[0],
				casted[1],
				casted[2]);
			myfile << buff;
		}

		for (int ii = 0; ii < 3 * primCount; ii +=3) {
			sprintf(buff, "f %d %d %d\n",
				indices[ii + 0] - MinVertexIndex + 1,
				indices[ii + 1] - MinVertexIndex + 1,
				indices[ii + 2] - MinVertexIndex + 1);
			myfile << buff;
		}
		myfile.close();

		delete indices;
		delete verts;
	}
	
	objCounter++;
EndDrawIndexedPrimitive:
	return ProxyInterface->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT m_IDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, CONST void *pIndexData, D3DFORMAT IndexDataFormat, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return ProxyInterface->DrawIndexedPrimitiveUP(PrimitiveType, MinIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT m_IDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return ProxyInterface->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT m_IDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	// TODO: High volume renders happening here
	// But they are pointlists?
	/*if (PrimitiveCount > 100) {
		Log() << "DrawPrimitiveUP  P " << PrimitiveCount << "  T " << PrimitiveType << "  S " << VertexStreamZeroStride;

		char buff[256];
		std::ofstream myfile;
		sprintf(buff, "meshes/up_%d_%d.obj", frameCounter, PrimitiveCount);
		myfile.open(buff);

		FLOAT* verts = (FLOAT*)pVertexStreamZeroData;
		for (int ii = 0; ii < 12; ii+=4) {
			sprintf(buff, "  %d %f %f %f %f", ii, verts[ii + 0], verts[ii + 1], verts[ii + 2], verts[ii + 3]);
			Log() << "   " << buff;
		}
	}*/
	return ProxyInterface->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT m_IDirect3DDevice9::BeginScene()
{
	//Log() << "BeginScene";
	frameCounter += 1;
	objCounter = 0;
	Log() << "Frame " << frameCounter;
	if (ingame && frameCounter % 500 == 1) {
		MessageBox(NULL, L"One Frame", L"DEBUG", MB_OK);
	}
	return ProxyInterface->BeginScene();
}

HRESULT m_IDirect3DDevice9::GetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride)
{
	HRESULT hr = ProxyInterface->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);

	if (SUCCEEDED(hr) && ppStreamData)
	{
		*ppStreamData = ProxyAddressLookupTable->FindAddress<m_IDirect3DVertexBuffer9>(*ppStreamData);
	}

	return hr;
}

IDirect3DVertexBuffer9* validVertex = NULL;
int bufferStride = 0;
HRESULT m_IDirect3DDevice9::SetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	//Log() << "SetStream " << StreamNumber;
	if (pStreamData)
	{
		if (StreamNumber == 0) bufferStride = Stride;
		validVertex = pStreamData;
		//Log() << "SetStreamSource N " << StreamNumber << "  Std " << Stride;
		pStreamData = static_cast<m_IDirect3DVertexBuffer9 *>(pStreamData)->GetProxyInterface();
	}

	return ProxyInterface->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT m_IDirect3DDevice9::GetBackBuffer(THIS_ UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	HRESULT hr = ProxyInterface->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);

	if (SUCCEEDED(hr) && ppBackBuffer)
	{
		*ppBackBuffer = ProxyAddressLookupTable->FindAddress<m_IDirect3DSurface9>(*ppBackBuffer);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9 **ppZStencilSurface)
{
	HRESULT hr = ProxyInterface->GetDepthStencilSurface(ppZStencilSurface);

	if (SUCCEEDED(hr) && ppZStencilSurface)
	{
		*ppZStencilSurface = ProxyAddressLookupTable->FindAddress<m_IDirect3DSurface9>(*ppZStencilSurface);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::GetTexture(DWORD Stage, IDirect3DBaseTexture9 **ppTexture)
{
	HRESULT hr = ProxyInterface->GetTexture(Stage, ppTexture);

	if (SUCCEEDED(hr) && ppTexture && *ppTexture)
	{
		switch ((*ppTexture)->GetType())
		{
		case D3DRTYPE_TEXTURE:
			*ppTexture = ProxyAddressLookupTable->FindAddress<m_IDirect3DTexture9>(*ppTexture);
			break;
		case D3DRTYPE_VOLUMETEXTURE:
			*ppTexture = ProxyAddressLookupTable->FindAddress<m_IDirect3DVolumeTexture9>(*ppTexture);
			break;
		case D3DRTYPE_CUBETEXTURE:
			*ppTexture = ProxyAddressLookupTable->FindAddress<m_IDirect3DCubeTexture9>(*ppTexture);
			break;
		default:
			return D3DERR_INVALIDCALL;
		}
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue)
{
	return ProxyInterface->GetTextureStageState(Stage, Type, pValue);
}

HRESULT m_IDirect3DDevice9::SetTexture(DWORD Stage, IDirect3DBaseTexture9 *pTexture)
{
	if (pTexture)
	{
		switch (pTexture->GetType())
		{
		case D3DRTYPE_TEXTURE:
			pTexture = static_cast<m_IDirect3DTexture9 *>(pTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_VOLUMETEXTURE:
			pTexture = static_cast<m_IDirect3DVolumeTexture9 *>(pTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_CUBETEXTURE:
			pTexture = static_cast<m_IDirect3DCubeTexture9 *>(pTexture)->GetProxyInterface();
			break;
		default:
			return D3DERR_INVALIDCALL;
		}
	}

	return ProxyInterface->SetTexture(Stage, pTexture);
}

HRESULT m_IDirect3DDevice9::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return ProxyInterface->SetTextureStageState(Stage, Type, Value);
}

HRESULT m_IDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture)
{
	if (pSourceTexture)
	{
		switch (pSourceTexture->GetType())
		{
		case D3DRTYPE_TEXTURE:
			pSourceTexture = static_cast<m_IDirect3DTexture9 *>(pSourceTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_VOLUMETEXTURE:
			pSourceTexture = static_cast<m_IDirect3DVolumeTexture9 *>(pSourceTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_CUBETEXTURE:
			pSourceTexture = static_cast<m_IDirect3DCubeTexture9 *>(pSourceTexture)->GetProxyInterface();
			break;
		default:
			return D3DERR_INVALIDCALL;
		}
	}
	if (pDestinationTexture)
	{
		switch (pDestinationTexture->GetType())
		{
		case D3DRTYPE_TEXTURE:
			pDestinationTexture = static_cast<m_IDirect3DTexture9 *>(pDestinationTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_VOLUMETEXTURE:
			pDestinationTexture = static_cast<m_IDirect3DVolumeTexture9 *>(pDestinationTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_CUBETEXTURE:
			pDestinationTexture = static_cast<m_IDirect3DCubeTexture9 *>(pDestinationTexture)->GetProxyInterface();
			break;
		default:
			return D3DERR_INVALIDCALL;
		}
	}

	return ProxyInterface->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT m_IDirect3DDevice9::ValidateDevice(DWORD *pNumPasses)
{
	return ProxyInterface->ValidateDevice(pNumPasses);
}

HRESULT m_IDirect3DDevice9::GetClipPlane(DWORD Index, float *pPlane)
{
	return ProxyInterface->GetClipPlane(Index, pPlane);
}

HRESULT m_IDirect3DDevice9::SetClipPlane(DWORD Index, CONST float *pPlane)
{
	return ProxyInterface->SetClipPlane(Index, pPlane);
}

HRESULT m_IDirect3DDevice9::Clear(DWORD Count, CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return ProxyInterface->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT m_IDirect3DDevice9::GetViewport(D3DVIEWPORT9 *pViewport)
{
	return ProxyInterface->GetViewport(pViewport);
}

HRESULT m_IDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9 *pViewport)
{
	return ProxyInterface->SetViewport(pViewport);
}

HRESULT m_IDirect3DDevice9::CreateVertexShader(THIS_ CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	HRESULT hr = ProxyInterface->CreateVertexShader(pFunction, ppShader);

	if (SUCCEEDED(hr) && ppShader)
	{
		*ppShader = ProxyAddressLookupTable->FindAddress<m_IDirect3DVertexShader9>(*ppShader);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::GetVertexShader(THIS_ IDirect3DVertexShader9** ppShader)
{
	HRESULT hr = ProxyInterface->GetVertexShader(ppShader);

	if (SUCCEEDED(hr) && ppShader)
	{
		*ppShader = ProxyAddressLookupTable->FindAddress<m_IDirect3DVertexShader9>(*ppShader);
	}

	return hr;
}

IDirect3DVertexShader9 * CurVShader = NULL;

HRESULT m_IDirect3DDevice9::SetVertexShader(THIS_ IDirect3DVertexShader9* pShader)
{
	if (pShader)
	{
		CurVShader = pShader;
		pShader = static_cast<m_IDirect3DVertexShader9 *>(pShader)->GetProxyInterface();
	}

	return ProxyInterface->SetVertexShader(pShader);
}

HRESULT m_IDirect3DDevice9::CreateQuery(THIS_ D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	HRESULT hr = ProxyInterface->CreateQuery(Type, ppQuery);

	if (SUCCEEDED(hr) && ppQuery)
	{
		*ppQuery = ProxyAddressLookupTable->FindAddress<m_IDirect3DQuery9>(*ppQuery);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::SetPixelShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	return ProxyInterface->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT m_IDirect3DDevice9::GetPixelShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return ProxyInterface->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT m_IDirect3DDevice9::SetPixelShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return ProxyInterface->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT m_IDirect3DDevice9::GetPixelShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return ProxyInterface->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT m_IDirect3DDevice9::SetPixelShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return ProxyInterface->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT m_IDirect3DDevice9::GetPixelShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return ProxyInterface->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT m_IDirect3DDevice9::SetStreamSourceFreq(THIS_ UINT StreamNumber, UINT Divider)
{
	return ProxyInterface->SetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT m_IDirect3DDevice9::GetStreamSourceFreq(THIS_ UINT StreamNumber, UINT* Divider)
{
	return ProxyInterface->GetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT m_IDirect3DDevice9::SetVertexShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	return ProxyInterface->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT m_IDirect3DDevice9::GetVertexShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return ProxyInterface->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT m_IDirect3DDevice9::SetVertexShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	//if (ingame) Log() << "SetVertexShaderConstantF  St " << StartRegister << "   N " << Vector4fCount;
	
	while (vsConstants.size() < StartRegister + Vector4fCount)
		vsConstants.push_back(D3DXVECTOR4(-1, 0, 0, -1));

	for (int ii = 0; ii < Vector4fCount; ii++) {
		int offset = 4 * ii;
		
		vsConstants[StartRegister + ii].x = pConstantData[offset + 0];
		vsConstants[StartRegister + ii].y = pConstantData[offset + 1];
		vsConstants[StartRegister + ii].z = pConstantData[offset + 2];
		vsConstants[StartRegister + ii].w = pConstantData[offset + 3];
	}

	return ProxyInterface->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT m_IDirect3DDevice9::GetVertexShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return ProxyInterface->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT m_IDirect3DDevice9::SetVertexShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return ProxyInterface->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT m_IDirect3DDevice9::GetVertexShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return ProxyInterface->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT m_IDirect3DDevice9::SetFVF(THIS_ DWORD FVF)
{
	return ProxyInterface->SetFVF(FVF);
}

HRESULT m_IDirect3DDevice9::GetFVF(THIS_ DWORD* pFVF)
{
	return ProxyInterface->GetFVF(pFVF);
}

HRESULT m_IDirect3DDevice9::CreateVertexDeclaration(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	HRESULT hr = ProxyInterface->CreateVertexDeclaration(pVertexElements, ppDecl);

	if (SUCCEEDED(hr) && ppDecl)
	{
		*ppDecl = ProxyAddressLookupTable->FindAddress<m_IDirect3DVertexDeclaration9>(*ppDecl);
	}

	return hr;
}

IDirect3DVertexDeclaration9* vertexType = NULL;
HRESULT m_IDirect3DDevice9::SetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9* pDecl)
{
	if (pDecl)
	{
		vertexType = pDecl;
		pDecl = static_cast<m_IDirect3DVertexDeclaration9 *>(pDecl)->GetProxyInterface();
	}

	return ProxyInterface->SetVertexDeclaration(pDecl);
}

HRESULT m_IDirect3DDevice9::GetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9** ppDecl)
{
	HRESULT hr = ProxyInterface->GetVertexDeclaration(ppDecl);

	if (SUCCEEDED(hr) && ppDecl)
	{
		*ppDecl = ProxyAddressLookupTable->FindAddress<m_IDirect3DVertexDeclaration9>(*ppDecl);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::SetNPatchMode(THIS_ float nSegments)
{
	return ProxyInterface->SetNPatchMode(nSegments);
}

float m_IDirect3DDevice9::GetNPatchMode(THIS)
{
	return ProxyInterface->GetNPatchMode();
}

int m_IDirect3DDevice9::GetSoftwareVertexProcessing(THIS)
{
	return ProxyInterface->GetSoftwareVertexProcessing();
}

unsigned int m_IDirect3DDevice9::GetNumberOfSwapChains(THIS)
{
	return ProxyInterface->GetNumberOfSwapChains();
}

HRESULT m_IDirect3DDevice9::EvictManagedResources(THIS)
{
	return ProxyInterface->EvictManagedResources();
}

HRESULT m_IDirect3DDevice9::SetSoftwareVertexProcessing(THIS_ BOOL bSoftware)
{
	return ProxyInterface->SetSoftwareVertexProcessing(bSoftware);
}

HRESULT m_IDirect3DDevice9::SetScissorRect(THIS_ CONST RECT* pRect)
{
	return ProxyInterface->SetScissorRect(pRect);
}

HRESULT m_IDirect3DDevice9::GetScissorRect(THIS_ RECT* pRect)
{
	return ProxyInterface->GetScissorRect(pRect);
}

HRESULT m_IDirect3DDevice9::GetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return ProxyInterface->GetSamplerState(Sampler, Type, pValue);
}

HRESULT m_IDirect3DDevice9::SetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return ProxyInterface->SetSamplerState(Sampler, Type, Value);
}

HRESULT m_IDirect3DDevice9::SetDepthStencilSurface(THIS_ IDirect3DSurface9* pNewZStencil)
{
	if (pNewZStencil)
	{
		pNewZStencil = static_cast<m_IDirect3DSurface9 *>(pNewZStencil)->GetProxyInterface();
	}

	return ProxyInterface->SetDepthStencilSurface(pNewZStencil);
}

HRESULT m_IDirect3DDevice9::CreateOffscreenPlainSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	HRESULT hr = ProxyInterface->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);

	if (SUCCEEDED(hr) && ppSurface)
	{
		*ppSurface = ProxyAddressLookupTable->FindAddress<m_IDirect3DSurface9>(*ppSurface);
	}

	return hr;
}

HRESULT m_IDirect3DDevice9::ColorFill(THIS_ IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	if (pSurface)
	{
		pSurface = static_cast<m_IDirect3DSurface9 *>(pSurface)->GetProxyInterface();
	}

	return ProxyInterface->ColorFill(pSurface, pRect, color);
}

HRESULT m_IDirect3DDevice9::StretchRect(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	if (pSourceSurface)
	{
		pSourceSurface = static_cast<m_IDirect3DSurface9 *>(pSourceSurface)->GetProxyInterface();
	}

	if (pDestSurface)
	{
		pDestSurface = static_cast<m_IDirect3DSurface9 *>(pDestSurface)->GetProxyInterface();
	}

	return ProxyInterface->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT m_IDirect3DDevice9::GetFrontBufferData(THIS_ UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	if (pDestSurface)
	{
		pDestSurface = static_cast<m_IDirect3DSurface9 *>(pDestSurface)->GetProxyInterface();
	}

	return ProxyInterface->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT m_IDirect3DDevice9::GetRenderTargetData(THIS_ IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	if (pRenderTarget)
	{
		pRenderTarget = static_cast<m_IDirect3DSurface9 *>(pRenderTarget)->GetProxyInterface();
	}

	if (pDestSurface)
	{
		pDestSurface = static_cast<m_IDirect3DSurface9 *>(pDestSurface)->GetProxyInterface();
	}

	return ProxyInterface->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT m_IDirect3DDevice9::UpdateSurface(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	if (pSourceSurface)
	{
		pSourceSurface = static_cast<m_IDirect3DSurface9 *>(pSourceSurface)->GetProxyInterface();
	}

	if (pDestinationSurface)
	{
		pDestinationSurface = static_cast<m_IDirect3DSurface9 *>(pDestinationSurface)->GetProxyInterface();
	}

	return ProxyInterface->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT m_IDirect3DDevice9::SetDialogBoxMode(THIS_ BOOL bEnableDialogs)
{
	return ProxyInterface->SetDialogBoxMode(bEnableDialogs);
}

HRESULT m_IDirect3DDevice9::GetSwapChain(THIS_ UINT iSwapChain, IDirect3DSwapChain9** ppSwapChain)
{
	HRESULT hr = ProxyInterface->GetSwapChain(iSwapChain, ppSwapChain);

	if (SUCCEEDED(hr) && ppSwapChain)
	{
		*ppSwapChain = ProxyAddressLookupTable->FindAddress<m_IDirect3DSwapChain9>(*ppSwapChain);
	}

	return hr;
}
