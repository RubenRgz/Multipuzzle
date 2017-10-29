/********************************************************************/
/**
* @LC	  2017/10/18
* @file   Timer.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  This class manag the time of the application
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Timer Class											                */
/************************************************************************/
class Timer
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	Timer();											/*!< Standrad Constructor */
	virtual ~Timer();									/*!< Standrad Destructor */

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	void Reset();										/*!< Reset the timer to zero */
	unsigned long getMilliseconds();					/*!< Returns time in milliseconds since timer was initialized or last reset */
	unsigned long getMicroseconds();					/*!< Returns time in microseconds since timer was initialized or last reset */
	unsigned long getMillisecondsCPU();					/*!< Returns time in milliseconds since timer was initialized or last reset. Only CPU timer measured */
	unsigned long getMicrosecondsCPU();					/*!< Returns time in microseconds since timer was initialized or last reset. Only CPU timer measured */
	unsigned long getStartMs() const;					/*!< Returns the time at which the timer was initialized, in milliseconds. */

	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
private:
	struct Data;
	Data* m_pData;
};

