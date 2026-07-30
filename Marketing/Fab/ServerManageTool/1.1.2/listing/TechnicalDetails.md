# Technical Details

## Product identity

| Field | Value |
| --- | --- |
| Product | Server Manage Tool |
| Current version | 1.1.2 |
| Plugin descriptor version | 4 |
| Engine version | Unreal Engine 5.8 |
| Verified platform | Win64 |
| Distribution | Unreal Engine Code Plugin |
| Source code included | Yes |
| Precompiled Win64 Editor binaries included | Yes |
| Documentation included | Yes |
| Third-party dependencies | None detected |
| Fab category | Tools & Plugins |
| Fab subcategory | Network & Multiplayer |
| Fab license | Fab Standard License |
| Publisher | metyatech |

## Package composition

| Field | Verified value |
| --- | ---: |
| Unreal plugin modules | 3 |
| Editor modules | 1 |
| Runtime modules | 2 |
| Source files | 17 |
| C++ source files | 7 |
| Header files | 7 |
| Build.cs files | 3 |
| UCLASS declarations | 3 |
| USTRUCT declarations | 1 |
| BlueprintCallable functions | 2 |
| Plugin content files in public release ZIP | 1 |
| Packaged documentation files | 1 |
| Public release ZIP file count | 34 |
| Public release ZIP bytes | 169,758 |
| Public release ZIP uncompressed bytes | 350,308 |

Network Replication: Not provided by the plugin.

The three modules are:

- ServerModePlayMenu — Editor module for the Server Mode menu, PIE lifecycle, local process launch, UDP preflight, and managed cleanup.
- ServerInfoSettingsModule — Runtime module for server-list settings data.
- ServerManageLibrary — Runtime module for the Blueprint address and exit API plus runtime port validation.

## Blueprint API

- Get Server Address — pure and callable Blueprint function in the Server Management category. It resolves the configured address or the Local Launch loopback address for the map.
- Request Server Exit — callable Blueprint function in the Server Management category. It requests exit from the current process and is intended for the dedicated-server side of the project.

## Runtime behavior

- Project Setting mode returns the configured Server Address for the matching map.
- Local Launch starts all configured entries during PIE, in Server List order.
- Local Launch assigns ports from fixed base port 7777.
- The plugin preflights every required UDP port before creating a managed process.
- If a required port is unavailable, the launch attempt is rejected without a partial managed group.
- Each managed process receives an expected port and is checked against its actual bound port.
- End PIE and module shutdown clear the managed process collection.
- Client connection or travel remains the responsibility of the project.

## Dependencies and compatibility

- No third-party dependency was detected in the Build.cs dependency lists or the public release package.
- The verified host matrix includes a Blueprint-only host and real C++ game-project Development and Shipping integration.
- A dedicated TargetType.Server executable is not included or verified.
- The package is not a server hosting service and does not provide deployment infrastructure.
