#include "TToken.h"
void Divide(double dividend, double divider, double *result)
{
	if (divider == 0)			// ���� �߻�
		throw false;			// ���ܰ� �߻������� �˸�
	*result = dividend / divider;		// ���� ó��
}

int main(void)
{
	double a, b, result;
	cout << "0�� �ƴ� �� ���� �Է��ϼ���: ";
	cin >> a;
	cin >> b;
	try
	{
		Divide(a, b, &result);
		cout << a << "/" << b << " = " << result << endl;
	}
	catch (...)
	{
		cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
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