/*
 * netbase.cpp
 *
 *  Created on: 25 okt 2010
 *      Author: Ali Mosavian
 */
#include <maapi.h>
#include "netbase.h"


/**
 * Waits for a network event.
 *
 * @param ms 		Maximum number of milliseconds to wait
 * @param opType 	Connection even type
 *
 * @return True if event was caught with the given time limit.
 */
bool NetBase::waitForEvent ( int ms, int opType )
{
	int result;
	return waitForEvent ( ms, opType, result );
}


/**
 * Waits for a network event and returns the event
 * return code.
 *
 * @param ms 		Maximum number of milliseconds to wait.
 * @param opType 	Connection even type.
 * @param result    Event result code [out].
 *
 * @return True if event was caught with the given time limit.
 */
bool NetBase::waitForEvent ( int ms, int opType, int &result )
{
	MAEvent event;
	long startTime = maGetMilliSecondCount( );

	while ( maGetMilliSecondCount( )-startTime < ms )
	{
		maWait( 100 );
		while( maGetEvent( &event ) != 0 )
		{
			if ( event.type == EVENT_TYPE_CONN &&
				 event.conn.opType == opType )
			{
				result = event.conn.result;
				return true;
			}
		}
	}

	return false;
}



