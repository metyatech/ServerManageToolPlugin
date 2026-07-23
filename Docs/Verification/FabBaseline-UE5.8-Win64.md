# Fab Baseline Audit: UE 5.8 / Win64

Audit date: 2026-07-23 (Asia/Tokyo)

This is a read-only implementation and runtime baseline audit. No `.cpp`, `.h`, `.cs`, `.uplugin`, README, configuration, content, CI, or packaging source was changed. The only repository artifact added by this audit is this report.

## 1. Overall status — FAIL

The plugin is not ready for Fab implementation or submission work. The UE 5.8 Launcher Installed Build is available and the direct `UnrealEditor.exe -server` runtime path works on Win64, but the required BuildPlugin step fails with five UE 5.8 UHT errors. Consequently, plugin loading, plugin-managed PIE lifecycle, and Game/Shipping configuration coverage were not eligible for execution or success claims.

## 2. Git baseline — PASS

The start conditions were all satisfied before the audit branch was created:

- `origin`: `https://github.com/metyatech/ServerManageToolPlugin`
- branch: `master`
- start HEAD: `67cae225ff9d616f3bac4709dc951ba7a829cdd2`
- `master...origin/master`: `0 0`
- tracked and untracked status: clean
- `ServerManageTool.uplugin`: present at repository root
- `audit/fab-ue58-baseline`: absent locally and remotely before creation

The audit branch `audit/fab-ue58-baseline` was created as required. The final commit and push result are recorded in the delivery message because the final commit hash cannot be embedded in its own content without changing that hash.

## 3. UE 5.8 environment — PASS

PowerShell 7.6.1 was used. `UE_5_8_ROOT` was empty, so the specified fallback was selected:

```text
C:\Program Files\Epic Games\UE_5.8
```

All required files were present:

- `Engine\Build\Build.version`
- `Engine\Binaries\Win64\UnrealEditor.exe`
- `Engine\Binaries\Win64\UnrealEditor-Cmd.exe`
- `Engine\Build\BatchFiles\RunUAT.bat`

`Build.version` reported `MajorVersion=5`, `MinorVersion=8`, `PatchVersion=0`.

## 4. Installed Build determination — PASS

`Engine\Build\InstalledBuild.txt` exists and contains `UE_5.8`. This audit therefore used the UE 5.8 Launcher Installed Build, not a Source Build.

## 5. Current implementation facts — FAIL

The following facts were verified against the current source. Line numbers refer to the pre-audit source.

- `PASS` — At PIE start, every element of `ServerList` is processed: `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp:84-99`.
- `PASS` — Ports start at `7777` and increment once per array element: `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp:94-99`.
- `PASS` — The launched executable is the current editor executable from `FPlatformProcess::ExecutablePath()`, not a packaged server executable: `Source/ServerModePlayMenu/Private/ServerProcess.cpp:5-10`.
- `PASS` — The current command line is `<uproject> <MapName> -Port=<port> -server -log`, assembled at `Source/ServerModePlayMenu/Private/ServerProcess.cpp:24-32`.
- `PASS` — PIE end clears the managed process collection, causing each `ServerProcess` destructor to call `Kill()`: `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp:103-105` and `Source/ServerModePlayMenu/Private/ServerProcess.cpp:43-54`.
- `FAIL` — `StartupModule()` registers `BeginPIE` and `EndPIE`, but `ShutdownModule()` does not remove either delegate: `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp:21-39`.
- `PASS` — Map configuration is string-backed (`FString MapName`): `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:14-19`.
- `PASS` — Runtime lookup uses exact equality between `Map.GetLongPackageName()` and configured `MapName`: `Source/ServerManageLibrary/Private/ServerManageLibraryBP.cpp:21-27`.
- `PASS` — A missing map registration returns an empty string: `Source/ServerManageLibrary/Private/ServerManageLibraryBP.cpp:29-34`.
- `PASS` — Local Launch resolves to `127.0.0.1:(7777 + array index)`: `Source/ServerManageLibrary/Private/ServerManageLibraryBP.cpp:36-47`.
- `FAIL` — Runtime `ServerManageLibrary` has a conditional public dependency on the Editor module `ServerModePlayMenu`: `Source/ServerManageLibrary/ServerManageLibrary.Build.cs:34-37`.
- `FAIL` — The `.uplugin` has no UE 5.8, Win64, Fab, documentation, or support sales metadata: `ServerManageTool.uplugin:5-12`.
- `FAIL` — No `README.md`, `Config`, `Content`, automated test directory, `.github` CI directory, or Fab package script existed in the checkout at audit start.
- `FAIL` — Template copyright comments remain in source files, for example `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:1` and `Source/ServerManageLibrary/ServerManageLibrary.Build.cs:1`.
- `FAIL` — Template Build.cs comments remain, for example `Source/ServerManageLibrary/ServerManageLibrary.Build.cs:13-14`, `20-21`, and `30`.

## 6. BuildPlugin — FAIL

The required UE 5.8 Win64 command was executed without source changes. Exit code was `6` (`OtherCompilationError`). The combined stdout/stderr log SHA-256 was:

```text
6D2A24509415BC0268E9B89633E7C0B72D245274C382B5BA0BB8FB50AE3C131C
```

The first compile error, in full apart from replacing the temporary-root prefix with `<auditRoot>`, was:

```text
<auditRoot>\BuildPlugin\HostProject\Plugins\ServerManageTool\Source\ServerInfoSettingsModule\Public\ServerInfoSettings.h(15): Error: An explicit Category specifier is required for any property exposed to the editor or Blueprints in an Engine module.
```

The complete first-error group was:

```text
ServerInfoSettings.h(15): Error: An explicit Category specifier is required for any property exposed to the editor or Blueprints in an Engine module.
ServerInfoSettings.h(18): Error: An explicit Category specifier is required for any property exposed to the editor or Blueprints in an Engine module.
ServerInfoSettings.h(30): Error: An explicit Category specifier is required for any property exposed to the editor or Blueprints in an Engine module.
ServerManageLibraryBP.h(21): Error: An explicit Category specifier is required for Blueprint accessible functions in an Engine module.
ServerManageLibraryBP.h(24): Error: An explicit Category specifier is required for Blueprint accessible functions in an Engine module.
```

The BuildPlugin log shows the attempted target as `UnrealEditor Win64 Development` (Development Editor). The source `.uplugin` lists these modules: `ServerModePlayMenu` (Editor), `ServerInfoSettingsModule` (Runtime), and `ServerManageLibrary` (Runtime). Compilation did not complete and no successful module binary set was produced.

The package output under `<auditRoot>\BuildPlugin\HostProject\Plugins\ServerManageTool` contained:

| Output | Present | Result |
| --- | --- | --- |
| `.uplugin` | Yes | Copied, but not a successful built artifact |
| `Source` | Yes | Present |
| `Binaries` | No | No compiled package binaries |
| `Intermediate` | Yes | Partial failed-build intermediates |
| `Resources` | Yes | Present |
| `Content` | No | Absent |
| `Config` | Yes | Generated `FilterPlugin.ini` |

The copied `.uplugin` reported `Installed=false`, no `EngineVersion` field, and the three modules listed above.

## 7. Blueprint-only project — BLOCKED

Per the audit gate, this step runs only after a successful BuildPlugin. BuildPlugin failed with exit code `6`, so the plugin package was not loaded into a Blueprint-only project. No missing-module, incompatible-module, compile-request, or C++ conversion result is claimed.

## 8. Direct UnrealEditor server launch — PASS

A separate content-only host project with no plugin enabled and no C++ module was created under the temporary audit root. It used `EngineAssociation=5.8` and `/Engine/Maps/Entry` as the default/server map. The process was started with `System.Diagnostics.ProcessStartInfo.ArgumentList`; launch arguments were not assembled into an `Arguments` string.

Single-server result:

- `PASS` — PID `42000` remained alive while the readiness check ran.
- `PASS` — port `17777` listen was observed in the log: `LogNet: Created socket for bind address: 0.0.0.0:17777`.
- `PASS` — no packaged Server executable was created; the process was `UnrealEditor.exe`.
- command line included the requested uproject, `/Engine/Maps/Entry`, `-Port=17777`, `-server`, `-unattended`, `-nullrhi`, `-nosplash`, `-log`, and a unique `-AbsLog`.

The single process was force-terminated after evidence capture and exited with `-1` as a result of termination. This is cleanup behavior, not a listen failure.

## 9. Multiple servers — PASS

Two processes were started concurrently with separate logs:

- `PASS` — PID `44904` listened on `17777`.
- `PASS` — PID `54972` listened on `17778`.
- `PASS` — both processes were alive concurrently and had different PIDs.
- `PASS` — log files were separate: `DirectMulti-17777.log` and `DirectMulti-17778.log`.

The observed listen lines were `Created socket for bind address: 0.0.0.0:17777` and `Created socket for bind address: 0.0.0.0:17778`.

## 10. Port conflict — FAIL

With PID `44904` still holding `17777` and PID `54972` holding `17778`, a third process was started with `-Port=17777`.

- third-process PID: `26188`
- after 30 seconds: process still running; exit code was `<still-running>`
- explicit bind error: not present in the captured log
- automatic port change: observed; it listened on `17779`
- post-error process state: process remained alive until force termination
- observed line: `LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 17779`

This behavior is a release blocker because a requested port collision does not fail fast and does not preserve the requested port.

## 11. Plugin-managed PIE lifecycle — BLOCKED

The required BuildPlugin-success and Blueprint-only-load-success gates were not met. The PIE/Simulate Python automation was therefore not run, and no claim is made for:

- child processes on ports `7777` and `7778` through the plugin;
- child cleanup within 10 seconds after PIE end; or
- the documented Simulate behavior.

## 12. Editor shutdown orphan check — BLOCKED

This check depends on the plugin-managed PIE run and was not executed because sections 6 and 7 were blocked. The direct-launch cleanup is separate evidence and must not be treated as evidence for Editor shutdown orphan handling.

## 13. Development / Shipping — FAIL

- `FAIL` — Development Editor: BuildPlugin targeted `UnrealEditor Win64 Development` and failed with exit code `6`.
- `BLOCKED` — Development Game: not targeted by the BuildPlugin invocation; no successful Game build evidence exists.
- `BLOCKED` — Shipping Game: not targeted by the BuildPlugin invocation; no successful Shipping build evidence exists.

The Editor-only `ServerModePlayMenu` module was not proven absent from Game/Shipping output because those configurations were not built. The conditional runtime-to-Editor public dependency was observed statically at `Source/ServerManageLibrary/ServerManageLibrary.Build.cs:34-37`, but no configuration-specific dependency result is claimed beyond the failed Development Editor attempt.

## 14. Windows以外 — NOT_APPLICABLE

This baseline scope is explicitly UE 5.8 Win64 on Windows. No non-Windows platform claim is made.

## 15. Confirmed product scope — FAIL

- `PASS` — The current editor executable can be launched with `-server` and can listen on a requested port in a content-only host without a packaged Server executable.
- `BLOCKED` — Packaging/building a packaged dedicated server was not confirmed. BuildPlugin failed before producing compiled plugin binaries.
- `BLOCKED` — PIE client behavior was not confirmed because plugin package load and plugin-managed PIE gates were blocked.
- `NOT_APPLICABLE` — A plugin-owned client-process launch path was not identified in the audited implementation; the observed `ServerProcess` path launches editor server processes.

These are separate scopes. Direct `UnrealEditor -server` success is not evidence of packaged dedicated-server packaging, PIE client behavior, or plugin-owned client-process startup.

## 16. Blockers before implementation — FAIL

The following must be resolved before Fab implementation/submission work:

1. Fix the five UE 5.8 UHT `Category` errors and rerun BuildPlugin without changing the audit baseline retroactively.
2. Produce and verify a successful Win64 package with actual binaries; confirm `Installed`, `EngineVersion`, module contents, and all required package directories.
3. Verify Blueprint-only loading and explicitly record missing-module, incompatible-module, compile-request, and C++ conversion outcomes.
4. Run plugin-managed PIE, Simulate, normal Editor shutdown, and orphan-process checks with the required timeout evidence.
5. Decide and test the intended port-conflict policy; current behavior auto-increments and leaves the conflicting launch alive.
6. Build and verify Development Game and Shipping Game separately; prove Editor-only module exclusion and runtime dependency correctness.
7. Replace missing Fab metadata/documentation/support information and add the absent README, Config, Content, automated tests, CI, and package script as a separate implementation phase.
8. Remove template copyright and Build.cs comments as part of the implementation phase.
9. Address the missing Editor delegate unregistration in `ShutdownModule()` before treating Editor lifecycle behavior as production-ready.

## 17. Evidence table — PASS

All evidence below was kept under the temporary audit root and was not committed.

| Evidence | Result |
| --- | --- |
| `BuildPlugin.log` | exit `6`; SHA-256 `6D2A24509415BC0268E9B89633E7C0B72D245274C382B5BA0BB8FB50AE3C131C` |
| `DirectServerAudit.txt` | SHA-256 `1AC5FB4FEFCDE1EF739FB53FCD35A00C549ECEF915301EAE4D2602C05D16E862` |
| `DirectSingle-17777.log` | SHA-256 `0DDC7C2CE04EB117756933B64694E874E56DE7132F9065F0ACC1722D482F3312` |
| `DirectMulti-17777.log` | SHA-256 `E1C71AD3B5B0E3004137AB2F3855A86DDA1FD01B3AABE905D85ADA7C4EFFE619` |
| `DirectMulti-17778.log` | SHA-256 `F5B29C57680FD8747778903463BCD9621C68E55337824CA43400DB94004DEE2C` |
| `DirectConflict-17777.log` | SHA-256 `89C516E1EE8E5D7E74A3BD45488798A2A5FA471E2C2C252403DED84C13562C9D` |
| final process check | `0` processes containing the direct-host uproject and `-server`, 10 seconds after forced cleanup |
| repository artifact check | generated `Config/FilterPlugin.ini` was removed after absolute-path verification; no audit artifact remains in the repository |

## 18. Exact reproduction commands — PASS

The following commands reproduce the required BuildPlugin invocation and the direct-server launch shape. Run them from the repository root in PowerShell 7. The temporary-root value is intentionally variable so the commands do not depend on a user-specific path.

```powershell
$ErrorActionPreference = "Stop"
$repoRoot = (Get-Location).Path
$ueRoot = $env:UE_5_8_ROOT
if ([string]::IsNullOrWhiteSpace($ueRoot)) {
    $ueRoot = "C:\Program Files\Epic Games\UE_5.8"
}
$stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$auditRoot = Join-Path $env:TEMP "ServerManageToolPlugin-FabAudit-$stamp"
$buildRoot = Join-Path $auditRoot "BuildPlugin"
$buildLog = Join-Path $auditRoot "BuildPlugin.log"
New-Item -ItemType Directory -Path $auditRoot -Force | Out-Null

& "$ueRoot\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
    "-Plugin=$repoRoot\ServerManageTool.uplugin" `
    "-Package=$buildRoot" `
    -TargetPlatforms=Win64 `
    -Rocket *> $buildLog
$buildExitCode = $LASTEXITCODE
Get-FileHash -Algorithm SHA256 -LiteralPath $buildLog
Write-Output "BuildPluginExitCode=$buildExitCode"
```

The direct process must be created with `ArgumentList`, not a concatenated `Arguments` string:

```powershell
$startInfo = [System.Diagnostics.ProcessStartInfo]::new()
$startInfo.FileName = "$ueRoot\Engine\Binaries\Win64\UnrealEditor.exe"
$startInfo.UseShellExecute = $false
$startInfo.CreateNoWindow = $true
foreach ($argument in @(
    $hostProject,
    "/Engine/Maps/Entry",
    "-Port=17777",
    "-server",
    "-unattended",
    "-nullrhi",
    "-nosplash",
    "-log",
    "-AbsLog=$auditRoot\DirectSingle-17777.log"
)) {
    [void]$startInfo.ArgumentList.Add($argument)
}
$process = [System.Diagnostics.Process]::new()
$process.StartInfo = $startInfo
[void]$process.Start()
```

The Blueprint-only load command, plugin-managed PIE command sequence, and Game/Shipping builds were not executed because their explicit prerequisites were blocked; they must not be represented as successful reproductions from this baseline.
