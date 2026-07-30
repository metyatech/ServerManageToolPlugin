# Listing copy

## Thumbnail

**Server Manage Tool**

Reliable Local Server Workflows for Unreal Engine PIE

Map-specific addresses • all-port preflight • managed cleanup

Verified on UE 5.8 Win64

## Gallery 01 — Project Settings

**Configure Your Server List**

Map each Unreal level to the address your project should use.

Project Settings > Project > Servers

`/Game/Maps/Lobby`

`/Game/Maps/Match`

Install as a project-local plugin: `YourProject / Plugins / ServerManageTool`

## Gallery 02 — Blueprint API

**Resolve Server Addresses in Blueprint**

- Project Setting returns the configured address
- Local Launch returns loopback ports starting at 7777
- Null or missing maps return an empty string

Request Server Exit should only be used in the server process.

## Gallery 03 — Local Launch

**Launch the Complete Local Server Group**

Every required UDP port is checked before any managed process starts.

Lobby — Requested 7777 — Actual 7777 — Validated

Match — Requested 7778 — Actual 7778 — Validated

`SMT_PORT_PREFLIGHT_PASSED`

Ports Available means the required UDP ports were available before launch.

`SMT_PORT_VALIDATION_PASSED`

Validated means the requested and actual bound ports matched.

Actual UE 5.8 Local Launch evidence

## Gallery 04 — Port Conflict

**Prevent Partial Launches**

If one required port is unavailable, no managed server from that launch attempt is started.

7778 unavailable

`SMT_PORT_PREFLIGHT_FAILED`

Managed children: 0

No port shifting or partial launch is implied.

## Gallery 05 — Cleanup and Scope

**Clean Editor Testing Workflows**

Managed server processes stop when PIE ends and are cleared during module shutdown.

Start PIE → 2 managed servers → End PIE → 0 managed processes → 0 UDP owners

Actual post-End PIE cleanup evidence

Editor / PIE only

Does not build, deploy, or host production servers.

A dedicated `TargetType.Server` executable is not included.

## Claim audit

All six blocks are classified `CLAIMS_ACCURATE`. The evidence is limited to UE 5.8 Win64 Editor/PIE runs, the project-local plugin package, Project Settings address lookup, port preflight, expected/actual validation, and cleanup observations. No block claims production hosting, deployment, health checks, retry, automatic restart, automatic port shifting, or guaranteed OS exit status.
