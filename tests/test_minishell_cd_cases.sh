#!/bin/bash
# test_minishell_cd_exit_cases.sh

echo "Testing Bash exit command:"

./minishell << EOF
cd headers
EOF
echo "Exit status: $?"

./minishell << EOF
cd bobo
EOF
echo "Exit status: $?"

./minishell << EOF
unset HOME
cd ~
EOF
echo "Exit status: $?"

./minishell << EOF
cd headers
cd unset OLDPWD
cd -
EOF
echo "Exit status: $?"

