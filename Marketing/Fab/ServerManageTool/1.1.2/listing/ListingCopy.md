# Server Manage Tool — Fab Listing Copy

## Title

Server Manage Tool

## Short description

Configure map-specific server addresses and launch managed local server groups during Unreal Engine PIE with all-port preflight, port validation, and cleanup.

## Long description

### What it does

Server Manage Tool is an Unreal Engine code plugin for mapping server addresses to maps and launching a project’s local dedicated-server processes during Play In Editor (PIE). It is an editor workflow for projects that already support running their own game with the Unreal Engine server argument.

Before Local Launch starts any managed process, the plugin checks every UDP port required by the configured Server List. If one required port is unavailable, the complete launch attempt is rejected and no partial managed server group is started. When launch succeeds, the plugin records the expected ports, validates the ports actually bound by the server processes, and requests server exit when a mismatch is detected.

### Key features

- Map-specific server address entries in Project Settings at Project Settings > Project > Servers.
- Project Setting mode for returning the configured address for a matching map.
- Local Launch mode for starting one local server process per configured Server List entry at PIE begin.
- Sequential Local Launch port assignment from fixed base port 7777, following Server List order.
- All-port UDP preflight before a Local Launch process is created.
- All-or-nothing launch behavior when a required UDP port is unavailable.
- Runtime expected-versus-actual port validation for managed server processes.
- Cleanup of managed Local Launch processes at End PIE and during module shutdown.
- Two Blueprint nodes: Get Server Address and Request Server Exit.

### Typical workflow

1. Open Project Settings > Project > Servers.
2. Add one Server List entry for each server map.
3. Enter each map’s full Unreal package name, such as /Game/Maps/Lobby.
4. Enter the address to return in Project Setting mode.
5. Open the Unreal Editor Play menu and select Server Mode.
6. Choose Project Setting or Local Launch.
7. Start PIE.
8. Use Get Server Address in the project’s own client connection or travel flow.
9. End PIE to release the managed Local Launch processes.

For Local Launch, the first Server List entry uses 127.0.0.1:7777 and each later entry increments the port by one. The plugin checks the complete required port set before it starts the group.

### Blueprint API

Get Server Address takes a map asset reference and returns the configured address in Project Setting mode. In Local Launch mode it returns the matching loopback address based on the map’s Server List position. A null map or a missing exact map entry returns an empty string and writes an error to the log.

Request Server Exit requests exit from the current process. It is intended for the dedicated-server side of a project that is ready to stop. It does not provide a client connection flow, a retry mechanism, or a guaranteed operating-system exit code.

### Requirements and scope

- Unreal Engine 5.8 is the verified engine version.
- Win64 is the verified platform for version 1.1.2.
- The project must have a valid .uproject and must already support its own -server behavior.
- Map entries must use full Unreal package names.
- Local Launch requires the Unreal Editor executable used by the project.
- The package is verified with a Blueprint-only host and with real C++ game-project Development and Shipping integration paths.

This product is an Editor/PIE workflow. It does not add a TargetType.Server executable and does not build, package, deploy, or host production servers. It does not automatically connect clients, perform health checks, retry failed starts, restart processes, select individual entries, or shift the fixed base port.

### Source and release transparency

The source repository and prebuilt release files are publicly accessible. The repository does not grant an open-source license.

Purchases through Fab are provided under the Fab Standard License and directly support continued development and maintenance.

- Source repository: https://github.com/metyatech/ServerManageToolPlugin
- Public release files: https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip
- Published release SHA-256: C1A043C3388520446DAB93B40FEFD6CE0E05F87D94544BB28A14B98098601443

### Documentation and support

- Online documentation: https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/
- Support and issue tracker: https://github.com/metyatech/ServerManageToolPlugin/issues
- The package includes a Quick Start file under Content/ServerManageTool/Documentation/QuickStart.txt.

When reporting an issue, include the plugin version, Unreal Engine version, selected Server Mode, sanitized Output Log markers, and the relevant Server List configuration. Remove credentials, private project data, production addresses, and machine-specific information before sharing logs.

## Changelog for 1.1.2

- Verified UE 5.8 Win64 package and real C++ game-project Development and Shipping integration paths.
- Retained map-specific Project Setting and Local Launch workflows.
- Retained all-port UDP preflight and all-or-nothing Local Launch behavior.
- Retained requested-versus-actual runtime port validation and managed cleanup.
- Retained the Get Server Address and Request Server Exit Blueprint API.
- Updated release and provenance documentation without changing product behavior or the Blueprint API.
