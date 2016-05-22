#include "KSelect.h"
KSelect g_Select;

int main()
{
	if (g_Select.InitSelectServer()==false)
	{
		printf("\n윈속 초기화 오류");
		return 0;
	}
	if (g_Select.NetworkProcess() == false)
	{
		printf("\n서버가 비 정상 종료 되었습니다.");
	}
	printf("\n서버가 정상 종료 되었습니다.");
	g_Select.Release();
	getchar();
	return 0;
}