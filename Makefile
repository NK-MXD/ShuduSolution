# 设置编译器
CC = g++
# 设置编译选项
CFLAGS = -std=c++11 -Wall -Wextra -O2
# 源文件目录
SRCDIR := src
# 头文件目录
INCDIR := include
# 可执行文件目录
BINDIR := bin
# 源文件后缀
SRCEXT := cpp
# 头文件后缀
HEADEREXT := h
# 可执行文件名称
EXECUTABLE := shudu

# 获取所有的源文件
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# 获取所有的头文件
HEADERS := $(shell find $(INCDIR) -type f -name *.$(HEADEREXT))
# 生成对应的目标文件
OBJECTS := $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
# 生成依赖文件
DEPS := $(OBJECTS:.o=.d)

# 定义测试文件夹路径和测试命令
TESTDIR = test
TESTCMD = $(BINDIR)/$(EXECUTABLE) -s

# 获取test文件夹下的所有文件
TESTFILES := $(wildcard $(TESTDIR)/*)

# 生成可执行文件
$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) -o $@ $^

# 生成目标文件
$(BINDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -I$(INCDIR) -MMD -c -o $@ $<

# 执行测试命令
run:
	@for file in $(TESTFILES); do \
		echo "Testing $$file"; \
		$(TESTCMD) $$file; \
	done

# 清理生成的文件
clean:
	@rm -f $(BINDIR)/*
	@rm -f ./*.txt

