#!/bin/bash
# test_bash_cd_exit_cases.sh

echo "Testing Bash exit command:"

bash << EOF
cd headers
EOF
echo "Exit status: $?"

bash << EOF
cd bobo
EOF
echo "Exit status: $?"

bash << EOF
unset HOME
cd ~
EOF
echo "Exit status: $?"

bash << EOF
cd headers
cd unset OLDPWD
cd -
EOF
echo "Exit status: $?"
