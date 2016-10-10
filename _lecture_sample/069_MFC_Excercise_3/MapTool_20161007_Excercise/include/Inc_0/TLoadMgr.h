#pragma once
#include <windows.h>

class TCallBackBase
{
	public:
		virtual bool Execute() const =0;
};

template <class TObjectType>
class TLoadCallBack : public TCallBackBase 
{
	public:
		TLoadCallBack() 
		{			
			m_pFunction = 0;
			m_hThread = 0;
		}

		typedef bool (TObjectType::*FUNCTIONCALL)();		
		
		virtual bool Execute() const 
		{
			if (m_pFunction) return (m_pObjectType->*m_pFunction)();
			return false;
		}		
		void SetCallback (TObjectType	*pObjectType, 
						  FUNCTIONCALL   pFunction )
		{
			m_pObjectType		= pObjectType;
			m_pFunction			= pFunction;
		}
	public:
		static DWORD	WINAPI LoadMgrThread(void* lParam);
		
		DWORD	m_dwThreadID;
		HANDLE	m_hThread;
		bool	m_bEndOfLoadData;	

	public:	
		bool	NewThread();
		bool	SetThread();
		bool	EndThread();
	private:
		TObjectType  *m_pObjectType;
		FUNCTIONCALL  m_pFunction;
};

template <class TObjectType >
TLoadCallBack<TObjectType> SetProc(TObjectType pObjType)
{
	return TLoadCallBack<TObjectType>(&pObjType);
}
template <class TObjectType>
DWORD  WINAPI TLoadCallBack<TObjectType>::LoadMgrThread(void* lParam)
{	
	 if(lParam)
	 {  		 
		 TLoadCallBack* pLoadMgr=(TLoadCallBack*)lParam;			
		 pLoadMgr->Execute();	 
	 }
	 return 0;
}

template <class TObjectType>
bool TLoadCallBack<TObjectType>::NewThread()
{
	m_bEndOfLoadData = false;
	m_hThread = CreateThread( NULL, 0, TLoadCallBack::LoadMgrThread, this, CREATE_SUSPENDED, &m_dwThreadID );
	if( m_hThread == NULL )
	{
		return false;
	}	
	return true;
}
template <class TObjectType>
bool TLoadCallBack<TObjectType>::SetThread()
{
	ResumeThread(m_hThread);	
	return true;
}
template <class TObjectType>
bool TLoadCallBack<TObjectType>::EndThread()
{
	TerminateThread(m_hThread,m_dwThreadID);
	CloseHandle( m_hThread );
	return true;
}
