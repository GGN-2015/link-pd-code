import os
import re

src_dir  = os.path.dirname(os.path.abspath(__file__)) # 项目 src 目录
root_dir = os.path.dirname(src_dir) # 项目根目录
test_dir = os.path.join(src_dir, "test")
data_dir = os.path.join(root_dir, "test_data") # 测试数据目录
test_utils_cpp = os.path.join(test_dir, "TestUtils.cpp")
os.path.isdir(test_dir)

os.chdir(root_dir)

# 获取一个文件夹中的所有文件
def get_all_file(path: str):
    if os.path.isfile(path):
        return [path]
    elif os.path.isdir(path):
        ans = []
        for file in os.listdir(path):
            filepath = os.path.join(path, file)
            ans += get_all_file(filepath)
        return ans
    else:
        return []


def find_cpp_files(folder_path):
    cpp_files = []
    # 遍历指定文件夹及其子文件夹
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            # 检查文件扩展名是否为 .cpp
            if file.lower().endswith('.cpp'):
                # 构建文件的完整路径
                cpp_files.append(os.path.join(root, file))
    return cpp_files

def find_void_functions(code):
    pattern = r'void\s+test(\w*)\s*\(\s*\)' # 定义正则表达式模式
    matches = re.findall(pattern, code) # 使用 findall 方法查找所有匹配的函数
    return matches

def get_void_func_list(all_cpp_file):
    func_list = []
    for file in all_cpp_file:
        func_list += find_void_functions(open(file).read())
    return func_list

def get_content(func_list):
    head = """// 所有用于测试的函数需要在此文件中进行注册
// -DTEST 可以打开测试开关，让主程序调用测试程序集合
// 此代码由自动化程序 genTestAll.py 生成，不要试图修改这个文件
// 那些所有以 test 为前缀的返回值为 void 类型的没有参数函数都会被当作测试用函数被程序自动化整理过来
#pragma once\n#include <iostream>\n"""

    void_func = "".join(["void test%s();\n" % file for file in func_list]) 
    call_func = "".join(["    std::cout << \"\\033[1;33mtest%s\\033[0m\" << std::endl; test%s();\n" % (func, func) for func in func_list])
    return "%s\n%s\nstatic void testAll() {\n%s}\n" % (head, void_func, call_func)

if __name__ == "__main__":
    all_cpp_file = find_cpp_files(src_dir) # 收集测试函数，生成测试代码
    func_list    = get_void_func_list(all_cpp_file)
    content      = get_content(func_list)
    open(os.path.join(src_dir, "TestAll.h"), "w", encoding="utf-8").write(content)

    data_list = ",\n    ".join([ # 获取所有测试数据文件 data.txt
        chr(34) + file + chr(34)
        for file in get_all_file("./test_data")
        if os.path.basename(file) == "data.txt"
    ])
    ok_flag = "const char* OK_FLAG = \"    \\033[1;32mOK\\033[0m:\";\n"
    chk_flag = "const char* CHK_FLAG = \"    \\033[1;31mCHK\\033[0m:\";\n"
    content = '#include <test/TestUtils.h>\n\n' + ok_flag + chk_flag + 'const std::vector<std::string> TEST_FILE_LIST {\n    %s};' % data_list
    open(test_utils_cpp, "w", encoding="utf-8").write(content)