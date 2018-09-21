#pragma once

//struct ConsoleLine
//{
//	String Text;
//	RGBColor Color;
//};
//
//struct ConsolePanel
//{
//    UINT CurHeadPtr;
//	Vector<ConsoleLine> Lines;
//};

class Overlay
{
public:
	Overlay();
	void FreeMemory();
	void Init(LPDIRECT3DDEVICE9 Device);
    //void CreateNullPixelShader();
    //void SetNullPixelShader();
	//void OnLostDevice();
	//void OnResetDevice();
    
    //void WriteLine(const string text, RGBColor Color, UINT PanelIndex);
    //void ClearPanel(UINT PanelIndex);

    //void AddMesh(const Mesh &M);
    //void SetMeshTransform(const Matrix4 &Transform);
    //void ClearMeshes();

    void RenderConsole();
    //void RenderMeshes();

private:
    //static const UINT ConsolePanelCount = 5;
	//ConsolePanel _Panels[ConsolePanelCount];

	LPD3DXFONT _Font;
	ID3DXSprite* _Sprite;
    LPDIRECT3DDEVICE9 _Device;

    //D3D9Base::LPDIRECT3DPIXELSHADER9 _NullPixelShader;

    //Vector<Mesh *> _Meshes;
    //Matrix4 _MeshTransform;
};
