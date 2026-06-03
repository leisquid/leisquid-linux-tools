#!/bin/bash

##  utf16-file-replace.sh - batch replace content in UTF-16LE text files
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

STRING_TO_FIND=''
STRING_TO_REPLACE=''

usage() {
    echo "$0 - batch replace content in UTF-16LE text files

Summary:
    This is a Shell script that finds and replaces a specific string in all text
    files encoded in UTF-16LE with BOM in the current directory.

Usage:
    $0 find_str replace_str
    $0 -h|--help

Output:
    When a UTF-16LE encoded text file containing the string to be searched for
    is found, a message including path of this file will be printed.
    Of course, no files outputted if no strings found.

Returns:
    0 for operation successfully; 1 for wrong argument(s).

Author:
    leisquid_tianyi_li

Licensing:
    AGPLv3+ license"
}

main() {
    echo "Your OS type is ${OSTYPE}". > /dev/stderr
    case "${OSTYPE}" in
        "linux-gnu")
            echo "GNU sed style command will be executed.
" > /dev/stderr
            ;;
        *)
            echo "BSD sed style command will be executed.
" > /dev/stderr
            ;;
    esac

    STRING_TO_FIND=$1
    STRING_TO_REPLACE=$2

    fileList=$(find . -type f)
    for singleFile in ${fileList}
    do
        file ${singleFile} | grep "UTF-16" > /dev/null
        if [ $? = 0 ]; then
            iconv -f UTF-16 -t UTF-8 ${singleFile} | grep "${STRING_TO_FIND}" > /dev/null
            if [ $? != 0 ]; then
                continue
            fi
            echo "Found UTF-16 text file: ${singleFile}"
            echo -ne '\xff\xfe' > "${singleFile}.tmp"
            iconv -f UTF-16 -t UTF-8 ${singleFile} > "${singleFile}.utf-8.tmp"
            case "${OSTYPE}" in
                "linux-gnu")
                    sed -i "s/${STRING_TO_FIND}/${STRING_TO_REPLACE}/g" "${singleFile}.utf-8.tmp"
                    ;;
                *)
                    sed -i '' "s/${STRING_TO_FIND}/${STRING_TO_REPLACE}/g" "${singleFile}.utf-8.tmp"
                    ;;
            esac
            iconv -f UTF-8 -t UTF-16LE "${singleFile}.utf-8.tmp" >> "${singleFile}.tmp"
            rm "${singleFile}.utf-8.tmp"
            mv "${singleFile}.tmp" ${singleFile}
        fi
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
