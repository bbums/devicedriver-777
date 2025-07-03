#include <vector>
#include <iostream>

// DIP 원칙을 위해 Checker 를 만든다. ISP 는?

#define interface struct

interface Checker{
public:
	virtual bool valid(int n) = 0;
};

class CoinChecker : public Checker {
public:
	bool valid(int n) override { // 위조 코인 검사 모듈
		// 한국조폐공사에 요청하느 ㄴ코드
		// 인증, 요청할 때마다 100원씩 차감
		return (n % 2 == 0);
	}
};

// SUT
class GameMachine {
public:
	GameMachine(Checker* cc) : checker{ cc } {} // 여기서 mock injection 하면 됨

	void insertCoin(int coin) {
		if (checker->valid(coin)) { // 이 비용 !
			std::cout << "입금 완료\n";
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