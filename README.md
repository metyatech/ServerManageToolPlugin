# Server Manage Tool

**Server Manage Tool maps server addresses to Unreal maps and launches local dedicated-server processes during Play In Editor.** It does not build or deploy a production server.

## Overview

Configure one server entry per map, choose how the editor should resolve server addresses, and use the Blueprint API from your own connection flow.

## Features

- **Map-specific server address configuration** in Project Settings.
- **Project Settings integration** at `Project Settings > Project > Servers`.
- **Project Setting mode** for configured server addresses.
- **Local Launch mode** for local dedicated-server processes during PIE.
- **All-port UDP preflight** before Local Launch.
- **All-or-nothing launch** when a configured port is unavailable.
- **Shifted-port runtime detection** through the expected-port validator.
- Cleanup at PIE end and during editor module shutdown.
- Blueprint functions `Get Server Address` and `Request Server Exit`.

## Requirements

- Unreal Engine 5.8 Win64 is the supported verification target for version 1.1.0.
- The project must already support running its game with `-server`.
- A valid `.uproject` and maps with full Unreal package names are required.
- Local Launch requires the Unreal Editor executable used by the project.

## Installation

### Fab installation

Install the plugin through Fab for the Unreal Engine version used by your project. Enable **Server Manage Tool** in `Edit > Plugins`, then restart the editor when requested.

### Project plugin installation

For a source or locally copied package, place the plugin folder at:

```text
<Project>/Plugins/ServerManageTool
```

Enable it in the editor and restart the editor before using the Server Mode menu.

## Quick Start

1. Open `Project Settings > Project > Servers`.
2. Add one `Server List` entry per server map.
3. Enter each map's full package name, such as `/Game/Maps/Lobby`.
4. Enter the address used by Project Setting mode.
5. Open the Unreal Editor Play menu.
6. Open **Server Mode**.
7. Select **Project Setting** or **Local Launch**.
8. Call `Get Server Address` from your own connection flow.
9. For a dedicated server process, call `Request Server Exit` only when that process should exit.
10. Review the Output Log markers if a local server does not start or binds a different port.

Local Launch assigns ports from the `Server List` order, beginning at fixed base port `7777`. It checks all configured ports first and starts no partial server group when any required port is unavailable.

## Documentation

- [User guide](Docs/UserGuide/index.md)
- [Online documentation](https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/)
- [Quick Start in the packaged Content folder](Content/ServerManageTool/Documentation/QuickStart.txt)

## Support

Open an issue with the project Unreal Engine version, plugin version, selected mode, relevant map configuration, and the relevant Output Log markers.

- [GitHub issues](https://github.com/metyatech/ServerManageToolPlugin/issues)

## Limitations

- Local Launch is an **Editor/PIE-only** workflow.
- The Local Launch base port is fixed at `7777`.
- Port assignment follows `Server List` order.
- Local Launch launches all configured entries.
- The plugin does not connect the client automatically.
- The project must already support `-server`.
- The plugin does not build, package, deploy, or host a production server.
- Do not rely on a specific operating-system exit code after shifted-port detection.
- Real game-project Development/Shipping integration and packaged dedicated-server executable behavior remain unverified.

## Version

**1.1.0** adds UDP preflight, atomic all-or-nothing Local Launch, shifted-port validation, editor delegate cleanup, module-shutdown server cleanup, and Fab package documentation structure.
