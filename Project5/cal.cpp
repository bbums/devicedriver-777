#include <vector>
#include <iostream>

// DIP ��Ģ�� ���� Checker �� �����. ISP ��?

#define interface struct

interface Checker{
public:
	virtual bool valid(int n) = 0;
};

class CoinChecker : public Checker {
public:
	bool valid(int n) override { // ���� ���� �˻� ���
		// �ѱ�������翡 ��û�ϴ� ���ڵ�
		// ����, ��û�� ������ 100���� ����
		return (n % 2 == 0);
	}
};

// SUT
class GameMachine {
public:
	GameMachine(Checker* cc) : checker{ cc } {} // ���⼭ mock injection �ϸ� ��

	void insertCoin(int coin) {
		if (checker->valid(coin)) { // �� ��� !
			std::cout << "�Ա� �Ϸ�\n";
		}
	}
private:
	Checker* checker;
};

class Cal {
public:
	int getSum(int a, int b) {
		return a + b;
	}
	int getValue() {
		return t;
	}
private:
	int t = 100;
};