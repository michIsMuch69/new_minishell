#!/bin/bash
# test_ft_exit_cases.sh

echo "Testing custom ft_exit function:"

./minishell << EOF
exit 0
EOF
echo "Exit status: $?"

./minishell << EOF
exit 1
EOF
echo "Exit status: $?"

./minishell << EOF
exit 42
EOF
echo "Exit status: $?"

./minishell << EOF
exit 255
EOF
echo "Exit status: $?"

./minishell << EOF
exit
EOF
echo "Exit status: $?"

./minishell << EOF
exit abc
EOF
echo "Exit status: $?"

./minishell << EOF
exit 256
EOF
echo "Exit status: $?"

./minishell << EOF
exit -1
EOF
echo "Exit status: $?"

./minishell << EOF
exit 1000
EOF
echo "Exit status: $?"

./minishell << EOF
pwd
exit
EOF
echo "Exit status: $?"

# ./minishell << EOF
# cd headers
# EOF
# echo "Exit status: $?"