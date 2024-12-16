#!/bin/bash

source ./.scripts/.source.sh

if [ -e "./.warnings.log" ]; then
	while IFS= read -r line; do
		if [[ "$line" =~ ^(.+):([0-9]+):([0-9]+):\ (warning|note|error):\ (.+)$ ]]; then
			FILE="${CYAN}${BASH_REMATCH[1]}${RESET}"
			POSITION="${YELLOW}${BASH_REMATCH[2]}:${BASH_REMATCH[3]}${RESET}"
			TYPE="${RED}${BASH_REMATCH[4]}${RESET}"
			MESSAGE="${WHITE}${BASH_REMATCH[5]}${RESET}"
			echo -e "${FILE}:${POSITION}: ${TYPE}: ${MESSAGE}"
		else
			echo "$line"
		fi
	done < "./.warnings.log"
	rm -f "./.warnings.log"
fi