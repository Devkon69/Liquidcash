 #!/usr/bin/env bash

 # Execute this file to install the liquidcash cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Liquidcash-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Liquidcash-Qt.app/Contents/MacOS/liquidcashd /usr/local/bin/liquidcashd
 sudo ln -s ${LOCATION}/Liquidcash-Qt.app/Contents/MacOS/liquidcash-cli /usr/local/bin/liquidcash-cli
