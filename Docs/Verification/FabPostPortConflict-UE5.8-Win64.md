# Fab post-port-conflict verification — UE 5.8 Win64

## 1. Scope and verdict

This report covers the Local Launch UDP port-conflict fail-fast change on the
existing `fix/ue58-uht-categories` baseline. The implementation was built and
exercised on a real UE 5.8 Windows installed build.

The requested fail-fast behavior is implemented and the two requested
preflight conflict cases pass. The normal Local Launch lifecycle passes. The
direct race guard detects an Unreal Engine port shift and emits the required
failure marker, but UE 5.8 `UnrealEditor.exe` returns exit code `0` after
`FPlatformMisc::RequestExitWithStatus(false, 2, ...)`; therefore the direct
mismatch acceptance criterion requiring clean exit code `2` is not fully met.
No forceful exit was added to mask this engine behavior.

Fab release readiness remains `FAIL`. This change does not add package content,
configuration, user documentation, release metadata, or a Fab submission.

## 2. Start gate

| Item | Result |
| --- | --- |
| Repository | `D:\ghws\ServerManageToolPlugin` |
| Origin | `https://github.com/metyatech/ServerManageToolPlugin` |
| Starting branch | `fix/ue58-uht-categories` |
| Starting local and remote HEAD | `5f5ddd543ace8b34cec71141aa83e63fa55faaa7` |
| Starting divergence | `0 0` |
| Starting working tree | clean |
| UE root | `C:\Program Files\Epic Games\UE_5.8` |
| Build.version | MajorVersion `5`, MinorVersion `8`, PatchVersion `0` |
| Installed build marker | `Engine\Build\InstalledBuild.txt` present |
| Implementation branch | `fix/port-conflict-fail-fast` |

The implementation branch was created directly from the verified starting
HEAD. No existing branch was reset, rebased, merged, or amended.

## 3. Source changes

Only the following permitted source files changed:

- `Source/ServerModePlayMenu/ServerModePlayMenu.Build.cs` — add the `Sockets`
  dependency.
- `Source/ServerModePlayMenu/Public/ServerModePlayMenu.h` — add the
  notification helper declaration.
- `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp` — add the RAII UDP
  bind preflight, unavailable-port notification, pass/fail markers, and atomic
  launch rollback.
- `Source/ServerModePlayMenu/Private/ServerProcess.h` — add requested-port
  state, `IsValid()`, and `GetRequestedPort()`.
- `Source/ServerModePlayMenu/Private/ServerProcess.cpp` — add the expected-port
  argument, private log category, and launch-failure marker with map, port,
  executable, and project details.
- `Source/ServerManageLibrary/ServerManageLibrary.Build.cs` — add the
  `Sockets` dependency.
- `Source/ServerManageLibrary/Public/ServerManageLibrary.h` — add the core
  ticker state and validator declarations.
- `Source/ServerManageLibrary/Private/ServerManageLibrary.cpp` — add the
  dedicated-server-only expected-port parser and actual `GameNetDriver`
  validation ticker.

No `ServerInfoSettings`, Blueprint, uplugin, Config, Content, README, CI, port
scheme, map-port mapping, delegate, or unrelated source file was changed.

## 4. Behavior implemented

### Editor preflight

At `BeginPIE`, Local Launch probes every configured port starting at `7777` in
server-list order. Each probe uses
`ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)`, `CreateUniqueSocket`, an
any-address UDP endpoint, `SetReuseAddr(false)`, and `Bind`. The unique socket
owns its cleanup through UE's socket RAII type.

If any port is unavailable, no server process is created. The error log emits
`SMT_PORT_PREFLIGHT_FAILED` with the complete unavailable-port list, and an
interactive nonmodal Slate notification is shown only after checking Slate
initialization and unattended mode.

If every port is available, exactly one
`SMT_PORT_PREFLIGHT_PASSED` marker is emitted for the configured range and
count. Server processes are then created in list order. If any `ServerProcess`
is invalid, all already-created processes are destroyed and no later process
is created.

### Child process launch

The existing `-Port=<requested>` argument is preserved and each child now also
receives `-ServerManageExpectedPort=<requested>`. `CreateProc` failures emit
`SMT_SERVER_PROCESS_LAUNCH_FAILED` with map, requested port, executable, and
project values. `IsValid()` reports only `ProcessHandle.IsValid()`.

### Dedicated-server validation

`ServerManageLibrary` registers a `0.1` second core ticker only when running as
a dedicated server and only when `ServerManageExpectedPort=` is present. It
waits without a fixed timeout until a dedicated world has a `GameNetDriver`
with a known local address. A matching port emits
`SMT_PORT_VALIDATION_PASSED`; a mismatch emits
`SMT_PORT_VALIDATION_FAILED` and calls
`FPlatformMisc::RequestExitWithStatus(false, 2, ...)`. The validator does not
force-exit, fatal, abort, follow a shifted port, or terminate a parent or other
server. The ticker is removed on either result and during module shutdown.

## 5. BuildPlugin and package

The reproducible command was:

```powershell
RunUAT.bat BuildPlugin `
  -Plugin=D:\ghws\ServerManageToolPlugin\ServerManageTool.uplugin `
  -Package=D:\T\SMTPF-20260723-180419\P `
  -TargetPlatforms=Win64 -Rocket
```

Results from `D:\T\SMTPF-20260723-180419\BuildPlugin.log`:

| Gate | Result |
| --- | --- |
| UAT exit code | `0` |
| UnrealEditor Win64 Development | `Result: Succeeded` |
| UnrealGame Win64 Development | `Result: Succeeded` |
| UnrealGame Win64 Shipping | `Result: Succeeded` |
| UHT Category errors | `0` |
| path-length errors over 260 | `0` |
| `BUILD SUCCESSFUL` | present |

Final package checks:

- `ServerManageTool.uplugin` present at package root.
- `Binaries\Win64` present.
- `UnrealEditor.modules` present.
- uplugin modules: `ServerModePlayMenu`, `ServerInfoSettingsModule`,
  `ServerManageLibrary`.
- binary module names match those three modules.
- package uplugin SHA-256:
  `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146`.
- package `.modules` SHA-256:
  `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274`.

## 6. Blueprint-only clean load

The fresh host used the new package and enabled all three plugin modules. The
command was:

```powershell
pwsh -NoLogo -NoProfile -File `
  D:\T\SMTPF-20260723-180419\BlueprintLoad\RunBlueprintOnlyCleanExit.ps1
```

| Check | Result |
| --- | --- |
| Blueprint compatibility marker | `PASS` |
| exit code | `0` |
| timeout | `false` |
| forced cleanup | `false` |
| final host process count | `0` |
| enabled plugin modules | `3` |
| plugin missing/incompatible module evidence | none |

The host log contains normal UE diagnostic lines, but no plugin missing-module,
incompatible-module, compile, fatal, ensure, or crash failure.

## 7. Local Launch lifecycle

The lifecycle host used the Local Launch configuration with two server entries
at `7777` and `7778`. Each mode was run once with the same new package:

```powershell
pwsh -NoLogo -NoProfile -File D:\T\SMTPF-20260723-180419\LifecycleLocal\RunLifecycle.ps1 -Mode PIE
pwsh -NoLogo -NoProfile -File D:\T\SMTPF-20260723-180419\LifecycleLocal\RunLifecycle.ps1 -Mode SIMULATE
pwsh -NoLogo -NoProfile -File D:\T\SMTPF-20260723-180419\LifecycleLocal\RunLifecycle.ps1 -Mode ORPHAN
```

| Mode | Harness status | Parent exit | Timeout | Max child servers | Preflight pass | Launch failures | Final parent/child |
| --- | --- | ---: | --- | ---: | ---: | ---: | --- |
| PIE | `PASS` | `0` | no | `2` | `1` | `0` | `0 / 0` |
| Simulate | `PASS` | `0` | no | `2` | `1` | `0` | `0 / 0` |
| ORPHAN | `PASS` | `0` | no | `2` | `1` | `0` | `0 / 0` |

The child command lines retained the requested ports and
`ServerManageExpectedPort` values. The lifecycle logs showed no preflight
failure, launch-failure marker, or validation-failure marker. UE log rollover
retained two explicit matching validator markers across the lifecycle log set,
one for `7777` and one for `7778`; the direct control below provides a dedicated
single-process validation marker check.

## 8. Conflict test: holder on 7777

An independent .NET `UdpClient` held `0.0.0.0:7777` with exclusive address use
while PIE was requested. The holder remained alive until after final evidence
collection.

| Check | Result |
| --- | --- |
| `SMT_PORT_PREFLIGHT_FAILED` | exactly `1` |
| unavailable port | `7777` |
| `SMT_PORT_PREFLIGHT_PASSED` | `0` |
| `SMT_SERVER_PROCESS_LAUNCH_FAILED` | `0` |
| `SMT_PORT_VALIDATION_PASSED/FAILED` | `0 / 0` |
| child server count | `0` |
| PIE result / parent exit | `PASS / 0` |
| timeout / forced termination | `false / false` |
| holder still present before cleanup | `true` |
| unrelated owners | `0` |

Summary SHA-256:
`0E1259DD51F9E0E8032A0BFB566928061BBB3036823ECFC1364296BA2589D407`.

## 9. Conflict test: holder on 7778

The same independent-holder test was repeated with `0.0.0.0:7778` held.

| Check | Result |
| --- | --- |
| `SMT_PORT_PREFLIGHT_FAILED` | exactly `1` |
| unavailable port | `7778` |
| `SMT_PORT_PREFLIGHT_PASSED` | `0` |
| `SMT_SERVER_PROCESS_LAUNCH_FAILED` | `0` |
| `SMT_PORT_VALIDATION_PASSED/FAILED` | `0 / 0` |
| child server count, including 7777 | `0` |
| PIE result / parent exit | `PASS / 0` |
| timeout / forced termination | `false / false` |
| holder still present before cleanup | `true` |
| unrelated owners | `0` |

Summary SHA-256:
`BCF01D6DFF3B01B22A5F4B07BE69274E087532852CFEC0B47AF00293498DEA9F`.

These two tests demonstrate the all-or-nothing property: a conflict in either
configured port prevents both servers from launching and does not follow an
automatically shifted port.

## 10. Direct race guard on 17777

### 10.1 Mismatch case

With an independent .NET UDP holder on `17777`, the direct command was:

```text
UnrealEditor.exe <host> /Engine/Maps/Entry -Port=17777 -ServerManageExpectedPort=17777 -server -unattended -nullrhi -nosplash -log -AbsLog=<log>
```

UE 5.8 reproduced the race by binding `17778`. The plugin emitted exactly:

```text
SMT_PORT_VALIDATION_FAILED expected_port=17777 actual_port=17778 world=Entry pid=62620
```

The holder remained, no `17778` residue remained, and the process was not
force-terminated. However, the observed process exit code was `0`, not the
required `2`. The log also records the requested call:

```text
FPlatformMisc::RequestExitWithStatus(0, 2, ServerManageExpectedPort does not match bound port)
```

This is an engine-side propagation limitation, not a missing validator
decision. In the installed UE 5.8 source, Windows `RequestExitWithStatus(false,
2)` calls `PostQuitMessage(2)`, while `LaunchWindowsStartup` returns the
existing `ErrorLevel` from `GuardedMain`; the normal non-commandlet path leaves
that value at `0`. The source files for that behavior are:

- `Engine\Source\Runtime\Core\Private\Windows\WindowsPlatformMisc.cpp`
- `Engine\Source\Runtime\Launch\Private\Windows\LaunchWindows.cpp`
- `Engine\Source\Runtime\Launch\Private\Launch.cpp`

Using `RequestExitWithStatus(true, 2)` or another hard termination would violate
the requested no-force behavior, so it was not added.

Mismatch summary SHA-256:
`4BA252213414F15580188C3D47FD1D26F72E71A4E30730F3409D97783871E886`.

### 10.2 Matching control

After releasing the holder, the same direct command was run with port `17777`
free. The process stayed alive for at least five seconds, emitted exactly one
`SMT_PORT_VALIDATION_PASSED` marker with expected and actual `17777`, emitted no
failure marker, and was then cleaned up by the harness after validation. Final
port-owner count was `0` and shifted-port residue was `0`.

Control summary SHA-256:
`0B94DBE113CAD456BF031FCA81B09761CE5BC19DAD0E98873A21107C790B6203`.

## 11. Cleanup and process safety

All harness cleanup was identity-gated. A process was eligible for cleanup only
when its PID, `UnrealEditor.exe` name, host-project path, and server role
matched. Conflict holders were disposed only after the holder-presence check.
Final checks showed no target host parent, no target child server, no
unrelated UDP owner, and no `7778` residue in the direct mismatch run.

## 12. Evidence hashes

| Evidence | SHA-256 |
| --- | --- |
| BuildPlugin log | `788261340593D3303566BA1F737BB8B1CDC2B85E8E1DA41187CE6AD2B0E102E6` |
| Blueprint clean-load summary | `15510423D42BC2DC9F802B940EE997088DB2141C6417F30C59490297397F297C` |
| PIE summary | `8FE09378CB50D75DDA4FF7A6A7744492958562E98E685566778C047D3D621EC2` |
| Simulate summary | `AF973252F6B1560591749F62850162834DB05010C77DE3BCD0C3E6C746701D80` |
| ORPHAN summary | `3F03FC704B8E3902DCE95A20D024AE3D87C7017047E7F616E6D84C68F2F4B165` |
| 7777 conflict summary | `0E1259DD51F9E0E8032A0BFB566928061BBB3036823ECFC1364296BA2589D407` |
| 7778 conflict summary | `BCF01D6DFF3B01B22A5F4B07BE69274E087532852CFEC0B47AF00293498DEA9F` |
| 17777 mismatch summary | `4BA252213414F15580188C3D47FD1D26F72E71A4E30730F3409D97783871E886` |
| 17777 control summary | `0B94DBE113CAD456BF031FCA81B09761CE5BC19DAD0E98873A21107C790B6203` |
| mismatch log | `52821537A5DC39B23E3E929B017069E15EDA340EE6C9C739C25848D51E052139` |
| control log | `7E0328A39BFA602CD47D671E418D190EA7BDD6651C4BC1838F3D8D52643C18E5` |

## 13. Final Git state and delivery

The source change is intended for commit 1:

```text
fix: fail fast on local server port conflicts
```

The report is intended for commit 2:

```text
docs: verify port conflict fail-fast
```

The requested delivery is a push of
`origin/fix/port-conflict-fail-fast`. No pull request, tag, release, or Fab
submission is created by this task.

The direct mismatch exit-code limitation remains an unresolved technical
friction and must be addressed by an approved UE-side integration or a change
to the no-force requirement before this narrow gate can be called fully green.
