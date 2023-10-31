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
void NextRunProcess()
{
    if (ReadyPoint == -1)
    {
        return;
    }
    if (RunPoint == -1)
    {
        if (ReadyPoint != -1)
        {
            RunPoint = ReadyPoint;
            proc[RunPoint].p_state = 'C';
            ReadyPoint = proc[ReadyPoint].p_next;
            int n = ReadyPoint;
        }
    }
    else
    {
        proc[RunPoint].p_state = 'R';
        proc[RunPoint].p_next = -1;
        int n = ReadyPoint;
        if (n == -1)
        {
            ReadyPoint = RunPoint;
        }
        else
        {
            while (proc[n].p_next != -1)
            {
                n = proc[n].p_next;
            }
            proc[n].p_next = RunPoint;
            RunPoint = ReadyPoint;
            proc[RunPoint].p_state = 'C';
            ReadyPoint = proc[RunPoint].p_next;
        }
    }
}
void NextWaitProcess()
{
    cout << "--------------------" << endl;
    int n = WaitPoint;
    while (n != -1)
    {
        cout << "   " << n;
        n = proc[n].p_next;
    }
    cout << endl;
    if (proc[WaitPoint].p_next != -1)
    {
        int n = WaitPoint;
        int t = proc[WaitPoint].p_next;
        int z = WaitPoint;
        while (proc[n].p_next != -1)
        {
            n = proc[n].p_next;
        }
        proc[n].p_next = WaitPoint;
        WaitPoint = t;
        proc[z].p_next = -1;
    }
    n = WaitPoint;
    while (n != -1)
    {
        cout << "   " << n;
        n = proc[n].p_next;
    }
    cout << endl;
}
void IO_Sched()
{
    int n;
    if (WaitPoint == -1)
        return;                 // 没有等待I/O的进程，直接返回
    proc[WaitPoint].p_iotime--; // 进行1个时钟的I/O时间
    if (proc[WaitPoint].p_iotime > 0)
    {
        NextWaitProcess();
        return; // 还没有完成本次I/O
    }
    else
    {
        proc[WaitPoint].p_pos++;
        if (proc[WaitPoint].p_rserial[0] + 1 == proc[WaitPoint].p_pos) // 进程全部序列执行完成
        {
            FinishedProc++;
            proc[WaitPoint].p_state = 'F';
            proc[WaitPoint].p_endtime = ClockNumber;
            WaitPoint = proc[WaitPoint].p_next; // 无进程执行
        }
        else
        {
            proc[WaitPoint].p_state = 'R';
            proc[WaitPoint].p_cputime = proc[WaitPoint].p_rserial[proc[WaitPoint].p_pos];

            proc[WaitPoint].p_next = -1;
            int n = ReadyPoint;
            if (ReadyPoint == -1)
            {
                ReadyPoint = WaitPoint;
            }
            else
            {
                while (proc[n].p_next != -1)
                {
                    n = proc[n].p_next;
                }
                proc[n].p_next = WaitPoint;
            }
            WaitPoint = proc[WaitPoint].p_next;
        }
        return;
    }
}
void DisResult()
{
}
void Display_ProcInfo()
{
    system("cls");
    printf("当前系统模拟%d个进程的运行%d个时钟:", ProcNumber, ClockNumber);
    printf("就绪指针=%d, 运行指针=%d, 阻塞指针=%d\n", ReadyPoint, RunPoint, WaitPoint);
    if (RunPoint != -1)
    {
        for (int i = 0; i < ProcNumber; i++)
        {
            if (proc[i].p_state == 'C')
            {
                cout << "NO." << i << " ID:  " << proc[i].p_pid << "(" << proc[i].p_rserial[0] << "," << proc[i].p_starttime << ")";
                for (int j = 1; j <= proc[i].p_rserial[0]; j++)
                {
                    if (j != proc[i].p_rserial[0])
                    {
                        cout << "  " << proc[i].p_rserial[j];
                    }
                    else
                    {
                        cout << "  " << proc[i].p_rserial[j] << endl;
                    }
                }
            }
        }
    }
    else
        printf("No Process Running !\n");
    for (int i = 0; i < 3; i++)
    {
        cout << "------------------" << endl;
        cout << "NO." << i << " ID:  " << proc[i].p_pid << "(" << proc[i].p_rserial[0] << "," << proc[i].p_starttime << ")"
             << "  next" << proc[i].p_next << "  state  " << proc[i].p_state << endl;
    }
    int n = ReadyPoint;
    printf("\n Ready Process ...... \n");
    int t = 0;
    while (n != -1) // 显示就绪进程信息
    {
        printf("re");
        cout << "NO." << n << " ID:  " << proc[n].p_pid << "(" << proc[n].p_rserial[0] << "," << proc[n].p_starttime << ")";
        for (int j = 1; j <= proc[n].p_rserial[0]; j++)
        {
            if (j != proc[n].p_rserial[0])
            {
                cout << "  " << proc[n].p_rserial[j];
            }
            else
            {
                cout << "  " << proc[n].p_rserial[j];
            }
        }
        cout << "  "
             << "next" << proc[n].p_next << endl;
        n = proc[n].p_next;
        if(proc[n].p_next == n || proc[n].p_next ==proc[proc[n].p_next].p_next){
            cout << "重复" << endl;
        }
    }
    n = WaitPoint;
    printf("\n Waiting Process ...... \n");
    t = 0;
    while (n != -1) // 显示阻塞进程信息
    {
        printf("bl");
        cout << "NO." << n << " ID:  " << proc[n].p_pid << "(" << proc[n].p_rserial[0] << "," << proc[n].p_starttime << ")";
        for (int j = 1; j <= proc[n].p_rserial[0]; j++)
        {
            if (j != proc[n].p_rserial[0])
            {
                cout << "  " << proc[n].p_rserial[j];
            }
            else
            {
                cout << "  " << proc[n].p_rserial[j];
            }
        }
        cout << "  "
             << "next" << proc[n].p_next << endl;
        n = proc[n].p_next;
    }
    printf("\n=================== 后备进程 ====================\n");
    for (int i = 0; i < ProcNumber; i++)
    {
        if (proc[i].p_state == 'B')
        {
            cout << "NO." << i << " ID:  " << proc[i].p_pid << "(" << proc[i].p_rserial[0] << "," << proc[i].p_starttime << ")";
            for (int j = 1; j <= proc[i].p_rserial[0]; j++)
            {
                if (j != proc[i].p_rserial[0])
                {
                    cout << "  " << proc[i].p_rserial[j];
                }
                else
                {
                    cout << "  " << proc[i].p_rserial[j] << endl;
                }
            }
        }
    }
    printf("\n================ 已经完成的进程 =================\n");
    for (int i = 0; i < ProcNumber; i++)
    {
        if (proc[i].p_state == 'F')
        {
            cout << "NO." << i << " ID:  " << proc[i].p_pid << "(" << proc[i].p_rserial[0] << "," << proc[i].p_starttime << ")"
                 << "   Endtime:" << proc[i].p_endtime;
            for (int j = 1; j <= proc[i].p_rserial[0]; j++)
            {
                if (j != proc[i].p_rserial[0])
                {
                    cout << "  " << proc[i].p_rserial[j];
                }
                else
                {
                    cout << "  " << proc[i].p_rserial[j] << endl;
                }
            }
        }
    }
    
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
        int number = rand() % 3 + 2;
        proc[i].p_rserial[0] = number;
        for (int j = 1; j <= number; j++)
        {
            proc[i].p_rserial[j] = rand() % 2 + 3;
        }
    }
    printf("\n---------------------------\n    建立了%2d 个进程数据序列\n\n", ProcNumber);
    DisData(); // 该函数为在屏幕上打印所创建的进程的具体信息，Dis是Display的缩写.
    // getch();
}
char _getch()
{
    char str;
    cin >> str;
    return str;
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
void Cpu_Sched(void)
{
    int n;
    if (RunPoint == -1) // 没有进程在CPU上执行
    {
        NextRunProcess();
        return;
    }

    proc[RunPoint].p_cputime--; // 进程CPU执行时间减少1个时钟单位

    if (proc[RunPoint].p_cputime > 0)
    {
        NextRunProcess();
        return; // 还需要CPU时间，下次继续，这次就返回了
    }

    // 如果不满足以上>0的条件，就意味着=0，就不会自动返回，接着做以下事情。
    // 进程完成本次CPU后的处理
    proc[RunPoint].p_pos++;
    if (proc[RunPoint].p_rserial[0] + 1 == proc[RunPoint].p_pos) // 进程全部序列执行完成
    {
        FinishedProc++;
        proc[RunPoint].p_state = 'F';
        proc[RunPoint].p_endtime = ClockNumber;
        RunPoint = ReadyPoint;
        if (ReadyPoint != -1)
        {
            ReadyPoint = proc[ReadyPoint].p_next;
            proc[RunPoint].p_state = 'C';
        }
    }
    else
    {
        proc[RunPoint].p_state = 'W';
        proc[RunPoint].p_iotime = proc[RunPoint].p_rserial[proc[RunPoint].p_pos];
        proc[RunPoint].p_next = -1;
        n = WaitPoint;
        if (n == -1)
        {
            WaitPoint = RunPoint;
        }
        else
        {
            while (proc[n].p_next != -1)
            {
                n = proc[n].p_next;
            }
            proc[n].p_next = RunPoint;
        }
        cout << endl;
        RunPoint = -1;
    }
    
    return;
}
void getch()
{
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
        ClockNumber++;  // 时钟前进1个单位
        NewReadyProc(); // 判别新进程是否到达
        Cpu_Sched();    // CPU调度
        IO_Sched();     // IO调度
        Display_ProcInfo(); // 显示当前状态

        Sleep(700);
    }
    cout << "运行完毕" << endl;
    DisResult();
    getch();
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
    getch();
}