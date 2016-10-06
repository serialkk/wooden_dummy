#pragma once
#include "TObjStd.h"
#include "TMesh.h"

class TAnimation
{
public:
	D3DXMATRIX	Interpolate(TMesh* pMesh, D3DXMATRIX* matParents, float fFrameTick, TScene tScene);
	D3DXMATRIX	Update(float fElapseTime, TMesh* pMesh, D3DXMATRIX &matWorld, TScene &tScene);
	bool		GetAnimationTrack(float fFrame, vector<shared_ptr<TAnimTrack>>& pTrackList, TAnimTrack** pStartTrack, TAnimTrack** pEndTrack);
public:
	TAnimation(void);
	virtual ~TAnimation(void);
};

