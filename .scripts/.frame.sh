#!/bin/bash

source ./.scripts/.source.sh

frame_lines=(
	"		     +--------------------------+"
	"		     |                          |"
	"		     |       ${RED}✠    ✠    ✠${YELLOW}        |"
	"		     |                          |"
	"		     |            ${WHITE}By${YELLOW}            |"
	"		     |                          |"
	"		     |   ${WHITE}- Crusader ${BLUE}adesille${YELLOW}    |"
	"		     |   ${WHITE}- Templar  ${BLUE}aheitz ${YELLOW}     |"
	"		     |                          |"
	"		     |       ${RED}✠    ✠    ✠${YELLOW}        |"
	"		     |                          |"
	"		     +--------------------------+"
)

printf "${NEWLINE}"

for i in "${!frame_lines[@]}"; do
	printf "$YELLOW"
	line="${frame_lines[$i]}"
	length=${#line}
	current_line=""
	for ((i = 0; i < length; i++)); do
		char="${line:i:1}"
		current_line="${current_line}${char}"
		if [ "$char" != "	" ]; then
			sleep 0.01
			printf "${CARRIAGE_RETURN}${current_line}${ERASE}${RESET}🖋️${YELLOW}"
		fi
	done
	printf "${CARRIAGE_RETURN}${current_line}${ERASE}${NEWLINE}"
done

printf "${RESET}${SHOW_CURSOR}"