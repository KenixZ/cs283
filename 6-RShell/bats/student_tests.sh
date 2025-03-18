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
    expected_output="${current}localmodedsh4>dsh4>dsh4>"

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
    expected_output="execvp:Nosuchfileordirectorylocalmodedsh4>localmodedsh4>dsh4>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
}

@test "c files" {
    run "./dsh" <<EOF
ls | grep .c
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="dsh_cli.cdshlib.crsh_cli.crsh_server.clocalmodedsh4>dsh4>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "number of files" {
    run "./dsh" <<EOF
ls | wc -l
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="10localmodedsh4>dsh4>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

