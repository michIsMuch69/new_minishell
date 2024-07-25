#!/bin/bash
# test_bash_exit_cases.sh

echo "Testing Bash exit command:"

bash << EOF
exit 0
EOF
echo "Exit status: $?"

bash << EOF
exit 1
EOF
echo "Exit status: $?"

bash << EOF
exit 42
EOF
echo "Exit status: $?"

bash << EOF
exit 255
EOF
echo "Exit status: $?"

bash << EOF
exit
EOF
echo "Exit status: $?"

bash << EOF
exit abc
EOF
echo "Exit status: $?"

bash << EOF
exit 256
EOF
echo "Exit status: $?"

bash << EOF
exit -1
EOF
echo "Exit status: $?"

bash << EOF
exit 1000
EOF
echo "Exit status: $?"

bash << EOF
pwd
exit
EOF
echo "Exit status: $?"

# bash << EOF
# cd headers
# EOF
# echo "Exit status: $?"