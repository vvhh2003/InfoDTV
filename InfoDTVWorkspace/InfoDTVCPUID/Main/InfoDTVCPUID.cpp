//============================================================================
// Name        : InfoDTVCPUID.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>


#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include "DTAPI.h"
#include <boost/lexical_cast.hpp>
bool CheckMAC(unsigned int aNetworkCardID,unsigned char aSrcMac[])
{
	struct ifreq ifr;
	int sock;
	unsigned char *ptr;
	int status;
	//string TmpStr="eth"+
	sprintf(ifr.ifr_name,"eth%d",aNetworkCardID);
//	strcpy (ifr.ifr_name , "eth1");
	sock = socket (PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock == -1)
	{
		return false;
	}
	status = ioctl (sock, SIOCGIFHWADDR, &ifr);
	if (status < 0)
	{
		close (sock);
		return false;
	}
	ptr =(unsigned char *) ifr.ifr_hwaddr.sa_data;
	if(ptr[0]==aSrcMac[0]&&ptr[1]==aSrcMac[1]
	&&ptr[2]==aSrcMac[2]&&ptr[3]==aSrcMac[3]
   &&ptr[4]==aSrcMac[4]&&ptr[5]==aSrcMac[5])
		return true;
	else
		return false;
}
bool CheckResult(DTAPI_RESULT AResult, bool AIsNeedBreak, std::string AErrorStr)
	{
		if (AResult!=DTAPI_OK)
		{
			std::string TT=AErrorStr+":"+boost::lexical_cast<std::string>(AResult);
			std::cout<<TT;
			if (AIsNeedBreak)
				return false;
		}
		return true;
	}

int main()
{
	DtDevice FDevice;

			//DtInpChannel InputChannel;
	DTAPI_RESULT Result=FDevice.AttachToType(2145);
		if (!CheckResult(Result, true, "InitDriverByType Error:"))
		{
			return false;
		}

		char TT[64];
		std::memset(TT,0,64);
		std::string SN="";
		Result=FDevice.VpdRead("SN",TT);
		if (!CheckResult(Result, true, "Check Device Error:"))
		{
			return false;
		}
		std::string TmpStr=TT;

	std::cout<<TmpStr;
}
int main3()
{
	unsigned char TT[]={0x8,0x0,0x27,0x1F,0xAC,0x5A};
	if(CheckMAC(1,TT))
			printf("oK");
    struct ifreq ifr;
    int sock;
    unsigned char *ptr;
    int status;
    strcpy (ifr.ifr_name , "eth0");
    sock = socket (PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock == -1)
    {
        perror ("socket error ");
        return -1;
    }
    status = ioctl (sock, SIOCGIFHWADDR, &ifr);
    if (status < 0)
    {
        perror ("ioctl error ");
        close (sock);
        return -2;
    }
    ptr =(unsigned char *) ifr.ifr_hwaddr.sa_data;
    printf("%02x.%02x.%02x.%02x.%02x.%02x\n",
            ptr[0], ptr[1],ptr[2],ptr[3],ptr[4],ptr[5]);
}


using namespace std;
enum x86_cpus {
    X86_VENDOR_INTEL,
    X86_VENDOR_AMD,
    X86_VENDOR_CYRIX,
    X86_VENDOR_TRANSMETA,
    X86_VENDOR_UNKNOWN
} x86_vendor;


void print_cache_descriptor(unsigned char);
int main2() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!





    unsigned int eflags1, eflags2 = 0;
    unsigned int eax, ebx, ecx, edx;
    unsigned int serial_num = 0;

    eax = ebx = ecx = edx = 0;

    /**
     * 测试CPU是否支持CPUID指令。
     * eflags寄存器的第21位，如果程序可以清楚/设置它，则说明CPU支持CPUID指令。否则不支持
     */

    /* 先取eflags */
    asm volatile ("pushf\n\t"
              "popl %%eax"
              : "=a"(eflags1)
              :
              : "memory"
              );
    printf("original eflags is\t\t: 0x%08x\n", eflags1);




    /* 把eflags的第21位取反，写回寄存器中 */
    asm volatile ("pushl %0\n\t"
                  "popf"
                  :
                  : "g"(eflags1 ^ 0x00200000)
                  );

    /* 检查一下现在的eflags，确认第21位和最初的值相反 */
    asm volatile ("pushf\n\t"
              "popl %%eax"
              : "=a"(eflags2)
              :
              : "memory"
              );
    printf("modified eflags is\t\t: 0x%08x\n", eflags2);

    /* 如果eflags的值没有发生改变，则说明CPU不支持cpuid指令，程序退出 */
    if (eflags1 == eflags2) {
        printf("Sorry, Your CPU dosen't support CPUID instruction.\n");
        exit(1);
    }

    /* 把原来的eflags值设置回去 */
    asm volatile ("pushl %0\n\t"
              "popf"
              :
              : "g"(eflags1)
              );
    /**
     * FIXME: Intel文档并没有说，如果不支持CPUID的话，clear/set eflags的第21位会有什么错误。
     * 它只说，在不支持CPUID指令的CPU上，如80386，执行CPUID会产生invalid opcode错误
     *
     * ──我猜测，如果CPUID不被支持，只是程序无法clear/set EFLAGS[21]而已.
     * 所以，在这里我们不处理 读/写 eflags 第21比特失败的情形
     */


    /**
     * eax == 0
     * eax    : cpuid指令允许的最大eax输入值
     * ebx    : "Genu"
     * ecx    : "ntel"
     * edx    : "ineI"
     */
    asm volatile ("cpuid"
              : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
              : "0"(0)
              );
    printf("Maximum CPUID Input EAX\t\t: 0x%08x\n", eax);

    char string[128];
    snprintf(string, 5, "%s", (char *)&ebx);
    snprintf(string + 4, 5, "%s", (char *)&edx);
    snprintf(string + 8, 5, "%s", (char *)&ecx);
    printf("Vendor\t\t\t\t: %s\n", string);

    if (strcmp(string, "GenuineIntel") == 0)
        x86_vendor = X86_VENDOR_INTEL;
    else if (strstr(string, "AuthenticAMD") == 0 )
        x86_vendor = X86_VENDOR_AMD;
    else if (strstr(string, "CyrixInstead") == 0 )
        x86_vendor = X86_VENDOR_CYRIX;
    else if ( (strcmp(string, "GenuineTMx86") == 0) || (strcmp(string, "TransmetaCPU") == 0) )
        x86_vendor = X86_VENDOR_TRANSMETA;
    else
        x86_vendor = X86_VENDOR_UNKNOWN;


    printf("\n");





    /**
     *  eax == 1，则在eax中返回Family/Model/Stepping等信息
     *            在EBX返回另一些信息
     *            ECX和EDX返回一些features信息
     *
     *  EAX[0:3]    stepping
     *  EAX[4:7]    model
     *  EAX[8:11]    family
     *  EAX[12:13]    processor type
     *  EAX[16:19]    extended model ID
     *  EAX[20:27]    extended family ID
     *
     *  EBX[0:7]     Brand index
     *  EBX[8:15]     CLFLUSH. 执行clflush时作用的I-Cache line size，Pentium4引入
     *  EBX[24:31]     Local APIC ID，也是Pentium4引入
     *          //FIXME: Core2的x2APIC的APIC ID已经扩展到32bit，怎么处理？
     *         //FIX: 回答：见下面ECX[21]bit的描述
     *
     *  ECX[0]     SSE3
     *  ECX[3]     MONITOR/MWAIT
     *  ECX[4]     CPL Qualified Debug Store
     *  ECX[5]     VMX
     *  ECX[7]     EST, Enhanced SpeedStep Technology
     *  ECX[8]     TM2, Thermal Monitor2
     *  ECX[9]     SSSE3, Supplemental SSE3
     *  ECX[10]     CNXT-ID, L1 Context ID. 如果为1,则说明L1 D-Cache可以设置为 自适应(adaptive)模式
     *          或shared模式. 为0则说明不支持。
     *  ECX[13]     CMPXCHG16B. 如果为1则说明支持该指令。
     *  ECX[14]     xTPR Update Control. 为1则说明支持改变MSR寄存器IA32_MISC_ENABLES[23]的值
     *  ECX[16]     PDCM, Perfmon and Debug Capability，1说明支持MSR寄存器IA32_PERF_CAPABILITIES
     *  ECX[21]     x2APIC. 并且，如果该bit为1,则需要使eax==0xb && ecx==0，执行cpuid，如果ebx!=0，则CPU
     *          支持extended topology enumeration leaf
     *
     *  EDX[0]     FPU
     *  EDX[1]     VME, 用CR4的VME控制
     *  EDX[2]     DE, Debugging Extensions, 用CR4的DE控制
     *  EDX[3]     PSE, Page Size Extensions, 用CR4的PSE控制
     *  EDX[4]     TSC, 是否支持rdtsc和wrtsc指令。用CR4.TSD控制RING3是否可以访问TSC
     *  EDX[5]     MSR，是否支持rdmsr和wrmsrl指令
     *  EDX[6]     PAE, Physical Address Extionsion.
     *  EDX[7]     MCE, Machine Check Exception. 由CR4.MCE控制MCE特性
     *  EDX[8]     CX8, CMPXCHG8B指令
     *  EDX[9]     APIC On-Chip. CPU是否有APIC，内存映射默认在物理地址范围0xfffe0000~0xfffe0fff，
     *          有些CPU允许APIC被relocate
     *  EDX[11]     SEP. sysenter和sysexit指令，以及相关的MSR寄存器是否可用
     *  EDX[12]     MTRR. MTRRcap MSR寄存器包含一些bits，描述了支持的variable和fixed MTRR
     *  EDX[13]     PGE. PTE Global Bit. PDEs(page directory entries)和PTEs中的global bit是否支持.
     *          如果为1,则那些对不同进程都一样的TLB entries在进程切换时不用冲刷。
     *          用CR4.PGE来控制该特性。
     *  EDX[14]     MCA, Machine Check Architecture. P6开始支持，MSR寄存器MCG_CAP包含其他多少个
     *          相关的MSR寄存器被支持
     *  EDX[15]     CMOV, Conditional Move Instructions. 看CMOV指令是否支持。 另外，如果CPUID.FPU
     *          支持，则FCOMI和FCOMV指令支持。
     *  EDX[16]     PAT. Page Attribute Table. 类似于MTRR，但PAT指定的是线性地址范围
     *  EDX[17]     PSE-36, 36位的Page Size Extension. 物理地址36bit，其中高4bit用来指定一个4M页
     *          的PDE的13~16位。
     *  EDX[18]     PSN. Serial Number是否支持。
     *  EDX[19]     CLFLUSH指令是否支持
     *  EDX[21]     DS, Debug Store. 如果支持DS，就是CPU把调试信息写到一块驻留内存的buffer(
     *          memory-resident buffer). 该特性可以被BTS(Branch Trace Store)和PEBS(Precis
     *          event-based sampling)使用。见手册'Debugging and Performance Monitoring'部分
     *  EDX[22]     ACPI, Thermal Monitor and Software Controlled Clock Facilities. 如果为真，则
     *          CPU支持热量控制和由软件控制CPU主频等ACPI特性。
     *  EDX[23]     MMX
     *  EDX[24]     FXSR, FXSAVE和FXRSTOR指令。 用来快速的保存/恢复 浮点上下文。 注意：即使该指令
     *          可用，也要看CR4.OSFXSR的设置，根据后者的不同设置，FXSAVE/FXRSTOR所作用的寄存器
     *          不同。
     *  EDX[25]     SSE
     *  EDX[26]     SSE2
     *  EDX[27]     SS, Self Snoop. CPU支持对cache snooping进行管理。
     *  EDX[28]     HTT, Muti-Threading
     *  EDX[29]     TM, Thermal Monitor. CPU实现了热量监控电路(TCC: thermal control circuitry)
     *  EDX[31]     PBE, Pending Break Enable. 如果支持，那么CPU处于Stop状态时(STPCLK# is asserted),
     *          可以通过FERR#/PBE#针脚告诉CPU有中断正pending，唤醒它到正常状态去处理中断 * * *
     */
    asm volatile ("cpuid"
              : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
              : "0"(1)
              );
    printf("\n");


    /* 处理eax */
    printf("Extended Family\t\t\t: %d\n", (0xff00000 & eax) >> 20);
    printf("Extended Model\t\t\t: %d\n", (0xf0000 & eax) >> 16);
    printf("Processor type\t\t\t: ");
    switch( (0x3000 & eax) >> 12 )
    {
        case 0:
            printf("Original OEM Processor\n");
            break;
        case 1:
            printf("Intel OverDrive Processor\n");
            break;
        case 2:
            printf("Dual Processor\n");
            break;
        case 3:
            printf("Intel Reserved\n");
            break;
        default:
            printf("UNKNOWN\n");
    }
    printf("Family\t\t\t\t: %d\n", (0xf00 & eax) >> 8);
    printf("Model\t\t\t\t: %d\n", (0xf0 & eax) >> 4);
    printf("Stepping:\t\t\t: %d\n", (0xf & eax));

    printf("\n");

    /* 处理ebx */
    printf("Brand Index\t\t\t: %d\n", (0xff & ebx));
    printf("I-Cache line size with CLFLUSH\t: %d\n", (0xff00 & ebx) >> 8 );

    /* 我在Core 2 Duo上执行，输出有时是0,有时是1, 说明前后被调度到了不同的core上 */
    printf("Local APIC ID\t\t\t: %d\n", (0xff000000 & ebx) >> 24 );

    printf("\n");


    /* 处理ecx */
    printf("Features: ");
    if ( ecx & 1 )
        printf("\t\t\tSSE2\n");
    if ( ecx & (1 << 3) )
        printf("\t\t\t\tMONITOR/MWAIT\n");
    if ( ecx & (1 << 4) )
        printf("\t\t\t\tCPL\n");
    if ( ecx & (1 << 5) )
        printf("\t\t\t\tVMX\n");
    if ( ecx & (1 << 7) )
        printf("\t\t\t\tEST\n");
    if ( ecx & (1 << 8) )
        printf("\t\t\t\tTM2\n");
    if ( ecx & (1 << 9) )
        printf("\t\t\t\tSSSE3\n");
    if ( ecx & (1 << 10) )
        printf("\t\t\t\tCNXT\n");
    if ( ecx & (1 << 13) )
        printf("\t\t\t\tCMPXCHG16B\n");
    if ( ecx & (1 << 14) )
        printf("\t\t\t\txPTR\n");
    if ( ecx & (1 << 16) )
        printf("\t\t\t\tPDCM\t");


    /* 处理edx */
    if ( edx & 1 )
        printf("\t\t\t\tFPU\n");
    if ( edx & (1 << 1) )
        printf("\t\t\t\tVME\n");
    if ( edx & (1 << 2) )
        printf("\t\t\t\tDE\n");
    if ( edx & (1 << 3) )
        printf("\t\t\t\tPSE\n");
    if ( edx & (1 << 4) )
        printf("\t\t\t\tTSC\n");
    if ( edx & (1 << 5) )
        printf("\t\t\t\tMSR\n");
    if ( edx & (1 << 6) )
        printf("\t\t\t\tPAE\n");
    if ( edx & (1 << 7) )
        printf("\t\t\t\tMCE\n");
    if ( edx & (1 << 8) )
        printf("\t\t\t\tCMPXCHG8B\n");
    if ( edx & (1 << 9) )
        printf("\t\t\t\tAPIC\n");
    if ( edx & (1 << 11) )
        printf("\t\t\t\tSEP: sysenter/sysexit\n");
    if ( edx & (1 << 12) )
        printf("\t\t\t\tMTRR\n");
    if ( edx & (1 << 13) )
        printf("\t\t\t\tPGE: PTE Global Bit\n");
    if ( edx & (1 << 14) )
        printf("\t\t\t\tMCA: Machine Check Architecture\n");
    if ( edx & (1 << 15) )
        printf("\t\t\t\tCMOV: Conditional Move Instruction\n");
    if ( edx & (1 << 16) )
        printf("\t\t\t\tPAT: Page Attribute Table\n");
    if ( edx & (1 << 17) )
        printf("\t\t\t\tPSE-36\n");
    if ( edx & (1 << 18) ) {
        printf("\t\t\tPSN: Processor Serial Number\n");
        serial_num = 1;
    }
    if ( edx & (1 << 19) )
        printf("\t\t\t\tCLFLUSH\n");
    if ( edx & (1 << 21) )
        printf("\t\t\t\tDS: Debug Store\n");
    if ( edx & (1 << 22) )
        printf("\t\t\t\tACPI\n");
    if ( edx & (1 << 23) )
        printf("\t\t\t\tMMX\n");
    if ( edx & (1 << 24) )
        printf("\t\t\t\tFXSR: FXSAVE and FXRSTOR\n");
    if ( edx & (1 << 25) )
        printf("\t\t\t\tSSE\n");
    if ( edx & (1 << 26) )
        printf("\t\t\t\tSSE2\n");
    if ( edx & (1 << 27) )
        printf("\t\t\t\tSS: Self Snoop\n");
    if ( edx & (1 << 28) )
        printf("\t\t\t\tHTT: Multi-Threading\n");
    if ( edx & (1 << 29) )
        printf("\t\t\t\tTM: Thermal Monitor\n");
    if ( edx & (1 << 31) )
        printf("\t\t\t\tPBE: Pending Break Enable\n");


    printf("\n");


    /**
     * edx的第18比特为1，则CPU支持serial number
     *         为0，则不支持，或者被disabled
     * 序列号有96位，其中最高32位即是eax的输出值。应当把它保存下来，然后
     * 再设置eax==3, 取剩下的64位
     */
    if ( serial_num ) {
        /* serial number supported */
        /* edx输出中间32位的序列号，ecx输出最低32位的序列号 */
        asm volatile ("cpuid"
                  : "=c"(ecx), "=d"(edx)
                  : "a"(3)
                  );
        printf("Serial Number\t : %x-%x-%x-%x-%x-%x\n", eax >> 16, (eax << 16) >> 16,
                edx >> 16, (edx << 16) >> 16, ecx >> 16, (ecx << 16) >> 16);
    } else
        printf("Serial Number not supported.\n");


    printf("\n");




    /**
     * eax == 2,  Cache/TLB相关信息在EAX/EBX/ECX/EDX中返回。
     *
     * eax[0:7]     : 一个数值，表示eax==2的CPUID指令需要执行几次才能完整获取Cache/TLB的信息
     *         : 例如如果al是2,则你还要执行一次CPUID指令(with eax==2)
     *
     * [eax|ebx|ecx|edx][31] : 每个寄存器的第31bit，代表了该寄存器是否包含合法的信息
     *              : 如果为0则合法，1非法
     *
     * 如果某寄存器第31bit为0，则每个字节(对EAX来说，第一次执行eax==2的cpuid指令时，[0:7]这个
     * 字节不算)都包含一个值，根据这个值到表(Intel Manuals, Volume 2A, Table 3-17)中查找它代表
     * 的意义。
     *
     * 该表内容见Intel手册2A，表3-17. 也可以在print_cache_descriptor()函数中找到。
     *
     */
    unsigned int count = 0;
    static unsigned char desc[4][4];
    int i, j;

    /** AMD的CPUID指令，其eax输入值0x0000 000[4:2] 为保留 */
    if( x86_vendor != X86_VENDOR_AMD ) {/*{{{*/
        do {
            asm volatile ("cpuid"
                    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                    : "0"(2)
                     );

            if (count == 0 ) /* the first pass */
                count =  (unsigned int)(eax & 0xff);

            if ( !(eax >> 31) ) {
                if ( count == (unsigned int)(eax & 0xff) )
                    desc[0][0] = 0;
                else
                    desc[0][0] = (unsigned char)eax & 0xff;
                desc[0][1] = (eax & 0xff00) >> 8;
                desc[0][2] = (eax & 0xff0000) >> 16;
                desc[0][3] = (eax & 0xff000000) >> 24;
            };

            if ( !(ebx >> 31) ) {
                desc[1][0] = (ebx & 0xff);
                desc[1][1] = (ebx & 0xff00) >> 8;
                desc[1][2] = (ebx & 0xff0000) >> 16;
                desc[1][3] = (ebx & 0xff000000) >> 24;
            };

            if ( !(ecx >> 31) ) {
                desc[2][0] = (ecx & 0xff);
                desc[2][1] = (ecx & 0xff00) >> 8;
                desc[2][2] = (ecx & 0xff0000) >> 16;
                desc[2][3] = (ecx & 0xff000000) >> 24;
            };

            if ( !(edx >> 31) ) {
                desc[3][0] = (edx & 0xff);
                desc[3][1] = (edx & 0xff00) >> 8;
                desc[3][2] = (edx & 0xff0000) >> 16;
                desc[3][3] = (edx & 0xff000000) >> 24;
            };

            printf("Cache and TLB information:\n");

            for (i = 0; i < 4; i++)
                for(j = 0; j < 4; j++) {
                    print_cache_descriptor( (unsigned char)desc[i][j] );
                }

        } while (--count);
    }/*}}}*/


    printf("\n");




    /**
     * Input : eax == 4 && ecx ==
     * eax ==4时的cpuid指令输出取决于ecx的输入值。
     * 返回：Deterministic Cache Parameters Leaf
     *
     * ecx中的值是index，可以从0开始，一直到cpuid返回的eax[0:4]值为0.
     *
     * EAX[0:4]     : Cache Type,Type:    0 -- 没有更多level的Cache了
     *                     1 -- 数据Cache
     *                     2 -- 指令Cache
     *                     3 -- 统一Cache(不分指令/数据)
     * EAX[5:7]     : Cache Level
     * EAX[8]     : Self Initializing cache level(不需要软件初试化)
     * EAX[9]     : Fully Associative cache
     * EAX[10]     : Write-Back Invalidate和Invalidate的方式
     *           0 : 多个线程共享Cache时，当其中一个执行WBINVD/INVD指令，
     *               CPU能保证作用到lower Level的Caches
     *           1 : 共享Cache的多个线程，若一个线程不是WBINVD/INVD指令
     *               的发起者，CPU不保证指令能作用到lower Level的Caches
     * EAX[11]     : Cache Inclusiveness
     *           0 : Cache is not inclusive of lower cache levels
     *           1 : Cache is inclusive of lower cache levels
     * EAX[14:25]     : 一个物理CPU package中，多少线程共享该Cache(需加1)
     * EAX[26:31]     : 一个物理CPU package中，共有多少Cores. (需加1)
     *
     * EBX[00:11]     : L = System Coherency Line Size(需加1)
     * EBX[12:21]     : P = physical Line Partitions(需加1)
     * EBX[22:31]     : W = ways of associativity(需加1)
     *
     * ECX[00:31]     : Number of Set，有多少组。(需加1)
     *
     *
     * (eax[31:26] + 1) 是该物理处理器package上实现的core CPUs数目
     */


    /* AMD CPU的[2:4]输入值是保留了的 */
    if ( x86_vendor != X86_VENDOR_AMD ) {/*{{{*/

        printf("Deterministic Cache Parameters Leaf:\n");
        int index = 0;
        while(1)
        {
            asm volatile ("cpuid"
                    : "=a"(eax), "=b"(ebx), "=c"(ecx)
                    : "0"(4), "2"(index)
                     );

            // no more caches

            if ( !(eax & 0x1f) )
                break;

            printf("Index %d :\n", index);
            printf("\tCache Type: ");
            switch( (eax & 0x1f) ) {
                case 0:
                    printf("Null-No more Caches\n");
                    break;
                case 1:
                    printf("Data Cache\n");
                    break;
                case 2:
                    printf("Instruction Cache\n");
                    break;
                case 3:
                    printf("Unified Cache\n");
                    break;
                default:
                    ;/* wrong value. we'll keep silent with this */
            }

            printf("\tCache Level\t: %d\n", (eax & 0xe0) >> 5);
            printf("\tSelf Initializing cache level: %d\n", (eax & 0x100) >> 8);
            printf("\tFully Associative cache: %d\n", (eax & 0x200) >> 9);
            printf("\tWBINVD/INVD act upon lower shared cache? %s\n", (eax & (1<<10))?"No":"Yes" );
            printf("\tCache Inclusiveness: %s\n", (eax & (1<<11))?"inclusive of lower cache levels":
                    "not inclusive of lower cache levels" );
            printf("\tMaximum number of threads sharing this cache in a physical package: %d\n",
                    ((eax&0x3ffc000) >> 14) + 1 );
            printf("\tMaximum number of cores in the physical package: %d\n",
                    (eax >> 26) + 1 );

            //处理ebx

            printf("\tSystem Coherency Line Size: %d\n", (ebx & 0xfff) + 1 );
            printf("\tPhysical Line partitions: %d\n", ((ebx & 0x3ff000) >> 12) +1 );
            printf("\t%d-Ways of associativity\n", (ebx >> 22) + 1 );

            //处理ecx

            printf("\tNumber of Sets: %d\n", ecx + 1);




            printf("\n");
            index++;
        };


    }/*}}}*/



    /*
     * 探测x2APIC分2步：
     *     step 1: eax == 1
     *          ECX[21]     x2APIC.
     *     step 2: eax == 0xb && ecx == 0
     *         ebx != 0     如果ebx!=0，则CPU支持extended topology emumeration leaf。否则不支持
     *
     *     注意step1执行之后发现ecx[21]==1才进行step2。
     */
    unsigned int has_x2apic = 0;
    asm volatile ("cpuid"
              : "=c" (ecx)
              : "a"(0)
             );
    if (ecx & 0x00200000) {
        printf("\t\t\t x2APIC\n");
        has_x2apic = 1;
    }

    if (has_x2apic) {
        asm volatile("cpuid"
                 : "=b" (ebx)
                 : "a"(0xb), "c"(0)
                );

        if (ebx != 0)
            printf("\t\t\t Extended topology enumeration leaf\n");
    }











    /* XXX: eax >= 0x80000000 的输入值，是CPUID指令的扩展功能. 下面的代码是这部分功能的探测 */







    /**
     * eax == 0x800000000
     * 如果CPU支持Brand String，则在EAX中返 >= 0x80000004的值。
     */
    asm volatile ("cpuid"
              : "=a"(eax)
              : "0"(0x80000000)
              );
    printf("CPU support Brand String?\t: %s\n", eax >= 0x80000004? "yes":"no");


    /**
     * 如果支持Brand String，则EAX从0x80000002到0x80000004，每次增1，CPUID指令返回：
     * EAX    : Processor Brand String
     * EBX    : Processor Brand String Continued
     * ECX    : Processor Brand String Continued
     * EDX    : Processor Brand String Continued
     */

    if(eax >= 0x80000004) {
        printf("Brand String\t\t\t: ");

        /*
        unsigned int brands[4]; //每次的eax、ebx、ecx、edx
        unsigned int i;

        for (i = 0x80000002; i <= 0x80000004; i++) {
            asm volatile ("cpuid"
                      : "=a"(brands[0]), "=b"(brands[1]), "=c"(brands[2]), "=d"(brands[3])
                      : "0" (i)
                      );
            printf("%s", (char *)brands);
        } */


//        unsigned int bs[] = { [0 ... 12] = 0 };
//        asm volatile("cpuid"
//                 : "=a"(bs[0]), "=b"(bs[1]), "=c"(bs[2]), "=d"(bs[3])
//                 : "0"(0x80000002)
//                );
//        asm volatile("cpuid"
//                 : "=a"(bs[4]), "=b"(bs[5]), "=c"(bs[6]), "=d"(bs[7])
//                 : "0"(0x80000003)
//                );
//        asm volatile("cpuid"
//                 : "=a"(bs[8]), "=b"(bs[9]), "=c"(bs[10]), "=d"(bs[11])
//                 : "0"(0x80000004)
//                );
//
//        printf("%s\n", (char *)bs);


    }


    printf("\n");


    /**
     * eax == 0x80000001
     * 如果CPU支持NX，如果edx的第20比特为1,则说明支持NX(Non-eXecute)；否则不支持。
     *
     * eax : extended processor signature and extended feature bits
     * ecx[0]  : LAHF/SAHF 在64位模式下有效
     * edx[11] : SYSCALL/SYSRET在64-bit下有效
     * edx[20] : NX
     * edx[29] : Intel 64技术(AKA EM64T)
     */
    asm volatile ("cpuid"
                  : "=d"(edx)
                  : "a"(0x80000001)
                  );

    if ( ecx & 0x1 )
        printf("\t\t\t\tLAHF/SAHF available when in 64-bit mode.\n");

    if ( edx & 0x800 )
        printf("\t\t\t\tSYSCALL/SYSRET available when in 64-bit mode.\n");
    if ( edx & 0x100000 )
        printf("\t\t\t\tNX: Execute Disable\n");
    if ( edx & 0x20000000 )
        printf("\t\t\t\tIntel 64(AKA EM64T)\n");


    printf("\n");



    printf("\n");


    /**
     * eax == 80000006h，返回L2 Cache的信息
     *
     * ecx[31:16]    : L2 Cache size, in Kbytes
     * ecx[15:12]    : L2 Cache Associativity
     *           00h disabled
     *           01h direct mapped
     *           02h 2-Way
     *           04h 4-Way
     *           06h 8-Way
     *           08h 16-Way
     *           0Fh Fully associative
     * ecx[7:0]    : L2 Cache Line size in bytes
     */
    asm volatile ("cpuid"
              : "=c"(ecx)
              : "a"(0x80000006)
              );
    printf("L2 Cache Size\t\t\t: %d Kbytes\n", ( ecx >> 16 ) );
    printf("L2 Cache Line Size\t\t: %d bytes\n", (ecx & 0xff));

    printf("L2 Cache Associativity\t\t: ");
    switch ( (ecx & 0xf000) >> 12 )
    {
        case 0x00:
            printf("%s\n", "disabled");
            break;
        case 0x01:
            printf("%s\n", "direct mapped");
            break;
        case 0x02:
            printf("%s\n", "2-Way");
            break;
        case 0x04:
            printf("%s\n", "4-Way");
            break;
        case 0x06:
            printf("%s\n", "8-Way");
            break;
        case 0x08:
            printf("%s\n", "16-Way");
            break;
        case 0x0f:
            printf("Fully associative");
            break;
        default:
            printf("No such entry...\n");
    }

    printf("\n");




    /**
     * eax == 0x80000008
     *
     * EAX[0:7]     : 物理地址bits
     * EAX[8:15]     : 虚拟地址bits
     */
    asm volatile ("cpuid"
              : "=a"(eax)
              : "0"(0x80000008)
             );
    printf("Physical Address Bits\t\t: %d\n", (0xff & eax));
    printf("Virtual Address Bits\t\t: %d\n", (0xff00 & eax) >> 8);

    printf("\n");

    asm volatile ("cpuid"
              : "=a"(eax)
              : "a"(1)
              );

    printf("Serial Hight:%d\n",eax);

    asm volatile ("cpuid"
              : "=c"(ecx)
              : "a"(3)
              );

    printf("Serial low:%d",ecx);
    printf("\n");

    return 0;
}



void print_cache_descriptor(unsigned char desc)
{/*{{{*/
    switch (desc)
    {
        case 0x00:
            break;
        case 0x01:
            printf("\t\t\t\t: Instruction TLB: 4 KByte pages, 4-way set associative, 32 entries\n");
            break;
        case 0x02:
            printf("\t\t\t\t: Instruction TLB: 4 MByte pages, 4-way set associative, 2 entries\n");
            break;
        case 0x03:
            printf("\t\t\t\t: Data TLB: 4 KByte pages, 4-way set associative, 64 entries\n");
            break;
        case 0x04:
            printf("\t\t\t\t: Data TLB: 4 MByte pages, 4-way set associative, 8 entries\n");
            break;
        case 0x05:
            printf("\t\t\t\t: Data TLB1: 4 MByte pages, 4-way set associative, 32 entries\n");
            break;
        case 0x06:
            printf("\t\t\t\t: 1st-level instruction cache: 8 KBytes, 4-way set associative, 32 byte line size\n");
            break;
        case 0x08:
            printf("\t\t\t\t: 1st-level instruction cache: 16 KBytes, 4-way set associative, 32 byte line size\n");
            break;
        case 0x0a:
            printf("\t\t\t\t: 1st-level data cache: 8 KBytes, 2-way set associative, 32 byte line size\n");
            break;
        case 0x0b:
            printf("\t\t\t\t: Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries\n");
            break;
        case 0x0c:
            printf("\t\t\t\t: 1st-level data cache: 16 KBytes, 4-way set associative, 32 byte line size\n");
            break;
        case 0x22:
            printf("\t\t\t\t: 3rd-level cache: 512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x23:
            printf("\t\t\t\t: 3rd-level cache: 1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x25:
            printf("\t\t\t\t: 3rd-level cache: 2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x29:
            printf("\t\t\t\t: 3rd-level cache: 4 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x2c:
            printf("\t\t\t\t: 1st-level data cache: 32 KBytes, 8-way set associative, 64 byte line size\n");
            break;
        case 0x30:
            printf("\t\t\t\t: 1st-level instruction cache: 32 KBytes, 8-way set associative, 64 byte line size\n");
            break;
        case 0x40:
            printf("\t\t\t\t: No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache\n");
            break;
        case 0x41:
            printf("\t\t\t\t: 2nd-level cache: 128 KBytes, 4-way set associative, 32 byte line size\n");
            break;
        case 0x42:
            printf("\t\t\t\t: 2nd-level cache: 256 KBytes, 4-way set associative, 32 byte line size\n");
            break;
        case 0x43:
            printf("\t\t\t\t: 2nd-level cache: 512 KBytes, 4-way set associative, 32 byte line size\n");
            break;
        case 0x44:
            printf("\t\t\t\t: 2nd-level cache: 1 MByte, 4-way set associative, 32 byte line size\n");
            break;
        case 0x45:
            printf("\t\t\t\t: 2nd-level cache: 2 MByte, 4-way set associative, 32 byte line size\n");
            break;
        case 0x46:
            printf("\t\t\t\t: 3rd-level cache: 4 MByte, 4-way set associative, 64 byte line size\n");
            break;
        case 0x47:
            printf("\t\t\t\t: 3rd-level cache: 8 MByte, 8-way set associative, 64 byte line size\n");
            break;
        case 0x49:
            printf("\t\t\t\t: 2nd-level cache: 4 MByte, 16-way set associative, 64 byte line size\n");
            break;
        case 0x50:
            printf("\t\t\t\t: Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 64 entries\n");
            break;
        case 0x51:
            printf("\t\t\t\t: Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 128 entries\n");
            break;
        case 0x52:
            printf("\t\t\t\t: Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 256 entries\n");
            break;
        case 0x56:
            printf("\t\t\t\t: Data TLB0: 4 MByte pages, 4-way set associative, 16 entries\n");
            break;
        case 0x57:
            printf("\t\t\t\t: Data TLB0: 4 KByte pages, 4-way associative, 16 entries\n");
            break;
        case 0x5B:
            printf("\t\t\t\t: Data TLB: 4 KByte and 4 MByte pages, 64 entries\n");
            break;
        case 0x5c:
            printf("\t\t\t\t: Data TLB: 4 KByte and 4 MByte pages,128 entries\n");
            break;
        case 0x5d:
            printf("\t\t\t\t: Data TLB: 4 KByte and 4 MByte pages,256 entries\n");
            break;
        case 0x60:
            printf("\t\t\t\t: 1st-level data cache: 16 KByte, 8-way set associative, 64 byte line size\n");
            break;
        case 0x66:
            printf("\t\t\t\t: 1st-level data cache: 8 KByte, 4-way set associative, 64 byte line size\n");
            break;
        case 0x67:
            printf("\t\t\t\t: 1st-level data cache: 16 KByte, 4-way set associative, 64 byte line size\n");
            break;
        case 0x68:
            printf("\t\t\t\t: 1st-level data cache: 32 KByte, 4-way set associative, 64 byte line size\n");
            break;
        case 0x70:
            printf("\t\t\t\t: Trace cache: 12 K-μop, 8-way set associative\n");
            break;
        case 0x71:
            printf("\t\t\t\t: Trace cache: 16 K-μop, 8-way set associative\n");
            break;
        case 0x72:
            printf("\t\t\t\t: Trace cache: 32 K-μop, 8-way set associative\n");
            break;
        case 0x78:
            printf("\t\t\t\t: 2nd-level cache: 1 MByte, 4-way set associative, 64byte line size\n");
            break;
        case 0x79:
            printf("\t\t\t\t: 2nd-level cache: 128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x7a:
            printf("\t\t\t\t: 2nd-level cache: 256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x7b:
            printf("\t\t\t\t: 2nd-level cache: 512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x7c:
            printf("\t\t\t\t: 2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector\n");
            break;
        case 0x7d:
            printf("\t\t\t\t: 2nd-level cache: 2 MByte, 8-way set associative, 64byte line size\n");
            break;
        case 0x7f:
            printf("\t\t\t\t: 2nd-level cache: 512 KByte, 2-way set associative, 64-byte line size\n");
            break;
        case 0x82:
            printf("\t\t\t\t: 2nd-level cache: 256 KByte, 8-way set associative, 32 byte line size\n");
            break;
        case 0x83:
            printf("\t\t\t\t: 2nd-level cache: 512 KByte, 8-way set associative, 32 byte line size\n");
            break;
        case 0x84:
            printf("\t\t\t\t: 2nd-level cache: 1 MByte, 8-way set associative, 32 byte line size\n");
            break;
        case 0x85:
            printf("\t\t\t\t: 2nd-level cache: 2 MByte, 8-way set associative, 32 byte line size\n");
            break;
        case 0x86:
            printf("\t\t\t\t: 2nd-level cache: 512 KByte, 4-way set associative, 64 byte line size\n");
            break;
        case 0x87:
            printf("\t\t\t\t: 2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size\n");
            break;
        case 0xb0:
            printf("\t\t\t\t: Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries\n");
            break;
        case 0xb3:
            printf("\t\t\t\t: Data TLB: 4 KByte pages, 4-way set associative, 128 entries\n");
            break;
        case 0xb4:
            printf("\t\t\t\t: Data TLB1: 4 KByte pages, 4-way associative, 256 entries\n");
            break;
        case 0xf0:
            printf("\t\t\t\t: 64-Byte prefetching\n");
            break;
        case 0xf1:
            printf("\t\t\t\t: 128-Byte prefetching\n");
            break;

        default:
            ;/* invalid descriptor. We'll print nothing */
    }

}
