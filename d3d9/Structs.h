#pragma once

struct FVF {
	FLOAT x, y, z;
};

struct V4 {
	/*Identifying declaration: 4
	0: D3DDECLTYPE_FLOAT3
	1: D3DDECLTYPE_FLOAT16_4
	2: D3DDECLTYPE_SHORT4N*/
	D3DXVECTOR3 Position;
	D3DXVECTOR4_16F p4;
	FLOAT short4n, c;
};

struct V6 {
	/*Identifying declaration : 6
	0 : D3DDECLTYPE_FLOAT3
	1 : D3DDECLTYPE_FLOAT16_4
	2 : D3DDECLTYPE_SHORT2N
	3 : D3DDECLTYPE_SHORT4N
	4 : D3DDECLTYPE_SHORT4N*/
	D3DXVECTOR3 Position; // 12
	D3DXVECTOR4_16F p4;   // 8
	FLOAT short2n;    // add up to 4 bytes
	FLOAT a, b; // add up to 8 bits
	FLOAT d, e;       // add up to 8 bits
};

struct V6B {
	/*Identifying declaration : 6
	0 : D3DDECLTYPE_FLOAT3
	1 : D3DDECLTYPE_FLOAT16_4
	2 : D3DDECLTYPE_SHORT2N
	3 : D3DDECLTYPE_SHORT4N
	4 : D3DDECLTYPE_SHORT4N*/
	D3DXVECTOR3 Position;
	D3DXVECTOR4_16F p4;
	FLOAT what;  // 4
	FLOAT a, b; // add up to 64 bits
	FLOAT d, e;       // add up to 64 bits
};

struct V5 {
	/*Identifying declaration : 5
	0 : D3DDECLTYPE_FLOAT3
	1 : D3DDECLTYPE_FLOAT16_4
	2 : D3DDECLTYPE_SHORT4N
	3 : D3DDECLTYPE_SHORT4N*/
	D3DXVECTOR3 Position;
	D3DXVECTOR4_16F p4;
	FLOAT d, e;       // 8
	FLOAT c, f;       // 8
};

struct V5B {
	/*Identifying declaration : 5
	0 : D3DDECLTYPE_FLOAT4  D3DDECLUSAGE_POSITION
	1 : D3DDECLTYPE_SHORT4N  D3DDECLUSAGE_TEXCOORD
	2 : D3DDECLTYPE_UBYTE4  D3DDECLUSAGE_BLENDINDICES
	3 : D3DDECLTYPE_UBYTE4N  D3DDECLUSAGE_BLENDWEIGHT*/
	D3DXVECTOR4 Position;   // 16
	FLOAT d, e;       // 8
	FLOAT a;       // 4
	FLOAT b;       // 4
};








