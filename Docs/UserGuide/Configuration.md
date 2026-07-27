# Configuration

**Configure one entry per server map using each map's full Unreal package name.** Local Launch ports are derived from list order, so reordering entries changes the assigned ports.

## Project Settings location

Open:

```text
Project Settings > Project > Servers
```

The **Server List** contains these fields:

- **Map Name** — the exact full map package name.
- **Server Address** — the address returned by Project Setting mode.

## Full map package names

Use the long package name, not only the asset name.

**OK example:**

```text
/Game/Maps/Lobby
```

**NG example:**

```text
Lobby
```

The full package name matters because the Blueprint lookup compares the configured map name with the map's long package name.

## Server modes

- **Project Setting** returns the configured `Server Address` for the matching map.
- **Local Launch** starts every configured entry at PIE begin and returns a loopback address for the matching list position.

## Port assignment

Local Launch uses fixed base port `7777` and increments once per Server List entry:

```text
Entry 0: /Game/Maps/Lobby -> 7777
Entry 1: /Game/Maps/Match -> 7778
Entry 2: /Game/Maps/Results -> 7779
```

**Reordering entries changes Local Launch ports.** Keep list order stable when another part of the project expects a particular port.

Before launch, the plugin checks all required UDP ports. If any port is unavailable, it stops the launch before starting a partial server group.

## Configuration example

```text
Server List
  Map Name: /Game/Maps/Lobby
  Server Address: lobby.example.test:9001

  Map Name: /Game/Maps/Match
  Server Address: match.example.test:9002
```

The addresses above apply to Project Setting mode. In Local Launch mode, the matching entries resolve to `127.0.0.1:7777` and `127.0.0.1:7778`.
