
help () {
    echo "COMMANDS:"
    echo "   build        - build the project"
    echo "   clean-build  - build the project from a clean state"
    echo "   refresh      - refresh cmake project"
    echo "   help         - print this"
}

if [[ $# -lt 1 ]]; then
    echo "expected a command"
    help
    exit 1
fi

COMMAND=$1
ARGS=${@:2:$#-1}

if [[ $COMMAND == "build" ]]; then
    cmake --build build/ $ARGS
elif [[ $COMMAND == "clean-build" ]]; then
    cmake --build build/ --clean-first $ARGS
elif [[ $COMMAND == "refresh" ]]; then
    cmake -B build $ARGS -Wno-author
elif [[ $COMMAND == "help" ]]; then
    help
else
    echo "error: invalid command \`$COMMAND\`"
    echo "note: try \`$0 help\`"
fi
