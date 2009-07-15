#include <iostream>
#include <cstdlib>
#include "luisita.h"

/**

  "escena org dentro v2" / xplsv

  Start date ~ april 2008
  Released 20080511
  Source released 20090715

  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  Copyright 2008-2009 Soledad Penades http://soledadpenades.com
 
  This file is part of xplsv_eorgd2
 
  xplsv_eorgd2 is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 3 only, as published
  by the Free Software Foundation.
 
  xplsv_eorgd2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with xplsv_eorgd2. If not, see <http://www.gnu.org/licenses/>.
*/

void lastFunction(void)
{
	luisita_end();
}

int main(int argc, char *argv[])
{
	char *scriptFile;
	char defaultScript[] = "data/demo.lua";
	
	if(argc < 2)
	{
		scriptFile = defaultScript;
	}
	else
	{
		scriptFile = argv[1];
	}
	
	// Cleanup
	atexit(lastFunction);

	if(!luisita_init() || !luisita_runScript(scriptFile))
	{
		exit(-1);
	}
	
	// Main loop: loop forever.
	while(!luisita_hasFinished())
	{
		luisita_render();
	}
	
    return 0;
}
