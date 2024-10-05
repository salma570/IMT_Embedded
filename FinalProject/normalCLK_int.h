typedef struct {
	u8 u8Hour;
	u8 u8Minute;
  u8 u8Seconds;
} strctAlarm;
const u8 * u8DaysOfWeek_Arr[7] = {"Mon","Tues","Wed","Thu","Fri","Sat","Sun"};
//set
void normlClk_SetAlarmFlag(u8 OnOff); 
void normlClk_SetAlarmValue(strctAlarm* alarm); //store value in Sram??
//get
u8 normlClk_voidGetAlarmFlag(void);
void normlClk_GetAlarm_Value();
void alarm_timerIncrement();
//display 
void normlClk_DisplayTime();
//clear
void normlClk_ClrAlarmFlag(void);
//normal time & flag
u8DisplayTimeFlag = 0; // display or we are in diffrent mode
u8 u8AlarmFlag =0; // there's no alarm set
u32CountTime; // mi4 fakra
RTC_val rtc; // needed or added in main 
strctAlarm strctAlarmNode; // add alarms in form of linked lists
