CC = g++
CFLAGS = 

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = sudoku

# 指定需要编译的源文件和头文件
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
INCS = -I$(INCDIR)

# 默认目标，编译生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

# 编译每个源文件
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# 清理编译生成的目标文件和可执行文件
clean:
	del $(BUILDDIR)\*.o
