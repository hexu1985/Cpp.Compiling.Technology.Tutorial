### 反汇编二进制文件

对此特定任务而言，objdump是最佳工具。
实际上，这可能是readelf无法提供平行解决方案的唯一场景。
具体来说，可通过以下命令反汇编.text段：

```bash
$ objdump -d <二进制文件路径>
```

此外，还可指定反汇编格式（AT&T与Intel风格）：

```bash
$ objdump -d -M intel <二进制文件路径>
```

```bash
$ objdump -d -Mintel libdemo.so | grep -A 10 add_and_multiply
0000000000001141 <add_and_multiply>:
    1141:	f3 0f 1e fa          	endbr64
    1145:	55                   	push   rbp
    1146:	48 89 e5             	mov    rbp,rsp
    1149:	48 83 ec 20          	sub    rsp,0x20
    114d:	f3 0f 11 45 ec       	movss  DWORD PTR [rbp-0x14],xmm0
    1152:	f3 0f 11 4d e8       	movss  DWORD PTR [rbp-0x18],xmm1
    1157:	f3 0f 10 45 e8       	movss  xmm0,DWORD PTR [rbp-0x18]
    115c:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
    115f:	0f 28 c8             	movaps xmm1,xmm0
    1162:	66 0f 6e c0          	movd   xmm0,eax
```

```bash
$ objdump -d -M intel appDemo | grep -A 10 '<main>'
    1078:	48 8d 3d ca 00 00 00 	lea    rdi,[rip+0xca]        # 1149 <main>
    107f:	ff 15 4b 2f 00 00    	call   QWORD PTR [rip+0x2f4b]        # 3fd0 <__libc_start_main@GLIBC_2.34>
    1085:	f4                   	hlt
    1086:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    108d:	00 00 00

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 79 2f 00 00 	lea    rdi,[rip+0x2f79]        # 4010 <__TMC_END__>
    1097:	48 8d 05 72 2f 00 00 	lea    rax,[rip+0x2f72]        # 4010 <__TMC_END__>
    109e:	48 39 f8             	cmp    rax,rdi
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
--
0000000000001149 <main>:
    1149:	f3 0f 1e fa          	endbr64
    114d:	55                   	push   rbp
    114e:	48 89 e5             	mov    rbp,rsp
    1151:	48 83 ec 20          	sub    rsp,0x20
    1155:	89 7d ec             	mov    DWORD PTR [rbp-0x14],edi
    1158:	48 89 75 e0          	mov    QWORD PTR [rbp-0x20],rsi
    115c:	f3 0f 10 05 a0 0e 00 	movss  xmm0,DWORD PTR [rip+0xea0]        # 2004 <_IO_stdin_used+0x4>
    1163:	00
    1164:	f3 0f 11 45 f4       	movss  DWORD PTR [rbp-0xc],xmm0
    1169:	f3 0f 10 05 97 0e 00 	movss  xmm0,DWORD PTR [rip+0xe97]        # 2008 <_IO_stdin_used+0x8>
```

若需要查看与汇编指令交织显示的源代码（若可用），可运行：

```bash
$ objdump -d -M intel -S <二进制文件路径>
```

该选项仅在二进制文件为调试版本（即使用-g选项编译）时生效。

```bash
$ objdump -d -S -M intel libdemo.so | grep -A 26 '<add_and_multiply>'
0000000000001141 <add_and_multiply>:

float add_and_multiply(float x, float y)
{
    1141:	f3 0f 1e fa          	endbr64
    1145:	55                   	push   rbp
    1146:	48 89 e5             	mov    rbp,rsp
    1149:	48 83 ec 20          	sub    rsp,0x20
    114d:	f3 0f 11 45 ec       	movss  DWORD PTR [rbp-0x14],xmm0
    1152:	f3 0f 11 4d e8       	movss  DWORD PTR [rbp-0x18],xmm1
    float z = add(x,y);
    1157:	f3 0f 10 45 e8       	movss  xmm0,DWORD PTR [rbp-0x18]
    115c:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
    115f:	0f 28 c8             	movaps xmm1,xmm0
    1162:	66 0f 6e c0          	movd   xmm0,eax
    1166:	e8 e5 fe ff ff       	call   1050 <add@plt>
    116b:	66 0f 7e c0          	movd   eax,xmm0
    116f:	89 45 fc             	mov    DWORD PTR [rbp-0x4],eax
    z *= MULTIPLIER;
    1172:	f3 0f 10 4d fc       	movss  xmm1,DWORD PTR [rbp-0x4]
    1177:	f3 0f 10 05 81 0e 00 	movss  xmm0,DWORD PTR [rip+0xe81]        # 2000 <_fini+0xe70>
    117e:	00
    117f:	f3 0f 59 c1          	mulss  xmm0,xmm1
    1183:	f3 0f 11 45 fc       	movss  DWORD PTR [rbp-0x4],xmm0
    return z;
    1188:	f3 0f 10 45 fc       	movss  xmm0,DWORD PTR [rbp-0x4]
}
```

最后，您可能需要分析特定节内的代码。除了众所周知的代码节.text外，其他节（例如.plt）也可能包含源代码。

默认情况下，objdump会反汇编所有包含代码的节。若要指定反汇编某个特定的节，可使用`-j`选项：

```bash
$ objdump -d -S -M intel -j .plt <二进制文件路径>
```

```bash
$ objdump -d -M intel -j .plt appDemo

appDemo：     文件格式 elf64-x86-64


Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 92 2f 00 00    	push   QWORD PTR [rip+0x2f92]        # 3fb8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 93 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f93]        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nop    DWORD PTR [rax]
    1030:	f3 0f 1e fa          	endbr64
    1034:	68 00 00 00 00       	push   0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
```

#### 参考资料:
《高级C/C++编译技术》: 12.2.3 objdump、13.7.1 反汇编二进制文件

