/*
 * Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in the
 *          documentation and/or other materials provided with the distribution.
 *        * Neither the name of The Linux Foundation nor
 *          the names of its contributors may be used to endorse or promote
 *          products derived from this software without specific prior written
 *          permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _REQUESTS_H_
#define _REQUESTS_H_


#ifdef __cplusplus
extern "C" {
#endif


#include <curl/curl.h>


/* Report #30, general success */
#define R30_SUCCESS		0

/* Report #30, general case failure */
#define R30_FAILURE		(-1)

/* Report #30, string length, single words: verbs and abbreviations */
#define R30_STRNLEN		80

/* Report #30, general purposed timeout; nice to have various waits for various site-operations */
#define R30_GP_TMO		2

/* Report #30, timeout for Tab2; nice to have nice to have various waits for various site-operations on Tab2 */
#define R30_TAB2_TMO		3




/* Report #30, String tocken length; */
#define R30_TKN_LENGTH		32

/* String tocken wrapper length; same as strlen("stok="); */
#define R30_TKN_WRP_LENGTH	5



/* TODO: give a comment */
#define R30_PSW_LENGTH		256

/* TODO: give a comment */
#define R30_PSW_SP_LENGTH	6



/* Report #30, TODO string length */
#define R30_CKY_LENGTH		32

/* String tocken wrapper length; same as strlen("sysauth="); */
#define R30_WRP_CKY_LENGTH	8

/* Traffic disignator, should be unique among the existing User-Agents */
#define R30_CKY_MARKER		"MAZUKOWITZ-2450"




/* Max len of HTTP request */
#define R30_HTTP_LENGTH		0x200

/* Suppose 32K is enough to include any HTML responce from T5; used in <iRecvClbk()> */
#define R30_HTTP_CBK_BUF	0x400*32


/* Alternatively, use <node> */
#define INTERPRETER_FNAME	"nodejs"

/* Java script obtained via HTTP form P5 with minor custom amends */
#define RSA_COMPUTER_FNAME	"source/network/rsa.js"

/* File lenth; let's have it exactly what it should be */
#define R30_RSA_LEN		0x100


/* File to catch computed RSA-value to */
#define ENCR_FNAME		"_delme.rsa"

/* File to store cookie(s) being found diring run*/
#define CKY_FNAME		"_delme.cky"

/* File to store tocken as is and wrapped one being found diring run */
#define TOKEN_FNAME		"_delme.tkn"

/* File to store passwords as they're been fond while diring run */
#define PASSWD_FNAME		"_delme.psw"

/* A name template for series of image files to store RLDA data to */
#define RLDA_TEMPLATE		"rlda_epoque_"

/* Max length of system commands we launch in external shell (bash, sh, ksh, usw) */
#define BASH_STRING_LEN		0x100


/* TODO: or #if defined (RESPONCE_LATENCY_DISTRIBUTION_ANALYSIS) */
#if defined (RESPONCE_LATENCY_GAUGING) 

/* File to store time elapsed between HTTP request and responce */
#define RLG_FNAME		"_delme.rlg"

/* Max length of data we send to file and put to STDOUT while gauging the time between HTTP request and responce */
#define GAUGE_STRING_LEN	0x100

/* Max filename lenth for intermediate images */
#define RLDA_IMAGE_FNAME_LEN	0x100

/* Amount of seconds after which a responce should be regarded as 'bug reproduce' delay */
#define GAUGE_HTTP_THRESHOLD	29500

#endif /* (RESPONCE_LATENCY_GAUGING) */


/* Report #30, set to 1 to explore traffic in hexadecimal view, keep as 0 in rest cases */
#define R30_DUMPING	0

/* Marker of command to open site */
#define OPEN_SITE	"open"

/* Marker of command to pass authentication */
#define AUTH		"auth"

/* Marker of command to switch to tab 1, same as passing authentication, see <auth>  */
#define TAB1		"tab1"

/* Marker of command to switch to tab 2 */
#define TAB2		"tab2"

/* Marker of command to switch to tab 3 */
#define TAB3		"tab3"


/* Default RSA key; used when it's impossible to compute the one in conventional way */
#define STUB0 "286d0d177bd567ba5db27bb709a0f041b9400dbc1961f47fff06f8cf10ea1325023fba8aa416049d9897d1dff49088f67347c825d495741563154d1b749466c939b1cf4bf7175d73e93554b359580c46be069e0c87d21a7d3fb356c7d39d8f3a2ea0507b5b21aefc08ad2ec9d39b4858845e0dfc44c5792ec66925772deb8d7c"

/* Spare 1; Not used by now */
#define STUB1 "626da1760f49737dbb3a60fee63ad025fee41e65e7fa2347e5e1aaa4e9e7a8644ed4df93881998e2707c1417d8caba93398875cf7e837cc14119b9779e86aace7ebc256e6e6817fa90cd58ee5ebe50de6810308ed39298d5c468713186adaebdbd186715f1612828ff39c082aaadeafd2817d65b73a39a99a7dc8b946d992c38"

/* Spare 2; Not used by now */
#define STUB2 "626da1760f49737dbb3a60fee63ad025fee41e65e7fa2347e5e1aaa4e9e7a8644ed4df93881998e2707c1417d8caba93398875cf7e837cc14119b9779e86aace7ebc256e6e6817fa90cd58ee5ebe50de6810308ed39298d5c468713186adaebdbd186715f1612828ff39c082aaadeafd2817d65b73a39a99a7dc8b946d992c38"


/* Default cookie; used when it's impossible to compute the one in conventional way */
#define CUKY0 "effbf71a985814ee44e1181771a8a5a8"

/* Spare 1; Not used by now */
#define CUKY1 "770605707cda9615628eb35650a1bb6f"

/* Spare 2; Not used by now */
#define CUKY2 "353bcc80989c36c52a20fd3d4674b9a1"



/* Structure to keep a HTTP-request pair: request itself and index to tell how the request has to be processeed */
typedef struct _GP 
{
	/* 0 - GET, otherwise - POST; 666 - is not processed, the rest - are */
	const int iGetOrPost;

	/* Contents */
	const char * pcAddrStr;

} Gp , * pGp;

/* Structure to keep a HTTP-reponce pair: responce itself and its size; used in <iRecvClbk()> */
typedef struct _RespStruct
{
	char * cpResponce;

	size_t iSize;

} RespStruct, *pRespStruct;




/* Defined in <requests.c> */
int iProcessArray(CURL * curl, void * pGpArray);

/* Defined in <requests.c> */
int iTrace(CURL * handle, curl_infotype type, char *data, size_t size, void *userp);

/* Defined in <requests.c> */
void ComputeRSA();



/* They're defined and chnged in <requests.c>, we just initialize them */
int m_TokenFound, m_PasswordFound, m_CookieFound;



void * get_aOpenArray();

void * get_aAuthArray();

void * get_aTab2Open_Array();

void * get_aExitArray();

#if (RESPONCE_LATENCY_GAUGING)

/* gettimeofday() and time structures */
#include <sys/time.h>

/* Time structured of HTTP-request and corresponding to it HTTP-responce */
struct timeval stHttpRequest, stHttpResponce;

char pcAddrStr[R30_HTTP_LENGTH];

size_t iRecvClbk(void *contents, size_t size, size_t nmemb, void *userp);

#endif /* (RESPONCE_LATENCY_GAUGING) */



#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* !defined(_REQUESTS_H_) */
