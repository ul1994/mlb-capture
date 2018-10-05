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
	D3DXVECTOR3 Position;
	D3DXVECTOR4_16F p4;
	FLOAT short2n;    // add up to 32 bits
	FLOAT short4n, c; // add up to 64 bits
	FLOAT d, e;       // add up to 64 bits
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
	D3DXVECTOR2 what;
	FLOAT short4n, c; // add up to 64 bits
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
	FLOAT d, e;       // add up to 64 bits
	FLOAT c, f;       // add up to 64 bits
};






