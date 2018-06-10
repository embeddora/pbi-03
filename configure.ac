#
# Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#        * Redistributions of source code must retain the above copyright
#          notice, this list of conditions and the following disclaimer.
#        * Redistributions in binary form must reproduce the above copyright
#          notice, this list of conditions and the following disclaimer in the
#          documentation and/or other materials provided with the distribution.
#        * Neither the name of The Linux Foundation nor
#          the names of its contributors may be used to endorse or promote
#          products derived from this software without specific prior written
#          permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Abstract: config & build file for PBI3 projecct
#
# Usage:               none
#
# Version:             0.0.2
#



AC_INIT("pbi" project's, ver. 3.0)

AC_MSG_NOTICE([Preparing single 'configure' file for application: "PBI3" (Post Browser Interface 3)])

echo "Testing a compiler"
AC_PROG_CC
AC_LANG(C)

cu_in_h=1
AC_CHECK_HEADERS(curl/curl.h, [], [cu_in_h=0])
if test $cu_in_h == 0
then
	AC_MSG_NOTICE([curl/curl.h is missing.])
	echo 1>&2 "** check libcurl headers (suggested: sudo apt-get install libcurl4-gnutls-dev)"
	exit -1
else
	AC_MSG_NOTICE([curl/curl.h is present])
fi


cu_in_l=1
AC_CHECK_LIB(curl, curl_easy_init, [], [cu_in_l=0])
if test $cu_in_l == 0
then
	AC_MSG_NOTICE([libcurl.a items fail.])
	echo 1>&2 "** install libcurl (suggested: sudo apt-get install libcurl4-gnutls-dev)"
	exit -1

else
	AC_MSG_NOTICE([libcurl.a items found working.])
fi

sdl2_in_h=1
AC_CHECK_HEADERS(SDL2/SDL.h, [], [sdl2_in_h=0])
if test $sdl2_in_h == 0
then
	AC_MSG_NOTICE([SDL2/SDL.h is missing.])
	echo 1>&2 "** check libSD2 headers (suggested: sudo apt-get install libsdl2-dev)"
	exit -1
else
	AC_MSG_NOTICE([SDL/SDL2.h is present])
fi


sdl2_in_l=1
AC_CHECK_LIB(SDL2, SDL_Init, [], [sdl2_in_l=0])
if test $sdl2_in_l == 0
then
	AC_MSG_NOTICE([libSDL2.a items fail.])
	echo 1>&2 "** install libSDL2 (suggested: sudo apt-get install libsdl2-dev)"
	exit -1

else
	AC_MSG_NOTICE([libsdl2 items found working.])
fi


AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([boost/foreach.hpp], [], [AC_MSG_ERROR(You need the Boost libraries. Suggested: sudo apt-get install libboost-thread-dev.  )])
AC_LANG_POP([C++])


AC_SUBST(BUILD_CURL, $BUILD_CURL)

AC_SUBST(PLATFORM, $(uname -s))

AC_SUBST(INSTALL_OPTIONS, $INSTALL_OPTIONS)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
