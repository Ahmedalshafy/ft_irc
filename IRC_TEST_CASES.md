# IRC Server Test Cases

This document contains test cases for the IRC server implementation. Each test case includes the commands to run using `nc` (netcat) and explanations of the expected behavior.

## Basic Setup
To connect to the server using netcat:
```bash
nc localhost 4242
```

## Test Categories

### 1. Connection and Authentication
#### Test 1.1: Basic Connection with Valid Password
```bash
PASS your_password
NICK user1
USER user1 0 * :Real Name
```
**Expected Behavior:**
- Server should accept the connection
- Server should send welcome messages
- Client should be registered successfully

#### Test 1.2: Invalid Password
```bash
PASS wrongpassword
NICK user2
USER user2 0 * :Real Name
```
**Expected Behavior:**
- Server should reject the connection
- Error message should be sent to client
- Connection should be closed

### 2. Channel Operations
#### Test 2.1: Create and Join Channel
```bash
PASS your_password
NICK user3
USER user3 0 * :Real Name
JOIN #testchannel
```
**Expected Behavior:**
- Channel should be created if it doesn't exist
- User should be made channel operator
- Server should send JOIN confirmation
- Server should send channel topic (if set)
- Server should send list of users in channel

#### Test 2.2: Channel Modes
```bash
# Set channel as invite-only
MODE #testchannel +i

# Set channel key (password)
MODE #testchannel +k secretkey

# Set user limit
MODE #testchannel +l 10

# Give/take operator status
MODE #testchannel +o nickname
```
**Expected Behavior:**
- Server should confirm mode changes
- Mode changes should be effective immediately
- Only operators should be able to change modes

### 3. Private Messages
#### Test 3.1: User to User Message
```bash
# First terminal (User1):
PASS your_password
NICK user1
USER user1 0 * :Real Name

# Second terminal (User2):
PASS your_password
NICK user2
USER user2 0 * :Real Name
PRIVMSG user1 :Hello there!
```
**Expected Behavior:**
- Message should be delivered to user1
- If user1 doesn't exist, appropriate error should be sent

#### Test 3.2: Channel Message
```bash
PRIVMSG #testchannel :Hello everyone!
```
**Expected Behavior:**
- Message should be broadcast to all channel members
- If not in channel, appropriate error should be sent

### 4. Invite Command
#### Test 4.1: Basic Invite
```bash
# As channel operator:
INVITE user2 #testchannel
```
**Expected Behavior:**
- Invited user should receive invite notification
- Only channel operators can invite
- Cannot invite to non-existent channels

### 5. Error Cases
#### Test 5.1: Invalid Nickname
```bash
NICK @invalid
```
**Expected Behavior:**
- Server should reject invalid nickname
- Appropriate error message should be sent

#### Test 5.2: Join Protected Channel
```bash
# Try joining without key
JOIN #protected

# Try joining with wrong key
JOIN #protected wrongkey
```
**Expected Behavior:**
- Server should reject both attempts
- Appropriate error messages should be sent

### 6. Channel Communication
#### Test 6.1: Multiple Users Interaction
```bash
# Terminal 1:
PASS your_password
NICK user1
USER user1 0 * :Real Name
JOIN #testchannel
PRIVMSG #testchannel :Hello everyone!

# Terminal 2:
PASS your_password
NICK user2
USER user2 0 * :Real Name
JOIN #testchannel
PRIVMSG #testchannel :Hi user1!
```
**Expected Behavior:**
- Both users should receive all messages
- JOIN/PART notifications should be sent to all channel members

## Running the Tests
1. Start your IRC server
2. Open multiple terminal windows for different clients
3. Use `nc localhost 4242` to connect
4. Copy and paste the commands from each test case
5. Verify the server responses match the expected behavior

## Notes
- Replace `your_password` with your actual server password
- Some commands may need operator privileges
- Server responses may vary slightly but should convey the same information
- All error cases should return appropriate numeric replies as per IRC protocol
