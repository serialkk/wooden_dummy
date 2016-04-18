#include "TToken.h"
void Divide(double dividend, double divider, double *result)
{
	if (divider == 0)			// 예외 발생
		throw false;			// 예외가 발생했음을 알림
	*result = dividend / divider;		// 정상 처리
}

int main(void)
{
	double a, b, result;
	cout << "0이 아닌 두 수를 입력하세요: ";
	cin >> a;
	cin >> b;
	try
	{
		Divide(a, b, &result);
		cout << a << "/" << b << " = " << result << endl;
	}
	catch (...)
	{
		cout << "입력이 잘못되었습니다." << endl;
	}
	return 0;
}

//
//void main()
//{
//	TCHAR buffer[] = _T("kgca game academy");
//	try {
//		TToken token(buffer);
//		token.Show();
//	}
//	catch (TCHAR* pData)
//	{
//		std::wcout << _T("Error!!!!");
//	}
//}