#ifndef LNETDEF
#define LNETDEF

#endif // LNETDEF

// 根据数据包结构不同划分命令主命令
enum E_MainCmd
{
    EM_NetCheck,        // 网络监测
    EM_PacketFile,      // 文件包
    EM_PacketText       // 字节包
};
