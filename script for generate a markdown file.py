import os
from pathlib import Path

def generate_markdown(root_dir, output_file="output.md", ignore_prefix="."):
    """
    递归生成文件夹结构的Markdown文档
    
    :param root_dir: 要扫描的根目录
    :param output_file: 输出的Markdown文件名
    :param ignore_prefix: 要忽略的文件/文件夹前缀
    """
    root_path = Path(root_dir)
    with open(output_file, 'w', encoding='utf-8') as md_file:
        # 写入根目录标题
        md_file.write("\n\n[TOC]\n")
        md_file.write(f"# {root_path.name}\n\n")
        
        # 递归处理目录
        _process_directory(root_path, md_file, ignore_prefix, current_depth=1)

def _process_directory(directory, md_file, ignore_prefix, current_depth):
    """递归处理目录"""
    for item in sorted(directory.iterdir()):
        # 跳过以指定前缀开头的文件/目录
        if item.name.startswith(ignore_prefix):
            continue
            
        if item.is_dir():
            # 写入目录标题
            md_file.write(f"{'#' * (current_depth + 1)} {item.name}\n\n")
            # 递归处理子目录
            _process_directory(item, md_file, ignore_prefix, current_depth + 1)
        elif item.is_file():
            # 写入文件标题（去掉扩展名）
            file_title = item.stem
            md_file.write(f"{'#' * (current_depth + 1)} {file_title}\n\n")
            
            # 如果是C++文件，写入代码块
            if item.suffix in ('.cpp', '.h', '.hpp', '.c', '.cc'):
                try:
                    with open(item, 'r', encoding='utf-8') as f:
                        content = f.read()
                    md_file.write(f"```cpp\n{content}\n```\n\n")
                except Exception as e:
                    md_file.write(f"```\n[无法读取文件内容: {e}]\n```\n\n")
            else:
                md_file.write(f"```\n[非C++文件，内容省略]\n```\n\n")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("用法: python script.py <目录路径> [输出文件名]")
        sys.exit(1)
        
    target_dir = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else "output.md"
    
    if not os.path.isdir(target_dir):
        print(f"错误: '{target_dir}' 不是有效目录")
        sys.exit(1)
    
    generate_markdown(target_dir, output_file)
    print(f"Markdown文档已生成: {output_file}")