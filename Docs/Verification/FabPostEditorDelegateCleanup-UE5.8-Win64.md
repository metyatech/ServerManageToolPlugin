# Fab Post-Editor Delegate Cleanup Verification — UE 5.8 Win64

Verification date: 2026-07-27 (JST)

Verification root: `D:\T\SMTDG-20260727-132935`

## 1. Scope and verdict

This audit covers the requested lifecycle hardening for the raw `FEditorDelegates::BeginPIE` and `FEditorDelegates::EndPIE` registrations in `FServerModePlayMenuModule`.

The product change is limited to:

- retaining one `FDelegateHandle` per editor delegate;
- registering only when the corresponding handle is invalid;
- removing each delegate by its saved handle and resetting it during shutdown;
- clearing the managed `ServerProcesses` collection immediately after delegate removal during shutdown.

No port-conflict implementation, exit-status propagation, Fab structure, product documentation, server-process implementation, runtime validator, `.uplugin`, Config, or Content change was made.

| Decision | Result |
| --- | --- |
| Editor delegate cleanup | **PASS** |
| Existing editor exit-status classification | `EDITOR_STATUS_INCONSISTENT` (preserved; not reclassified) |
| Existing port-conflict implementation classification | `PARTIAL_PACKAGED_TEST_BLOCKED` (preserved) |
| Product readiness | **FAIL** |

The editor delegate cleanup blocker is resolved by this change. Product readiness remains `FAIL` because the unrelated Fab and packaged-product blockers listed in section 20 remain.

## 2. Start Git state

The start gate was executed with PowerShell 7 (`pwsh 7.6.3`) before any repository change.

| Check | Observed value |
| --- | --- |
| Repository | `D:\ghws\ServerManageToolPlugin` |
| Remote | `https://github.com/metyatech/ServerManageToolPlugin` (`metyatech/ServerManageToolPlugin`) |
| Starting branch | `fix/port-conflict-fail-fast` |
| Starting local HEAD | `3379866c73f34048400438deced75316462be5ef` |
| Starting `origin/fix/port-conflict-fail-fast` | `3379866c73f34048400438deced75316462be5ef` |
| Starting divergence | `0 0` |
| Starting working tree | Clean |
| Unreal Engine root | `C:\Program Files\Epic Games\UE_5.8` |
| `Build.version` | Major `5`, Minor `8` |
| `InstalledBuild.txt` | Present |
| Created branch | `fix/editor-delegate-cleanup` |
| Branch base | `3379866c73f34048400438deced75316462be5ef` |

## 3. Exact source changes

The source commit changes exactly these two allowed product files:

- [`ServerModePlayMenu.h`](../../Source/ServerModePlayMenu/Public/ServerModePlayMenu.h)
- [`ServerModePlayMenu.cpp`](../../Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp)

The source diff is 29 insertions and 3 deletions. The header adds the two private handle members at lines 30–31. The implementation changes only the editor delegate registration and shutdown prefix:

- `StartupModule()` checks both handles with `ensureAlwaysMsgf` and conditionally assigns the `AddRaw` return values.
- `ShutdownModule()` removes the saved handles, resets them, and then calls `ServerProcesses.clear()`.
- Existing ToolMenus, settings, menu, ServerList, launch, preflight, validator, notification, Blueprint API, log marker, `GetServerAddress`, and `RequestServerExit` code is unchanged.

Static source constraints passed:

- `BeginPIE.AddRaw`: one occurrence, inside one handle assignment.
- `EndPIE.AddRaw`: one occurrence, inside one handle assignment.
- `BeginPIE.Remove(saved handle)`: one occurrence.
- `EndPIE.Remove(saved handle)`: one occurrence.
- Both handle `Reset()` calls present.
- `ShutdownModule()` contains `ServerProcesses.clear()`.
- `RemoveAll(this)`: zero occurrences.
- Forbidden product paths: zero diff.
- `.uplugin`: zero diff.
- Port preflight, launch, runtime validator, and exit-status implementation: zero diff.
- `git diff --check`: PASS.

## 4. Delegate-handle design

The module owns two independent handles:

```cpp
FDelegateHandle BeginPIEDelegateHandle;
FDelegateHandle EndPIEDelegateHandle;
```

`StartupModule()` uses an invalid-handle guard for each registration. A repeated startup call therefore does not add a second raw callback. The `ensureAlwaysMsgf` calls expose an unexpected already-registered state without using `RemoveAll(this)` to mask it.

`ShutdownModule()` removes each delegate through the exact saved handle and immediately resets that handle. The probe verified the externally observable result on the actual module object: bound before shutdown, unbound after shutdown, and bound again after startup.

## 5. Shutdown ordering

The implemented order is fixed and was checked in the source:

1. Remove `BeginPIE` using `BeginPIEDelegateHandle` and reset it.
2. Remove `EndPIE` using `EndPIEDelegateHandle` and reset it.
3. Call `ServerProcesses.clear()`.
4. Unregister the ToolMenus startup callback.
5. Unregister the ToolMenus owner.
6. Unregister settings.

This prevents new PIE callbacks after shutdown starts and lets the existing `ServerProcess` destructor cleanup run when the managed collection is cleared. The active-PIE test in section 12 observed the managed child count reaching zero without harness-forced termination.

## 6. BuildPlugin

Command used:

```powershell
$stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$verifyRoot = "D:\T\SMTDG-$stamp"
$packageRoot = Join-Path $verifyRoot "P"
$buildLog = Join-Path $verifyRoot "BuildPlugin.log"

& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  "-Plugin=D:\ghws\ServerManageToolPlugin\ServerManageTool.uplugin" `
  "-Package=$packageRoot" `
  -TargetPlatforms=Win64 `
  -Rocket *> $buildLog

$buildExitCode = $LASTEXITCODE
```

Observed result:

| Gate | Result |
| --- | --- |
| BuildPlugin exit code | `0` |
| UnrealEditor Win64 Development | Succeeded |
| UnrealGame Win64 Development | Succeeded |
| UnrealGame Win64 Shipping | Succeeded |
| UHT Category errors | `0` |
| Path-length errors | `0` |
| `BUILD SUCCESSFUL` | Present |
| Final `.uplugin` | Present |
| `Binaries\Win64` | Present |
| `UnrealEditor.modules` | Present |

Build log: `D:\T\SMTDG-20260727-132935\BuildPlugin.log`.

## 7. Package

The product package is at `D:\T\SMTDG-20260727-132935\P` and was copied into the temporary host at `D:\T\SMTDG-20260727-132935\H\Plugins\ServerManageTool`.

The package contains the three expected product module DLLs:

- `UnrealEditor-ServerModePlayMenu.dll`
- `UnrealEditor-ServerManageLibrary.dll`
- `UnrealEditor-ServerInfoSettingsModule.dll`

Selected package SHA-256 values:

| Artifact | SHA-256 |
| --- | --- |
| `P\ServerManageTool.uplugin` | `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146` |
| `P\Binaries\Win64\UnrealEditor.modules` | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |
| `P\Binaries\Win64\UnrealEditor-ServerModePlayMenu.dll` | `E4EAC463C07DDDA3D5773579C82C560EED0AC97FFCF7C40474A4DEDA07997104` |
| `P\Binaries\Win64\UnrealEditor-ServerManageLibrary.dll` | `76F2AFE6E88F4346B4F4D7DFE33781B26464F8BA7A6779A3929B16C946F674B6` |
| `P\Binaries\Win64\UnrealEditor-ServerInfoSettingsModule.dll` | `361F2EE888CC16399025B582A1599771A6AAAEECCDCA7C05C9134D8B3A77F183` |
| `BuildPlugin.log` | `A180FD9F73DE709692CE6B6E1923DD1AD6F20167A597F1824D1449DF98E82668` |

## 8. Blueprint-only load

The clean-load host is Blueprint-only: no C++ `Modules` property is present in `ServerManageToolDelegateCleanupHost.uproject`. The enabled plugins are `ServerManageTool`, `PythonScriptPlugin`, `EditorScriptingUtilities`, and the temporary probe.

The existing Python keep-alive method was used. The final clean-load result was PASS:

- parent PID `55212`, exit code `0`;
- exactly three product module loads;
- missing modules `0`;
- incompatible modules `0`;
- compile requests `0`;
- C++ conversion requests `0`;
- fatal/ensure/crash count `0`;
- timeout `false`;
- forced termination `false`;
- final host process count `0`.

Result: `D:\T\SMTDG-20260727-132935\BlueprintOnlyCleanExit.summary.json`.

## 9. Probe plugin

The temporary probe source is at `D:\T\SMTDG-20260727-132935\ProbeSource\ServerManageToolDelegateProbe` and is not part of the repository.

It is an Editor module with only the requested minimum dependencies: `Core`, `CoreUObject`, `Engine`, `UnrealEd`, `Json`, and `Projects`. It has no `ServerModePlayMenu` Build.cs dependency and uses `FModuleManager` plus `IModuleInterface` to obtain the product module by name.

The probe calls only the product module's `StartupModule()` and `ShutdownModule()` and reads `IsBoundToObject` for the two editor delegates. It does not remove delegates, use `RemoveAll`, access product handles or `ServerProcesses`, start/stop a server, or access UDP ports.

Probe BuildPlugin result:

- exit code `0`;
- UnrealEditor Win64 Development succeeded;
- probe package generated;
- DLL and modules manifest generated;
- `BUILD SUCCESSFUL` present.

Probe log: `D:\T\SMTDG-20260727-132935\ProbeBuildPlugin.log`.

Probe package hashes:

| Artifact | SHA-256 |
| --- | --- |
| `ProbePackage\ServerManageToolDelegateProbe.uplugin` | `B23CAC87FD189B75613BF2075D79011B72DC52816D7FFFC4525FAF009DDFCD48` |
| `ProbePackage\Binaries\Win64\UnrealEditor-ServerManageToolDelegateProbe.dll` | `97EDBF0415E94BFC4D1B12B2E75B1877B10B13919EA37FC1B176D8D764ED7B29` |
| `ProbePackage\Binaries\Win64\UnrealEditor.modules` | `E2A092EDB794EAEEB4208D39C387056A9626BD8F0211513EAB6F4E861521D76B` |
| `ProbeBuildPlugin.log` | `A1E15280290506EC1B32BD506268BCEB716690A7ACD62A5D5798B185B3608E92` |

Probe source hashes:

| Artifact | SHA-256 |
| --- | --- |
| `ProbeSource\...\ServerManageToolDelegateProbe.uplugin` | `B7FECDAB543D205120E61F185A395D4789D2A7798220E63BB7854EC600D0C620` |
| `ProbeSource\...\ServerManageToolDelegateProbe.Build.cs` | `54DD15B531FFB53828C83E18BBB017D792E6B740764C99958BCD94AD1E95732E` |
| `ProbeSource\...\ServerManageToolDelegateProbe.cpp` | `DC0C2C19E1002DED8684E0AC0306E9B915E0505518469553A8E7D635DC4A4C7E` |
| `ProbeSource\...\Config\FilterPlugin.ini` | `B7776C3DF4F21643B440B96BDFCFB22E111F353A1D99BC5E0D8AC95133BFA8C1` |

## 10. Three lifecycle cycles

The same product module instance was used for all three cycles. `DelegateCycle.json` reported `PASS`, initial bound state `true/true`, final bound state `true/true`, and an empty error list.

| Cycle | Before shutdown Begin/End | After shutdown Begin/End | After startup Begin/End |
| ---: | --- | --- | --- |
| 1 | `true / true` | `false / false` | `true / true` |
| 2 | `true / true` | `false / false` | `true / true` |
| 3 | `true / true` | `false / false` | `true / true` |

This is direct evidence for Startup → Shutdown → Startup repeatability, no dangling raw delegate after shutdown, no duplicate callback registration, and valid final startup state.

## 11. First PIE after cycles

The first PIE after the three delegate cycles used parent PID `35172` and exactly two managed child PIDs:

| Child PID | Parent PID | Requested port | Actual port | First seen | Last seen |
| ---: | ---: | ---: | ---: | --- | --- |
| `64784` | `35172` | `7777` | `7777` | `04:58:27` | `04:58:56` |
| `51240` | `35172` | `7778` | `7778` | `04:58:27` | `04:58:56` |

The parent and child command lines contained the absolute host `.uproject` path; each child was an independent `-server` process. The first PIE result was:

- `SMT_PORT_PREFLIGHT_PASSED`: exactly `1`;
- requested ports: `7777`, `7778`, with no duplicate requested-port snapshot;
- actual validation: `7777 → 7777` and `7778 → 7778`;
- validation PASS: `2`;
- validation FAIL: `0`;
- launch failures: `0`;
- maximum observed child count: `2`;
- child count `3` or greater: `0` snapshots;
- ready within the 30-second acceptance window: PASS.

## 12. Active-PIE module shutdown

During the first PIE, the probe called `SMT.DelegateShutdown` while the play session remained active.

- shutdown JSON: `PASS`;
- before bound state: Begin/End `true/true`;
- after bound state: Begin/End `false/false`;
- managed child count reached `0` within the 10-second holding interval;
- product child UDP owner count reached `0`;
- editor parent PID `35172` remained alive;
- PIE was kept active until the Python harness explicitly ended it;
- harness forced cleanup: `false`.

This is the runtime evidence for `ServerProcesses.clear()` in `ShutdownModule()`.

## 13. Module startup after shutdown

While the same PIE remained active, the probe called `SMT.DelegateStartup` once.

- startup JSON: `PASS`;
- before bound state: Begin/End `false/false`;
- after bound state: Begin/End `true/true`;
- maximum child count during the startup-only interval: `0`;
- no server was started by `StartupModule()`;
- the following PIE end completed normally.

## 14. Second PIE after re-registration

The second PIE used the same editor parent PID `35172` and exactly two new managed child PIDs:

| Child PID | Parent PID | Requested port | Actual port | First seen | Last seen |
| ---: | ---: | ---: | ---: | --- | --- |
| `69492` | `35172` | `7777` | `7777` | `04:59:14` | `04:59:43` |
| `35292` | `35172` | `7778` | `7778` | `04:59:14` | `04:59:43` |

Second-PIE acceptance passed:

- one additional `SMT_PORT_PREFLIGHT_PASSED` marker;
- cumulative preflight PASS markers: exactly `2`;
- validation PASS in the second PIE: `2`;
- cumulative validation PASS markers: `4`;
- validation FAIL: `0`;
- maximum child count: `2`;
- child count `3` or greater: `0` snapshots;
- EndPIE child count: `0`;
- final UDP owner count: `0`.

## 15. Normal PIE regression

The normal regression run executed without issuing any probe command.

- parent PID: `9836`, exit code `0`;
- child PIDs: `36264` on `7777`, `69604` on `7778`;
- both child `ParentProcessId` values: `9836`;
- actual ports: `7777`, `7778`;
- preflight PASS: `1`;
- validation PASS: `2`;
- validation FAIL: `0`;
- maximum child count: `2`;
- final child count: `0`;
- final UDP owner count: `0`;
- timeout/forced cleanup: `false/false`.

Result: `PASS`.

## 16. Simulate regression

The Simulate regression run executed without issuing any probe command.

- parent PID: `53612`, exit code `0`;
- child PIDs: `42180` on `7777`, `67204` on `7778`;
- both child `ParentProcessId` values: `53612`;
- actual ports: `7777`, `7778`;
- preflight PASS: `1`;
- validation PASS: `2`;
- validation FAIL: `0`;
- maximum child count: `2`;
- final child count: `0`;
- final UDP owner count: `0`;
- timeout/forced cleanup: `false/false`.

Result: `PASS`.

## 17. ORPHAN regression

The ORPHAN regression run executed without issuing any probe command. The parent exited naturally and the monitor continued for more than 10 seconds after parent exit.

- parent PID: `48168`, exit code `0`;
- child PIDs: `54156` on `7777`, `71336` on `7778`;
- both child `ParentProcessId` values: `48168`;
- actual ports: `7777`, `7778`;
- preflight PASS: `1`;
- validation PASS: `2`;
- validation FAIL: `0`;
- maximum child count: `2`;
- every post-parent-exit poll in the 10-second observation window had child count `0`;
- final UDP owner count: `0`;
- timeout/forced cleanup: `false/false`.

Result: `PASS`.

## 18. 7778 conflict regression

This was a preflight-only conflict regression. An independent holder exclusively bound UDP `7778` before Local Launch PIE.

- holder PID: `51124`;
- holder endpoint before planned cleanup: one owner on `7778`;
- holder remained alive during the plugin test;
- `SMT_PORT_PREFLIGHT_FAILED`: `1`;
- unavailable port: `7778`;
- `started_server_count=0`: `1`;
- managed child count: `0` throughout;
- shifted child count: `0`;
- `7777` child was not started;
- holder was not terminated by the plugin;
- planned holder cleanup removed the holder and left endpoint count `0`;
- parent exited naturally and no harness-forced cleanup was used.

The exact marker was:

```text
SMT_PORT_PREFLIGHT_FAILED unavailable_ports=7778 server_count=2 started_server_count=0 rollback_count=0
```

The existing classification remains unchanged: `Port conflict implementation — PARTIAL_PACKAGED_TEST_BLOCKED`. Port-conflict exit-status classification was not rerun or changed.

## 19. Process cleanup

The monitor accepted a child only when all of the following held:

- PID was recorded by the harness;
- executable name was `UnrealEditor.exe`;
- command line contained the absolute host `.uproject` path;
- server child command line contained independent `-server`.

The monitor recorded parent PID, `ParentProcessId`, command line, requested port, child count, and UDP owners every 0.25–0.5 seconds. No unrelated UnrealEditor process was terminated. All accepted lifecycle runs ended with zero matching children and zero product UDP owners. Forced cleanup was false for clean load, delegate lifecycle, PIE, Simulate, ORPHAN, and conflict runs.

## 20. Remaining blockers

The delegate cleanup blocker is removed because this audit passed. Product readiness remains **FAIL** for these independent blockers:

- Fab Config remains insufficient.
- Fab Content remains insufficient.
- User documentation remains insufficient.
- Real game-project Development/Shipping integration remains unverified.
- Packaged executable remains unverified.
- Requested exit-status propagation remains unresolved; existing classification remains `EDITOR_STATUS_INCONSISTENT`.
- Port conflict implementation remains `PARTIAL_PACKAGED_TEST_BLOCKED`.

No stop condition from the requested delegate-cleanup scope was encountered: the probe did not need to remove product delegates, ToolMenus/settings were restored, active shutdown removed managed children, lifecycle cycles did not create three or more children, and normal PIE/Simulate/ORPHAN passed.

## 21. Evidence SHA-256

The complete temporary evidence set is covered by:

```text
D:\T\SMTDG-20260727-132935\Evidence-SHA256.txt
```

It contains 289 SHA-256 records for all files under the verification root, excluding the manifest itself. Manifest SHA-256:

```text
A8598A769ECF17D850AFB21272119500D217C69754D61991871678F3822592FD
```

Selected source hashes:

| Artifact | SHA-256 |
| --- | --- |
| `Source\ServerModePlayMenu\Public\ServerModePlayMenu.h` | `6E81109D1214624A776CA9E1FB45D2E95504A30E412B7C3E30765623EF6BF828` |
| `Source\ServerModePlayMenu\Private\ServerModePlayMenu.cpp` | `9F280D1142D027B5B67307CD5B417D7C1C19C4C25E72FC00E98CA666204BCDEC` |
| `DelegateCycle.json` | `6F2419A0DE7F644995A60786D2A07E57B768283F8BF3F54D7B65E362FDCFCCAE` |
| `DelegateShutdown.json` | `3AD5D7AD25B4FE1F8C965AE928F0AE45E6E13AB7F0B64A9541CBD60A9A07FFFC` |
| `DelegateStartup.json` | `53AE4D3BDAA3912C0F3B37D4888526B0BB86D76D95B064FA09DEE5B5E44E3188` |
| `DelegateLifecycle.summary.json` | `80E59C039C28ED68DCD1B0E1A7510339224FEB0E1B41B713231DF69E1D38299F` |
| `BlueprintOnlyCleanExit.summary.json` | `B086B59C472371E9C99B436383916DB2923A984F3B6ABF3E6CEA7900284C4FCE` |
| `Normal-PIE.summary.json` | `9F8ABFCA3034D0DE9DDCE3494095A22CDBD9606590052F7439A4F37C4B9944A6` |
| `Normal-SIMULATE.summary.json` | `ADFF602288F6C8CD782F8A8966B209B7E0D81FF9DCE0C23BD6BAE5617CD7FAE9` |
| `Normal-ORPHAN.summary.json` | `F39D2CB784B76F50CD1CC9F23AB5F4D14E6A45CBA28B9348A9E714793FE7733D` |
| `PortConflict.summary.json` | `8DED5B2199357F8037DE391993DA51F8E7F966BF5618A0AC92AB423CDD95690F` |

The package and probe hashes are recorded in sections 7 and 9. The report commit hash is intentionally supplied by the final handoff: including a commit's own hash in that commit would require an amend or a third commit, both prohibited by the request.

## 22. Exact reproduction commands

The following commands reproduce the principal gates using the recorded temporary root. Temporary host, probe, harness, logs, and packages remain outside the repository.

Build the product package:

```powershell
$verifyRoot = "D:\T\SMTDG-20260727-132935"
$packageRoot = Join-Path $verifyRoot "P"
$buildLog = Join-Path $verifyRoot "BuildPlugin.log"
& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  "-Plugin=D:\ghws\ServerManageToolPlugin\ServerManageTool.uplugin" `
  "-Package=$packageRoot" `
  -TargetPlatforms=Win64 `
  -Rocket *> $buildLog
$buildExitCode = $LASTEXITCODE
```

Build the temporary probe:

```powershell
& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  "-Plugin=D:\T\SMTDG-20260727-132935\ProbeSource\ServerManageToolDelegateProbe\ServerManageToolDelegateProbe.uplugin" `
  "-Package=D:\T\SMTDG-20260727-132935\ProbePackage" `
  -TargetPlatforms=Win64 `
  -Rocket
```

Run the clean Blueprint-only load, delegate lifecycle, and normal regression harnesses:

```powershell
pwsh -NoProfile -File D:\T\SMTDG-20260727-132935\RunBlueprintOnlyCleanExit.ps1
pwsh -NoProfile -File D:\T\SMTDG-20260727-132935\RunDelegateLifecycle.ps1
pwsh -NoProfile -File D:\T\SMTDG-20260727-132935\RunNormalLifecycle.ps1 -Mode PIE
pwsh -NoProfile -File D:\T\SMTDG-20260727-132935\RunNormalLifecycle.ps1 -Mode SIMULATE
pwsh -NoProfile -File D:\T\SMTDG-20260727-132935\RunNormalLifecycle.ps1 -Mode ORPHAN
```

The conflict harness is preflight-only and uses an independent UDP holder; it must not be used to reclassify the existing exit-status result:

```powershell
pwsh -NoProfile -File D:\T\SMTDG-20260727-132935\RunPortConflict.ps1
```

Verify the source scope and whitespace:

```powershell
git diff --check 3379866c73f34048400438deced75316462be5ef..HEAD
git diff --name-only 3379866c73f34048400438deced75316462be5ef..HEAD
rg -n "BeginPIE\.AddRaw|EndPIE\.AddRaw|BeginPIE\.Remove|EndPIE\.Remove|RemoveAll\(this\)|ServerProcesses\.clear|BeginPIEDelegateHandle|EndPIEDelegateHandle" Source/ServerModePlayMenu
```

## 23. Final Git state

The product-source commit was created first:

```text
Commit: b198cb9920f8a6feb4c6b43eab756a124ddfd571
Message: fix: unregister editor PIE delegates
URL: https://github.com/metyatech/ServerManageToolPlugin/commit/b198cb9920f8a6feb4c6b43eab756a124ddfd571
```

The report is the only file in the second commit, with message:

```text
docs: verify editor delegate cleanup
```

The second commit SHA, pushed branch URL, final divergence, and final clean-working-tree result are supplied in the final handoff immediately after the second commit and push. The report cannot contain its own final commit SHA without violating the requested two-commit/no-amend constraint.

Required final state:

- branch: `fix/editor-delegate-cleanup`;
- remote: `origin/fix/editor-delegate-cleanup`;
- remote HEAD: report commit;
- divergence: `0 0`;
- working tree: clean;
- no force push, PR, tag, release, or Fab submission.
