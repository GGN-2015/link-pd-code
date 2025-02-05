# 查找当前目录及其子目录下的所有 .cpp 文件
SRCS := $(shell find . -name '*.cpp')
# 将 .cpp 扩展名替换为 .o
OBJS := $(SRCS:.cpp=.o)
# 额外依赖
DEPS := TestAll.h

# 编译器和编译选项
CXX := g++
CXXFLAGS := -Wall -Wextra -g -I./src -DTEST

# 默认目标，链接所有 .o 文件生成 a.out
all: link-pd-code.out

TestAll.h: $(SRCS)
	python3 src/genTestAll.py

# 生成 link-pd-code.out 的规则
link-pd-code.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# 编译每个 .cpp 文件为 .o 文件的规则
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的 .o 文件和 a.out
clean:
	rm -f $(OBJS) link-pd-code.out

.PHONY: all clean