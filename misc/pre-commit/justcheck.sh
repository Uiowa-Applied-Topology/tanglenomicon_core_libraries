#!/bin/sh

# Prevent commit if 'just lint' recipe fails.
echo $PWD
just
if ! just check; then
    echo "Pre-commit check failed!"
    exit 1
fi
