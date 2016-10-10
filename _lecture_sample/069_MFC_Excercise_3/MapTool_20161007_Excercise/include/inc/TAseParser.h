#pragma once
#include "TObjStd.h"
#include "TLoadToken.h"


static TCHAR* AseSections[]={_T("SCENE "),_T("MATERIAL_LIST"),_T("GEOMOBJECT"),_T("HELPEROBJECT"), };	
enum AseSectionType			{ SCENE = 0,	MATERIALLIST,		GEOMOBJECT,		HELPEROBJECT, };

static TCHAR* AseMaterialTokens[] = { _T("NUMSUBMTLS"),	_T("MAP_"),_T("}"), };	
enum AseMaterialType				{ NUM_SUBMTRLS = 0, MAP, };	

static TCHAR* AseTextureTokens[] =	{_T("BITMAP "),		_T("}"), };	
enum AseTextureType					{ BITMAP_FILE=0, };	

static TCHAR* AseGeomObjectTokens[] = {
	_T("NODE_PARENT"), 
	_T("NODE_TM"), 
	_T("MESH {"), 
	_T("TM_ANIMATION"),
	_T("MATERIAL_REF"),

	_T("GEOMOBJECT"),	// Return
	_T("HELPEROBJECT"),	
};	
enum AseGeomObjectType {	NODE_PARENT=0,	MODE_TM,  
							MESH,			TM_ANIMATION,	MATERIAL_REF, };

static TCHAR* AseHelperObjectTokens[] = {
	_T("NODE_PARENT"), 
	_T("HELPER_CLASS"),
	_T("NODE_TM"), 
	_T("BOUNDINGBOX_MIN"),
	_T("TM_ANIMATION"),

	_T("GEOMOBJECT"),	// Return
	_T("HELPEROBJECT"),
	
};	
enum AseHelperObjectType {	HELPER_NODE_PARENT=0,	HELPER_CLASS,	HELPER_MODE_TM,  
							BOUNDINGBOX_MIN,	HELPER_TM_ANIMATION,  };

enum AseTrackType { POS_SAMLE_TRACK = 40,	ROT_SAMLE_TRACK,	SCL_SAMLE_TRACK, };


class TAseParser : public TLoadToken
{
public:
	vector<TAseMesh*>	m_pAseMesh;
public:
	bool			Release();
	bool			Load( const TCHAR* strFileName );
	bool			LoadScene(		TScene& tScene );
	bool			LoadMaterialList(vector<TMtrl>&	tMaterialList );
	bool			LoadMaterial(	TMtrl* pMaterial );
	bool			LoadTexture(  TTextexMap& TexMap   );	
	bool			LoadGeomObject();
	bool			LoadHelperObject();
	void			LoadTM( TAseMesh* pObject );
	void			LoadMesh( TAseMesh* pObject );
	void			LoadAnimation( TAseMesh* pObject );
public:
	bool			GetData( TCHAR* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA, bool bLoop= true);
	bool			GetData( VOID* pData = NULL,INT DataType = NULL_DATA);
	bool			GetVertexFromIndexData( TCHAR* strToken, DWORD dwSearchIndex, VOID* pData, INT DataType);
	bool			GetVertexListFromString( TCHAR* strVertexList, DWORD dwNumVertex, vector<D3DXVECTOR3>& VertexList, TCHAR* strToken = _T("*") );
	bool			GetFaceListFromString( TCHAR* strFaceList,  DWORD dwNumFace, TVertexList& VertexList, TCHAR* strToken = _T("*") );
	bool			GetPositionFaceListFromString( TCHAR* strFaceList,  DWORD dwNumFace, TVertexList& VertexList, TCHAR* strToken = _T("*") );
	bool			GetNormalListFromString( TCHAR* strFaceList, DWORD dwNumFace, TAseMesh* pGeomObject, TCHAR* strToken = _T("*") );
	// Ãß°¡
	bool			GetTrackListFromString( vector<TAnimTrack>& PosTrack, 
											AseTrackType TrackType );
	
public:
	TAseParser();
	~TAseParser();
};