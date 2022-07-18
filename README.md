## 2022.7.18 完成热点图移植、和udp波长存储、光谱存储模块结合(光谱的还没测试)

- 目前基本功能已经实现,后续就是将倍数因子接口留出(config文件参数设置),以及相关参数

- 一些零散的功能用函数封装,udp读取数据的代码太凌乱
- 第一次读取的波长数据用于初始化basewave数组,作为后续所有波长的基地,后续用于显示的波长数据都是和base的插值绝对值.
- 文本尾端补充之前的光谱和波长的笔记















# QColorMapDemo
a demo of colormap using QCustomPlot
![](https://img2020.cnblogs.com/blog/2146166/202104/2146166-20210425174356726-132664566.png)
## How to use [QCustomplot](https://www.qcustomplot.com/)
you just need to ```#include "qcustomplot.h"```

## which class need to use
![](https://img2020.cnblogs.com/blog/2146166/202104/2146166-20210425175204606-1942764609.png)





指令0x0116 + 一个字节通道号
返回该通道的光谱数据.
该指令发出,会返回6个udp包.
其中前5个是该通道的光谱数据,最后一个是波长数据(没用).
因此只需要前4个包
每个包包头都是2字节的`01 16` + 1字节通道号`00` + 1字节包号`00`
然后后面都是数据(100字节? 99字节?) 一个包是2048个字节


```bash
#send
011601
#recv
00000000  01 16 01 00 1f fe 20 fe  21 fe 20 fe 1e fe 1f fe  |...... .!. .....|
00000010  21 fe 22 fe 20 fe 1e fe  1e fe 22 fe 22 fe 20 fe  |!.". .....".". .|
00000020  20 fe 20 fe 21 fe 22 fe  20 fe 20 fe 1f fe 21 fe  | . .!.". . ...!.|
00000030  21 fe 1f fe 1d fe 1e fe  1f fe 20 fe 21 fe 22 fe  |!......... .!.".|
00000040  20 fe 20 fe 21 fe 22 fe  20 fe 20 fe 20 fe 21 fe  | . .!.". . . .!.|
00000050  21 fe 20 fe 20 fe 20 fe  22 fe 22 fe 22 fe 21 fe  |!. . . .".".".!.|
00000060  20 fe 23 fe 24 fe 24 fe  22 fe 21 fe 20 fe 21 fe  | .#.$.$.".!. .!.|
00000070  21 fe 20 fe 20 fe 21 fe  21 fe 21 fe 1f fe 1e fe  |!. . .!.!.!.....|
00000080  20 fe 21 fe 21 fe 1f fe  1f fe 20 fe 21 fe 21 fe  | .!.!..... .!.!.|
00000090  20 fe 1f fe 20 fe 22 fe  20 fe 20 fe 20 fe 21 fe  | ... .". . . .!.|
000000a0  22 fe 22 fe 22 fe 21 fe  21 fe 21 fe 1f fe 1f fe  |".".".!.!.!.....|
000000b0  22 fe 23 fe 23 fe 21 fe  22 fe 22 fe 20 fe 1f fe  |".#.#.!.".". ...|
000000c0  20 fe 22 fe 23 fe 24 fe  22 fe 20 fe 22 fe 23 fe  | .".#.$.". .".#.|
000000d0  22 fe 20 fe 20 fe 23 fe  23 fe 21 fe 1f fe 20 fe  |". . .#.#.!... .|
000000e0  22 fe 22 fe 21 fe 1f fe  21 fe 22 fe 22 fe 21 fe  |".".!...!.".".!.|
000000f0  21 fe 23 fe 24 fe 23 fe  22 fe 21 fe 23 fe 24 fe  |!.#.$.#.".!.#.$.|
00000100  24 fe 22 fe 21 fe 24 fe  26 fe 23 fe 21 fe 22 fe  |$.".!.$.&.#.!.".|
00000110  22 fe 23 fe 23 fe 21 fe  22 fe 23 fe 23 fe 21 fe  |".#.#.!.".#.#.!.|
00000120  20 fe 21 fe 23 fe 23 fe  21 fe 21 fe 23 fe 23 fe  | .!.#.#.!.!.#.#.|
00000130  22 fe 21 fe 21 fe 23 fe  22 fe 21 fe 21 fe 22 fe  |".!.!.#.".!.!.".|
00000140  23 fe 22 fe 22 fe 20 fe  21 fe 23 fe 22 fe 21 fe  |#.".". .!.#.".!.|
00000150  1f fe 1f fe 21 fe 22 fe  20 fe 20 fe 1f fe 20 fe  |....!.". . ... .|
00000160  20 fe 21 fe 20 fe 20 fe  21 fe 21 fe 22 fe 21 fe  | .!. . .!.!.".!.|
00000170  22 fe 22 fe 22 fe 21 fe  20 fe 21 fe 23 fe 22 fe  |".".".!. .!.#.".|
00000180  20 fe 20 fe 20 fe 21 fe  20 fe 22 fe 21 fe 20 fe  | . . .!. .".!. .|
00000190  1f fe 1e fe 1f fe 21 fe  21 fe 1f fe 1f fe 22 fe  |......!.!.....".|
000001a0  24 fe 23 fe 21 fe 1f fe  20 fe 24 fe 24 fe 21 fe  |$.#.!... .$.$.!.|
000001b0  20 fe 22 fe 23 fe 22 fe  1f fe 1f fe 20 fe 22 fe  | .".#."..... .".|
000001c0  22 fe 21 fe 1f fe 1f fe  22 fe 24 fe 22 fe 20 fe  |".!.....".$.". .|
000001d0  20 fe 21 fe 23 fe 23 fe  22 fe 22 fe 22 fe 22 fe  | .!.#.#.".".".".|
000001e0  22 fe 22 fe 20 fe 20 fe  22 fe 24 fe 23 fe 21 fe  |".". . .".$.#.!.|
000001f0  20 fe 22 fe 22 fe 22 fe  21 fe 21 fe 20 fe 22 fe  | .".".".!.!. .".|
00000200  22 fe 23 fe 23 fe 21 fe  21 fe 22 fe 22 fe 21 fe  |".#.#.!.!.".".!.|
00000210  20 fe 21 fe 23 fe 23 fe  22 fe 20 fe 22 fe 23 fe  | .!.#.#.". .".#.|
00000220  23 fe 21 fe 20 fe 21 fe  23 fe 23 fe 22 fe 21 fe  |#.!. .!.#.#.".!.|
00000230  22 fe 23 fe 23 fe 21 fe  21 fe 21 fe 21 fe 21 fe  |".#.#.!.!.!.!.!.|
00000240  21 fe 20 fe 21 fe 22 fe  23 fe 23 fe 22 fe 21 fe  |!. .!.".#.#.".!.|
00000250  20 fe 20 fe 21 fe 22 fe  22 fe 20 fe 1f fe 22 fe  | . .!.".". ...".|
00000260  23 fe 22 fe 20 fe 21 fe  23 fe 24 fe 22 fe 20 fe  |#.". .!.#.$.". .|
00000270  20 fe 21 fe 23 fe 22 fe  21 fe 22 fe 22 fe 23 fe  | .!.#.".!.".".#.|
00000280  24 fe 22 fe 21 fe 22 fe  23 fe 23 fe 20 fe 20 fe  |$.".!.".#.#. . .|
00000290  1f fe 21 fe 22 fe 21 fe  20 fe 21 fe 23 fe 23 fe  |..!.".!. .!.#.#.|
000002a0  21 fe 20 fe 23 fe 25 fe  24 fe 23 fe 22 fe 21 fe  |!. .#.%.$.#.".!.|
000002b0  21 fe 22 fe 21 fe 20 fe  20 fe 22 fe 23 fe 20 fe  |!.".!. . .".#. .|
000002c0  1f fe 20 fe 21 fe 23 fe  23 fe 21 fe 21 fe 22 fe  |.. .!.#.#.!.!.".|
000002d0  22 fe 23 fe 21 fe 20 fe  21 fe 22 fe 23 fe 22 fe  |".#.!. .!.".#.".|
000002e0  20 fe 20 fe 21 fe 21 fe  22 fe 22 fe 23 fe 22 fe  | . .!.!.".".#.".|
000002f0  22 fe 23 fe 22 fe 22 fe  20 fe 21 fe 22 fe 23 fe  |".#.".". .!.".#.|
00000300  22 fe 22 fe 24 fe 24 fe  23 fe 22 fe 21 fe 21 fe  |".".$.$.#.".!.!.|
00000310  24 fe 24 fe 23 fe 20 fe  21 fe 23 fe 22 fe 21 fe  |$.$.#. .!.#.".!.|
00000320  20 fe 20 fe 21 fe 22 fe  21 fe 20 fe 21 fe 21 fe  | . .!.".!. .!.!.|
00000330  21 fe 21 fe 21 fe 21 fe  21 fe 22 fe 22 fe 21 fe  |!.!.!.!.!.".".!.|
00000340  22 fe 22 fe 23 fe 22 fe  22 fe 22 fe 22 fe 21 fe  |".".#.".".".".!.|
00000350  21 fe 21 fe 20 fe 1f fe  1f fe 21 fe 22 fe 22 fe  |!.!. .....!.".".|
00000360  22 fe 21 fe 21 fe 22 fe  23 fe 21 fe 1e fe 20 fe  |".!.!.".#.!... .|
00000370  23 fe 24 fe 22 fe 20 fe  21 fe 23 fe 24 fe 23 fe  |#.$.". .!.#.$.#.|
00000380  21 fe 1f fe 21 fe 23 fe  22 fe 20 fe 1f fe 20 fe  |!...!.#.". ... .|
00000390  22 fe 22 fe 21 fe 20 fe  21 fe 24 fe 23 fe 20 fe  |".".!. .!.$.#. .|
000003a0  20 fe 22 fe 22 fe 22 fe  1f fe 1e fe 21 fe 22 fe  | .".".".....!.".|
000003b0  22 fe 20 fe 21 fe 21 fe  23 fe 22 fe 22 fe 21 fe  |". .!.!.#.".".!.|
000003c0  21 fe 22 fe 22 fe 22 fe  22 fe 20 fe 21 fe 23 fe  |!.".".".". .!.#.|
000003d0  24 fe 24 fe 24 fe 21 fe  21 fe 21 fe 22 fe 22 fe  |$.$.$.!.!.!.".".|
000003e0  21 fe 22 fe 23 fe 22 fe  21 fe 20 fe 01 16 01 01  |!.".#.".!. .....|
000003f0  21 fe 23 fe 23 fe 21 fe  20 fe 21 fe 23 fe 22 fe  |!.#.#.!. .!.#.".|
00000400  21 fe 21 fe 22 fe 24 fe  23 fe 21 fe 1f fe 21 fe  |!.!.".$.#.!...!.|
00000410  23 fe 21 fe 20 fe 1e fe  20 fe 22 fe 23 fe 21 fe  |#.!. ... .".#.!.|
00000420  20 fe 21 fe 22 fe 22 fe  22 fe 20 fe 21 fe 24 fe  | .!.".".". .!.$.|
00000430  24 fe 21 fe 20 fe 22 fe  22 fe 23 fe 22 fe 22 fe  |$.!. .".".#.".".|
00000440  23 fe 22 fe 21 fe 21 fe  22 fe 23 fe 21 fe 21 fe  |#.".!.!.".#.!.!.|
00000450  22 fe 22 fe 24 fe 23 fe  20 fe 21 fe 23 fe 23 fe  |".".$.#. .!.#.#.|
00000460  22 fe 22 fe 22 fe 23 fe  22 fe 21 fe 20 fe 21 fe  |".".".#.".!. .!.|
00000470  22 fe 23 fe 22 fe 21 fe  21 fe 22 fe 23 fe 23 fe  |".#.".!.!.".#.#.|
00000480  21 fe 22 fe 23 fe 23 fe  22 fe 21 fe 21 fe 22 fe  |!.".#.#.".!.!.".|
00000490  23 fe 22 fe 21 fe 21 fe  22 fe 21 fe 21 fe 21 fe  |#.".!.!.".!.!.!.|
000004a0  21 fe 22 fe 22 fe 21 fe  22 fe 21 fe 21 fe 21 fe  |!.".".!.".!.!.!.|
000004b0  21 fe 23 fe 21 fe 22 fe  21 fe 21 fe 24 fe 23 fe  |!.#.!.".!.!.$.#.|
000004c0  22 fe 22 fe 22 fe 22 fe  23 fe 21 fe 20 fe 21 fe  |".".".".#.!. .!.|
000004d0  22 fe 23 fe 23 fe 1f fe  20 fe 21 fe 21 fe 21 fe  |".#.#... .!.!.!.|
000004e0  1f fe 20 fe 22 fe 24 fe  22 fe 20 fe 20 fe 22 fe  |.. .".$.". . .".|
000004f0  23 fe 22 fe 21 fe 21 fe  22 fe 22 fe 23 fe 22 fe  |#.".!.!.".".#.".|
00000500  21 fe 22 fe 22 fe 21 fe  20 fe 21 fe 23 fe 23 fe  |!.".".!. .!.#.#.|
00000510  23 fe 21 fe 21 fe 22 fe  23 fe 22 fe 21 fe 21 fe  |#.!.!.".#.".!.!.|
00000520  21 fe 22 fe 21 fe 21 fe  22 fe 21 fe 22 fe 22 fe  |!.".!.!.".!.".".|
00000530  22 fe 23 fe 22 fe 22 fe  22 fe 23 fe 22 fe 21 fe  |".#.".".".#.".!.|
00000540  21 fe 20 fe 21 fe 21 fe  20 fe 1f fe 20 fe 21 fe  |!. .!.!. ... .!.|
00000550  22 fe 21 fe 20 fe 21 fe  22 fe 22 fe 20 fe 1f fe  |".!. .!.".". ...|
00000560  21 fe 23 fe 23 fe 22 fe  20 fe 22 fe 23 fe 24 fe  |!.#.#.". .".#.$.|
00000570  23 fe 21 fe 21 fe 21 fe  23 fe 21 fe 1e fe 20 fe  |#.!.!.!.#.!... .|
00000580  21 fe 22 fe 20 fe 1f fe  21 fe 22 fe 23 fe 20 fe  |!.". ...!.".#. .|
00000590  1d fe 1f fe 20 fe 21 fe  20 fe 20 fe 20 fe 21 fe  |.... .!. . . .!.|
000005a0  21 fe 20 fe 1f fe 20 fe  21 fe 22 fe 21 fe 21 fe  |!. ... .!.".!.!.|
000005b0  22 fe 21 fe 1f fe 20 fe  21 fe 21 fe 21 fe 21 fe  |".!... .!.!.!.!.|
000005c0  22 fe 23 fe 22 fe 21 fe  21 fe 22 fe 23 fe 23 fe  |".#.".!.!.".#.#.|
000005d0  21 fe 21 fe 22 fe 23 fe  24 fe 21 fe 1f fe 20 fe  |!.!.".#.$.!... .|
000005e0  23 fe 22 fe 20 fe 20 fe  23 fe 25 fe 24 fe 21 fe  |#.". . .#.%.$.!.|
000005f0  22 fe 23 fe 25 fe 21 fe  1f fe 22 fe 25 fe 24 fe  |".#.%.!...".%.$.|
00000600  22 fe 20 fe 20 fe 22 fe  23 fe 21 fe 1f fe 20 fe  |". . .".#.!... .|
00000610  22 fe 22 fe 20 fe 21 fe  21 fe 21 fe 22 fe 21 fe  |".". .!.!.!.".!.|
00000620  21 fe 21 fe 23 fe 23 fe  21 fe 21 fe 21 fe 21 fe  |!.!.#.#.!.!.!.!.|
00000630  20 fe 1e fe 20 fe 23 fe  22 fe 20 fe 1f fe 20 fe  | ... .#.". ... .|
00000640  21 fe 23 fe 21 fe 20 fe  20 fe 22 fe 23 fe 22 fe  |!.#.!. . .".#.".|
00000650  1f fe 20 fe 23 fe 24 fe  22 fe 1f fe 20 fe 23 fe  |.. .#.$."... .#.|
00000660  24 fe 23 fe 21 fe 20 fe  22 fe 23 fe 23 fe 21 fe  |$.#.!. .".#.#.!.|
00000670  20 fe 21 fe 24 fe 24 fe  21 fe 21 fe 21 fe 23 fe  | .!.$.$.!.!.!.#.|
00000680  24 fe 23 fe 22 fe 21 fe  22 fe 22 fe 21 fe 21 fe  |$.#.".!.".".!.!.|
00000690  21 fe 23 fe 24 fe 22 fe  21 fe 21 fe 22 fe 23 fe  |!.#.$.".!.!.".#.|
000006a0  23 fe 22 fe 21 fe 21 fe  22 fe 23 fe 22 fe 23 fe  |#.".!.!.".#.".#.|
000006b0  24 fe 22 fe 22 fe 21 fe  21 fe 20 fe 21 fe 22 fe  |$.".".!.!. .!.".|
000006c0  23 fe 23 fe 23 fe 21 fe  22 fe 22 fe 23 fe 23 fe  |#.#.#.!.".".#.#.|
000006d0  21 fe 21 fe 23 fe 23 fe  21 fe 22 fe 22 fe 23 fe  |!.!.#.#.!.".".#.|
000006e0  23 fe 22 fe 20 fe 20 fe  22 fe 23 fe 23 fe 23 fe  |#.". . .".#.#.#.|
000006f0  23 fe 24 fe 23 fe 22 fe  22 fe 23 fe 24 fe 23 fe  |#.$.#.".".#.$.#.|
00000700  22 fe 22 fe 21 fe 21 fe  22 fe 22 fe 20 fe 22 fe  |".".!.!.".". .".|
00000710  22 fe 22 fe 22 fe 21 fe  21 fe 22 fe 20 fe 1e fe  |".".".!.!.". ...|
00000720  20 fe 22 fe 23 fe 22 fe  1f fe 21 fe 22 fe 22 fe  | .".#."...!.".".|
00000730  21 fe 1f fe 20 fe 21 fe  21 fe 21 fe 20 fe 21 fe  |!... .!.!.!. .!.|
00000740  22 fe 23 fe 20 fe 1f fe  1f fe 21 fe 1f fe 20 fe  |".#. .....!... .|
00000750  20 fe 20 fe 1f fe 21 fe  21 fe 21 fe 21 fe 21 fe  | . ...!.!.!.!.!.|
00000760  21 fe 20 fe 21 fe 21 fe  21 fe 22 fe 22 fe 21 fe  |!. .!.!.!.".".!.|
00000770  20 fe 1f fe 21 fe 22 fe  21 fe 21 fe 21 fe 21 fe  | ...!.".!.!.!.!.|
00000780  20 fe 20 fe 20 fe 1f fe  1f fe 20 fe 20 fe 21 fe  | . . ..... . .!.|
00000790  20 fe 20 fe 20 fe 20 fe  21 fe 21 fe 1e fe 1d fe  | . . . .!.!.....|
000007a0  1f fe 20 fe 1f fe 20 fe  1f fe 21 fe 21 fe 20 fe  |.. ... ...!.!. .|
000007b0  1f fe 1f fe 1f fe 21 fe  21 fe 1f fe 1f fe 1f fe  |......!.!.......|
000007c0  20 fe 21 fe 1f fe 1e fe  1f fe 1f fe 20 fe 21 fe  | .!......... .!.|
000007d0  21 fe 1f fe 1f fe 20 fe  01 16 01 02 20 fe 20 fe  |!..... ..... . .|
000007e0  20 fe 21 fe 20 fe 21 fe  23 fe 21 fe 20 fe 20 fe  | .!. .!.#.!. . .|
000007f0  1f fe 20 fe 21 fe 21 fe  20 fe 20 fe 21 fe 23 fe  |.. .!.!. . .!.#.|
00000800  23 fe 20 fe 20 fe 22 fe  21 fe 22 fe 20 fe 20 fe  |#. . .".!.". . .|
00000810  23 fe 22 fe 21 fe 20 fe  20 fe 21 fe 22 fe 21 fe  |#.".!. . .!.".!.|
00000820  20 fe 1f fe 21 fe 22 fe  21 fe 21 fe 21 fe 22 fe  | ...!.".!.!.!.".|
00000830  22 fe 21 fe 20 fe 21 fe  22 fe 21 fe 21 fe 22 fe  |".!. .!.".!.!.".|
00000840  21 fe 21 fe 22 fe 21 fe  21 fe 21 fe 22 fe 22 fe  |!.!.".!.!.!.".".|
00000850  21 fe 22 fe 23 fe 24 fe  22 fe 20 fe 20 fe 23 fe  |!.".#.$.". . .#.|
00000860  23 fe 22 fe 21 fe 20 fe  22 fe 23 fe 23 fe 1f fe  |#.".!. .".#.#...|
00000870  1e fe 21 fe 24 fe 23 fe  21 fe 20 fe 21 fe 23 fe  |..!.$.#.!. .!.#.|
00000880  22 fe 1e fe 1d fe 20 fe  21 fe 21 fe 20 fe 1f fe  |"..... .!.!. ...|
00000890  21 fe 22 fe 21 fe 1f fe  1f fe 20 fe 21 fe 21 fe  |!.".!..... .!.!.|
000008a0  20 fe 1f fe 21 fe 21 fe  20 fe 1f fe 20 fe 20 fe  | ...!.!. ... . .|
000008b0  1f fe 20 fe 21 fe 1f fe  1f fe 1f fe 20 fe 21 fe  |.. .!....... .!.|
000008c0  23 fe 23 fe 22 fe 20 fe  21 fe 21 fe 23 fe 23 fe  |#.#.". .!.!.#.#.|
000008d0  21 fe 21 fe 21 fe 22 fe  21 fe 20 fe 1f fe 21 fe  |!.!.!.".!. ...!.|
000008e0  23 fe 22 fe 21 fe 1f fe  21 fe 24 fe 23 fe 20 fe  |#.".!...!.$.#. .|
000008f0  20 fe 21 fe 24 fe 23 fe  21 fe 1f fe 1f fe 21 fe  | .!.$.#.!.....!.|
00000900  23 fe 23 fe 21 fe 21 fe  22 fe 23 fe 23 fe 21 fe  |#.#.!.!.".#.#.!.|
00000910  21 fe 22 fe 23 fe 22 fe  21 fe 20 fe 1f fe 1f fe  |!.".#.".!. .....|
00000920  20 fe 1f fe 20 fe 20 fe  1e fe 1f fe 1f fe 21 fe  | ... . .......!.|
00000930  21 fe 1f fe 1f fe 21 fe  22 fe 1f fe 1e fe 1f fe  |!.....!.".......|
00000940  21 fe 22 fe 20 fe 1e fe  1f fe 20 fe 21 fe 20 fe  |!.". ..... .!. .|
00000950  1d fe 1e fe 21 fe 22 fe  22 fe 21 fe 20 fe 21 fe  |....!.".".!. .!.|
00000960  23 fe 21 fe 1f fe 1d fe  20 fe 23 fe 23 fe 23 fe  |#.!..... .#.#.#.|
00000970  20 fe 1f fe 20 fe 21 fe  20 fe 20 fe 20 fe 21 fe  | ... .!. . . .!.|
00000980  21 fe 20 fe 1f fe 20 fe  21 fe 21 fe 21 fe 22 fe  |!. ... .!.!.!.".|
00000990  22 fe 21 fe 20 fe 21 fe  21 fe 20 fe 1f fe 1e fe  |".!. .!.!. .....|
000009a0  1f fe 21 fe 21 fe 21 fe  21 fe 21 fe 21 fe 21 fe  |..!.!.!.!.!.!.!.|
000009b0  22 fe 20 fe 1f fe 20 fe  21 fe 21 fe 20 fe 20 fe  |". ... .!.!. . .|
000009c0  21 fe 22 fe 21 fe 1f fe  20 fe 20 fe 20 fe 20 fe  |!.".!... . . . .|
000009d0  20 fe 20 fe 20 fe 1f fe  20 fe 21 fe 20 fe 20 fe  | . . ... .!. . .|
000009e0  1f fe 1f fe 20 fe 21 fe  20 fe 1f fe 1f fe 1e fe  |.... .!. .......|
000009f0  1e fe 1f fe 1e fe 1e fe  1f fe 20 fe 20 fe 21 fe  |.......... . .!.|
00000a00  1f fe 20 fe 22 fe 22 fe  20 fe 1e fe 1f fe 21 fe  |.. .".". .....!.|
00000a10  23 fe 21 fe 1e fe 1e fe  21 fe 23 fe 23 fe 20 fe  |#.!.....!.#.#. .|
00000a20  1f fe 21 fe 24 fe 24 fe  1f fe 1e fe 21 fe 22 fe  |..!.$.$.....!.".|
00000a30  22 fe 1e fe 1e fe 1f fe  23 fe 21 fe 20 fe 1e fe  |".......#.!. ...|
00000a40  21 fe 24 fe 23 fe 21 fe  1f fe 20 fe 22 fe 25 fe  |!.$.#.!... .".%.|
00000a50  23 fe 21 fe 20 fe 23 fe  26 fe 24 fe 21 fe 20 fe  |#.!. .#.&.$.!. .|
00000a60  22 fe 23 fe 23 fe 22 fe  21 fe 21 fe 22 fe 23 fe  |".#.#.".!.!.".#.|
00000a70  23 fe 21 fe 20 fe 20 fe  22 fe 23 fe 22 fe 21 fe  |#.!. . .".#.".!.|
00000a80  20 fe 22 fe 24 fe 25 fe  23 fe 20 fe 20 fe 23 fe  | .".$.%.#. . .#.|
00000a90  24 fe 22 fe 1f fe 1f fe  22 fe 26 fe 26 fe 22 fe  |$.".....".&.&.".|
00000aa0  1f fe 21 fe 24 fe 24 fe  20 fe 1d fe 20 fe 23 fe  |..!.$.$. ... .#.|
00000ab0  24 fe 21 fe 1d fe 1e fe  23 fe 23 fe 22 fe 20 fe  |$.!.....#.#.". .|
00000ac0  20 fe 20 fe 21 fe 23 fe  22 fe 21 fe 21 fe 21 fe  | . .!.#.".!.!.!.|
00000ad0  23 fe 23 fe 22 fe 1f fe  1f fe 22 fe 22 fe 21 fe  |#.#.".....".".!.|
00000ae0  20 fe 1e fe 20 fe 21 fe  24 fe 21 fe 1e fe 1f fe  | ... .!.$.!.....|
00000af0  23 fe 24 fe 21 fe 1f fe  1e fe 21 fe 24 fe 24 fe  |#.$.!.....!.$.$.|
00000b00  1f fe 1d fe 1f fe 22 fe  23 fe 20 fe 1e fe 1f fe  |......".#. .....|
00000b10  23 fe 25 fe 23 fe 1f fe  1f fe 22 fe 24 fe 22 fe  |#.%.#.....".$.".|
00000b20  20 fe 20 fe 23 fe 25 fe  24 fe 23 fe 21 fe 22 fe  | . .#.%.$.#.!.".|
00000b30  23 fe 22 fe 21 fe 20 fe  22 fe 24 fe 23 fe 22 fe  |#.".!. .".$.#.".|
00000b40  22 fe 22 fe 22 fe 23 fe  24 fe 23 fe 22 fe 21 fe  |".".".#.$.#.".!.|
00000b50  20 fe 22 fe 24 fe 23 fe  21 fe 1f fe 20 fe 22 fe  | .".$.#.!... .".|
00000b60  23 fe 22 fe 1f fe 20 fe  23 fe 24 fe 23 fe 20 fe  |#."... .#.$.#. .|
00000b70  1f fe 21 fe 25 fe 25 fe  21 fe 20 fe 21 fe 23 fe  |..!.%.%.!. .!.#.|
00000b80  24 fe 1f fe 1e fe 20 fe  22 fe 24 fe 23 fe 21 fe  |$..... .".$.#.!.|
00000b90  21 fe 23 fe 23 fe 23 fe  22 fe 23 fe 22 fe 24 fe  |!.#.#.#.".#.".$.|
00000ba0  23 fe 22 fe 22 fe 21 fe  21 fe 23 fe 25 fe 24 fe  |#.".".!.!.#.%.$.|
00000bb0  22 fe 21 fe 23 fe 25 fe  24 fe 22 fe 20 fe 20 fe  |".!.#.%.$.". . .|
00000bc0  24 fe 25 fe 01 16 01 03  23 fe 20 fe 22 fe 21 fe  |$.%.....#. .".!.|
00000bd0  23 fe 22 fe 1e fe 1c fe  1f fe 22 fe 22 fe 1e fe  |#."......."."...|
00000be0  1c fe 1d fe 21 fe 23 fe  20 fe 1e fe 1d fe 22 fe  |....!.#. .....".|
00000bf0  24 fe 21 fe 1c fe 1d fe  20 fe 24 fe 21 fe 1d fe  |$.!..... .$.!...|
00000c00  1d fe 20 fe 24 fe 23 fe  20 fe 1f fe 21 fe 24 fe  |.. .$.#. ...!.$.|
00000c10  23 fe 1f fe 1e fe 1f fe  21 fe 21 fe 1e fe 1e fe  |#.......!.!.....|
00000c20  20 fe 21 fe 20 fe 20 fe  20 fe 20 fe 20 fe 21 fe  | .!. . . . . .!.|
00000c30  21 fe 22 fe 22 fe 21 fe  20 fe 21 fe 22 fe 22 fe  |!.".".!. .!.".".|
00000c40  21 fe 20 fe 1f fe 21 fe  22 fe 20 fe 1d fe 1d fe  |!. ...!.". .....|
00000c50  20 fe 22 fe 21 fe 1e fe  1e fe 20 fe 23 fe 21 fe  | .".!..... .#.!.|
00000c60  1e fe 1e fe 1f fe 23 fe  22 fe 20 fe 1c fe 1d fe  |......#.". .....|
00000c70  21 fe 21 fe 1f fe 1d fe  1e fe 20 fe 20 fe 1f fe  |!.!....... . ...|
00000c80  1d fe 1c fe 1f fe 21 fe  1f fe 1d fe 1c fe 1e fe  |......!.........|
00000c90  20 fe 20 fe 21 fe 20 fe  20 fe 20 fe 20 fe 22 fe  | . .!. . . . .".|
00000ca0  22 fe 21 fe 20 fe 1f fe  21 fe 22 fe 22 fe 20 fe  |".!. ...!.".". .|
00000cb0  20 fe 22 fe 23 fe 23 fe  20 fe 1f fe 22 fe 23 fe  | .".#.#. ...".#.|
00000cc0  23 fe 20 fe 1d fe 1d fe  22 fe 24 fe 20 fe 1d fe  |#. .....".$. ...|
00000cd0  1d fe 21 fe 25 fe 23 fe  1f fe 1d fe 21 fe 23 fe  |..!.%.#.....!.#.|
00000ce0  20 fe 1d fe 1d fe 1f fe  23 fe 24 fe 20 fe 1e fe  | .......#.$. ...|
00000cf0  1f fe 23 fe 24 fe 22 fe  20 fe 21 fe 21 fe 23 fe  |..#.$.". .!.!.#.|
00000d00  21 fe 1f fe 21 fe 21 fe  22 fe 21 fe 20 fe 21 fe  |!...!.!.".!. .!.|
00000d10  21 fe 21 fe 21 fe 21 fe  21 fe 22 fe 21 fe 1e fe  |!.!.!.!.!.".!...|
00000d20  21 fe 23 fe 22 fe 20 fe  20 fe 20 fe 23 fe 25 fe  |!.#.". . . .#.%.|
00000d30  23 fe 21 fe 1f fe 21 fe  24 fe 24 fe 20 fe 1f fe  |#.!...!.$.$. ...|
00000d40  22 fe 23 fe 22 fe 20 fe  20 fe 22 fe 24 fe 23 fe  |".#.". . .".$.#.|
00000d50  20 fe 1e fe 20 fe 23 fe  23 fe 21 fe 20 fe 22 fe  | ... .#.#.!. .".|
00000d60  22 fe 23 fe 22 fe 21 fe  20 fe 20 fe 21 fe 21 fe  |".#.".!. . .!.!.|
00000d70  21 fe 22 fe 21 fe 20 fe  1f fe 21 fe 22 fe 21 fe  |!.".!. ...!.".!.|
00000d80  20 fe 1e fe 21 fe 24 fe  21 fe 20 fe 1f fe 21 fe  | ...!.$.!. ...!.|
00000d90  23 fe 23 fe 20 fe 1f fe  22 fe 25 fe 25 fe 20 fe  |#.#. ...".%.%. .|
00000da0  1e fe 20 fe 23 fe 23 fe  1e fe 1c fe 1e fe 22 fe  |.. .#.#.......".|
00000db0  25 fe 23 fe 1f fe 1e fe  22 fe 24 fe 22 fe 1e fe  |%.#.....".$."...|
00000dc0  1d fe 21 fe 23 fe 21 fe  1e fe 1e fe 20 fe 23 fe  |..!.#.!..... .#.|
00000dd0  22 fe 20 fe 1f fe 21 fe  22 fe 22 fe 21 fe 21 fe  |". ...!.".".!.!.|
00000de0  22 fe 23 fe 22 fe 21 fe  22 fe 23 fe 23 fe 22 fe  |".#.".!.".#.#.".|
00000df0  22 fe 22 fe 22 fe 21 fe  1f fe 20 fe 23 fe 24 fe  |".".".!... .#.$.|
00000e00  21 fe 1e fe 1e fe 21 fe  23 fe 23 fe 20 fe 20 fe  |!.....!.#.#. . .|
00000e10  24 fe 25 fe 23 fe 21 fe  20 fe 23 fe 27 fe 24 fe  |$.%.#.!. .#.'.$.|
00000e20  20 fe 1f fe 22 fe 24 fe  25 fe 22 fe 1d fe 1d fe  | ...".$.%.".....|
00000e30  20 fe 21 fe 1f fe 1c fe  1c fe 1f fe 21 fe 20 fe  | .!.........!. .|
00000e40  1c fe 1e fe 21 fe 22 fe  1f fe 1e fe 1e fe 20 fe  |....!."....... .|
00000e50  1f fe 1d fe 1d fe 1f fe  20 fe 1f fe 1d fe 1d fe  |........ .......|
00000e60  1f fe 20 fe 1f fe 1d fe  1c fe 20 fe 22 fe 20 fe  |.. ....... .". .|
00000e70  1d fe 1c fe 1f fe 22 fe  21 fe 1d fe 1d fe 20 fe  |......".!..... .|
00000e80  23 fe 22 fe 1e fe 1c fe  1d fe 20 fe 22 fe 20 fe  |#."....... .". .|
00000e90  1c fe 1c fe 21 fe 21 fe  20 fe 1f fe 1c fe 1f fe  |....!.!. .......|
00000ea0  21 fe 1e fe 1e fe 1e fe  1e fe 1f fe 20 fe 1e fe  |!........... ...|
00000eb0  1e fe 1e fe 1e fe 1f fe  20 fe 20 fe 20 fe 20 fe  |........ . . . .|
00000ec0  1f fe 1e fe 1f fe 21 fe  20 fe 1e fe 1f fe 1f fe  |......!. .......|
00000ed0  21 fe 20 fe 1d fe 1e fe  20 fe 1f fe 1e fe 1d fe  |!. ..... .......|
00000ee0  1e fe 22 fe 24 fe 23 fe  1f fe 1e fe 20 fe 22 fe  |..".$.#..... .".|
00000ef0  23 fe 20 fe 1f fe 20 fe  22 fe 21 fe 20 fe 20 fe  |#. ... .".!. . .|
00000f00  21 fe 23 fe 23 fe 20 fe  1e fe 22 fe 23 fe 22 fe  |!.#.#. ...".#.".|
00000f10  20 fe 1f fe 20 fe 21 fe  20 fe 1f fe 20 fe 21 fe  | ... .!. ... .!.|
00000f20  23 fe 21 fe 1f fe 1f fe  21 fe 22 fe 1f fe 1d fe  |#.!.....!.".....|
00000f30  1e fe 21 fe 21 fe 20 fe  1d fe 1d fe 20 fe 21 fe  |..!.!. ..... .!.|
00000f40  21 fe 1e fe 1d fe 20 fe  23 fe 20 fe 1b fe 1d fe  |!..... .#. .....|
00000f50  20 fe 22 fe 21 fe 1d fe  1d fe 20 fe 22 fe 21 fe  | .".!..... .".!.|
00000f60  1d fe 1c fe 1f fe 22 fe  20 fe 1d fe 1c fe 1d fe  |......". .......|
00000f70  21 fe 21 fe 20 fe 1f fe  20 fe 22 fe 23 fe 21 fe  |!.!. ... .".#.!.|
00000f80  1e fe 20 fe 22 fe 23 fe  21 fe 1d fe 1f fe 22 fe  |.. .".#.!.....".|
00000f90  23 fe 20 fe 1e fe 1e fe  21 fe 21 fe 1e fe 1d fe  |#. .....!.!.....|
00000fa0  21 fe 23 fe 22 fe 1f fe  1e fe 20 fe 21 fe 22 fe  |!.#."..... .!.".|
00000fb0  01 16 01 04 24 fe a8 fd  a8 fd a8 fd a8 fd a8 fd  |....$...........|
00000fc0  a8 fd a8 fd a8 fd a8 fd  a8 fd a8 fd a8 fd a8 fd  |................|
*
00001390  a8 fd a8 fd a8 fd a8 fd  a8 fd a8 fd 01 16 01 05  |................|
000013a0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001410  00 00 00 00 00 00 00 00  00 fd a8 fd a8 fd a8 fd  |................|
00001420  a8 fd a8 fd a8 fd a8 fd  a8 fd a8 fd a8 fd a8 fd  |................|
*
00001788

```


## 发布版本v0.1 
完成存储,单通道单次扫描采样数据为2000个点.
加入bomberTimerSp用于定时,目前定时5小时,到时间软件自动关闭(自己生成的疑似bug,划水专用)

已加入UDP超时重启仪表发送功能实现,仪表的重新正确发送数据:
> 当仪表连续发送,可能会出现突然停止发包,这时如果直接重新发送获取当前通道光谱数据,后续获得的所有数据错误.因此改为发送关闭连接指令,然后再次发送获取当前通道数据,返回数据正确.(仅测试5小时)



-----


仪表ip `192.168.0.119`  port `4010`

客户端ip `192.168.0.xxx` port `8080` (别的port应该也可以)

## UDP协议
客户端发送
`0x10a55` 开启仪表发送
`0x10a00` 关闭仪表发送

## 接受数据包格式

开启仪表发送后仪表会一直发以下数据包, 直到客户端发送关闭仪表发送指令.
测试环境:仪表第三号通道连接一个光栅,其他通道无连接
以下每一组连续十六进制数字代表一个字节数据(开头0会省略比如`02`省略为`2`):
```
1 a 55 0

1 c 0 0 1 0 2 1 47 76 3 0 4 0 5 0 6 0 7 0 8 0 9 0 a 0 b 0 c 0 d 0 e 0 f 0

1 c 0 0 1 0 2 1 47 76 3 0 4 0 5 0 6 0 7 0 8 0 9 0 a 0 b 0 c 0 d 0 e 0 f 0

1 c 0 0 1 0 2 1 46 76 3 0 4 0 5 0 6 0 7 0 8 0 9 0 a 0 b 0 c 0 d 0 e 0 f 0

1 c 0 0 1 0 2 1 46 76 3 0 4 0 5 0 6 0 7 0 8 0 9 0 a 0 b 0 c 0 d 0 e 0 f 0
```

数据包详解:
- 接收到的第一个数据包`1 a 55 0`没有意义.
- 后续接收到的数据包长度相同(如果仪表上连接的光纤没有脱落或者折断)
- 每一行表示接收到的一个数据包.
- 每个数据包的开头都是1C
- 接下来的2个字节`0 0 `表示第一个通道数据(0)的数据无(0),由于没有连接光栅.
- 接下来2字节`1 0 `表示第二个通道(1)数据无(0),理由同上
- 接下来3字节`2 1 47 76`表示第三通道(2)存在一个数据数据(1),连接有一个光栅,光栅数据为`47 76`,这里的**光栅数据通过下面计算可以转换成波长值**.
- 通道内连接的每个光栅对应数据由2字节表示例如上面的`47 76`, 因此该通道n个光栅的数据长度是$2 \times n$, 如果没有光栅就是一个字节`0`.

$$
实际波长值为(DataL +DataH\times256) \div 1000+1520
$$


