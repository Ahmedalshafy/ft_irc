# IRC Server Test Guide

This document provides a comprehensive set of tests for the IRC server. Each test includes the commands to run and expected results.

## Prerequisites

1. Install an IRC client (e.g., irssi):
```bash
sudo apt-get install irssi
```

2. Start the IRC server:
```bash
./ircserv 6667 password123
```

## Test Categories

### 1. Connection and Authentication Tests

#### 1.1 Basic Connection
```bash
# Connect to server
irssi -c localhost -p 6667

# Register with server
/PASS password123
/NICK testuser1
/USER testuser1 0 * :Test User 1
```
Expected: Server accepts connection and responds with welcome message

#### 1.2 Invalid Password
```bash
/PASS wrongpassword
/NICK testuser2
/USER testuser2 0 * :Test User 2
```
Expected: Server rejects connection with error message

### 2. Channel Operations

#### 2.1 Create and Join Channel
```bash
# Create new channel
/JOIN #testchannel

# Verify channel creation
/LIST
```
Expected: Channel #testchannel is created and user becomes operator

#### 2.2 Channel Modes
```bash
# Set channel as invite-only
/MODE #testchannel +i

# Set channel key (password)
/MODE #testchannel +k secretkey

# Set user limit
/MODE #testchannel +l 10

# View channel modes
/MODE #testchannel
```
Expected: Channel modes are set and displayed correctly

#### 2.3 Topic Management
```bash
# Set channel topic
/TOPIC #testchannel :Welcome to the test channel!

# View topic
/TOPIC #testchannel
```
Expected: Topic is set and can be viewed by channel members

### 3. User Management

#### 3.1 Multiple Users (Use different terminals)
```bash
# Terminal 1
/NICK user1
/JOIN #testchannel

# Terminal 2
/NICK user2
/JOIN #testchannel secretkey  # If channel has key set
```
Expected: Both users can join and see each other

#### 3.2 Operator Commands
```bash
# Grant operator status
/MODE #testchannel +o user2

# Kick user
/KICK #testchannel user2 :Reason for kick

# Remove operator status
/MODE #testchannel -o user2
```
Expected: Operator commands execute successfully

### 4. Messaging Tests

#### 4.1 Channel Messages
```bash
# Send message to channel
/MSG #testchannel Hello everyone!
```
Expected: All channel members receive the message

#### 4.2 Private Messages
```bash
# Send private message
/MSG user2 Hello, this is a private message
```
Expected: Only target user receives the message

### 5. Edge Cases and Error Handling

#### 5.1 Invalid Commands
```bash
# Try to kick from channel without operator status
/KICK #testchannel user1

# Try to join non-existent channel
/JOIN #nonexistent

# Try to message non-existent user
/MSG nonexistent Hello
```
Expected: Appropriate error messages for each case

#### 5.2 Channel Restrictions
```bash
# Test invite-only channel
/MODE #testchannel +i
/NICK user3
/JOIN #testchannel  # Should fail without invite

# Test user limit
/MODE #testchannel +l 2
/NICK user4
/JOIN #testchannel  # Should fail if channel is full
```
Expected: Server enforces channel restrictions properly

### 6. Advanced Features

#### 6.1 Multiple Channel Management
```bash
# Join multiple channels
/JOIN #channel1
/JOIN #channel2

# Send messages to different channels
/MSG #channel1 Message for channel 1
/MSG #channel2 Message for channel 2
```
Expected: Messages are delivered to correct channels

#### 6.2 Channel Key Changes
```bash
# Change channel key
/MODE #testchannel +k newkey

# Try old key
/JOIN #testchannel secretkey  # Should fail

# Try new key
/JOIN #testchannel newkey  # Should succeed
```
Expected: Key changes are enforced correctly

### 7. Stress Testing

#### 7.1 Multiple Operations
```bash
# Rapid channel switching
/JOIN #channel1
/JOIN #channel2
/PART #channel1
/JOIN #channel3
/PART #channel2

# Rapid messaging
/MSG #channel3 Message 1
/MSG user2 Private message
/MSG #channel3 Message 2
```
Expected: Server handles rapid operations without issues

## Test Verification

After each test:
1. Check server logs for proper handling
2. Verify client received appropriate responses
3. Ensure other users see expected messages/changes
4. Confirm channel state is correct

## Common Issues and Debugging

1. Connection Issues:
   - Verify server is running
   - Check port number
   - Ensure password is correct

2. Permission Issues:
   - Verify user has operator status when needed
   - Check channel modes

3. Message Delivery:
   - Confirm users are in the correct channels
   - Check nickname registration

## Clean Up

After testing:
```bash
# Leave all channels
/PART #channel1
/PART #channel2
/PART #channel3

# Disconnect from server
/QUIT :Testing complete
```
