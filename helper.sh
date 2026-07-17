#!/usr/bin/env bash

LANG_CHOICE="$1"
MODULE_CHOICE="$2"
ACTION_CHOICE="$3"

TAB=$'\t'
BOLD="\033[1m"
RED="\033[1;31m"
RESET="\033[0m"

yes_arg() {
    (( $# == 3 ))
}

first_arg_check() {
    case "$1" in
        csharp|go|java|native|nodejs|python) return 0 ;;
        *) echo -e "${RED}Error:${RESET} Invalid Language '$1'"; return 1 ;;
    esac
}

second_arg_check() {
    case "$1" in
        all|cli|client|common|master|server) return 0 ;;
        *) echo -e "${RED}Error:${RESET} Invalid Module '$1'"; return 1 ;;
    esac
}

third_arg_check() {
    case "$1" in
        build|copy|package|setup|test) return 0 ;;
        *) echo -e "${RED}Error:${RESET} Invalid Action '$1'"; return 1 ;;
    esac
}

no_arg() {
    (( $# == 0 ))
}

if no_arg "$@"; then
    echo -e "${BOLD}Verteilen Helper${RESET}"
    echo "bash helper.sh [Language] [Module] [Action] [Arguments...]"
    echo ""
    echo "Language:"
    echo "${TAB}csharp - Build C# solutions"
    echo "${TAB}go - Build Golang solutions"
    echo "${TAB}java - Build Java solutions"
    echo "${TAB}native - Build C/C++ solutions"
    echo "${TAB}nodejs - Build NodeJS solutions"
    echo "${TAB}python - Build Python solutions"
    echo ""
    echo "Module:"
    echo "${TAB}all - Targeting all the modules"
    echo "${TAB}cli - Targeting CLI modules"
    echo "${TAB}client - Targeting Client modules"
    echo "${TAB}common - Targeting Core modules"
    echo "${TAB}master - Targeting Master modules"
    echo "${TAB}server - Targeting Server modules"
    echo ""
    echo "Action:"
    echo "${TAB}build - Build the library and executable"
    echo "${TAB}copy - Copy the resources"
    echo "${TAB}package - Packing the resources"
    echo "${TAB}setup - Setup project files"
    echo "${TAB}test - Start the testing"
    echo ""
    echo "Arguments:"
    exit 0
fi

if ! yes_arg "$@"; then
    echo -e "${RED}Error:${RESET} Missing required arguments. Expected at least 3."
    echo "Usage: bash helper.sh [Language] [Module] [Action] [Arguments...]"
    exit 1
fi

if ! first_arg_check "$1" || ! second_arg_check "$2" || ! third_arg_check "$3"; then
    exit 1
fi

shift 3
EXTRA_ARGS="$@"

cd "scripts/${LANG_CHOICE}" || { echo "Directory not found"; exit 1; }

bash "${ACTION_CHOICE}.sh" ${MODULE_CHOICE} ${EXTRA_ARGS}