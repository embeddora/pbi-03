/*
 * Copyright (C) 2018 ARNERI arneri@ukr.net All rights reserved
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Abstract: 
 */

/* Class <Engine> */
#include "core/Engine.h"

/* TODO: give a comment */
#include <stdio.h>

/* TODO: give a comment */
#include <stdlib.h>

/* TODO: give a comment */
#include <string.h>

/* unlink() */
#include <unistd.h>

/* CURL library API */
#include <curl/curl.h>

/* Own interface, structures, definitions */
#include "network/requests.h"

//extern int FMOD_Main();
extern int  fmod_init();
extern void fmod_play0();
extern void fmod_play1();
extern void fmod_play2();
extern void fmod_play3();
extern void fmod_play4();
extern void fmod_pause0();
extern void fmod_pause1();
extern void fmod_pause2();
extern void fmod_pause3();
extern void fmod_pause4();
extern int  fmod_dispose();

//int kind_of_main (int argc, char **argv)
int main (int argc, char **argv)
{
CURL *urlLib;

CURLcode iRes;

char cOpCode[R30_STRNLEN];

	/* True or forged, we need it for unlocking the site */
	ComputeRSA();

	/* Initialize variables and callbacks of library */
	urlLib = curl_easy_init();

	/* Can start as soon as library entry point was initialized */
	if(urlLib)
	{
	char cTemporary[0x200];

		/* Instantiate engine */
		Engine& engine = Engine::getInstance();

		/* Initialize SDL subsystem and main window  */
		engine.init();

		iRes = curl_easy_setopt(urlLib, CURLOPT_DEBUGFUNCTION, iTrace );
		iRes = curl_easy_setopt(urlLib, CURLOPT_HEADER, 1L);

		/* So far I experienced there's no other, lets use this one. TODO: check if it's really so in <TouchP5-xxxx> code*/
		iRes = curl_easy_setopt(urlLib, CURLOPT_REFERER, "http://192.168.0.1/webpages/index.html");

		
		/* Assign default value with which LUA-part of the site won't work anyway; only JS-part will. */
		sprintf (cTemporary, "sysauth=%s", CUKY0);
		iRes = curl_easy_setopt(urlLib, CURLOPT_COOKIE, cTemporary);


		/* Put our designations into traffic, so we're able to distingiosh own cookies from the rest */
		sprintf (cTemporary, "Mozilla/5.0 (X11; Ubuntu; %s) %s", argv[0], R30_CKY_MARKER);
		iRes = curl_easy_setopt(urlLib, CURLOPT_USERAGENT, cTemporary);

		iRes = curl_easy_setopt(urlLib, CURLOPT_CONNECTTIMEOUT, 30 );
		iRes = curl_easy_setopt(urlLib, CURLOPT_VERBOSE, 1L);

#if defined (RESPONCE_LATENCY_GAUGING)

		/* Send all data received to this function */
		curl_easy_setopt(urlLib, CURLOPT_WRITEFUNCTION, iRecvClbk);

#endif /* (RESPONCE_LATENCY_GAUGING) */

		/* Initialize audio subsystem */
		fmod_init();

		int iRepeats = 1;

		/* Decreasing index. Let's open the site, and do the rest */
		while (iRepeats--) {

		/* TODO: deploy for checking, or move away otherwise */
		int iRes;

			/* We should compute them anew each time we're opening the site */
			m_PasswordFound = m_TokenFound = m_CookieFound = 0;

#if defined (RESPONCE_LATENCY_GAUGING)

			/* TODO: give a comment */
			gettimeofday(&stHttpRequest, 0);
			/* TODO: give a comment */
			pcAddrStr[0]=0;

#endif /* (RESPONCE_LATENCY_GAUGING) */

			/* Play sound for scene 'scene.cube' */
			fmod_play1();
			/* Load MESH from a file */
			engine.initMesh("resources/meshes/prn1.vertex.surface" /*prn1.vertex.surface prn2.vertex.surface */);
			/* Cyclically process keys and draw a scene  */
			engine.startRendering();
			/* Let's open site. Mandatory for any other operation to be effective */
			iRes = iProcessArray(urlLib, get_aOpenArray() );
			/* Let's sleep for a site to become stable */
			sleep (R30_GP_TMO);
			/* Stop sound for scene 'scene.cube' */
			fmod_pause1();


			/* Play sound for scene 'scene.bicube' */
			fmod_play2();
			/* Load MESH from a file */
			engine.initMesh("resources/meshes/flash2.vertex.surface");
			/* Cyclically process keys and draw a scene  */
			engine.startRendering();
			/* Open first tab of site (seems to be must-have in order to proceed). Here <m_TokenFound> becomes 1 */
			iRes = iProcessArray(urlLib, get_aAuthArray() );
			/* Self-explanatory */
			printf("[%s] %s Site unlocked. Now can do _any operation\n", __FILE__, __func__); 
			/* To prevent libCURL from suppressing conventional output to '#2' */
			fflush(stderr);
			/* Stop sound for scene 'scene.bicube' */
			fmod_pause2();


			/* Play sound for scene 'scene.cube' */
			fmod_play3();
			/* Load MESH from a file */
			engine.initMesh("resources/meshes/flash1.vertex.surface");
			/* Cyclically process keys and draw a scene  */
			engine.startRendering();
			/* Let's deploy a duplication of <Gp aTab2Array[]> to see if it's necessary or not */
			iRes = iProcessArray(urlLib, get_aTab2Open_Array() );
			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s Competing Tab2-Open tested\n", __FILE__, __func__);
			/* Stop sound for scene 'scene.cube' */
			fmod_pause3();

#if 0

			/* Do the 'Network Map applet' */
			iRes = iProcessArray(urlLib, (void *) aTab2NetworkMap_Array);
			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s Network Map applet on Tab2 tested\n", __FILE__, __func__);

			/* Do the 'Internet applet' */
			iRes = iProcessArray(urlLib, (void *) aTab2Internet_Array);
			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s Internet applet on Tab2 tested\n", __FILE__, __func__);

			/* Do the 'Wireless applet' */
			iRes = iProcessArray(urlLib, (void *) aTab2Wireless_Array);
			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s Wireless applet on Tab2 tested\n", __FILE__, __func__);

			/* -------------------------------------------------------------------  */

			/* Switch off the flash */
			iRes = iProcessArray(urlLib, (void *) aTab2Flash_AUS_Array);
			/* Wait for a board to execute the <sftp_srv stop + PARAM_SAVE>, being invoced by LUA */
			sleep (R30_TAB2_TMO);

			/* Switch on the flash */
			iRes = iProcessArray(urlLib, (void *) aTab2Flash_EIN_Array);
			/* Wait for a board to execute the <sftp_srv start + PARAM_SAVE>, being invoced by LUA */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s USB-Sharing Flash applet on Tab2 tested\n", __FILE__, __func__);

			/* Open the printer applet */
			iRes = iProcessArray(urlLib, (void *) aTab2Printer_Array);
			/* Let's sleep for a site to become stable */
			sleep (R30_TAB2_TMO);

			/* Switch off the printer */
			iRes = iProcessArray(urlLib, (void *) aTab2Printer_AUS_Array);
			/* Wait for a to unload printer drivers, being invoced by LUA */
			sleep (R30_TAB2_TMO);

			/* Switch on the printer */
			iRes = iProcessArray(urlLib, (void *) aTab2Printer_EIN_Array);
			/* Wait for a to load printer drivers and bring-up Net interfaces, being invoced by LUA */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s USB-Sharing Printer Server applet on Tab2 tested\n", __FILE__, __func__);

			/* -------------------------------------------------------------------  */

			/* Do the 'Parentel Controls applet' */
			iRes = iProcessArray(urlLib, (void *) aTab2ParentalControls_Array);
			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s Parentel Controls applet on Tab2 tested\n", __FILE__, __func__);



			/* Do the 'Guest Network applet' */
			iRes = iProcessArray(urlLib, (void *) aTab2GuestNetwork_Array);
			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s Guest Network applet on Tab2 tested\n", __FILE__, __func__);



			/* Do the cloud applet' */
			iRes = iProcessArray(urlLib, (void *) aTab2TplinkCloud_Array);
			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);
			/* Self-explanatory */
			fprintf(stderr, "[%s] %s cloud applet on Tab2 tested\n", __FILE__, __func__);

#endif /* (0) */

#if 0
			/* Play sound for scene 'scene.bicube' */
			fmod_play4();
			/* Load MESH from a file */
			engine.initMesh("resources/meshes/hardware1.vertex.surface");
			/* Cyclically process keys and draw a scene  */
			engine.startRendering();
			/* Exit the site; let's not leave an opened backdoor after us. */
			iRes = iProcessArray(urlLib, get_aExitArray() );
			/* Self-explanatory */
			printf("[%s] %s Site closed. No opetaion is allowed unless it's opened again next time\n", __FILE__, __func__); 
			/* Needed, cause libcurl may appear to retain the output */
			fflush(stdout);
			/* Wait for a user to bank a kbd to hear the final sound */
			getchar();
			/* Stop sound for scene 'scene.bicube' */
			fmod_pause4();
#endif /* (0) */

		}

		/* Clean after ourselves */
		curl_easy_cleanup(urlLib);

	} /* if(urlLib) */

	/* Deinitialize audio subsystem */
	fmod_dispose();

#if (EXTRA_PURITY)
	unlink (ENCR_FNAME);

	unlink (CKY_FNAME);

	unlink (TOKEN_FNAME);

	unlink (PASSWD_FNAME);
#endif /* (EXTRA_PURITY) */

	/* TODO: who will catch this return code. if noone then what's the point? */
	return R30_SUCCESS;

} /* int _main (int argc, char **argv) */
