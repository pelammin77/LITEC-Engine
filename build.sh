#!/bin/bash

CONFIG=${1:-debug}

echo "Generating Makefiles with Premake5..."
premake5 gmake2

build_config() {
    echo "Building configuration: $1"
    make config=$1
}

case "$CONFIG" in
    debug)
        build_config debug
        ;;
    release)
        build_config release
        ;;
    all)
        build_config debug
        build_config release
        ;;
    *)
        echo "Unknown configuration: $CONFIG"
        echo "Usage: ./build.sh [debug|release|all]"
        exit 1
        ;;
esac
