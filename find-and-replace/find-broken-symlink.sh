#!/bin/bash

##  find-broken-symlink.sh - find broken symbolic link
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


PATH_TO_FIND=""

usage() {
    echo "$0 - find broken symbolic link

Summary:
    This is a Shell script that finds broken symbolic links in current directory
    or any directory you specify.
    The link named \`-h\` or \`--help\` will not be found because it will be
    seen as an option.

Usage:
    $0 filename ext_string
    $0 -h|--help
    $0 -- -h|--help         ## if your symlink to find named -h|--help

Output:
    \`ls -l --color=always --classify\` these broken symlink.
    No any output if no file found.

Returns:
    0 for operation successfully; other value for external program error.

Author:
    leisquid_tianyi_li

Licensing:
    AGPLv3+ license"
}

main() {
    for singleFile in $(find ${PATH_TO_FIND} -type l ! -exec test -e {} \; -print 2>/dev/null); do
        ${LS_COMMAND} ${singleFile}
    done
}

case "$OSTYPE" in
    linux-gnu*)
        LS_COMMAND="ls -l --color=always --classify"
        ;;
    *)
        LS_COMMAND="ls -FGl"
        ;;
esac

case $1 in
    '-h'|'--help')
        usage $@
        ;;
    --)
        case $2 in
            '')
                PATH_TO_FIND='./'
                main
                ;;
            *)
                PATH_TO_FIND=$2
                main
                ;;
        esac
        ;;
    '')
        PATH_TO_FIND='./'
        main
        ;;
    *)
        PATH_TO_FIND=$1
        main
        ;;
esac
