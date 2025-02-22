#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "cd changes directory correctly" {
    run ./dsh <<EOF
cd bats
pwd
EOF

    # Assertions
    [ "$status" -eq 0 ]
	 [[ "$output" =~ "bats" ]]
}

@test "exit command works" {
    run ./dsh <<EOF
exit
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "cd without commands works correctly" {
    current="$(pwd)"
    run ./dsh <<EOF
cd
pwd
exit
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="${current}dsh2>dsh2>dsh2>"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "mistyped command handled correctly" {
    run ./dsh <<EOF
cddd
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="forkfailed:Nosuchfileordirectorydsh2>dsh2>dsh2>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
}

@test "handles lots of spaces" {
    run "./dsh" <<EOF
   echo      " hello     world     "
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '\t\n\r\f\v')

    # Expected output with all whitespace removed for easier matching
    expected_output=" hello     world     dsh2>dsh2> cmd loop returned 0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}
