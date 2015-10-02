#! /bin/bash

KEYRING="keyring-test"
KEYRING_PWD="keyring_pwd"
SECRET="secret"
CLIRING="./cliring"
ATTRIBUTE1="app:test"
ATTRIBUTE2="user:m026839"
TOTAL_TESTS=0
SUCCESS=0

######## UTILS ########
function incTotal()
{
  TOTAL_TESTS=$(($TOTAL_TESTS + 1))
}

function incSuccess()
{
  SUCCESS=$(($SUCCESS + 1))
}

function on_success()
{
  echo -n "$1 "
  echo -e "\e[32mOK\e[39m"
  incSuccess
}

function on_failure()
{
  echo -n "$1 "
  echo -e "\e[31mKO\e[39m"
}

#######################

function test_add_keyring()
{
  # Counting keyrings before the add
  keyring_count=$($CLIRING list | wc -l)

  #Creating a new keyring. We use expect to provide the password
  expect << EOF > /dev/null
  spawn $CLIRING create -k $KEYRING
    expect "Enter the new keyring password:"
    send -- "$KEYRING_PWD\r"
    expect eof
EOF

  # Counting keyrings after the add
  count=$($CLIRING list | wc -l)

  # If we have one more keyring after the add
  incTotal
  if [ $(($keyring_count + 1)) -ne $count ]; then
    on_failure "Keyring add : number of keyrings"
  else
    on_success "Keyring add : number of keyrings"
  fi

  #If our keyring name is found in the list
  incTotal
  $CLIRING list | grep "^$KEYRING$" > /dev/null
  if [ $? -eq 0 ]; then
    on_success "Keyring add : keyring name"
  else
    on_failure "Keyring add : keyring name"
  fi
}

function test_delete_keyring()
{
  # Counting keyrings before the delete
  keyring_count=$($CLIRING list | wc -l)

  # Deleting the keyring
  $CLIRING delete -k $KEYRING

  # Counting keyrings after the delete
  count=$($CLIRING list | wc -l)

  # If we have one less keyring after the delete
  incTotal
  if [ $(($keyring_count - 1)) -ne $count ]; then
    on_failure "Keyring delete : number of keyrings"
  else
    on_success "Keyring delete : number of keyrings"
  fi

  # If our keyring name is not found in the list
  incTotal
  $CLIRING list | grep -v "^$KEYRING$" > /dev/null
  if [ $? -eq 0 ]; then
    on_success "Keyring delete : keyring name"
  else
    on_failure "Keyring delete : keyring name"
  fi
}

function test_lock_unlock()
{
  $CLIRING lock -k $KEYRING

  incTotal
  # If the unlock doesn't prompt for password, keyring wasn't locked correctly
  expect << EOF > /dev/null
  set timeout 1
  spawn $CLIRING unlock -k $KEYRING
  expect {
    timeout {exit 1}
    "Enter the keyring password:" {send -- "$KEYRING_PWD\r"}
  }
  expect eof
EOF

if [ $? -eq 0 ]; then
  on_success "Keyring lock"
else
  on_failure "Keyring lock"
fi

  incTotal
  # If unlock prompt for password, keyring wasn't unlocked correctly
  expect << EOF > /dev/null
  set timeout 1
  spawn $CLIRING unlock -k $KEYRING
  expect {
    "Enter the keyring password:" {exit 1}
  }
  exit 0
EOF

if [ $? -eq 0 ]; then
  on_success "Keyring unlock"
else
  on_failure "Keyring unlock"
fi

}

function test_store_get_password()
{
    # Storing a password
  incTotal
  expect << EOF
  set timeout 1
  spawn $CLIRING store -k $KEYRING -n secret -a $ATTRIBUTE1 -a $ATTRIBUTE2
  expect {
    timeout {exit 1}
    "Enter the password you want to store:" {send -- "$SECRET\r"}
  }
  expect eof
EOF

  if [ $? -eq 0 ]; then
    on_success "Password storage"
  else
    on_failure "Password storage"
  fi

  # Display the password
  incTotal

  # We check that the keyring will not prompt for password before the actual recovery
  expect << EOF > /dev/null
  set timeout 1
  spawn $CLIRING get -k $KEYRING -a $ATTRIBUTE1 -a $ATTRIBUTE2
  expect {
    timeout {exit 1}
    eof
  }
EOF

  if [ $? -ne 0 ]; then
    on_failure "Password recovery"
  else
    RESULT=$($CLIRING get -k $KEYRING -a $ATTRIBUTE1 -a $ATTRIBUTE2)
    if [ "$RESULT" = "$SECRET" ]; then
      on_success "Password recovery"
    else
      on_failure "Password recovery"
    fi
  fi
}

test_add_keyring
test_lock_unlock
test_store_get_password
test_delete_keyring

echo "$SUCCESS / $TOTAL_TESTS"
