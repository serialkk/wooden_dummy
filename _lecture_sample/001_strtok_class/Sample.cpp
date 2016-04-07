#include "KToken.h"

void main()
{
	TCHAR	buffer[] = _T("kgca game academy");

	KToken	token(buffer);
	token.Show();
}