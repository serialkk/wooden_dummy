#pragma once
#include "TObjStd.h"
#include "TMesh.h"
#include "TTimer.h"

class TAnimation
{
public:
	D3DXMATRIX	Interpolate( TMeshData<PNCT_VERTEX>* pMesh, D3DXMATRIX* matParents, float fFrameTick, TScene tScene );
	D3DXMATRIX	Update(float fElapseTime, TMeshData<PNCT_VERTEX>* pMesh, D3DXMATRIX &matWorld, TScene &tScene );
	bool		GetAnimationTrack(float fFrame, vector<TAnimTrack*> pTrackList, TAnimTrack** pStartTrack, TAnimTrack** pEndTrack );
public:
	TAnimation(void);
	virtual ~TAnimation(void);
};

