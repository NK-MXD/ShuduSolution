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

# 默认目标
all: $(EXES)

# 编译可执行文件
$(BINDIR)/%: $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $< -o $@

# 清理生成的文件
clean:
	@rm -f $(BINDIR)/*

