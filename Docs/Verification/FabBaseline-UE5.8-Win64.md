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

The structural requirements below are separated from the product quality gates. The Fab structural statements are based on Epic's [Fab asset file format and structure requirements](https://dev.epicgames.com/documentation/fab/asset-file-format-and-structure-requirements-in-fab). EngineVersion, DocsURL, SupportURL, and PlatformAllowList remain sales metadata and compatibility declarations in this audit; this report does not assert that Fab requires each of them structurally.

### Fab submission structural requirements — FAIL

- PASS — At least one code module: the plugin declares ServerModePlayMenu, ServerInfoSettingsModule, and ServerManageLibrary.
- PASS — .uplugin: ServerManageTool.uplugin exists.
- PASS — Source: the source module tree exists.
- FAIL — Content: no repository Content directory exists.
- FAIL — Config: no repository Config directory exists; the FilterPlugin.ini generated during the failed BuildPlugin run was removed and is not a product configuration.
- BLOCKED — A plugin-only .zip was not generated or inspected because BuildPlugin failed.
- BLOCKED — A public download link without login or individual permission was not configured or tested.

Epic's current Fab documentation states that Code Plugins must contain a .uplugin, Source, Content, and Config, must be compressed into a .zip, and must use a download link that does not require permissions.

### Product release quality gates — FAIL

- FAIL — README and user instructions are absent.
- FAIL — Detailed product documentation is absent.
- FAIL — Automated tests are absent.
- FAIL — CI is absent.
- FAIL — Fab package generation script is absent.
- FAIL — UE 5.8 real-device evidence is incomplete: direct editor-server launch passed, but BuildPlugin failed and plugin-managed lifecycle was blocked.
- FAIL — The existing port-conflict behavior auto-increments a requested 17777 launch to 17779 and keeps the process alive.
- FAIL — Editor delegates are not removed in ShutdownModule().
- FAIL — Template copyright and Build.cs comments remain.

EngineVersion, DocsURL, SupportURL, and PlatformAllowList are tracked separately as sales metadata and compatibility declarations, not as Fab structural requirements asserted by this report.

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

### Review correction validation — PASS

The exact script extracted from the marked Section 18 block was saved as a temporary .ps1 and executed. The original audit evidence above was not overwritten.

| Review-correction evidence | Result |
| --- | --- |
| extracted script SHA-256 | B60C6B0C34D6E0B8453658E578086FDD132A425AF4281D852B625FB74BAC68CD |
| validation exit code | 0 |
| validation status | PASS |
| validation transcript SHA-256 | FEE3788D16ECB24CCCA16251023BE165F797CAA3A65147BF221AA3A417104C0C |
| result JSON SHA-256 | 514423D405E422FB5C1262F7A0DC3868169DCD0C466A5F38DE97BB92006AABAB |
| validation wrapper output SHA-256 | 5FA5A95F4B8C56AF8E0E26B6FA2A3E06EE6EB2232FF84253D61DF2C14889EBF4 |
| single server | PID 43312; requested/actual 17777/17777 |
| multiple server A | PID 29680; requested/actual 17777/17777 |
| multiple server B | PID 60304; requested/actual 17778/17778 |
| conflict server | PID 18192; requested/actual 17777/17779; alive during the 30-second conflict check |
| final target process count | 0 after the required 10-second cleanup wait |
| server log: single | 51DCB05FA8357A019CBA0990A37E41F708B5D809689C8DF11A76B4AE2298908D |
| server log: multi 17777 | 0D1A1C9C1B88C0B5AFCB8B1D5A77EBA622C777E77494841A3D1FD3E5B869AA63 |
| server log: multi 17778 | 0C62C0AAD09EB7441E33FE80685BDFF1BCC43FC7F1E5385219F221B519BDBAE9 |
| server log: conflict | AA3C61902CDBFC362D5DB0DECE3D17F8840BA946FE5B25796995AB1A10C1ABF9 |

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

The following is the complete, self-contained direct-server validation script. It creates all projects, logs, JSON, and transcript files below a new TEMP audit root. It only terminates UnrealEditor.exe processes whose name, absolute generated uproject path, and independent -server argument all match the current run.

<!-- DIRECT-SERVER-SCRIPT-BEGIN -->
```powershell
$ErrorActionPreference = "Stop"

$startedProcesses = [System.Collections.Generic.List[System.Diagnostics.Process]]::new()
$records = [System.Collections.Generic.List[object]]::new()
$errors = [System.Collections.Generic.List[string]]::new()
$auditRoot = $null
$uprojectPath = $null
$resultPath = $null
$transcriptPath = $null
$transcriptStarted = $false
$scriptResult = [ordered]@{
    Status = "RUNNING"
    AuditRoot = $null
    HostProject = $null
    Processes = @()
    FinalTargetProcessCount = $null
    Errors = @()
}

function Add-AuditError {
    param([string]$Message)
    [void]$errors.Add($Message)
}

function Get-TargetProcesses {
    param([string]$TargetUProjectPath)
    $matches = [System.Collections.Generic.List[object]]::new()
    $allProcesses = Get-CimInstance Win32_Process
    foreach ($candidate in $allProcesses) {
        $name = [string]$candidate.Name
        $commandLine = [string]$candidate.CommandLine
        $hasIndependentServerArgument = $commandLine -match "(?i)(^|\s)-server(?=\s|$)"
        if ($name -eq "UnrealEditor.exe" -and
            $commandLine.Contains($TargetUProjectPath) -and
            $hasIndependentServerArgument) {
            [void]$matches.Add($candidate)
        }
    }
    return $matches.ToArray()
}

function Get-CommandLineByProcessId {
    param([int]$ProcessId)
    $deadline = [DateTime]::UtcNow.AddSeconds(10)
    while ([DateTime]::UtcNow -lt $deadline) {
        $processInfo = Get-CimInstance Win32_Process -Filter ("ProcessId = " + $ProcessId)
        if ($null -ne $processInfo -and -not [string]::IsNullOrWhiteSpace([string]$processInfo.CommandLine)) {
            return [string]$processInfo.CommandLine
        }
        Start-Sleep -Milliseconds 250
    }
    throw "Could not retrieve command line for PID $ProcessId within 10 seconds."
}

function Assert-UdpPortFree {
    param([int]$Port)
    $endpoints = @(Get-NetUDPEndpoint -LocalPort $Port -ErrorAction SilentlyContinue)
    if ($endpoints.Count -ne 0) {
        throw "UDP port $Port is already in use; no unrelated process was terminated."
    }
}

function New-ServerProcess {
    param(
        [string]$Role,
        [int]$RequestedPort,
        [string]$LogPath
    )
    $arguments = @(
        $uprojectPath,
        "/Engine/Maps/Entry",
        "-Port=$RequestedPort",
        "-server",
        "-unattended",
        "-nullrhi",
        "-nosplash",
        "-log",
        "-AbsLog=$LogPath"
    )
    $startInfo = [System.Diagnostics.ProcessStartInfo]::new()
    $startInfo.FileName = Join-Path $ueRoot "Engine\Binaries\Win64\UnrealEditor.exe"
    $startInfo.UseShellExecute = $false
    $startInfo.CreateNoWindow = $true
    foreach ($argument in $arguments) {
        [void]$startInfo.ArgumentList.Add($argument)
    }
    $process = [System.Diagnostics.Process]::new()
    $process.StartInfo = $startInfo
    if (-not $process.Start()) {
        throw "Process.Start returned false for role $Role."
    }
    [void]$startedProcesses.Add($process)
    $commandLine = Get-CommandLineByProcessId -ProcessId $process.Id
    return [pscustomobject]@{
        Role = $Role
        Process = $process
        PID = $process.Id
        RequestedPort = $RequestedPort
        LogPath = $LogPath
        CommandLine = $commandLine
    }
}

function Get-ListenResult {
    param(
        [pscustomobject]$Server,
        [int]$ExpectedPort,
        [int]$TimeoutSeconds
    )
    $deadline = [DateTime]::UtcNow.AddSeconds($TimeoutSeconds)
    while ([DateTime]::UtcNow -lt $deadline) {
        if ($Server.Process.HasExited) {
            return [pscustomobject]@{
                Success = $false
                ActualPort = $null
                ListenLine = $null
                Reason = "Process exited with code $($Server.Process.ExitCode)."
            }
        }
        if (Test-Path -LiteralPath $Server.LogPath) {
            $lines = Get-Content -LiteralPath $Server.LogPath -ErrorAction SilentlyContinue
            foreach ($line in $lines) {
                $socketPattern = "(?i)Created socket for bind address:\s+\S+:$ExpectedPort\b"
                $listenPattern = "(?i)IpNetDriver listening on port\s+$ExpectedPort\b"
                if ($line -match $socketPattern -or $line -match $listenPattern) {
                    $actualPort = $ExpectedPort
                    if ($line -match "(?i)listening on port\s+(\d+)\b") {
                        $actualPort = [int]$Matches[1]
                    } elseif ($line -match "(?i)bind address:\s+\S+:(\d+)\b") {
                        $actualPort = [int]$Matches[1]
                    }
                    return [pscustomobject]@{
                        Success = $true
                        ActualPort = $actualPort
                        ListenLine = $line
                        Reason = $null
                    }
                }
            }
        }
        Start-Sleep -Milliseconds 500
    }
    return [pscustomobject]@{
        Success = $false
        ActualPort = $null
        ListenLine = $null
        Reason = "Listen confirmation timed out after $TimeoutSeconds seconds."
    }
}

function Add-ProcessRecord {
    param(
        [pscustomobject]$Server,
        [pscustomobject]$ListenResult
    )
    [void]$records.Add([ordered]@{
        Role = $Server.Role
        PID = $Server.PID
        CommandLine = $Server.CommandLine
        RequestedPort = $Server.RequestedPort
        ActualPort = $ListenResult.ActualPort
        ListenLine = $ListenResult.ListenLine
        LogPath = $Server.LogPath
    })
}

function Stop-StartedProcess {
    param([System.Diagnostics.Process]$Process)
    if ($null -eq $Process) {
        return
    }
    try {
        if (-not $Process.HasExited) {
            $Process.Kill($true)
            [void]$Process.WaitForExit(10000)
        }
    } catch {
        Add-AuditError ("Cleanup failed for PID " + $Process.Id + ": " + $_.Exception.Message)
    }
}

try {
    $repoRoot = (Get-Location).Path
    $ueRoot = $env:UE_5_8_ROOT
    if ([string]::IsNullOrWhiteSpace($ueRoot)) {
        $ueRoot = "C:\Program Files\Epic Games\UE_5.8"
    }
    $ueRoot = [System.IO.Path]::GetFullPath($ueRoot)
    $buildVersionPath = Join-Path $ueRoot "Engine\Build\Build.version"
    $installedBuildPath = Join-Path $ueRoot "Engine\Build\InstalledBuild.txt"
    $buildVersion = Get-Content -Raw -LiteralPath $buildVersionPath | ConvertFrom-Json
    if ($buildVersion.MajorVersion -ne 5 -or $buildVersion.MinorVersion -ne 8) {
        throw "UE root is not UE 5.8."
    }
    if (-not (Test-Path -LiteralPath $installedBuildPath -PathType Leaf)) {
        throw "UE 5.8 InstalledBuild.txt is missing."
    }
    foreach ($requiredPath in @(
        (Join-Path $ueRoot "Engine\Binaries\Win64\UnrealEditor.exe"),
        (Join-Path $ueRoot "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"),
        (Join-Path $ueRoot "Engine\Build\BatchFiles\RunUAT.bat")
    )) {
        if (-not (Test-Path -LiteralPath $requiredPath -PathType Leaf)) {
            throw "Required UE file is missing: $requiredPath"
        }
    }

    $stamp = Get-Date -Format "yyyyMMdd-HHmmss"
    $auditRoot = Join-Path $env:TEMP "ServerManageToolPlugin-FabAudit-$stamp"
    $hostRoot = Join-Path $auditRoot "ServerManageToolBlueprintHost"
    $configRoot = Join-Path $hostRoot "Config"
    $null = New-Item -ItemType Directory -Path $configRoot -Force
    $uprojectPath = Join-Path $hostRoot "ServerManageToolBlueprintHost.uproject"
    $resultPath = Join-Path $auditRoot "DirectServerValidation.json"
    $transcriptPath = Join-Path $auditRoot "DirectServerValidation.transcript.txt"
    $scriptResult.AuditRoot = $auditRoot
    $scriptResult.HostProject = $uprojectPath

    $projectObject = [ordered]@{
        FileVersion = 3
        EngineAssociation = "5.8"
        Plugins = @()
    }
    $projectText = ConvertTo-Json -InputObject $projectObject -Depth 5
    Set-Content -LiteralPath $uprojectPath -Value $projectText -Encoding utf8NoBOM
    $newline = [Environment]::NewLine
    $engineIni = "[/Script/EngineSettings.GameMapsSettings]" + $newline +
        "GameDefaultMap=/Engine/Maps/Entry" + $newline +
        "ServerDefaultMap=/Engine/Maps/Entry" + $newline
    Set-Content -LiteralPath (Join-Path $configRoot "DefaultEngine.ini") -Value $engineIni -Encoding utf8NoBOM

    $null = Start-Transcript -Path $transcriptPath -Force
    $transcriptStarted = $true
    Write-Output "UE root: $ueRoot"
    Write-Output "Installed Build: $((Get-Content -Raw -LiteralPath $installedBuildPath).Trim())"
    Write-Output "Audit root: $auditRoot"
    Write-Output "Host project: $uprojectPath"

    foreach ($port in 17777, 17778, 17779) {
        Assert-UdpPortFree -Port $port
    }

    $singleLog = Join-Path $auditRoot "DirectSingle-17777.log"
    $single = New-ServerProcess -Role "single" -RequestedPort 17777 -LogPath $singleLog
    $singleListen = Get-ListenResult -Server $single -ExpectedPort 17777 -TimeoutSeconds 60
    if (-not $singleListen.Success -or $single.Process.HasExited) {
        throw "Single-server validation failed: $($singleListen.Reason)"
    }
    Add-ProcessRecord -Server $single -ListenResult $singleListen
    Stop-StartedProcess -Process $single.Process

    $multi17777 = New-ServerProcess -Role "multi-17777" -RequestedPort 17777 -LogPath (Join-Path $auditRoot "DirectMulti-17777.log")
    $multi17778 = New-ServerProcess -Role "multi-17778" -RequestedPort 17778 -LogPath (Join-Path $auditRoot "DirectMulti-17778.log")
    $multiListen17777 = Get-ListenResult -Server $multi17777 -ExpectedPort 17777 -TimeoutSeconds 60
    $multiListen17778 = Get-ListenResult -Server $multi17778 -ExpectedPort 17778 -TimeoutSeconds 60
    if (-not $multiListen17777.Success -or -not $multiListen17778.Success) {
        throw "Multiple-server validation failed."
    }
    if ($multi17777.Process.HasExited -or $multi17778.Process.HasExited -or $multi17777.PID -eq $multi17778.PID) {
        throw "Multiple-server PID/liveness validation failed."
    }
    Add-ProcessRecord -Server $multi17777 -ListenResult $multiListen17777
    Add-ProcessRecord -Server $multi17778 -ListenResult $multiListen17778

    $conflict = New-ServerProcess -Role "conflict-request-17777" -RequestedPort 17777 -LogPath (Join-Path $auditRoot "DirectConflict-17777.log")
    $conflictListen = Get-ListenResult -Server $conflict -ExpectedPort 17779 -TimeoutSeconds 30
    if (-not $conflictListen.Success -or $conflictListen.ActualPort -ne 17779 -or $conflict.Process.HasExited) {
        throw "Port-conflict validation failed: requested 17777 did not remain alive on actual 17779."
    }
    Add-ProcessRecord -Server $conflict -ListenResult $conflictListen
    $scriptResult.Status = "PASS"
} catch {
    $scriptResult.Status = "FAIL"
    Add-AuditError $_.Exception.ToString()
    Write-Error $_.Exception.ToString()
} finally {
    foreach ($started in $startedProcesses) {
        Stop-StartedProcess -Process $started
    }
    if ($null -ne $uprojectPath) {
        Start-Sleep -Seconds 10
        $remaining = @(Get-TargetProcesses -TargetUProjectPath $uprojectPath)
        $scriptResult.FinalTargetProcessCount = $remaining.Count
        if ($remaining.Count -ne 0) {
            $scriptResult.Status = "FAIL"
            Add-AuditError "Final target process count was $($remaining.Count), expected 0."
        }
    }
    $scriptResult.Processes = @($records.ToArray())
    $scriptResult.Errors = @($errors.ToArray())
    if ($null -ne $resultPath) {
        $resultText = ConvertTo-Json -InputObject $scriptResult -Depth 10
        Set-Content -LiteralPath $resultPath -Value $resultText -Encoding utf8NoBOM
    }
    if ($transcriptStarted) {
        Stop-Transcript | Out-Null
    }
}

Write-Output ("ValidationStatus=" + $scriptResult.Status)
Write-Output ("FinalTargetProcessCount=" + $scriptResult.FinalTargetProcessCount)
Write-Output ("ValidationTranscriptSHA256=" + (Get-FileHash -Algorithm SHA256 -LiteralPath $transcriptPath).Hash)
Write-Output ("ResultJsonSHA256=" + (Get-FileHash -Algorithm SHA256 -LiteralPath $resultPath).Hash)
$logPaths = @($records | ForEach-Object { $_.LogPath } | Sort-Object -Unique)
foreach ($logPath in $logPaths) {
    Write-Output ("LogSHA256 path=" + $logPath + " hash=" + (Get-FileHash -Algorithm SHA256 -LiteralPath $logPath).Hash)
}
if ($scriptResult.Status -ne "PASS" -or $scriptResult.FinalTargetProcessCount -ne 0) {
    exit 1
}
```
<!-- DIRECT-SERVER-SCRIPT-END -->

The Blueprint-only load command, plugin-managed PIE command sequence, and Game/Shipping builds remain separately gated by BuildPlugin and host-load success; they must not be represented as successful reproductions from this baseline.
