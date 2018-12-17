# OEIS-Spider 使用说明

##  懒人专用

下载并打开 print/oeis.pdf ， Ctrl + P ，完成。

##  准备阶段

1. 切换到 prepare 目录下。

2. 先在 http://oeis.org/wiki/QandA_For_New_OEIS#The_files_stripped.gz.2C_names.gz 下载 stripped.gz 。

3. 用 a.cpp 处理 stripped ，输出单调不下降的数列集合 verified 。

4. 将 verified 第一行加上 taskId ，重命名为 allNeed.csv

5. 将 0 写入 begin.txt ，数列总数 - 1 写入 end.txt ，-1 写入 lastans.txt 。begin.txt 表示开始编号， end.txt 表示结束编号，前闭后开。 lastans.txt 表示最后处理的数列编号。

6. 运行 fetch.py 。

##  排序

1. 将 result.csv 复制到 result_sort 目录下。

2. 切换到 result_sort 目录下。

3. 运行 main.cpp ，得到 tex.txt

## 生成 PDF

1. 切换到 print 目录下。

2. 执行 compile.sh 。

oeis.pdf 即为答案文件。
