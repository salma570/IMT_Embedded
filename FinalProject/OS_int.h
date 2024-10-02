#ifndef OS_INT_H_
#define OS_INT_H_

typedef struct
{
	void(*Task_ptr)(void);
	u16 Task_Periodicity;
}TASK;

u8 OS_CreateTask(void(*ptr)(void), u16 Copy_u16Periodicity, u8 Copy_u8Priority, u8 Copy_u8FirstDelay);
void OS_Scheduler(void);
void OS_Start(void);

#endif
