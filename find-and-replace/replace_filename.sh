#!/bin/bash

##  replace_filename.sh - replace the filename for all matched file
##
##  Copyright (c) 2023-26 Leisquid Tianyi Li.
##
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU Affero General Public License as
##  published by the Free Software Foundation, either version 3 of the
##  License, or (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU Affero General Public License for more details.
##
##  You should have received a copy of the GNU Affero General Public License
##  along with this program.  If not, see <https://www.gnu.org/licenses/>.

usage() {
    echo "$0 - replace the filename for all matched file

Summary:
    This is a Shell script that finds all matched filename in current directory,
    and replaces its name with a new specified name.

Usage:
    $0 old_filename new_filename
    $0 -h|--help

Output:
    \` * Renamed: old_name -> new_name\`
    No any output if no file found.

Returns:
    0 for operation successfully; 1 for wrong argument(s).

Author:
    leisquid_tianyi_li

Licensing:
    AGPLv3+ license"
}

main() {
    old_filename=$1
    new_filename=$2
    find . -name "${old_filename}" -print0 | while read -r -d '' singleFile; do
        dir=$(dirname "${singleFile}")
        full_new_filename="${dir}/${new_filename}"
        i=1
        while [ -e "${full_new_filename}" ]; do
            full_new_filename="${dir}/${new_filename}_${i}"
            ((i++))
        done
        mv "${singleFile}" "${full_new_filename}"
        echo " * Renamed: ${singleFile} -> ${new_filename}"
    done
}

if [ $# = 2 ]; then
    main $@
elif [ $# = 1 ]; then
    case $1 in
        '-h'|'--help')
            usage $@
            exit 0
            ;;
        *)
            echo "You are asking help because you have given one invalid argument for this script!
    " > /dev/stderr
            usage $@ > /dev/stderr
            exit 1
            ;;
    esac
else
    echo "You are asking help because you have not given any valid argument for this
script!
" > /dev/stderr
    usage $@ > /dev/stderr
    exit 1
fi
exit 0
