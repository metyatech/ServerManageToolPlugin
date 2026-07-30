# Server Manage Tool — Fab Listing Copy

## Title

Server Manage Tool

## Short description

Configure server addresses per map and launch all configured local servers from Unreal Engine PIE with all-port preflight, port validation, and cleanup.

## Long description

### What it does

Server Manage Tool is an Unreal Engine code plugin for projects that need a repeatable local server workflow during Play In Editor (PIE). Configure an address for each map, choose how addresses should be resolved, and use the plugin to launch and clean up the configured local server group.

Your project must already support running its game with Unreal Engine's `-server` argument.

**Project Setting** returns the address configured for each map without launching local server processes.

**Local Launch** starts every configured Server List entry during PIE and returns matching loopback addresses beginning at `127.0.0.1:7777`.

Before Local Launch starts any managed process, the plugin checks every UDP port required by the Server List. If one required port is unavailable, the complete launch attempt is rejected and no partial managed server group is started. After launch, the plugin compares each expected port with the port actually bound by the process and records the validation result.

### Key features

- Map-specific server addresses in Project Settings > Project > Servers.
- Project Setting and Local Launch address modes.
- One local server process per configured Server List entry during Local Launch.
- Sequential Local Launch ports beginning at fixed base port `7777`.
- All-port UDP preflight before any managed process starts.
- All-or-nothing launch behavior when a required port is unavailable.
- Expected-versus-actual port validation for managed server processes.
- Managed-process cleanup at End PIE and during module shutdown.
- Blueprint nodes for `Get Server Address` and `Request Server Exit`.
- Source code, precompiled Win64 Editor binaries, and documentation included.

### Typical workflow

1. Configure maps and addresses under Project Settings > Project > Servers.
2. Choose Project Setting or Local Launch from the Server Mode menu.
3. Start PIE.
4. Pass `Get Server Address` to your project's own connection or travel flow.
5. End PIE to stop the managed Local Launch processes.

### Blueprint API

**Get Server Address**

Takes a map asset reference and returns:

- the configured address in Project Setting mode;
- the matching loopback address in Local Launch mode; or
- an empty string and an error log when the map is null or no exact entry exists.

The node returns an address string only. Client connection and travel remain the responsibility of the project.

**Request Server Exit**

Requests exit from the current process. Use it only from the server process that should stop. The plugin does not guarantee a specific operating-system exit code.

### Requirements and compatibility

- Verified with Unreal Engine 5.8 on Win64.
- The project must have a valid `.uproject`.
- The project must already support its intended `-server` behavior.
- Server List maps must use full Unreal package names, such as `/Game/Maps/Lobby`.
- Local Launch requires the Unreal Editor executable used by the project.
- The packaged plugin has been verified in a Blueprint-only host and in real C++ game-project Development and Shipping integration paths.

### Scope and limitations

- Local Launch is available only in the Editor during PIE.
- The base port is fixed at `7777`, and later ports follow Server List order.
- All configured entries launch as one group; selective launch and automatic port shifting are not provided.
- Client connection, gameplay networking and replication, health checks, retry, and automatic restart remain the responsibility of the project.
- The plugin does not build, package, deploy, or host production servers.
- A dedicated `TargetType.Server` executable is not included.

### Source and release transparency

The source repository and prebuilt releases are publicly accessible for inspection. The repository does not grant an open-source license. Purchases through Fab are provided under the Fab Standard License and support continued development and maintenance.

- Source repository: https://github.com/metyatech/ServerManageToolPlugin
- Public releases: https://github.com/metyatech/ServerManageToolPlugin/releases

### Documentation and support

- Documentation: https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/
- Support and issue tracker: https://github.com/metyatech/ServerManageToolPlugin/issues
- A Quick Start file is included in the plugin package.

When reporting an issue, include the plugin version, Unreal Engine version, selected Server Mode, relevant Server List configuration, reproduction steps, and sanitized `SMT_*` Output Log markers.

### Current release: 1.1.2

Verified for Unreal Engine 5.8 on Win64. Version 1.1.2 updates package verification and documentation without changing product behavior or the Blueprint API.
