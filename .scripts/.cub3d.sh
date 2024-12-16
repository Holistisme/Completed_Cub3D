#!/bin/bash

source ./.scripts/.source.sh

lines=(
    "   .+------+     +------+     +------+     +------+     +------+."
    " .' |      |    /|      |     |      |     |      |\    |      | \`."
    "+   | ${YELLOW} C ${GREEN}  |   + | ${YELLOW} U ${GREEN}  |     +  ${YELLOW} B ${GREEN} +     | ${YELLOW} 3 ${GREEN}  | +   | ${YELLOW} D ${GREEN}  |   +"
    "|   |      |   | |      |     |      |     |      | |   |      |   |"
    "|  .+------+   | +------+     +------+     +------+ |   +------+.  |"
    "|.'      .'    |/      /      |      |      \      \|    \`.      \`.|"
    "+------+'      +------+       +------+       +------+      \`+------+"
)

printf "${HIDE_CURSOR}${GREEN}"

for i in "${lines[@]}"; do
	printf "%s${NEWLINE}" "$i"
	sleep 0.2
done