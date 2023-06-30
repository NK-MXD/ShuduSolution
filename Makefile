# 设置编译器
CC = g++
# 设置编译选项
CFLAGS = -std=c++11 -Wall

# 源文件目录
SRCDIR = source
# 可执行文件目录
BINDIR = bin

# 获取源文件列表
SRCS := $(wildcard $(SRCDIR)/*.cpp)
# 根据源文件列表生成可执行文件列表
EXES := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%,$(SRCS))

# 定义测试文件夹路径和测试命令
TESTDIR = test
TESTCMD = $(BINDIR)/shudu -s

# 获取test文件夹下的所有文件
TESTFILES := $(wildcard $(TESTDIR)/*)

# 默认目标
all: $(EXES)

# 编译可执行文件
$(BINDIR)/%: $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $< -o $@

# 执行测试命令
run:
	@for file in $(TESTFILES); do \
		echo "Testing $$file"; \
		$(TESTCMD) $$file; \
	done

# 清理生成的文件
clean:
	@rm -f $(BINDIR)/*

