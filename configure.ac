#
# Copyright (C) 2018 ARNERI arneri@ukr.net All rights reserved
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#  Abstract: config & build file for PBI3 projecct



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



AC_SUBST(BUILD_CURL, $BUILD_CURL)

AC_SUBST(PLATFORM, $(uname -s))

AC_SUBST(INSTALL_OPTIONS, $INSTALL_OPTIONS)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
