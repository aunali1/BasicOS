#!/bin/sh

###############################################################################
#	BasicOS Kernel Host Patches Script				      #
#									      #
# 	License:							      #
#	BasicOS Operating System - An experimental operating system	      #
#	Copyright (C) 2015 Aun-Ali Zaidi and its contributors.		      #
#									      #
#	This program is free software: you can redistribute it and/or modify  #
#	it under the terms of the GNU General Public License as published by  #
#	the Free Software Foundation, either version 3 of the License, or     #
#	(at your option) any later version.				      #
#									      #
#	This program is distributed in the hope that it will be useful,	      #
#	but WITHOUT ANY WARRANTY; without even the implied warranty of	      #
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the	      #
#	GNU General Public License for more details.			      #
#									      #
#	You should have received a copy of the GNU General Public License     #
#	along with this program. If not, see <http://www.gnu.org/licenses/>.  #
###############################################################################

platform='unknown'
uname=$(uname)
if [[ "$uname" == 'Linux' ]]; then
	platform='linux'
elif [[ "$uname" == 'Darwin' ]]; then
	platform='macos'
elif [[ "$uname" == 'SunOS' ]]; then
	platform='solaris'
fi

if [[ $platform == 'solaris' ]]; then
	patch < ./scripts/solaris.patch
fi
