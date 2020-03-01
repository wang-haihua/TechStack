/* $begin pro_ctrl_wra.c */
#include "head.h"

/*******************
 * 进程控制函数封装
 *******************/

/*
* 
* Fork()函数
*
* Usage:
*   父进程调用Fork()函数创建一个新的子进程
*
* Return:
*    0-在父进程中返回子进程的PID
*    1-在子进程中返回0
* 
*/ 
pid_t Fork(void) 
{
    pid_t pid;

    if ((pid = fork()) < 0)
	unix_error("Fork error");
    return pid;
}

/*
* 
* Execve()函数
*
* Usage:
*   Execve()函数在调用的当前进程的上下文中加载并运行一个新程序
*
* Return:
* 
*/
void Execve(const char *filename, char *const argv[], char *const envp[]) 
{
    if (execve(filename, argv, envp) < 0)
	unix_error("Execve error");
}


/*
* 
* Waitpid()函数
*
* Usage:
*   父进程调用Waitpid()函数来等待其子进程的终止来回收子进程
*
* Return:
*    0-返回已终止的子进程的PID
* 
*/
pid_t Waitpid(pid_t pid, int *iptr, int options) 
{
    pid_t retpid;

    if ((retpid  = waitpid(pid, iptr, options)) < 0) 
	unix_error("Waitpid error");
    return(retpid);
}

/*
* 
* Wait()函数
*
* Usage:
*   Waitpid()函数的简单版本相当于调用waitpid(-1,&status,0)
*
* Return:
*    0-返回已终止的子进程的PID
* 
*/
pid_t Wait(int *status) 
{
    pid_t pid;

    if ((pid  = wait(status)) < 0)
	unix_error("Wait error");
    return pid;
}

/*
* 
* Kill()函数
*
* Usage:
*   Kill()函数终止进程
*
* Return:
* 
*/
void Kill(pid_t pid, int signum) 
{
    int rc;

    if ((rc = kill(pid, signum)) < 0)
	unix_error("Kill error");
}


/*
* 
* Pause()函数
*
* Usage:
*   Pause()函数让调用进程休眠知道该进程收到信号
*
* Return:
* 
*/
void Pause() 
{
    (void)pause();
    return;
}

/*
* 
* Sleep()函数
*
* Usage:
*   Sleep()函数将一个进程挂起指定的一段时间
*
* Return:
*    0-挂起时间到返回0
*    1-挂起时间未到返回剩下的挂起时间
* 
*/
unsigned int Sleep(unsigned int secs) 
{
    unsigned int rc;

    if ((rc = sleep(secs)) < 0)
	unix_error("Sleep error");
    return rc;
}

/*
unsigned int Alarm(unsigned int seconds) {
    return alarm(seconds);
}
 
void Setpgid(pid_t pid, pid_t pgid) {
    int rc;

    if ((rc = setpgid(pid, pgid)) < 0)
	unix_error("Setpgid error");
    return;
}

pid_t Getpgrp(void) {
    return getpgrp();
}
*/

/* $end pro_ctrl_wra.c */
