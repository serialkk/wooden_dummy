#pragma once


// TMap

class TMap : public CDockablePane
{
	DECLARE_DYNAMIC(TMap)

public:
	TMap();
	virtual ~TMap();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


