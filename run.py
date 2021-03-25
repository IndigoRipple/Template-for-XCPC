import os
import sys
import chardet

def main():
    template = str()
    now_file = sys.path[0]  # 得到本文件的路径
    files = os.listdir(now_file)  # 得到文件夹下的所有文件名称
    for temp in files:
        if os.path.isdir(temp) and temp != ".git": # 判断是否是文件夹，是文件夹才打开
            template += "# "
            template += temp
            template += "\n"
            files_in = os.listdir(now_file + "\\" + temp)
            for temp_in in files_in:
                if temp_in[:-4:-1][::-1] == "cpp":
                    template += temp_in[:-4]
                    template += "\n"
                    template += "```cpp\n"
                    encode = chardet.detect(open(now_file + "\\" + temp + "\\" + temp_in, 'rb').read())['encoding']  # 判断编码格式
                    f = open(now_file + "\\" + temp + "\\" + temp_in, 'r', encoding=encode)
                    template += f.read()
                    template += "\n"
                    template += "```\n"
                    f.close()
    f = open(now_file + "\\" + "template.md", 'w', encoding='utf-8')
    f.write(template)
    f.close()
    # print(template)

main()
