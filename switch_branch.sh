#!/bin/bash

CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)

if [[ "$CURRENT_BRANCH" == "main" ]]; then
    echo "Current branch is main. Switching to dev..."

    if git rev-parse --verify dev >/dev/null 2>&1; then
        git checkout dev
    else
        git checkout -b dev
        echo "Created new dev branch."
        git push -u origin dev
    fi

elif [[ "$CURRENT_BRANCH" == "dev" ]]; then
    echo "Current branch is dev. Switching to main..."
    git checkout main
else
    echo "You're on branch: $CURRENT_BRANCH"
    echo "Switching only supported between 'main' and 'dev'."
fi
