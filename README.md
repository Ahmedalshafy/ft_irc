# 42-ft_IRC

An Internet Relay Chat (IRC) server implementation in C++98 for the 42 curriculum.

## Overview

This IRC server implements the core features of the IRC protocol, allowing multiple clients to connect, join channels, and communicate in real-time. The server supports both private messaging and channel-based communication.

## Features

- **User Authentication**
  - Password-based server authentication
  - Nickname registration and validation
  - User information management

- **Channel Operations**
  - Channel creation and joining
  - Channel modes (invite-only, key protected, etc.)
  - Operator privileges
  - Topic management
  - User limits

- **Messaging**
  - Private messages between users
  - Channel messages
  - Server notices and broadcasts

- **Command Support**
  - NICK: Change nickname
  - JOIN: Join channels
  - PART: Leave channels
  - PRIVMSG: Send messages
  - MODE: Change channel/user modes
  - KICK: Remove users from channels
  - INVITE: Invite users to channels
  - TOPIC: View/change channel topics
  - NOTICE: Send notices
  - QUIT: Disconnect from server

## Architecture

### Core Components

1. **Server (`Server.cpp`)**
   - Singleton pattern implementation
   - Connection management
   - Client message processing
   - Event loop using poll()
   - Socket I/O handling

2. **Channel (`Channel.cpp`)**
   - Channel state management
   - User permissions (operators, regular users)
   - Channel modes
   - Message broadcasting
   - Invitation system

3. **Client (`Client.cpp`)**
   - Client state management
   - Message buffering
   - Registration status tracking
   - Connection handling

4. **Message Parser (`ParseMessage.cpp`)**
   - IRC protocol message parsing
   - Command extraction
   - Parameter validation

### Command Handlers

Each IRC command is implemented in its own file for modularity:
- `privateMessage.cpp`: Handle private and channel messages
- `join.cpp`: Channel joining logic
- `kick.cpp`: User removal from channels
- `modeCommand.cpp`: Channel and user mode management
- `nickCommand.cpp`: Nickname changes
- `topicCommand.cpp`: Channel topic management

## Network Implementation

The server uses non-blocking I/O with poll() for efficient connection handling:
- Multiple client support through I/O multiplexing
- Asynchronous message processing
- Buffer management for partial receives
- Clean connection termination

## Building and Running

1. **Compile the server**:
   ```bash
   make
   ```

2. **Run the server**:
   ```bash
   ./ircserv <port> <password>
   ```
   - `port`: Port number for the server to listen on
   - `password`: Password required for client connections

3. **Connect with a client** (e.g., irssi):
   ```bash
   irssi -c localhost -p <port>
   ```
   Then authenticate:
   ```
   /PASS <password>
   /NICK <nickname>
   /USER <username> 0 * :<realname>
   ```

## IRC Protocol Implementation

### Message Format
Messages follow the IRC protocol format:
```
[:<prefix>] <command> [<parameters>...] [:<trailing>]
```

### Channel Modes
- `i`: Invite-only channel
- `t`: Protected topic
- `k`: Key required to join
- `o`: Operator privileges
- `l`: User limit

### Error Handling
- Invalid commands
- Permission violations
- Resource limits
- Protocol violations
- Connection issues

## Code Structure

```
.
├── SRC/
│   ├── Server.cpp      # Core server implementation
│   ├── Channel.cpp     # Channel management
│   ├── Client.cpp      # Client handling
│   ├── Commands/       # Command implementations
│   │   ├── join.cpp
│   │   ├── kick.cpp
│   │   ├── mode.cpp
│   │   └── ...
│   └── Utils/         # Utility functions
├── Includes/
│   ├── Server.hpp
│   ├── Channel.hpp
│   └── ...
└── bircd/            # Low-level networking
    ├── init_env.c
    ├── client_read.c
    └── ...
```

## Testing

Test the server using:
1. Multiple simultaneous clients
2. Different IRC clients (irssi, WeeChat, etc.)
3. Various command combinations
4. Edge cases (disconnections, invalid commands)
5. Load testing with multiple channels and users

## Contributors
- [List of contributors]
