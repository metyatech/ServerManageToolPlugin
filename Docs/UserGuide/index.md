# Server Manage Tool User Guide

**Use this guide to configure map-specific addresses and safely launch all configured local server entries during PIE.** Local Launch is an editor workflow; it is not a production deployment system.

Version: **1.1.2**

## What this plugin does

Server Manage Tool provides Project Settings for a map-to-server-address list, a Server Mode menu in the editor Play menu, and Blueprint functions for resolving addresses and requesting server exit.

In Local Launch mode, the plugin checks every required UDP port before starting any process. This prevents a partially launched server group when a configured port is unavailable.

## Features

- Map-specific server address configuration.
- Project Setting and Local Launch modes.
- Local dedicated-server process launch at PIE begin.
- Server List order mapped to ports starting at `7777`.
- Runtime detection when a server binds a different port.
- PIE-end and module-shutdown cleanup.
- `Get Server Address` and `Request Server Exit` Blueprint functions.

## Ten-step quick start

1. Open `Project Settings > Project > Servers`.
2. Add one `Server List` entry per server map.
3. Enter each map's full Unreal package name.
4. Enter the address for Project Setting mode.
5. Save the project settings.
6. Open the Unreal Editor Play menu.
7. Open **Server Mode**.
8. Select **Project Setting** or **Local Launch**.
9. Use `Get Server Address` in your own connection flow.
10. Review Output Log markers when Local Launch fails or a runtime port mismatch is detected.

## Guide pages

- [Installation](Installation.md)
- [Configuration](Configuration.md)
- [Blueprint API](BlueprintAPI.md)
- [Local Launch](LocalLaunch.md)
- [Troubleshooting](Troubleshooting.md)
- [Release notes](ReleaseNotes.md)

## Scope

This guide covers the plugin's editor configuration, local PIE server lifecycle, and Blueprint API. It does not document building, deploying, hosting, or operating a production dedicated server. Version 1.1.2 was verified on UE 5.8 Win64 with a Blueprint-only host, a real C++ game project in Development and Shipping, and packaged Development and Shipping `AddressAndExit` runs. A dedicated `TargetType.Server` executable is not provided or verified.

For the latest online copy, see the [central documentation](https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/).
