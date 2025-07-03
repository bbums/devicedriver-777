#include "gmock/gmock.h"
#include "device_driver.h"
#include <stdexcept>
#include "application.cpp"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DriverFixture : public Test {
public:
	FlashMock mockHW;
	DeviceDriver dd{ &mockHW };
	Application app{ &dd };
	const unsigned char RIGHT_DATA = 0xAA;
	const unsigned char WRONG_DATA = 0xAB;
};

TEST_F(DriverFixture, SuccessReadFromHW) {
	EXPECT_CALL(mockHW, read)
		.Times(5)
		.WillRepeatedly(testing::Return(RIGHT_DATA));

	int output = (int)dd.read(100);

	EXPECT_EQ(RIGHT_DATA, output);
}

TEST_F(DriverFixture, GenExceptionWhileReadFromHW) {
	int addr = 100;

	EXPECT_CALL(mockHW, read)
		.Times(5)
		.WillOnce(testing::Return(RIGHT_DATA))
		.WillOnce(testing::Return(RIGHT_DATA))
		.WillOnce(testing::Return(RIGHT_DATA))
		.WillOnce(testing::Return(RIGHT_DATA))
		.WillOnce(testing::Return(WRONG_DATA));

	EXPECT_THROW({
		int output = (int)dd.read(addr);
	}, ReadFailException);
}

TEST_F(DriverFixture, SuccessWriteFromHW) {
	int addr = 500;

	EXPECT_CALL(mockHW, read(addr))
		.WillRepeatedly(testing::Return(0xFF));

	EXPECT_CALL(mockHW, write(addr, RIGHT_DATA));

	dd.write(addr, 0xAA);
}

TEST_F(DriverFixture, GenExceptionWhileWriteFromHW) {
	int addr = 500;

	EXPECT_CALL(mockHW, read(addr))
		.WillRepeatedly(testing::Return(0xDD));

	EXPECT_THROW({
		dd.write(addr, 0xAA);
		}, WriteFailException);
}

TEST_F(DriverFixture, ReadAndPrint) {
	EXPECT_CALL(mockHW, read)
		.WillRepeatedly(testing::Return('D'));

	app.readAndPrint(51, 55);
}

TEST_F(DriverFixture, WriteAll) {
	EXPECT_CALL(mockHW, read)
		.WillRepeatedly(testing::Return(0xFF));

	EXPECT_CALL(mockHW, write(0, 0xAA));
	EXPECT_CALL(mockHW, write(1, 0xAA));
	EXPECT_CALL(mockHW, write(2, 0xAA));
	EXPECT_CALL(mockHW, write(3, 0xAA));
	EXPECT_CALL(mockHW, write(4, 0xAA));

	app.writeAll(0xAA);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}