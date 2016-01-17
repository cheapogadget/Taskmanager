// written by : Doug Reuter
//
//    TaskManager32 - Manage task functions on 32bt arduino bords such as ( due or zero)
//      may work on other arduino boards as well
//    http://cheapogadget.com   https://github.com/cheapogadget/Taskmanager32
//    Copyright (C) 2016 Doug Reuter   dougreuter@gmail.com
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// SERIAL Helper Macros
#if defined ARDUINO_SAMD_ZERO
#define SER SerialUSB
#else
#define SER Serial
#endif
#define SERPL(X) SER.println(X);	// Print line
#define SERPT SER.print("\t");		//tab
#define SERP(X) SER.print(X);		//Print

// fequncy helper
#define FREQ_TO_PERIOD(X)	(1000000/X) //hz
#include <TaskManager32.h>

// task declares
void taskRandom();
void taskMonitor();
void taskBlinkLed();

// defined tasks  max = 10 change in TaskManager32.h  = TASKS_SIZE_EMPTY_DEFAULT 10
Task taskList[] =
{
	Task("250hz", taskRandom, FREQ_TO_PERIOD(250)  ,TASK_PRIORITY_LOW),
	Task("Monitor", taskMonitor, FREQ_TO_PERIOD(1)),
	Task("LED .5", taskBlinkLed, FREQ_TO_PERIOD(2) ,TASK_PRIORITY_LOW),
	Task("50hz", taskRandom, FREQ_TO_PERIOD(50)  ,TASK_PRIORITY_CRITICAL),
	Task("Disabled Task", taskRandom, FREQ_TO_PERIOD(50)  ,TASK_PRIORITY_MEDIUM,false),
};
void setup()
{
	SER.begin(115200);

	//LED Init
	pinMode(LED_BUILTIN, OUTPUT);

	// int task manager 
	int taskListCount = sizeof(taskList) / sizeof(taskList[0]);
	taskManager.init(taskList, taskListCount);
	 

}
float idleTime = 0;
float processTime = 0;
float totalTime = 0;
void loop()
{
	uint32_t ts = micros();

	if (taskManager.update())
		processTime += (micros() - ts);
	else
		idleTime += (micros() - ts);

}
void taskRandom() {

	delayMicroseconds(random(100, 600)); //burn some time
}
void taskMonitor()
{
	totalTime = processTime + idleTime;
	SERP("Idle time "); SERP((idleTime / totalTime) * 100);
	SERP(" process time "); SERPL((processTime / totalTime) * 100);
	for (int i = 0; i < taskManager.taskCount; i++)
	{
		if (taskManager.taskPtr[i]->isEnabled)
		{
			SERP(taskManager.taskPtr[i]->taskName) SERPT SERP(taskManager.taskPtr[i]->executeLastPeriod);
			SERPT SERP(taskManager.taskPtr[i]->period);
			SERP(" exeTime ") SERPT SERP(taskManager.taskPtr[i]->avgerageRuntime);
			SERPL("")
		}
	}

}
bool v = false;
void taskBlinkLed()
{
	 v = !v;
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) == HIGH ? LOW : HIGH);

}
