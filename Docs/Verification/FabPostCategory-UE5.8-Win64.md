# Post-category Verification: UE 5.8 / Win64

Verification date: 2026-07-23 (Asia/Tokyo)

This report records the reproducibility completion requested for the existing `fix/ue58-uht-categories` branch. Source code was not changed in this phase. The only repository file changed by this phase is this report. Temporary projects, logs, JSON, and scripts are outside the repository under the recorded short root.

## 1. Verification execution status — FAIL

The short-root retry removed the previous path-length harness failure: BuildPlugin returned exit code 0, all three requested target invocations reported `Result: Succeeded`, the log contained zero 260-character action-path errors, and the five UE 5.8 UHT Category errors remained absent.

The resulting package is not release-ready: `Config` and `Content` are absent, `Intermediate` remains, and no Game `.modules` or Game binaries are present. The Blueprint-only host was attempted after the successful BuildPlugin gate, but the editor stopped making progress after `[Cmd: Quit]`; it was force-terminated after the bounded observation window. Therefore the Blueprint-only gate is FAIL and normal PIE, Simulate, and Editor-shutdown orphan tests were not run.

Overall post-category verification result: FAIL.

## 2. Product readiness status — FAIL

The five Category declarations are fixed and the short-root BuildPlugin compilation gate succeeds, but the final package and runtime acceptance gates do not. Fab readiness is not established.

## 3. Git baseline and scope — PASS

- origin: `https://github.com/metyatech/ServerManageToolPlugin`
- branch: `fix/ue58-uht-categories`
- start HEAD: `88d66e09287c8ddc44948fc469519428e45a74df`
- start `origin/fix/ue58-uht-categories`: `88d66e09287c8ddc44948fc469519428e45a74df`
- start divergence: `0 0`
- start worktree: clean
- category-fix commit: [`d67cac11d1ee93b8c9fe8d0f8d56952e83f95f09`](https://github.com/metyatech/ServerManageToolPlugin/commit/d67cac11d1ee93b8c9fe8d0f8d56952e83f95f09)
- preceding post-category verification commit: [`88d66e09287c8ddc44948fc469519428e45a74df`](https://github.com/metyatech/ServerManageToolPlugin/commit/88d66e09287c8ddc44948fc469519428e45a74df)
- End HEAD (post-commit): the commit that records this report; its exact SHA and URL are supplied in the delivery result
- no merge, rebase, squash, force push, tag, release, PR, or Fab submission was performed

## 4. Exact source change carried into this verification — PASS

The verified source state contains only the requested five Category declarations:

- `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:15` — `Category = "Server Management"`
- `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:18` — `Category = "Server Management"`
- `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:30` — `Category = "Server Management"`
- `Source/ServerManageLibrary/Public/ServerManageLibraryBP.h:21` — `Category = "Server Management"`
- `Source/ServerManageLibrary/Public/ServerManageLibraryBP.h:24` — `Category = "Server Management"`

The existing `EditAnyWhere` spelling was preserved. No function name, type, return value, module structure, Build.cs, `.uplugin`, copyright, map, process, delegate, port, README, Config, Content, CI, or template comment was changed.

## 5. UE environment and short-root preflight — PASS

PowerShell 7 was used. `UE_5_8_ROOT` was unset, so the specified fallback was used:

    C:\Program Files\Epic Games\UE_5.8

`Build.version` reported Major 5, Minor 8, Patch 0. `InstalledBuild.txt` exists, so this was the Launcher Installed Build. The short-root preflight passed:

- short audit root: `D:\T\S58-20260723-131534` (length 24)
- package root: `D:\T\S58-20260723-131534\P` (length 26)
- D: exists and D:\T was createable
- free space before BuildPlugin: 1,224.71 GB
- audit root was absent before creation
- `$env:TEMP` was not used for the short-root retry

## 6. Long-path attempt — FAIL (reproduced prior result)

The original post-category attempt used a TEMP-based audit root and reached the known UE 5.8 Windows action-path limit. It returned exit code 6 before a compiled package was produced.

- BuildPlugin log SHA-256: `92CAF8BB7830DBB4B61FA6783C33DF34B4D06E8031F6BDD8BA0846EFA2503DA3`
- detailed UBT log SHA-256: `0C5C9FC79A4BAABC00F8AA2C8191DCB4D6E407E38F4F8CB341CC1011502023BC`
- rejected action-path lengths: 262, 261, 263, and 263 characters
- consequential exception: `BuildException: The following action paths are longer than 260 characters`
- UHT Category errors: 0

This was an audit-harness path failure, not a remaining UHT Category failure.

## 7. Short-root BuildPlugin retry — PASS

The required BuildPlugin command was rerun with the short package root recorded in Section 5.

- exit code: `0`
- combined log: `D:\T\S58-20260723-131534\BuildPlugin-short-root.log`
- BuildPlugin log SHA-256: `82D0DF6B6D191B4E05936C3D187FE6EB74730738EF1943FE038C0464F103541D`
- `Result: Succeeded` markers: UnrealEditor Win64 Development, UnrealGame Win64 Development, UnrealGame Win64 Shipping
- `BUILD SUCCESSFUL`: present
- AutomationTool exit: `0 (Success)`
- action-path errors over 260 characters: `0`
- UHT Category errors: `0`

The short root therefore resolves the previous path-length reproduction blocker. It does not resolve the package-structure or runtime gates below.

## 8. Configuration results — MIXED; overall FAIL

The target-level compilation results and the final package-artifact results are reported separately because the BuildPlugin log reports successful Game target commands while the final package contains no Game artifacts.

| Configuration | BuildPlugin target | Final package artifact gate | Result |
| --- | --- | --- | --- |
| UnrealEditor Win64 Development | `Result: Succeeded` | Editor DLLs and one Editor `.modules` present | PASS |
| UnrealGame Win64 Development | `Result: Succeeded` | No Game DLL and no Game `.modules` present | FAIL |
| UnrealGame Win64 Shipping | `Result: Succeeded` | No Shipping Game DLL and no Game `.modules` present | FAIL |

The only final `.modules` file is the Editor mapping. It maps `ServerModePlayMenu` (Editor), `ServerInfoSettingsModule` (Runtime), and `ServerManageLibrary` (Runtime). Because no Game mapping was packaged, the required Game/Shipping check that `ServerInfoSettingsModule` and `ServerManageLibrary` are present and `ServerModePlayMenu` is absent cannot pass.

## 9. Final package contents — FAIL

Final package root: `D:\T\S58-20260723-131534\P`.

Top-level entries were exactly:

    Binaries
    Intermediate
    Resources
    Source
    ServerManageTool.uplugin

| Package check | Result | Evidence |
| --- | --- | --- |
| `ServerManageTool.uplugin` | PASS | present; `Installed: true`, `EngineVersion: "5.8.0"` |
| `Binaries\Win64` | PASS | present; Editor DLL/PDB files and Editor `.modules` |
| `Config` | FAIL | absent |
| `Content` | FAIL | absent |
| `Docs` | FAIL | absent |
| `.git` / `.github` | PASS | absent |
| `Intermediate` | FAIL | remains in final package |
| Game binaries / Game `.modules` | FAIL | none found |

Package file count was 66 and total size was 213,653,840 bytes. The packaged `.uplugin` SHA-256 is `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146`. The single packaged `.modules` SHA-256 is `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274`.

## 10. Blueprint-only load — FAIL

Because BuildPlugin passed, the final package was copied to a temporary host project:

- host root: `D:\T\S58-20260723-131534\H`
- project: `H\ServerManageToolBlueprintHost.uproject`
- no project `Modules` property was added
- enabled plugins: `ServerManageTool`, `PythonScriptPlugin`, `EditorScriptingUtilities`
- `GameDefaultMap` and `ServerDefaultMap`: `/Engine/Maps/Entry`
- final package: `H\Plugins\ServerManageTool`

The exact command reached `[Cmd: Quit]`, then stopped progressing during asset-registry/DerivedData maintenance. After more than three minutes without progress, process identity was checked against the exact host project path and PID 57320 was force-terminated. This is recorded as a failed completion, not as a successful exit.

- result: `FAIL`
- observed exit code after bounded forced cleanup: `-1`
- load log SHA-256: `D3BF8E28D535162DA3953A9BBEE3F684FCB7218DA1BF179DA98232E31315FFCA`
- console transcript SHA-256: `8B28BDAFE52E7AF2572475C9F3EC90258BD3F4F51B70531680E07C76BE38956D`
- plugin modules observed loading: `ServerInfoSettingsModule`, `ServerManageLibrary`, `ServerModePlayMenu`
- missing/incompatible-module message: not observed
- compile request or C++ conversion request: not observed
- exact host-project target process count after cleanup: 0
- exact host-project independent `-server` target process count after cleanup: 0

The log also contains normal installed-build warnings and the host's absent `Content` directory warning. Those observations do not turn the incomplete/hung Blueprint-only run into a pass.

## 11. Normal PIE lifecycle — BLOCKED

Not run. The user-specified stop condition applies because the Blueprint-only load did not complete successfully.

## 12. Simulate lifecycle — BLOCKED

Not run. The user-specified stop condition applies because the Blueprint-only load did not complete successfully.

## 13. Editor shutdown orphan — BLOCKED

Not run. No plugin-managed PIE or Simulate parent/child process was created after the Blueprint-only failure. The zero process count in Section 10 is host cleanup evidence, not an Editor-shutdown orphan result.

## 14. Direct-server evidence — Phase 1 carry-forward, not rerun post-category

The following direct-server evidence is preserved from Phase 1. It was not rerun after the Category-only source change in this phase. The Category declarations do not alter the direct-server launch/port path, so the evidence is carried forward with that scope correction.

- single: PID 43312, requested/actual port 17777/17777
- multiple: PID 29680, requested/actual port 17777/17777
- multiple: PID 60304, requested/actual port 17778/17778
- conflict: PID 18192, requested port 17777, actual port 17779, alive during the 30-second check
- final matching target process count after cleanup: 0

The direct-server result remains FAIL for the known requested-port conflict behavior. The PIDs and hashes below remain Phase 1 evidence and must not be read as post-category rerun evidence.

## 15. Remaining blockers — FAIL

1. Produce a Fab-compliant final package without `Intermediate` and with the required `Config`, `Content`, and `Docs` contents.
2. Produce and verify Game Development and Game Shipping package artifacts and their `.modules` mappings.
3. Establish a successful Blueprint-only host completion with a clean process exit.
4. Run normal PIE, Simulate, and Editor-shutdown orphan checks after the Blueprint-only gate passes.
5. Resolve the requested-port conflict policy; the carried-forward behavior changes 17777 to 17779 and leaves the conflict process alive during the check.
6. Complete the remaining Fab structural and release-quality gates recorded in the baseline report.

## 16. Evidence table — PASS

All short-root evidence below is under `D:\T\S58-20260723-131534`.

| Evidence | SHA-256 or result |
| --- | --- |
| `BuildPlugin-short-root.log` | `82D0DF6B6D191B4E05936C3D187FE6EB74730738EF1943FE038C0464F103541D` |
| `ShortRootFinalSummary.json` | `9873A75ACF85284B85CD022E5BAFEE5AC48C965142EF141CE95A368C9871CB92` |
| `BlueprintOnlyLoad.log` | `D3BF8E28D535162DA3953A9BBEE3F684FCB7218DA1BF179DA98232E31315FFCA` |
| `BlueprintOnlyLoad.console.txt` | `8B28BDAFE52E7AF2572475C9F3EC90258BD3F4F51B70531680E07C76BE38956D` |
| packaged `ServerManageTool.uplugin` | `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146` |
| packaged `UnrealEditor.modules` | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |
| long-path BuildPlugin log | `92CAF8BB7830DBB4B61FA6783C33DF34B4D06E8031F6BDD8BA0846EFA2503DA3` |
| long-path detailed UBT log | `0C5C9FC79A4BAABC00F8AA2C8191DCB4D6E407E38F4F8CB341CC1011502023BC` |
| Phase 1 direct validation script | `B60C6B0C34D6E0B8453658E578086FDD132A425AF4281D852B625FB74BAC68CD` |
| Phase 1 direct validation transcript | `FEE3788D16ECB24CCCA16251023BE165F797CAA3A65147BF221AA3A417104C0C` |
| Phase 1 direct validation result JSON | `514423D405E422FB5C1262F7A0DC3868169DCD0C466A5F38DE97BB92006AABAB` |
| Phase 1 `DirectSingle-17777.log` | `51DCB05FA8357A019CBA0990A37E41F708B5D809689C8DF11A76B4AE2298908D` |
| Phase 1 `DirectMulti-17777.log` | `0D1A1C9C1B88C0B5AFCB8B1D5A77EBA622C777E77494841A3D1FD3E5B869AA63` |
| Phase 1 `DirectMulti-17778.log` | `0C62C0AAD09EB7441E33FE80685BDFF1BCC43FC7F1E5385219F221B519BDBAE9` |
| Phase 1 `DirectConflict-17777.log` | `AA3C61902CDBFC362D5DB0DECE3D17F8840BA946FE5B25796995AB1A10C1ABF9` |
| final exact host target process count | `0` |
| source change in this phase | none; report-only repository change |

## 17. Exact short-root reproduction commands — PASS

Run from the repository root in PowerShell 7. The following is the short-root preflight and BuildPlugin command used for this verification:

```powershell
$ErrorActionPreference = "Stop"
$repoRoot = "D:\ghws\ServerManageToolPlugin"
$ueRoot = "C:\Program Files\Epic Games\UE_5.8"
$stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$auditRoot = "D:\T\S58-$stamp"
$packageRoot = Join-Path $auditRoot "P"
if (-not (Test-Path -LiteralPath "D:\" -PathType Container)) { throw "D: is unavailable" }
New-Item -ItemType Directory -Path "D:\T" -Force | Out-Null
if (Test-Path -LiteralPath $auditRoot) { throw "auditRoot already exists: $auditRoot" }
$freeBytes = (Get-PSDrive -Name D).Free
if ($freeBytes -lt 30GB) { throw "D: free space is below 30 GB" }
New-Item -ItemType Directory -Path $auditRoot -Force | Out-Null
New-Item -ItemType Directory -Path $packageRoot -Force | Out-Null
$buildLog = Join-Path $auditRoot "BuildPlugin-short-root.log"
& "$ueRoot\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin "-Plugin=$repoRoot\ServerManageTool.uplugin" "-Package=$packageRoot" -TargetPlatforms=Win64 -Rocket *> $buildLog
$exitCode = $LASTEXITCODE
Write-Output "BuildPluginExitCode=$exitCode"
if ($exitCode -ne 0) { throw "BuildPlugin failed: $exitCode" }
if (-not (Test-Path -LiteralPath "$packageRoot\ServerManageTool.uplugin" -PathType Leaf)) { throw "final .uplugin is missing" }
if (-not (Test-Path -LiteralPath "$packageRoot\Binaries\Win64" -PathType Container)) { throw "final Binaries\\Win64 is missing" }
if (@(Get-ChildItem -LiteralPath "$packageRoot\Binaries\Win64" -Filter '*.modules' -File).Count -lt 1) { throw "final .modules is missing" }
if (-not (Select-String -LiteralPath $buildLog -Pattern 'BUILD SUCCESSFUL')) { throw "success marker is missing" }
```

The Blueprint-only command used after the package gate was:

```powershell
& "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "D:\T\S58-20260723-131534\H\ServerManageToolBlueprintHost.uproject" -unattended -nop4 -nosplash -nullrhi -ExecCmds=Quit -AbsLog="D:\T\S58-20260723-131534\BlueprintOnlyLoad.log"
```

Normal PIE, Simulate, and shutdown-orphan commands were intentionally not run after the Blueprint-only failure. The complete Phase 1 direct-server script remains linked at [`FabBaseline-UE5.8-Win64.md`](FabBaseline-UE5.8-Win64.md#18-exact-reproduction-commands--pass); its hashes and scope are recorded in Sections 14 and 16 of this report.
