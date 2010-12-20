/* Copyright (C) 2010 MoSync AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

/** @file helloworld.cpp
*
* This application provides a very basic example of how to use MoSync
* to print the text "Hello World" to a device's screen. The code is very
* well commented so that you can see exactly what's happening at each step.
* The application makes use of MoSync's Moblet framework to handle events.
* Full documentation for this application can be found at the MoSync web site:
* http://www.mosync.com/documentation/manualpages/hello-world-deconstructed
*
* @author Chris Hughes
*/

//Include the header files for MoSync Moblets so that we can
//access the Moblet library code from our application.
#include <MAUtil/Moblet.h>

//Declare the MAUtil namespace so that we can use the short forms of
//identifiers in our code.
using namespace MAUtil;

//Create an event-handling wrapper for our application based on the
//Moblet base class.
class MyMoblet : public Moblet {

//Define our new class's public methods.
public:

	//First, the constructor, which we will call whenever we need an
	//instance of MyMoblet. In this case, the constructor consists
	//of three syscalls.
	MyMoblet() {
		//The first syscall sets the background colour.
		maSetColor(0xFFFFFF),
		//The second syscall writes the text "Hello World" to the backbuffer.
		maDrawText(0, 32, "Hello World!");
		//The third syscall copies the contents of the backbuffer to the
		//physical screen.
		maUpdateScreen();
	}

	//Next, a method for detecting key presses. This is a method we have
	//inherited from the Moblet base class, and here we will override that
	//method with some processing of our own.
	void keyPressEvent(int keyCode, int nativeCode) {
		//Close the application if key 0 is pressed.
		if(keyCode == MAK_0)
		{
			close();
		}
	}

	//Finally, a code stub we might need to use later for another event type.
	void keyReleaseEvent(int keyCode, int nativeCode) {
		//to do: handle key releases - put your code here.
	}
};

//Now we get to the entry point for the application - the place where
//processing starts.
extern "C" int MAMain() {

	//Create an instance of MyMoblet
	MyMoblet myMoblet;

	// Give the moblet responsibility for event handling.
	Moblet::run( &myMoblet );

	//MyMoblet will run until it is closed by the user pressing key 0. When
	//it's closed we end our program in a well-behaved way by returning zero.
	return 0;
};
