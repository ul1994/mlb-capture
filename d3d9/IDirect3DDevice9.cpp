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
	HRESULT hr = ProxyInterface->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);

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
	// TODO: render texts here
	m_Overlay->RenderConsole();
	return ProxyInterface->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT m_IDirect3DDevice9::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	bool verbose = false;
	// NumVertices - reflects full size of vertex buffer regardless of which indices are used
	
	if (NumVertices > 50 && Type == D3DPT_TRIANGLELIST) {
		if (verbose) Log() << "DrawIndexedPrimitive   V " << NumVertices << ",  S " << startIndex << ",  P " << primCount;


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
		}
		else {
			short* indices = new short[range];
			memcpy(indices, pVoid, rangeInBytes);
			localIndex->Unlock();

			for (int ii = 0; ii < 1; ii++) {
				sprintf(buff, "%hu %hu %hu",
					indices[3 * ii + 0],
					indices[3 * ii + 1],
					indices[3 * ii + 2]);
				if (verbose) Log() << "    " << buff;
			}
			if (verbose) Log() << "    ...";
			for (int ii = 0; ii < 1; ii++) {
				sprintf(buff, "%hu %hu %hu",
					indices[3 * (primCount - ii - 1) + 0],
					indices[3 * (primCount - ii - 1) + 1],
					indices[3 * (primCount - ii - 1) + 2]);
				if (verbose) Log() << "    " << buff;
			}

			short minInd = indices[0];
			short maxInd = indices[0];
			for (int ii = 0; ii < range; ii++) {
				if (indices[ii] < minInd) minInd = indices[ii];
				if (indices[ii] > maxInd) maxInd = indices[ii];
			}
			if (verbose) Log() << "    Param min: " << MinVertexIndex << "  Act min: " << minInd << "   Max: " << maxInd << "   Range: " << (maxInd - minInd);

			int dtype = -1;
			identifyVertex(vertexType, &dtype, verbose);

			if (dtype > 0) {
				int dsize = 0;
				if (dtype == 1) {
					dsize = sizeof(V6);
				}
				else if (dtype == 2) {
					dsize = sizeof(V6B);
				}
				else if (dtype == 3) {
					dsize = sizeof(V5);
				}
				else if (dtype == 4) {
					dsize = sizeof(V5B);
				}

				if (dsize != bufferStride) {
					Log() << dtype << " Guess size " << dsize << " vs  Stride " << bufferStride << "   Float size" << sizeof(FLOAT);
				}

				//dsize = bufferStride;
				int vertexStartInBytes = dsize * MinVertexIndex;
				int vertexRange = (maxInd - minInd);
				int vertexRangeInBytes = dsize * vertexRange;
				HRESULT hr = validVertex->Lock(vertexStartInBytes, vertexRangeInBytes, &pVoid, 0);
				if (FAILED(hr)) {
					Log() << "! VERTEX LOCK FAILED";
				}
				else {
					VOID* verts = malloc(vertexRangeInBytes);
					memcpy(verts, pVoid, vertexRangeInBytes);
					validVertex->Unlock();

					FLOAT* casted = (FLOAT*)verts;

					int unit = sizeof(FLOAT);
					int stride = dsize / unit;
					sprintf(buff, "%f %f %f",
						casted[stride*0 + 0],
						casted[stride * 0 + 1],
						casted[stride*0 + 2]);

					Log() << "  " << buff;

					delete verts;

					/*if (verbose) Log() << " Verts:";
					if (dtype == 1) {
						V6* casted = (V6*)verts;
						sprintf(buff, "%f %f %f",
							casted[indices[4] - minInd].Position.x,
							casted[indices[4] - minInd].Position.y,
							casted[indices[4] - minInd].Position.z);
					}
					else if (dtype == 2) {
						V6B* casted = (V6B*)verts;
						sprintf(buff, "%f %f %f",
							casted[indices[4] - minInd].Position.x,
							casted[indices[4] - minInd].Position.y,
							casted[indices[4] - minInd].Position.z);
					}
					else if (dtype == 3) {
						V5* casted = (V5*)verts;
						sprintf(buff, "%f %f %f",
							casted[indices[4] - minInd].Position.x,
							casted[indices[4] - minInd].Position.y,
							casted[indices[4] - minInd].Position.z);
					}
					else if (dtype == 4) {
						V5B* casted = (V5B*)verts;
						sprintf(buff, "%f %f %f %f",
							casted[indices[4] - minInd].Position.x,
							casted[indices[4] - minInd].Position.y,
							casted[indices[4] - minInd].Position.z,
							casted[indices[4] - minInd].Position.w);
					}
					if (verbose) Log() << "    " << buff;*/

					
				}
			}

			delete indices;
		}
		
	}
	
	return ProxyInterface->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT m_IDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, CONST void *pIndexData, D3DFORMAT IndexDataFormat, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	//Log() << "DrawIndexedPrimitiveUP";
	return ProxyInterface->DrawIndexedPrimitiveUP(PrimitiveType, MinIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT m_IDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	renderManager.DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
	return ProxyInterface->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT m_IDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return ProxyInterface->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT m_IDirect3DDevice9::BeginScene()
{
	//Log() << "BeginScene";
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
	if (pStreamData)
	{
		bufferStride = Stride;
		validVertex = pStreamData;
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

void m_IDirect3DDevice9::identifyVertex(IDirect3DVertexDeclaration9* ppDecl, int* dtype, bool verbose) {
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
	}
	else {
		//if (numElements == 6) {
		if (verbose) Log() << "  Identifying declaration: " << numElements;
		for (int ii = 0; ii < numElements - 1; ii++) {
			int typei = 0;
			for (typei = 0; typei < 18; typei++) {
				D3DDECLTYPE dtype = static_cast<D3DDECLTYPE>(typei);
				if (dtype == decl[ii].Type) {
					break;
				}
			}

			int usei = 0;
			for (usei = 0; usei < 14; usei++) {
				if (static_cast<D3DDECLUSAGE>(usei) == decl[ii].Usage) {
					break;
				}
			}

			sprintf(buff, "%d: %s  %s", ii, names[typei].c_str(), use_names[usei].c_str());
			if (verbose) Log() << "   " << buff;
		}

		if (numElements == 6) {
			if (decl[0].Type == static_cast<D3DDECLTYPE>(2)
				&& decl[1].Type == static_cast<D3DDECLTYPE>(16)
				&& decl[2].Type == static_cast<D3DDECLTYPE>(9)
				&& decl[3].Type == static_cast<D3DDECLTYPE>(10)
				&& decl[4].Type == static_cast<D3DDECLTYPE>(10)) {

				if (verbose) Log() << "  Identified: V6 !!!";

				*dtype = 1;
			}

			if (decl[0].Type == static_cast<D3DDECLTYPE>(2)
				&& decl[1].Type == static_cast<D3DDECLTYPE>(16)
				&& decl[2].Type == static_cast<D3DDECLTYPE>(1)
				&& decl[3].Type == static_cast<D3DDECLTYPE>(10)
				&& decl[4].Type == static_cast<D3DDECLTYPE>(10)) {

				if (verbose) Log() << "  Identified: V6B !!!";

				*dtype = 2;
			}
		}
		else if (numElements == 5) {
			if (decl[0].Type == static_cast<D3DDECLTYPE>(2)
				&& decl[1].Type == static_cast<D3DDECLTYPE>(16)
				&& decl[2].Type == static_cast<D3DDECLTYPE>(10)
				&& decl[3].Type == static_cast<D3DDECLTYPE>(10)) {

				if (verbose) Log() << "  Identified: V5 !!!";

				*dtype = 3;
			}

			if (decl[0].Type == static_cast<D3DDECLTYPE>(3)
				&& decl[1].Type == static_cast<D3DDECLTYPE>(10)
				&& decl[2].Type == static_cast<D3DDECLTYPE>(5)
				&& decl[3].Type == static_cast<D3DDECLTYPE>(8)) {

				if (verbose) Log() << "  Identified: V5B !!!";

				*dtype = 4;
			}
		}
		/*else if (numElements == 4) {
		if (decl[0].Type == static_cast<D3DDECLTYPE>(2)
		&& decl[1].Type == static_cast<D3DDECLTYPE>(16)
		&& decl[2].Type == static_cast<D3DDECLTYPE>(10)) {

		Log() << "Identified: V4 !!!";

		*dtype = 4;
		}
		}*/
	}
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
