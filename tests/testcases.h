// Test 1: Single command without arguments

echo "Executing a single command without arguments..."
echo "/bin/ls" | ./hsh
echo

// Test 2: Single command with one argument

echo "Executing a single command with one argument..."
echo "/bin/ls -l" | ./hsh
echo

// Test 3: Single command with multiple arguments

echo "Executing a command with multiple arguments..."
echo "/bin/ls -la" | ./hsh
echo

// Test 4: Invalid command

echo "Executing an invalid command..."
echo "invalid_command" | ./hsh
echo

// Test 5: Command with an invalid argument

echo "Executing a command with an invalid argument..."
echo "/bin/ls --invalid_arg" | ./hsh
echo

// Test 6: End of file (Ctrl+D) test

echo "Simulating Ctrl+D (End of File)..."
printf "/bin/ls" | ./hsh
echo

// Test 7: Testing for Memory Loss 

echo "Memory"
printf valgrind ./hsh
