#include "STD_Types.h"
#include "BIT_MATH.h"
#include "GIE_int.h"
#include "Timer_int.h"
#include "OS_cfg.h"
#include "OS_int.h"

TASK Task_arr[MAX_NUM_OF_TASKS] = {{0}};
u16 Timing_arr[MAX_NUM_OF_TASKS] = {0};

static void func(void)
{
	static u32 c = 0;
	if(c == 3907)
	{
		OS_Scheduler();
		TIM0_OVFSetRegValue(192);
		c = 0;
	}
	else
	{
		c++;
	}
}

u8 OS_CreateTask(void(*ptr)(void), u16 Copy_u16Periodicity, u8 Copy_u8Priority, u8 Copy_u8FirstDelay)
{
	u8 Local_Variable = 0;
	if(Copy_u8Priority < MAX_NUM_OF_TASKS)
	{
		if(Task_arr[Copy_u8Priority].Task_ptr == 0)
		{
			Task_arr[Copy_u8Priority].Task_ptr = ptr;
			Task_arr[Copy_u8Priority].Task_Periodicity = Copy_u16Periodicity;
			Timing_arr[Copy_u8Priority] = Copy_u8FirstDelay;
		}
		else
		{
			Local_Variable = 2;
		}
	}
	else
	{
		Local_Variable = 1;
	}
	return Local_Variable;
}

void OS_Scheduler(void)
{
	for(u8 i = 0; i < MAX_NUM_OF_TASKS; i++)
	{
		if(Task_arr[i].Task_ptr != 0)
		{
			if(Timing_arr[i] == 0)
			{
				Task_arr[i].Task_ptr();
				Timing_arr[i] = Task_arr[i].Task_Periodicity;
			}
			Timing_arr[i]--;
		}
	}
}

void OS_Start(void)
{
	TIM0_init();
	TIM0_OVFSetRegValue(192);
	TIM0_OVFCallBack(func);
	GIE_Enable();
	TIM0_OVFIntEnable();
}
