# 可执行程序名称
TARGET := main.out

# 目录设置（中间文件存放于 bin 目录）
BIN_DIR := bin
SRCS := $(wildcard *.cpp)  # 所有 .cpp 源文件
OBJS := $(SRCS:%.cpp=$(BIN_DIR)/%.o)  # 所有 .o 文件路径（bin/xxx.o）
DEPS := $(OBJS:.o=.d)  # 依赖文件路径（bin/xxx.d）

# 编译器和编译选项
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2  # 可根据需要修改 C++ 标准
LDFLAGS :=  # 链接选项（如 -lm、-lpthread 等）

# 默认目标：创建 bin 目录并编译链接
all: $(BIN_DIR) $(TARGET)

# 创建 bin 目录（如果不存在）
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# 链接：使用 bin 目录下的 .o 文件生成可执行程序（默认放在当前目录，可修改为 $(BIN_DIR)/$(TARGET)）
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "链接完成：$@"

# 编译：将 .cpp 编译为 bin 目录下的 .o，并生成依赖文件
$(BIN_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
	@echo "编译完成：$@"

# 包含依赖文件（检测头文件变化）
-include $(DEPS)

run: all
	./$(TARGET)

# 清理：删除 bin 目录和可执行程序
clean:
	rm -rf $(BIN_DIR) $(TARGET)
	@echo "清理完成（删除 bin 目录和可执行程序）"

# 伪目标（防止目录中存在同名文件）
.PHONY: all run clean $(BIN_DIR)