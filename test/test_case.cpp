#include "pch.h"

// -s 分支的测试用例
TEST(ProcessArgsTest, SolveSudokuWithPathValidTest) {
	int argc = 3;
	char* argv[] = { "program_name", "-s", "G:/repo/2023SE-sudoku/puzzle.txt" };
	ASSERT_TRUE(processArgs(argc, argv));
}
//
TEST(ProcessArgsTest, SolveSudokuWithPathInvalidTest) {
	int argc = 3;
	char* argv[] = { "program_name", "-s", "invalid_path.txt" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, SolveSudokuWithCountsValidTest) {
	int argc = 5;
	char* argv[] = { "program_name", "-s", "G:/repo/2023SE-sudoku/puzzle.txt", "-n", "1" };
	ASSERT_TRUE(processArgs(argc, argv));
}


TEST(ProcessArgsTest, SolveSudokuWithCountsInvalidTest_neg) {
	int argc = 5;
	char* argv[] = { "program_name", "-s", "G:/repo/2023SE-sudoku/puzzle.txt", "-n", "-10" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, SolveSudokuWithCountsInvalidTest_zero) {
	int argc = 5;
	char* argv[] = { "program_name", "-s", "G:/repo/2023SE-sudoku/puzzle.txt", "-n", "0" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, SolveSudokuInvalidArgsTest) {
	int argc = 2;
	char* argv[] = { "program_name", "-s" };
	ASSERT_FALSE(processArgs(argc, argv));
}

// -c 分支的测试用例
TEST(ProcessArgsTest, CreateSudokuWithCountsValidTest) {
	int argc = 3;
	char* argv[] = { "program_name", "-c", "10" };
	ASSERT_TRUE(processArgs(argc, argv));
}


TEST(ProcessArgsTest, CreateSudokuInvalidArgsTest) {
	int argc = 2;
	char* argv[] = { "program_name", "-c" };
	ASSERT_FALSE(processArgs(argc, argv));
}


// -h 分支的测试用例
TEST(ProcessArgsTest, PrintHelpTest) {
	int argc = 2;
	char* argv[] = { "program_name", "-h" };
	ASSERT_TRUE(processArgs(argc, argv));
}

// -c
TEST(ProcessArgsTest, OtherInvalidArgsTest) {
	int argc = 2;
	char* argv[] = { "program_name", "-x" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CountsBoundaryTest) {
	int argc = 3;
	char* argv[] = { "program_name", "-c", "1000000" };
	ASSERT_TRUE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CountsInvalidBoundaryTest) {
	int argc = 3;
	char* argv[] = { "program_name", "-c", "0" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuInvalidArgsN) {
	int argc = 2;
	char* argv[] = { "program_name", "-n" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuValidArgsN) {
	int argc = 3;
	char* argv[] = { "program_name", "-n", "5"};
	ASSERT_TRUE(processArgs(argc, argv));
}


TEST(ProcessArgsTest, CreateSudokuInvalidArgsNCounts) {
	int argc = 3;
	char* argv[] = { "program_name", "-n", "0" };
	ASSERT_FALSE(processArgs(argc, argv));
}

// -m
TEST(ProcessArgsTest, CreateSudokuInvalidArgsM) {
	int argc = 2;
	char* argv[] = { "program_name", "-m" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuInvalidArgsMnumber) {
	int argc = 5;
	char* argv[] = { "program_name", "-n", "2", "-m" ,"5"};
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuValidArgsMnumber1) {
	int argc = 5;
	char* argv[] = { "program_name", "-n", "2", "-m" ,"1" };
	ASSERT_TRUE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuValidArgsMnumber2) {
	int argc = 5;
	char* argv[] = { "program_name", "-n", "2", "-m" ,"2" };
	ASSERT_TRUE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuValidArgsMnumber3) {
	int argc = 5;
	char* argv[] = { "program_name", "-n", "2", "-m" ,"3" };
	ASSERT_TRUE(processArgs(argc, argv));
}

// -u
TEST(ProcessArgsTest, CreateSudokuInvalidArgsU) {
	int argc = 4;
	char* argv[] = { "program_name", "-n", "2", "-u" };
	ASSERT_TRUE(processArgs(argc, argv));
}

// -r
TEST(ProcessArgsTest, CreateSudokuInvalidArgsR) {
	int argc = 4;
	char* argv[] = { "program_name", "-n", "2", "-r" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuInvalidArgsRnumber) {
	int argc = 5;
	char* argv[] = { "program_name", "-n", "2", "-r" ,"20-50" };
	ASSERT_FALSE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuValidArgsRnumber) {
	int argc = 5;
	char* argv[] = { "program_name", "-n", "2", "-r" ,"20~50" };
	ASSERT_TRUE(processArgs(argc, argv));
}

TEST(ProcessArgsTest, CreateSudokuInvalidArgsRange) {
	int argc = 5;
	char* argv[] = { "program_name", "-n", "2", "-r","5~80" };
	ASSERT_FALSE(processArgs(argc, argv));
}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
