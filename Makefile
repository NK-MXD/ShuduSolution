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
TESTGOODDIR = test/good
TESTBADDIR = test/bad
TESTINVALUDCMD = $(BINDIR)/$(EXECUTABLE) -d -e
TESTGENFINALCMD = $(BINDIR)/$(EXECUTABLE) -c
TESTGENGAMECMD = $(BINDIR)/$(EXECUTABLE) -r 30~40 -n
TESTSOLEVCMD = $(BINDIR)/$(EXECUTABLE) -s

# 获取test文件夹下的所有文件
TESTGOODFILES := $(wildcard $(TESTGOODDIR)/*)
TESTBADFILES := $(wildcard $(TESTBADDIR)/*)

# 生成可执行文件
$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) -o $@ $^

# 生成目标文件
$(BINDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -I$(INCDIR) -MMD -c -o $@ $<

$(BINDIR)/unittest:
	@g++ $(TESTDIR)/test.cpp $(SRCDIR)/sudoku.cpp -lgtest -lpthread -o $(BINDIR)/unittest

# 执行测试命令
test-units: $(BINDIR)/unittest
	@$(BINDIR)/unittest

define run_test
	@$(1); \
	if [ $$? -eq 0 ]; then \
		echo "\033[32mTest passed: $$file\033[0m"; \
	else \
		echo "\033[31mTest failed: $$file\033[0m"; \
	fi
endef

test-solve-good: $(BINDIR)/$(EXECUTABLE)
	@total_tests=0; \
	passed_tests=0; \
	for file in $(TESTGOODFILES); do \
		echo -e "\033[1mTesting good $$file\033[0m"; \
		$(TESTSOLEVCMD) $$file; \
		total_tests=$$((total_tests+1)); \
		passed_tests=$$((passed_tests+1)); \
	done; \
	echo "\n\033[1mTotal tests: $$total_tests\033[0m"; \
	echo "\033[32mTests passed: $$passed_tests\033[0m"


test-solve-bad:$(BINDIR)/$(EXECUTABLE)
	@total_tests=0; \
	passed_tests=0; \
	for file in $(TESTBADFILES); do \
		echo "\033[1mTesting bad $$file\033[0m"; \
		$(TESTSOLEVCMD) $$file; \
		total_tests=$$((total_tests+1)); \
		passed_tests=$$((passed_tests+1)); \
	done; \
	echo "\n\033[1mTotal tests: $$total_tests\033[0m"; \
	echo "\033[32mTests passed: $$passed_tests\033[0m"

# 清理生成的文件
clean:
	@rm -f $(BINDIR)/*
	@rm -f ./*.txt

