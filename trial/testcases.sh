# Test 1: Single command without arguments
echo "Executing a single command without arguments..."
echo "/bin/ls" | ./trial
echo

# Test 2: Single command with one argument
echo "Executing a single command with one argument..."
echo "/bin/ls -l" | ./trial
echo

# Test 3: Single command with multiple arguments
echo "Executing a command with multiple arguments..."
echo "/bin/ls -la" | ./trial
echo

# Test 4: Invalid command
echo "Executing an invalid command..."
echo "invalid_command" | ./trial
echo

# Test 5: Command with an invalid argument
echo "Executing a command with an invalid argument..."
echo "/bin/ls --invalid_arg" | ./trial
echo

# Test 6: Multiple commands in sequence (Note: Your shell needs to handle this properly)
echo "Executing multiple commands in sequence..."
{
    echo "/bin/ls";
    echo "echo Hello, World!";
} | ./trial
echo

# Test 7: Commands with special characters (assuming you want to handle them)
echo "Executing commands with special characters..."
echo "echo * | grep shell" | ./trial
echo

# Test 8: End of file (Ctrl+D) test
echo "Simulating Ctrl+D (End of File)..."
printf "/bin/ls" | ./trial
echo

# Test 9: Print Environment Path
echo "Test 1: Print Environment Path"
echo "echo \$PATH" | ./trial
echo

# Test 10: Use 'ls' command
echo "\nTest 2: Use 'ls' command"
echo "ls" | ./trial
echo

# Test 11: Use 'ls' with full path
echo "\nTest 3: Use 'ls' with full path"
echo "/bin/ls" | ./trial
echo

# Test 12: 'ls' with an argument
echo "\nTest 4: 'ls' with an argument"
echo "ls -la" | ./trial
echo

# Test 13: Change directory and then list
echo "\nTest 5: Change directory and then list"
echo "cd ..\nls" | ./trial
echo

# Test 14: Testing for Memory
echo "Memory"
printf valgrind ./trial