#pragma once
#include "TObjStd.h"
#include "TLoadToken.h"


static TCHAR* AseSections[] = { _T("SCENE "),_T("MATERIAL_LIST"),_T("GEOMOBJECT"),_T("HELPEROBJECT"), };
enum AseSectionType { SCENE = 0, MATERIALLIST, GEOMOBJECT, HELPEROBJECT, };

static TCHAR* AseMaterialTokens[] = { _T("NUMSUBMTLS"),	_T("MAP_"),_T("}"), };
enum AseMaterialType { NUM_SUBMTRLS = 0, MAP, };

static TCHAR* AseTextureTokens[] = { _T("BITMAP "),		_T("}"), };
enum AseTextureType { BITMAP_FILE = 0, };

static TCHAR* AseGeomObjectTokens[] = {
	_T("NODE_PARENT"),
	_T("NODE_TM"),
	_T("MESH {"),
	_T("TM_ANIMATION"),
	_T("NODE_VISIBILITY_TRACK"),
	_T("MATERIAL_REF"),

	_T("GEOMOBJECT"),	// Return
	_T("HELPEROBJECT"),
};
enum AseGeomObjectType {
	NODE_PARENT = 0, MODE_TM,
	MESH, TM_ANIMATION, TM_VISIBILITY, MATERIAL_REF,
};

static TCHAR* AseHelperObjectTokens[] = {
	_T("NODE_PARENT"),
	_T("HELPER_CLASS"),
	_T("NODE_TM"),
	_T("BOUNDINGBOX_MIN"),
	_T("TM_ANIMATION"),

	_T("GEOMOBJECT"),	// Return
	_T("HELPEROBJECT"),

};
enum AseHelperObjectType {
	HELPER_NODE_PARENT = 0, HELPER_CLASS, HELPER_MODE_TM,
	BOUNDINGBOX_MIN, HELPER_TM_ANIMATION,
};

enum AseTrackType {
	POS_SAMLE_TRACK = 40, ROT_SAMLE_TRACK, SCL_SAMLE_TRACK, VIS_SAMLE_TRACK
};


struct TAseMesh
{
	D3DXMATRIX				m_matWorld;
	T_STR					m_strNodeName;
	DWORD					m_iNumFace;
	INT						m_iMtrlRef;
	TVertexList				m_PosVertexList;
	TVertexList				m_TexVertexList;
	TVertexList				m_ColVertexList;
	TVertexList				m_NorVertexList;

	D3DXMATRIX				m_matWorldTrans;	// 월드 이동 행렬
	D3DXMATRIX				m_matWorldRotate;	// 월드 회전 행렬
	D3DXMATRIX				m_matWorldScale;	// 월드 신축 행렬

	vector<TAnimTrack>		m_PosTrack;		// 이동 트랙 
	vector<TAnimTrack>		m_RotTrack;		// 회전 트랙
	vector<TAnimTrack>		m_SclTrack;		// 신축 트랙												
	vector<TAnimTrack>		m_VisTrack;		// 알파 트랙
	OBJECTCLASSTYPE			m_ClassType;		// 본 : 더미 : 지오메트리 지정	
	T_STR					m_strParentName;	// 부모이름
	T_BOX					m_BBox;
	TAseMesh()
	{
		m_iNumFace = 0;
		m_iMtrlRef = -1;
	}
};
class TAseParser : public TLoadToken
{
public:
	vector<shared_ptr<TAseMesh>>	m_pAseMesh;
public:
	bool			Release();
	bool			Load(const TCHAR* strFileName);
	bool			LoadScene(TScene& tScene);
	bool			LoadMaterialList(vector<TMtrl>&	tMaterialList);
	bool			LoadMaterial(TMtrl* pMaterial);
	bool			LoadTexture(TTextexMap& TexMap);
	bool			LoadGeomObject();
	bool			LoadHelperObject();
	void			LoadTM(TAseMesh* pObject);
	void			LoadMesh(TAseMesh* pObject);
	void			LoadAnimation(TAseMesh* pObject);
	void			LoadVisAnimation(TAseMesh* pObject);
public:
	bool			GetData(TCHAR* pString = NULL, VOID* pData = NULL, INT DataType = NULL_DATA, bool bLoop = true);
	bool			GetData(VOID* pData = NULL, INT DataType = NULL_DATA);
	bool			GetVertexFromIndexData(TCHAR* strToken, DWORD dwSearchIndex, VOID* pData, INT DataType);
	bool			GetVertexListFromString(TCHAR* strVertexList, DWORD dwNumVertex, vector<D3DXVECTOR3>& VertexList, TCHAR* strToken = _T("*"));
	bool			GetFaceListFromString(TCHAR* strFaceList, DWORD dwNumFace, TVertexList& VertexList, TCHAR* strToken = _T("*"));
	bool			GetPositionFaceListFromString(TCHAR* strFaceList, DWORD dwNumFace, TVertexList& VertexList, TCHAR* strToken = _T("*"));
	bool			GetNormalListFromString(TCHAR* strFaceList, DWORD dwNumFace, TAseMesh* pGeomObject, TCHAR* strToken = _T("*"));
	bool			GetTrackListFromString(vector<TAnimTrack>& PosTrack,
		AseTrackType TrackType);

public:
	TAseParser();
	virtual ~TAseParser();
};