#!/bin/bash

source ./.scripts/.source.sh

INSTRUCTION=$(cat ./.instruction.log)
TOTAL_FILES=0
COMPILED_FILES=0

if [ "$INSTRUCTION" -eq 1 ]; then
	TOTAL_FILES=$(find ./mandatory -type f -name "*.c" | wc -l)
	COMPILED_FILES=$(find ./build/mandatory -type f -name "*.o" | wc -l)
elif [ "$INSTRUCTION" -eq 2 ]; then
	TOTAL_FILES=$(find ./bonus -type f -name "*.c" | wc -l)
	COMPILED_FILES=$(find ./build/bonus -type f -name "*.o" | wc -l)
elif [ "$INSTRUCTION" -eq 3 ]; then
	TOTAL_FILES=$(( $(find ./mandatory -type f -name "*.c" | wc -l) + $(find ./bonus -type f -name "*.c" | wc -l) ))
	COMPILED_FILES=$(find ./build -type f -name "*.o" | wc -l)
fi

PROGRESS=$((COMPILED_FILES * 100 / TOTAL_FILES))
R=$((255 - (255 * PROGRESS / 100)))
G=$((255 * PROGRESS / 100))
COLOR="\033[38;2;${R};${G};0m"

FILLED_LENGTH=$((PROGRESS * 50 / 100))
BAR=$(printf "%0.s█" $(seq 1 $FILLED_LENGTH))
EMPTY=$(printf "%0.s " $(seq 1 $((50 - FILLED_LENGTH))))

printf "${HIDE_CURSOR}${ERASE_LINE}${COLOR}|${BAR}${EMPTY}| [${PROGRESS}%%] (${COMPILED_FILES}/${TOTAL_FILES})${RESET}"

if [ "$COMPILED_FILES" -eq 0 ] || [ "$COMPILED_FILES" -eq "$TOTAL_FILES" ]; then
	printf "${ERASE_LINE}${SHOW_CURSOR}"
fi