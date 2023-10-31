#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <time.h>
using namespace std;
int RunPoint;     // 运行进程指针，-1时为没有运行进程
int WaitPoint;    // 阻塞队列指针，-1时为没有阻塞进程
int ReadyPoint;   // 就绪队列指针，-1时为没有就绪进程
long ClockNumber; // 系统时钟
int ProcNumber;   // 系统中模拟产生的进程总数
int FinishedProc; // 系统中目前已执行完毕的进程总数
struct ProcStruct
{
    int p_pid;         // 进程的标识号
    char p_state;      // 进程的状态，C--运行  R--就绪  W--组塞  B--后备  F--完成
    int p_rserial[10]; // 模拟的进程执行的CPU和I/O时间数据序列，间隔存储，第0项存储随后序列的长度（项数），以便知晓啥时该进程执行结束
    int p_pos;         // 当前进程运行到的位置，用来记忆执行到序列中的哪项
    int p_starttime;   // 进程建立时间
    int p_endtime;     // 进程运行结束时间
    int p_cputime;     // 当前运行时间段进程剩余的需要运行时间
    int p_iotime;      // 当前I/O时间段进程剩余的I/O时间
    int p_next;        // 进程控制块的链接指针
} proc[10];
void DisData()
{
    ofstream outFile;                    // 同时将该信息写入磁盘的某txt文件中 ，该函数要#include <fstream.h>
    outFile.open("operatingsystem.txt"); // 该txt 文件名可自己命名，第1次open时磁盘 中没有该文件，系统会创建一个空白的。
    for (int i = 0; i < ProcNumber; i++)
    {
        int leng = proc[i].p_rserial[0];
        printf("ID=%d(len=%d,start=%d):\t", proc[i].p_pid, leng, proc[i].p_starttime);
        outFile << "ID=" << proc[i].p_pid << "(len=" << leng << ",start=" << proc[i].p_starttime << "):";
        for (int j = 1; j <= leng; j++)
        {
            if (j != leng)
            {
                outFile << "  " << proc[i].p_rserial[j];
                printf("  %d", proc[i].p_rserial[j]);
            }
            else
            {
                outFile << "  " << proc[i].p_rserial[j] << endl;
                printf("  %d\n", proc[i].p_rserial[j]);
            }
        }
        // 写到txt文件中
        // 打印到屏幕上
    }
    outFile.close(); // 写入txt文件的流被冲刷，保存到磁盘上
}
void Read_Process_Info()
{
    ifstream inFile; // 定义打开文件的文件流
    char ch;
    int i, j, k, tmp;
    inFile.open("operatingsystem.txt"); // 打开上次写的txt进行信息文件流

    i = 0;
    while (inFile)
    {
        inFile.get(ch);
        for (j = 0; j < 3; j++)
            inFile.get(ch); // 扔掉3个字符，
        inFile >> proc[i].p_pid;
        for (j = 0; j < 5; j++)
            inFile.get(ch); // 继续读，扔掉5个字符
        inFile >> proc[i].p_rserial[0];
        for (j = 0; j < 7; j++)
            inFile.get(ch); // 继续读，扔掉7个字符
        inFile >> proc[i].p_starttime;
        for (j = 0; j < 2; j++)
            inFile.get(ch); // 继续读，扔掉2个字符
        for (k = 1; k <= proc[i].p_rserial[0]; k++)
        {
            inFile >> tmp;
            proc[i].p_rserial[k] = tmp;
        }
        proc[i].p_state = 'B';
        proc[i].p_pos = 1;
        proc[i].p_endtime = 0;
        proc[i].p_next = -1;
        proc[i].p_cputime = proc[i].p_rserial[1];
        proc[i].p_iotime = proc[i].p_rserial[2];
        i++; // 本行结束，一个进程信息读完，序号+1, 准备 next process
    }
    ProcNumber = i - 1; // 给ProcNumber赋值，i最后有++，回位下
    DisData();
    inFile.close(); // 完工后，记得归位，关灯。
}

void create()
{
    srand(time(0));
    ProcNumber = 3;                      // 随机产生数量5~10
    for (int i = 0; i < ProcNumber; i++) // 生成进程的CPU--I/O时间数据序列
    {
        int time = rand() % (5) + 3;
        proc[i].p_starttime = time;
        proc[i].p_pid = ((float)rand() / 32767) * 1000; // 初始化随机的进程ID号
        proc[i].p_state = 'B';                          // 初始都为后备状态，可用其他表示符
        int number = rand() % 3 + 3;
        proc[i].p_rserial[0] = number;
        for (int j = 1; j <= number; j++)
        {
            proc[i].p_rserial[j] = rand() % 6 + 3;
        }
    }
    printf("\n---------------------------\n    建立了%2d 个进程数据序列\n\n", ProcNumber);
    DisData(); // 该函数为在屏幕上打印所创建的进程的具体信息，Dis是Display的缩写.
    // getch();
}
void NewReadyProc(void)
{
    for (int i = 0; i < ProcNumber; i++)
    {
        if (proc[i].p_starttime == ClockNumber) // 进程进入时间达到系统时间，ClockNumber是当前的系统时间
        {
            proc[i].p_state = 'R'; //	进程状态修改为就绪
            proc[i].p_next = -1;   // 该进行即将要挂在队列末尾，它肯定是尾巴，后面没人的，所以先设置next=-1
            proc[i].p_pos = 1;
            proc[i].p_cputime = proc[i].p_rserial[proc[i].p_pos];
            if (ReadyPoint == -1) // 如果当前就绪队列无进程
                ReadyPoint = i;
            else // 如果就绪队列有进程，放入队列尾
            {
                int n = ReadyPoint;
                while (proc[n].p_next != -1)
                    n = proc[n].p_next; // 找到原来队伍中的尾巴
                proc[n].p_next = i;     // 挂在这个尾巴后面
            }
        }
    }
}
void Display_ProcInfo(){

}
void Cpu_Sched(){

}
void IO_Sched(){

}
void Scheduler_FF()
{
    if (ProcNumber == 0) // 该值居然是0？ 只能说用户没创建进程
    {
        Read_Process_Info(); // 那么，从磁盘读取上次创建的进程信息，赋值给相应变量
    }
    ClockNumber = 0; // 时钟开始计时, 开始调度模拟

    while (FinishedProc < ProcNumber) // 执行算法
    {
        ClockNumber++;      // 时钟前进1个单位
        NewReadyProc();     // 判别新进程是否到达
        Cpu_Sched();        // CPU调度
        IO_Sched();         // IO调度
        Display_ProcInfo(); // 显示当前状态

        Sleep(1000);
    }
    cout << "运行完毕" << endl;
}
char _getch()
{
    char str;
    cin >> str;
    return str;
}
void Create_ProcInfo()
{
    create();
}
int main()
{
    char ch;
    RunPoint = -1;   // 运行进程指针，-1时为没有运行进程
    WaitPoint = -1;  // 阻塞队列指针，-1时为没有阻塞进程
    ReadyPoint = -1; // 就绪队列指针，-1时为没有就绪进程
    ClockNumber = 0; // 系统时钟
    ProcNumber = 0;  // 当前系统中的进程总数
    system("cls");
    while (true)
    {
        printf("***********************************\n");
        printf("     1: 建立进程调度数据序列 \n");
        printf("     2: 读进程信息，执行调度算法\n");
        printf("***********************************\n");
        printf("Enter your choice (1 ~ 2): ");
        do
            ch = (char)_getch(); // 如果输入信息不正确，继续输入
        while (ch != '1' && ch != '2');

        if (ch == '2')
            Scheduler_FF(); // 选择2
        else if (ch == '1')
            Create_ProcInfo(); // 选择1
        _getch();
        system("cls");
    }

}