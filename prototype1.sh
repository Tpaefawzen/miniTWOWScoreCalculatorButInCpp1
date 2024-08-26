#!/bin/sh

################################################################################
#
# prototype1.sh
#
################################################################################

# boilerplate
set -eu
umask 0022
export LC_ALL=C
if _path="$( command -p getconf PATH 2>/dev/null )"; then
	export PATH="$_path${PATH+:}${PATH:-}"
fi
export UNIX_STD=2003
export POSIXLY_CORRECT=1 POSIX_ME_HARDER=1

# @function usage
# @description Shows usage of this utility to stderr.
#
usage(){
	cat 1>&2 <<-USAGE
	Usage: ${0##*/} [-0|-1|-2] [-n RESPONSES] [FILE]
	       ${0##*/} [-0|-1|-2] [-nRESPONSES] [FILE]
	Flags: [-0|-1|-2] Specifies when duplicated vote is found; e.g. ABCDEFA
	       -0 The vote shall be invalid.
	       -1 Highest one is counted.
	       -2 Lowest one is counted.
	Operands: RESPONSES Number of responses. When not specified, assumed from input.
	          FILE Newline-separated list of votes.
USAGE
}

# @function die
# @synopsis {die} [{status}] {message} ...
# @param {status} exit status; default is 1.
# @param {message} to be output.
# @description Shows diagnostic message to exit.
