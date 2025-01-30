# link-pd-code
给定三维坐标序列，计算链环的 PD_CODE。



## 使用方式

```bash
cd src
make all
./link-pd-code.out < 3d_coord_file.txt > pd_code.txt
```

其中 `3d_coord_file.txt` 是存储三维链环采样点的信息，计算得到的 PD_CODE 将被存储到文件 `pd_code.txt` 中。



## 输入格式

第一行包含一个整数 $L$，表示联通分支的总个数。其后内容可以分为 $L$ 组，每组描述一个联通分支的节点信息。

在一个连通分支的节点信息中，第一行包含一个整数 $N$ 表示该连通分支由一个有 $N$ 个采样点的折线段回路描述。其后 $N$ 行每行包含三个浮点数，表示一个采样点的三维空间坐标。将这些采样点依次连接，并将最后一个采样点与第一个采样点连接，即可得到完整的连通分支采样信息。



## 输出格式

包含一行，一个 PD_CODE。
