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
#include "requests.h"




#if (RESPONCE_LATENCY_GAUGING)

/* gettimeofday() and time structures */
#include <sys/time.h>

/* Time structured of HTTP-request and corresponding to it HTTP-responce */
struct timeval stHttpRequest, stHttpResponce;

/* Suppose 32K is enough to include any HTML responce from T5; used in <iRecvClbk()> */
char cBuffer[R30_HTTP_CBK_BUF];

// TODO: why do I need increment 65536, isn't it not incremented already? 
// TODO: remove char	wr_buf[R30_HTTP_CBK_BUF+1];

/* Position ot last char in receive buffer processed by <iRecvClbk> */
int	wr_index;

char pcAddrStr[R30_HTTP_LENGTH];

#endif /* (RESPONCE_LATENCY_GAUGING) */





/* TODO: give a comment */
char cR30Token[R30_TKN_LENGTH+1];

char cR30Token_Wrapped[R30_TKN_LENGTH+5];//TODO: fix

/* Token is 32-char long string computed on side of P5 and passed to us in responce to TODO request */
int m_TokenFound;



/* TODO: give a comment */
char cR30Passwd[R30_PSW_LENGTH+1];

/* TODO: give a comment */
char cR30Passwd_Sp[R30_PSW_SP_LENGTH+1];

/* TODO: give a comment */
char cR30Passwd_Wrapped[R30_PSW_LENGTH+64];

/* Passowrd is first member of bi-string array, in respoince to TODO request */
int m_PasswordFound;


/* TODO: give a comment */
char cR30Cookie[R30_CKY_LENGTH+1];

/* TODO: give a comment */
char cR30Cookie_Wrapped[R30_CKY_LENGTH+15];//TODO: fix

/* Cookie is 32-char long string computed on side of P5 and passed to us in responce to TODO request */
int m_CookieFound;


/* Buffer to keep this session RSA key */
char STUB[R30_RSA_LEN + 1];










/* By this sequence we "open" website, so the certain calbacks on SRV side get prepared. Better name: aOpenSite_Array */
Gp aOpenArray[] = {

     { 0, "http://192.168.0.1/" },
     { 0, "http://192.168.0.1/webpages/login.html" },
     { 0, "http://192.168.0.1/webpages/css/widget.css" },
     { 0, "http://192.168.0.1/webpages/themes/green/css/style.css" },
     { 0, "http://192.168.0.1/webpages/js/libs/jquery.min.js" },
     { 0, "http://192.168.0.1/webpages/js/libs/jquery.nicescroll.min.js" },
     { 0, "http://192.168.0.1/webpages/js/su/locale.js" },
     { 0, "http://192.168.0.1/webpages/js/libs/encrypt.js" },
     { 0, "http://192.168.0.1/webpages/js/su/su.js" },
     { 0, "http://192.168.0.1/webpages/js/su/data/proxy.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/widget.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/window/msg.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/form/form.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/form/combobox.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/form/textbox.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/form/password.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/form/checkbox.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/form/button.js" },
     { 0, "http://192.168.0.1/webpages/js/su/widget/form/status.js" },
#if defined(EXTRA_PRECISION)
     { 0, "http://192.168.0.1/webpages/themes/green/img/icons.png"},
#endif /* (EXTRA_PRECISION) */
     { 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/locale?form=lang" },
     { 0, "http://192.168.0.1/webpages/app.manifest" },
     { 0, "http://192.168.0.1/webpages/locale/en_US/lan.js?_=1481111286804" },
     { 0, "http://192.168.0.1/webpages/locale/en_US/lan.css" },
     { 0, "http://192.168.0.1/webpages/locale/en_US/help.js?_=1481111286805" },
     { 0, "http://192.168.0.1/webpages/locale/language.js?_=1481111286806" },
     { 0, "http://192.168.0.1/webpages/js/libs/encrypt.js" },
     { 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/locale?form=list" },
     { 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=cloud_login" },
     { 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=login" },
     { 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=initial_login" },
     { 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=check_factory_default" },
     { 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/domain_login?form=dlogin" },
#if defined(EXTRA_PRECISION)
     {0, "http://192.168.0.1/webpages/themes/green/img/icons2.png"},
#endif /* (EXTRA_PRECISION) */

     { 0, NULL }
};

/* A specific data for get some server's stuff we use as JavaScript-software source on client's side. Better name: aCodeExtruder_Array */
Gp aCodeExtruderArray[] = {

	/* To get RSA-computation JavaScript-code use following HTTP-request(s), after 'opening' the site */
	{ 0, "http://192.168.0.1/webpages/js/libs/encrypt.js"},
	{ 0, NULL  }

};

/* Draft array. TODO: remove */
Gp _aAuthArray[] = {

	{ 2, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=login"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/ledgeneral?form=setting"},
	{ 0x0, NULL }
};

/* Better name: aAuth_Array */
Gp aAuthArray[]/* a.k.a. 'aTab1Array' */ = {

	{ 2, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=login"},
#if defined(EXTRA_PRECISION)
	{ 0, "http://192.168.0.1/webpages/themes/green/img/waiting.gif"},
#endif /* (EXTRA_PRECISION) */
	{ 0, "http://192.168.0.1/webpages/index.html"},
	{ 0, "http://192.168.0.1/webpages/css/widget.css"},
	{ 0, "http://192.168.0.1/webpages/js/libs/jquery.min.js"},
	{ 0, "http://192.168.0.1/webpages/themes/green/css/style.css"},
	{ 0, "http://192.168.0.1/webpages/js/libs/jquery.nicescroll.min.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/su.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/locale.js"},
	{ 0, "http://192.168.0.1/webpages/js/libs/encrypt.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/data/proxy.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/widget.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/window/msg.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/form.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/combobox.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/checkbox.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/textbox.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/button.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/password.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/status.js"},
	{ 0, "http://192.168.0.1/webpages/js/libs/jquery.scrollTo.min.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/data/store.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/data/treestore.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/window/panel.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/window/page.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/window/wizard.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/window/foldertree.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/window/keyword.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/grid/grid.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/grid/editor.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/grid/paging.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/fieldset.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/radio.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/textarea.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/time.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/file.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/timepicker.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/progressbar.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/slider.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/switch.js"},
	{ 666/*1000*/, "http://192.168.0.1/cgi-bin/luci/;stok=/locale?form=lang"},
#if defined(EXTRA_PRECISION)
	{ 0, "http://192.168.0.1/webpages/themes/green/img/loading.gif"},
	{ 0, "http://192.168.0.1/webpages/themes/green/img/icons2.png"},
	{ 0, "http://192.168.0.1/webpages/themes/green/img/icons.png"},
#endif /* (EXTRA_PRECISION) */
	{ 0, "http://192.168.0.1/webpages/locale/de_DE/lan.js?_=1482736660345"},
	{ 0, "http://192.168.0.1/webpages/locale/de_DE/lan.css"},
	{ 0, "http://192.168.0.1/webpages/locale/de_DE/help.js?_=1482736660346"},
	{ 0, "http://192.168.0.1/webpages/locale/language.js?_=1482736660347"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/userFeedBack.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/locale?form=list"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/ledgeneral?form=setting"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/cloud_account?form=check_login"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/system?form=sysmode"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/cloud_account?form=check_support"},
	{ 0, "http://192.168.0.1/webpages/data/region.json?operation=read&_=1482736660348"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/feedback?form=content"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/cloud_account?form=check_cloud_version"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/cloud_account?form=check_upgrade"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/firmware?form=upgrade"},
	{ 1, "http://192.168.0.1/webpages/pages/frame/quick-setup.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/administration?form=account"},
	{ 0, "http://192.168.0.1/webpages/locale/ru_RU/ispAutoConf.js?_=1482736660349"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/locale?form=country"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/cloud_account?form=user_login"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/locale?form=country_list"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/quick_setup?form=timezone"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/network?form=status_ipv4"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/quick_setup?form=quick_setup"},

	{ 0x0, NULL }
};

/* Better name: aTab2Open_Array */
Gp aTab2Array[] = {

	{ 1, "http://192.168.0.1/webpages/pages/frame/basic.html"},
	{ 0, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/menu?form=basic_menu"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_network.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/wireless?form=region"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/wireless?form=wireless_schedule_wifi_disable"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/status?form=all"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/status?form=internet"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/status?form=router"},
#if defined(EXTRA_PRECISION)
	{ 0, "http://192.168.0.1/webpages/themes/green/img/waiting.gif"},
#endif /* (EXTRA_PRECISION) */

	{ 0x0, NULL }
};

/* Better name: aTab2UsbStorateDevice_Array */
Gp aTab2Flash_Array[] = {

	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_diskSetting.html"},
	{ 0, "http://192.168.0.1/webpages/js/libs/excanvas.js?_=1482829173051"},
	{ 0, "http://192.168.0.1/webpages/js/libs/Chart.js?_=1482829173052"},
	{ 1, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/disk_setting?form=metadata"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=settings"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=server"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=auth"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=partial"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=guest"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=media"},
	{ 1, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=volumn"},
	{ 1002, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/disk_setting?form=contents&serial=0320815020006996"},
	{ 1004, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=tree"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=mode"},
	{ 0x0, NULL }
};

/* Better name: aTab2UsbStorateDevice_On_Array */
Gp aTab2Flash_AUS_Array[] = {
	{ 4/*3*/, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=settings"},
	{ 0x0, NULL }
};

/* Better name: aTab2UsbStorateDevice_Off_Array */
Gp aTab2Flash_EIN_Array[] = {
	{ 204/*3*/, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/folder_sharing?form=settings"},
	{ 0x0, NULL } 
};

/* Better name: aTab2PrintServer_Array */
Gp aTab2Printer_Array[] = {

	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_print.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/print_server"},
	{ 0x0, NULL }
};

/* Better name: aTab2PrintServer_On_Array */
Gp aTab2Printer_EIN_Array[] = {

	{ 203, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/print_server"},
	{ 0x0, NULL }
};

/* Better name: aTab2PrintServer_Off_Array */
Gp aTab2Printer_AUS_Array[] = {
	{ 303, "http://192.168.0.1/cgi-bin/luci/;stok=52fa3b96ab31531111331f8e6e44fa88/admin/print_server"},
	{ 0x0, NULL }
};

/* Better name: aTab3_Array */
Gp aTab3Array[] = {

	{ 1, "http://192.168.0.1/webpages/pages/frame/advanced.html"},
	{ 0, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/menu?form=advanced_menu"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/status.html"},
	{ 1, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/wireless?form=region"},  
	{ 1, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/wireless?form=wireless_schedule_wifi_disable"},  
	{ 1, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/status?form=all"},
	{ 1, "http://192.168.0.1/cgi-bin/luci/;stok=6c2a1ef44697a73379a350deec6601a0/admin/status?form=internet"},  

	{ 0x0, NULL }
};


/* Better name: aCloseSite_Array */
Gp aExitArray[] = {

	{ 1006, "http://192.168.0.1/cgi-bin/luci/;stok=b2c63d5a14d0699b233094bae241cc89/admin/system?form=logout"},
	{ 0, "http://192.168.0.1/"},
	{ 0, "http://192.168.0.1/webpages/login.html"},
	{ 0, "http://192.168.0.1/webpages/css/widget.css"},
	{ 0, "http://192.168.0.1/webpages/themes/green/css/style.css"},
	{ 0, "http://192.168.0.1/webpages/js/libs/jquery.nicescroll.min.js"},
	{ 0, "http://192.168.0.1/webpages/js/libs/jquery.min.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/locale.js"},
	{ 0, "http://192.168.0.1/webpages/js/libs/encrypt.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/su.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/data/proxy.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/widget.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/window/msg.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/form.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/combobox.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/textbox.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/password.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/checkbox.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/button.js"},
	{ 0, "http://192.168.0.1/webpages/js/su/widget/form/status.js"},
#if defined(EXTRA_PRECISION)
	{ 0, "http://192.168.0.1/webpages/themes/green/img/icons.png"},
#endif /* (EXTRA_PRECISION) */
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/locale?form=lang"},
	{ 0, "http://192.168.0.1/webpages/locale/de_DE/lan.js?_=1482885989441"},
	{ 0, "http://192.168.0.1/webpages/locale/de_DE/lan.css"},
	{ 0, "http://192.168.0.1/webpages/locale/de_DE/help.js?_=1482885989442"},
	{ 0, "http://192.168.0.1/webpages/locale/language.js?_=1482885989443"},
	{ 0, "http://192.168.0.1/webpages/js/libs/encrypt.js"},
#if 0
	/* TODO: normalerweise braucht man dies nicht */
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/locale?form=list"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=cloud_login"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=login"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=initial_login"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/login?form=check_factory_default"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=/domain_login?form=dlogin"},
#endif /* (0) */

#if defined(EXTRA_PRECISION)
	{ 0, "http://192.168.0.1/webpages/themes/green/img/icons2.png"},
#endif /* (EXTRA_PRECISION) */
	{ 0x0, NULL }
};


/* TODO: it's a duplication of <Gp aTab2Array[]>, REMOVE it after check. */
/* TODO: not checked. TODO: give a comment */
Gp aTab2Open_Array[] = {

	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/quick_setup?form=timezone"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/network?form=status_ipv4"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/quick_setup?form=quick_setup"},
	{ 1, "http://192.168.0.1/webpages/pages/frame/basic.html"},
	{ 0, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/menu?form=basic_menu"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_network.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=region"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=wireless_schedule_wifi_disable"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/status?form=all"},

	{ 0x0, NULL }
};

/* TODO: not checked. TODO: give a comment */
Gp aTab2GuestNetwork_Array[] = {

	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_guest.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=region"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=guest&form=guest_2g&form=guest_5g&form=guest_2g5g"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=wireless_2g"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=wireless_5g"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=syspara_2g"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=syspara_5g"},

	{ 0x0, NULL }
};

/* TODO: not checked. TODO: give a comment */
Gp aTab2Internet_Array[] = {

	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/status?form=internet"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/status?form=router"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_internet.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/network?form=status_ipv4"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/network?form=wan_ipv4_protos"},

	{ 0x0, NULL }
};

/* TODO: not checked. TODO: give a comment */
Gp aTab2NetworkMap_Array[] = {

	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_network.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=region"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=wireless_schedule_wifi_disable"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/status?form=all"},

	{ 0x0, NULL }
};

/* TODO: not checked. TODO: give a comment */
Gp aTab2ParentalControls_Array[] = {

	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/folder_sharing?form=mode"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/disk_setting?form=first"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_print.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/print_server"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_parental_control.html"},

	{ 0x0, NULL }
};

/* TODO: not checked. TODO: give a comment */
Gp aTab2TplinkCloud_Array[] = {

	/* WebUI: oops.. the device is offline */
	{ 0x0, NULL }
};

/* TODO: not checked. TODO: give a comment */
Gp aTab2Wireless_Array[] = {

	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=region"},
	{ 1, "http://192.168.0.1/webpages/pages/userrpm/basic_wireless.html"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=region"},
	{ 1000, "http://192.168.0.1/cgi-bin/luci/;stok=423f4e49ee265d083e9c09aabd63aeb1/admin/wireless?form=wireless_2g&form=wireless_5g"},

	{ 0x0, NULL }
};

void * get_aOpenArray()
{
	return (void*)aOpenArray;
}

void * get_aAuthArray()
{
	return (void*)aAuthArray;
}

void * get_aTab2Open_Array()
{
	return (void*)aTab2Open_Array;
}

void * get_aExitArray()
{
	return (void*)aExitArray;
}




/* Dump cpontents of HTTP traffic being received; for usage on narrow consoles */
static void Dump(const char *text, FILE *stream, unsigned char *ptr, size_t size)
{
size_t i,  c;

unsigned int width=0x20;

#if (EXTRA_INFORMATIVITY)

	fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n", text, (long)size, (long)size);

	for( i = 0; i < size; i += width )
	{
		fprintf(stream, "%4.4lx: ", (long)i);

		/* Show hex to the left */
		for(c = 0; c < width; c++)
		{
			if(i+c < size)

				fprintf(stream, "%02x ", ptr[i+c]);
			/* else
				fputs(" ", stream); */
		}

		/* Last row reqiures special tabulation */
		if (i + width > size)

			for(c = 0; c < width - (size % width); c++)	

				fputs("   ", stream);

		/* Show data on the right */
		for(c = 0; (c < width) && (i+c < size); c++)

			fputc((ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.', stream);

		fputc('\n', stream);
	}
#endif /* (EXTRA_INFORMATIVITY) */

} /* static void Dump( . . ) */

/* Define 1 to not check HEX output profoundly */
#define SKIP_ONE_HEX 1

/* Dump cpontents of HTTP traffic being received; for usage on wide consoles */
static void WideDump(const char *text, FILE *stream, unsigned char *ptr, size_t size)
{
size_t i,  c;

unsigned int width=0x40;

#if (EXTRA_INFORMATIVITY)

	fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n", text, (long)size, (long)size);

	for( i = 0; i < size; i += width )
	{
		fprintf(stream, "%4.4lx: ", (long)i);

		/* Show hex to the left */
		for(c = 0; c < width; c++)
		{
#if (SKIP_ONE_HEX)
			if(i+c < size)
				if ( (i+c) % 2) 

					/* Output hex for even bytes only - screen is not enough */
					fprintf(stream, "%02x", ptr[i+c]);
				else
					/* And skip odd bytes, anyway nobody looks at them */
					fprintf(stream, " ");


#else
			/* Output hex'es w/o whitespace  */
			if(i+c < size)

				fprintf(stream, "%02x", ptr[i+c]);
#endif /* (SKIP_ONE_HEX) */
		}

#if (SKIP_ONE_HEX)
		/* Last row reqiures special tabulation */
		if (i + width > size)
		{

			for(c = 0; c < width - (size % width); c++)
	
				if ( c % 2) 
					fputs("  ", stream);
				else
					fputs(" ", stream);

			if ( c % 2)

				fprintf(stream, " ");

		}
#else
		/* Last row reqiures special tabulation */
		if (i + width > size)

			for(c = 0; c < width - (size % width); c++)	

				fputs("  ", stream);
#endif /* (SKIP_ONE_HEX) */

		fprintf(stream, "   ");

		/* Show data on the right */
		for(c = 0; (c < width) && (i+c < size); c++)

			fputc((ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.', stream);

		fputc('\n', stream);
	}
#endif /* (EXTRA_INFORMATIVITY) */

} /* static void WideDump( . . . ) */


/* TODO: give a comment */
static int iGetToken(unsigned char *ptr)
{
char * cpAjaxPtr, * cp1;

	/* Clear token (itself and wrapped one) contents, i.e. body + TR0 */
	memset (cR30Token, 0 , R30_TKN_LENGTH + 1);
	memset (cR30Token_Wrapped, 0 , R30_TKN_LENGTH + R30_TKN_WRP_LENGTH + 1);

	/* Clean token-found value for accuracy. We expect it also to be cleared in main() */
	m_TokenFound = 0;

	if ( NULL != ( cpAjaxPtr = strstr(ptr, "stok\":\"") ) )
	{
		cpAjaxPtr = & cpAjaxPtr [strlen ("stok\":\"") ];

		cp1 = strtok(cpAjaxPtr, "\"");

		if (R30_TKN_LENGTH == strlen (cp1) )
		{
			m_TokenFound = 1;

			/* Without TR0 - see first instr. of this fn. */
			memcpy(cR30Token, cp1, R30_TKN_LENGTH );

			memcpy(cR30Token_Wrapped, "stok=", R30_TKN_WRP_LENGTH);

			/* Without TR0 - see second instr. of this fn. */
			memcpy(&cR30Token_Wrapped[R30_TKN_WRP_LENGTH], cp1, R30_TKN_LENGTH);

			char cFileBuf[BASH_STRING_LEN];

			sprintf(cFileBuf,  "echo \"token: %s, wrapped token: %s\">> ./%s", cR30Token, cR30Token_Wrapped, TOKEN_FNAME);
			system (cFileBuf);

			return R30_SUCCESS;
		}
	}

	return R30_FAILURE;

} /* static int iGetToken( . . .) */

/* TODO: give a comment */
static int iGetCookie(unsigned char *ptr, CURL * urlLib)
{
char * cpAjaxPtr, * cp1;

/* For exit with failure. But what if we don't need LUA-part of the site to work, i.e. what is we need only JS-part of it? */
int iRes;

	/* Clear cookie contents, i.e. body + TR0 */
	memset (cR30Cookie_Wrapped, 0 , R30_CKY_LENGTH + R30_WRP_CKY_LENGTH + 1 /* with TR0 */);

	/* Clean cookie-found value*/
	m_CookieFound = 0;

	if ( NULL != ( cpAjaxPtr = strstr(ptr, "sysauth=") ) )
	{
		memcpy(cR30Cookie_Wrapped, cpAjaxPtr, R30_CKY_LENGTH + R30_WRP_CKY_LENGTH /* without TR0 */);


#if (DONT_REFRESH_COOKIES)
		/* Let's stop for new cookies throughout working session; why not? */
		m_CookieFound = 1;
#endif /* (0) */

		iRes = curl_easy_setopt(urlLib, CURLOPT_COOKIE, cR30Cookie_Wrapped);

		char cFileBuf[BASH_STRING_LEN];		

		sprintf(cFileBuf,  "echo \"Wrapped cookie: %s\">> ./%s", cR30Cookie_Wrapped, CKY_FNAME);
		system (cFileBuf);

		return R30_SUCCESS;
	}

	return R30_FAILURE;

} /* static int iGetCookie(. . . ) */



/* TODO: give a comment */
static int iGetPassword(unsigned char *ptr)
{
char * cpAjaxPtr, * cpAjaxPtr_Sp;

char * cp1;

	/* Clear password contents */
	memset (cR30Passwd, 0 , R30_PSW_LENGTH);

	/* Clear password-sp's contents */
	memset (cR30Passwd_Sp, 0 , R30_PSW_SP_LENGTH);
	
	/* Clean password-found value for accuracy. We expect it also to be cleaned in main() */
	m_PasswordFound = 0;

	if ( NULL != ( cpAjaxPtr_Sp = cpAjaxPtr = strstr(ptr, "password\":[ \"") ) )
	{
		cpAjaxPtr = & cpAjaxPtr [strlen ("password\":[ \"") ];

		cpAjaxPtr_Sp = & cpAjaxPtr_Sp [strlen ("password\":[ \"")  + R30_PSW_LENGTH + 4 /* strlen(", ") */ ];

		memcpy (cR30Passwd_Sp, cpAjaxPtr_Sp, R30_PSW_SP_LENGTH); 

		cp1 = strtok(cpAjaxPtr, "\"");

		if (R30_PSW_LENGTH == strlen (cp1) )
		{
			m_PasswordFound = 1;

			memcpy(cR30Passwd, cp1, R30_PSW_LENGTH+1 );

			char cFileBuf[BASH_STRING_LEN*8];		

			sprintf(cFileBuf,  "echo \"password: %s, special: %s\">> ./%s", cR30Passwd, cR30Passwd_Sp, PASSWD_FNAME);
			system (cFileBuf);

			return R30_SUCCESS;
		}
	}

	return R30_FAILURE;

} /* static int iGetPassword( . . . ) */


/* Callback to execute on arrival of HTML responce */
int iTrace(CURL * handle, curl_infotype type, char *data, size_t size, void *userp)
{
const char *text;

(void)handle;

#if (EXTRA_INFORMATIVITY)

	switch (type)
	{
		/* In case a new one is introduced to knock me out */
		default:
		case CURLINFO_TEXT:
		{
			/* Self-explanatory:printf("[%s] %s: Skipping 'Info' or unknown header\n", __FILE__, __func__);*/
			return R30_FAILURE;
		}

		case CURLINFO_HEADER_OUT:
			text = "=> Send header";
		break;

		case CURLINFO_DATA_OUT:
			text = "=> Send data";
		break;

		case CURLINFO_SSL_DATA_OUT:
			text = "=> Send SSL data";
		break;

		case CURLINFO_HEADER_IN:
			text = "<= Recv header";
		break;

		case CURLINFO_DATA_IN:
			text = "<= Recv data";
		break;

		case CURLINFO_SSL_DATA_IN:
			text = "<= Recv SSL data";
		break;
	}


#if (WIDE_CONSOLE)
	WideDump(text, stderr, (unsigned char *)data, size);
#else
	Dump(text, stderr, (unsigned char *)data, size);
#endif /* (WIDE_CONSOLE) */


#endif /* (EXTRA_INFORMATIVITY) */

	/* Look for password only in data section of incomming packets */
	if (0 ==  m_PasswordFound && CURLINFO_DATA_IN == type)

			iGetPassword((unsigned char *)data );

	/* Look for tokens only in data section of incomming packets */
	if (0 ==  m_TokenFound && CURLINFO_DATA_IN == type)

			iGetToken((unsigned char *)data );

	/* Look for cookies only in header section of outgoing packets */
	if (0 ==  m_CookieFound  && CURLINFO_HEADER_IN == type )

			iGetCookie((unsigned char *)data , handle);

	return R30_SUCCESS;

} /* static int iTrace( . . . ) */

int iProcessArray(CURL * curl, void * pGpArray)
{
int i=0;

CURLcode iRes;

/* Pointer to an array being used currently */
pGp pGP_Array;

	pGP_Array = (pGp)pGpArray;

	while ( NULL != pGP_Array[i].pcAddrStr )
	{
#if (EXTRA_INFORMATIVITY)

		//.printf("%d : \t %d \t  %s  \n", i, pGP_Array[i].iGetOrPost , pGP_Array[i].pcAddrStr ) ;

#endif /* (EXTRA_INFORMATIVITY) */

	/* Temporary buffer to compose a XML payload of POST request */
	char cTemporary[0x400];

	/* Make variable instad of static-initialized, so the strstr() works on it */
	char pGP_ArrayI_pcAddrStr[R30_HTTP_LENGTH];

		strcpy (pGP_ArrayI_pcAddrStr, pGP_Array[i].pcAddrStr);

		/* <m_TokenFound> in perticular means that <cR30Token_Wrapped> is not NULL */
		if (m_TokenFound) 
		{
		char * pcHayStack = NULL;

			//strcpy (pGP_ArrayI_pcAddrStr, pGP_Array[i].pcAddrStr);

			if (NULL != (pcHayStack = strstr(pGP_ArrayI_pcAddrStr, "stok=")   ))
			{
				strcpy (pGP_ArrayI_pcAddrStr, pGP_Array[i].pcAddrStr);

				/* for all except very first and very specific inhabitor of <stok> */
				if (  2 != pGP_Array[i].iGetOrPost  )

					memcpy( pcHayStack, cR30Token_Wrapped, R30_TKN_LENGTH+R30_TKN_WRP_LENGTH );//TODO: fix; no TR0
			}
		}

		/* From now on let's work with <pGP_ArrayI_pcAddrStr> insted of <pGP_Array[i].pcAddrStr> */

		/* GET operations, no payload */
		if (0 == pGP_Array[i].iGetOrPost )
		{
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);

			iRes = curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr );
		}

		/* No payload POST operations */
		else if ( 1 == pGP_Array[i].iGetOrPost ) 
		{
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, 0/* "" cTemporary */);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0 /* (long)strlen(cTemporary)*/ );

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}
		/* Operation == login, payload ist must */
		else if (2 == pGP_Array[i].iGetOrPost )
		{
			/* We don't need no needle to be giving us a thrill */
			sprintf (cTemporary, "operation=login&password=%s", STUB0);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr );
		}

		/* Operation == read, vorbereiten */
		else if (1000 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=read");

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}

		/* Operation == load, vorbereiten */
		else if (1002 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=load");

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}

		/* Operation == load&path, vorbereiten */
		else if (1004 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=load&path=&uuid=06E7656ECAADDAAD31E883C869D713702e0F");

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}

		/* Operation == write, vorbereiten */
		else if (1006 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=write");

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}

		/* Operation == Druecker ausschalten */
		else if (303 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=write&enable=off");

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}

		/* Operation == druecker einschalten */
		else if (203 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=write&enable=on");

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}

		/* Operation == Flashspeicher ausschalten */
		else if (4 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=save&server=TPShare&enable=off%s2Coff%s2Coff%s2Coff&port=21", "%", "%", "%" );

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);


		}
		/* Operation == Flashspeicher ausschalten */
		else if (204 == pGP_Array[i].iGetOrPost )
		{
			sprintf (cTemporary, "operation=save&server=TPShare&enable=off%s2Coff%s2Coff%s2Con&port=21", "%", "%", "%" );

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cTemporary);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(cTemporary));

			curl_easy_setopt(curl, CURLOPT_URL, pGP_ArrayI_pcAddrStr);
		}

#if defined (RESPONCE_LATENCY_GAUGING)

		/* TODO: tongue-tied. rework. */

		/* Since the <iRecvClbk> is executed in separate thread we may get HTTP-responce-arrival values what are lower that HTTP-request-sending
		value so their subtraction (i.e. time difference we measure) will be negative. It's no a purpose, therefore we measure HTTP-request-sending
		value _before issuing the request. */

		/* Take current value as time of responce arrival into <stHttpResponce> structure */
		gettimeofday(&stHttpResponce, 0);

		/* Compute responce interval <dbRespInt> in microseconds */
		double dbRespInt = 1000000*(stHttpResponce.tv_sec - stHttpRequest.tv_sec) + stHttpResponce.tv_usec - stHttpRequest.tv_usec;

		memcpy ((void *)&stHttpRequest, (void *)&stHttpResponce, sizeof (struct timeval) ) ; 

		/* Filename variable */
		char cFileBuf[GAUGE_STRING_LEN];

		/* Store raw debug output into file */
		sprintf(cFileBuf,  "echo  \" prev. operation takes %9.3f milliseconds. Now doing operation <%s>\">> ./%s\n", dbRespInt/1000, pGP_ArrayI_pcAddrStr, RLG_FNAME);

		system (cFileBuf);

		/* Let's store all 'buig reproduced' cases into separate file */
		if (GAUGE_HTTP_THRESHOLD < dbRespInt/1000 )
		{
			/* On begin of life cycle the <pcAddrStr> will be null, but on that time the issue isn't reproducible. TODO: move word 'REPRODUCED' into header file */
			sprintf(cFileBuf,  "echo  \"REPRODUCED. %9.3f milliseconds: operation <%s>\">> ./%s.REPRODUCED\n", dbRespInt/1000, pcAddrStr, RLG_FNAME);

			printf("REPRODUCED. %9.3f milliseconds: operation <%s>\n ", dbRespInt/1000, pcAddrStr);

			system (cFileBuf);
		}

		/* Preserve current URL for next iteraion */
		strcpy ( pcAddrStr, pGP_ArrayI_pcAddrStr);	

		// TODO: 
		wr_index = 0;

#endif /* (RESPONCE_LATENCY_GAUGING) */

		iRes = curl_easy_perform(curl);

		i++;
	}

	return iRes;

} /* int iProcessArray(.  .  . )  */


#if defined (RESPONCE_LATENCY_GAUGING)

/* Not used. For a while */
size_t iRecvClbk(void *contents, size_t size, size_t nmemb, void *userp)
{
size_t realsize = size * nmemb;

	if ( R30_HTTP_CBK_BUF < wr_index + realsize )
	{
		*(int *)userp = 1;

		return 0;
	}

	/* Copy the data from the curl buffer into auto buffer */
	memcpy( (void *)&cBuffer[wr_index], contents, realsize );

	/* Update the write index */
	wr_index += realsize;

	/* Null terminate the buffer */
	cBuffer[wr_index] = 0;

	/* Tip: as the packet details' output may take up to few seconds we should measure time prior this output */

	return realsize;

} /* size_t iRecvClbk( . . . )  */

#endif /* (RESPONCE_LATENCY_GAUGING) */

void ComputeRSA()
{ 
char cNodeBuf[BASH_STRING_LEN], cRsaBuf[R30_RSA_LEN+1];

FILE * rsaFile;

	/* Be sure you've done <apt-get install node> <apt-get install nodejs> first */
	sprintf(cNodeBuf,  "%s ./%s >%s", INTERPRETER_FNAME, RSA_COMPUTER_FNAME, ENCR_FNAME);

	system (cNodeBuf);

	rsaFile = fopen(ENCR_FNAME, "r");

	if (NULL != rsaFile)
	{

		fflush(rsaFile);

		fscanf(rsaFile, "%s", cRsaBuf);

		fclose(rsaFile);
	}
	else
	{
		; /* do noting, we still may work wit pre-computed RSAs */
	}

	if (R30_RSA_LEN == strlen(cRsaBuf)  )

		/* Use freshest (valid) value */
		strcpy(STUB, cRsaBuf);
	else
		/* Use one of pre-computed values (they may appear to be not valid) */
		strcpy(STUB, STUB0);

} /* static void ComputeRSA( ) */



#if 0
//int kind_of_main (int argc, char **argv)
int _main (int argc, char **argv)
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

		int iRepeats = 1;;

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


			/* Let's open site. Mandatory for any other operation to be effective */
			iRes = iProcessArray(urlLib, (void *) aOpenArray);

			/* Let's sleep for a site to become stable */
			sleep (R30_GP_TMO);


			/* Here we have a change that <m_TokenFound> becomes 1 */
	
			/* Let's open first tab of site. Alegedly mandatory for any other operation to be effective */
			iRes = iProcessArray(urlLib, (void *) aAuthArray);

			/* Self-explanatory */
			printf("[%s] %s Site unlocked. Now can do _any operation\n", __FILE__, __func__); 




			/* To prevent libCURL from suppressing conventional output to '#2' */
			fflush(stderr);

			/* Let's deploy a duplication of <Gp aTab2Array[]> to see if it's necessary or not */
			iRes = iProcessArray(urlLib, (void *) aTab2Open_Array);

			/* Wait for system to stabilize */
			sleep (R30_TAB2_TMO);

			/* Self-explanatory */
			fprintf(stderr, "[%s] %s Competing Tab2-Open tested\n", __FILE__, __func__);

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

			/* Exit the site; let's not leave an opened backdoor after us. */
			iRes = iProcessArray(urlLib, (void *) aExitArray);

			/* Self-explanatory */
			printf("[%s] %s Site closed. No opetaion is allowed unless it's opened again next time\n", __FILE__, __func__); 

			/* Needed, cause libcurl may appear to retain the output */
			fflush(stdout);

		}

		/* Clean after ourselves */
		curl_easy_cleanup(urlLib);

	} /* if(urlLib) */


#if (EXTRA_PURITY)
	unlink (ENCR_FNAME);

	unlink (CKY_FNAME);

	unlink (TOKEN_FNAME);

	unlink (PASSWD_FNAME);
#endif /* (EXTRA_PURITY) */

	/* TODO: who will catch this return code. if noone then what's the point? */
	return R30_SUCCESS;

} /* int _main (int argc, char **argv) */


#endif /* (0) */
