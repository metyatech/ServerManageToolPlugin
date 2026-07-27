# Blueprint API

**Use `GetServerAddress(Map)` to resolve an address; use `RequestServerExit()` only from the dedicated server process that should exit.** The plugin does not perform client travel or automatic connection.

## GetServerAddress(Map)

Blueprint node: **Get Server Address**

### GetServerAddress inputs

- `Map` — a map asset reference. The lookup uses its full Unreal package name.

### GetServerAddress output

- `String` — the configured server address, or the Local Launch loopback address for that map's Server List position.

### GetServerAddress behavior

- In Project Setting mode, returns the matching `Server Address`.
- In Local Launch mode, returns `127.0.0.1:<port>`.
- The first Server List entry uses `7777`; each later entry increments the port.

### GetServerAddress failure behavior

Returns an empty string and logs an error when `Map` is null or no exact map entry exists.

### GetServerAddress example

```text
Address = Get Server Address(Map = Lobby)
Connect using Address in the project's own client flow.
```

### GetServerAddress safety notes

- Configure the map using its full package name, such as `/Game/Maps/Lobby`.
- Treat the returned string as an address for your own connection code.
- The node does not connect the client automatically.

## RequestServerExit()

Blueprint node: **Request Server Exit**

### RequestServerExit inputs

- None.

### RequestServerExit output

- None. The node requests exit from the current process.

### RequestServerExit behavior

Requests the current process's main loop to exit. It is intended for a dedicated server process.

### RequestServerExit failure behavior

The request is delivered to the current process. The plugin does not promise a specific operating-system exit code and does not provide a retry or restart mechanism.

### RequestServerExit example

```text
On server shutdown command
  -> Request Server Exit
```

### RequestServerExit safety notes

**Do not call this node casually from a client.** It requests exit for the current process, so use it only in the dedicated-server side of the project when that process is ready to stop.
