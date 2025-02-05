import os
import re

dirnow = os.path.dirname(os.path.abspath(__file__))
os.chdir(dirnow)

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
    all_cpp_file = find_cpp_files(".")
    func_list    = get_void_func_list(all_cpp_file)
    content      = get_content(func_list)
    open("TestAll.h", "w", encoding="utf-8").write(content)