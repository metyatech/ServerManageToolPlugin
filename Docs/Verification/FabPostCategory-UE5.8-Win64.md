# Post-category Verification: UE 5.8 / Win64

Verification date: 2026-07-23 (Asia/Tokyo)

This report records the Blueprint-only clean-exit and Server lifecycle verification requested for the existing `fix/ue58-uht-categories` branch. Source code was not changed. The only repository file changed by this phase is this report. All host projects, scripts, logs, JSON, monitor evidence, and package copies were kept outside the repository.

## 1. Verification execution status — PASS

All requested verification runners reached terminal results:

- the existing short-root BuildPlugin package was reused after exact SHA-256 verification;
- Blueprint-only plugin compatibility passed;
- Blueprint-only clean exit passed without force termination;
- the initial Normal PIE, Simulate, and single strict ORPHAN observations are retained as historical evidence;
- the single strict ORPHAN failure is explicitly treated as the trigger for the five-run repeatability investigation in Section 27;
- all five independent ORPHAN runs reached terminal results and passed the strict same-snapshot, timing, parent-exit, and cleanup predicates.

The verification execution status is PASS because all five terminal ORPHAN runs passed the authoritative repeatability acceptance. Product/Fab readiness remains FAIL because the package is still missing required Fab structure and real-game-project integration and packaged-executable execution were not tested.

## 2. Product readiness status — FAIL

The five UE 5.8 UHT Category declarations are fixed, BuildPlugin reports success for all three requested targets, and the package loads and runs the requested host lifecycle. Fab release readiness is not established because `Config`, `Content`, and user-facing `Docs` are absent from the final package. Real game-project Development/Shipping integration and packaged executable execution remain untested. The known requested-port conflict behavior and static delegate-unregister concern also remain blockers.

## 3. Git baseline and scope — PASS

- repository: `D:\ghws\ServerManageToolPlugin`
- origin: `https://github.com/metyatech/ServerManageToolPlugin`
- branch: `fix/ue58-uht-categories`
- start HEAD: `5c6fa1142f0bfc4761fb34ba21e37b3c82776e9f`
- start `origin/fix/ue58-uht-categories`: `5c6fa1142f0bfc4761fb34ba21e37b3c82776e9f`
- start divergence: `0 0`
- start worktree: clean
- category-fix commit: [`d67cac11d1ee93b8c9fe8d0f8d56952e83f95f09`](https://github.com/metyatech/ServerManageToolPlugin/commit/d67cac11d1ee93b8c9fe8d0f8d56952e83f95f09)
- preceding verification commit: [`c58810a98d58299777f089bcc59f794e1c6ed5ac`](https://github.com/metyatech/ServerManageToolPlugin/commit/c58810a98d58299777f089bcc59f794e1c6ed5ac)
- End HEAD: the commit that records this report; its exact SHA and URL are supplied in the delivery result
- no source, `.uplugin`, Build.cs, Config, Content, README, CI, package script, or unrelated repository file was changed
- no amend, rebase, squash, merge, PR, tag, release, or force push was performed

## 4. Exact source state carried into this verification — PASS

The verified source state contains the requested five Category declarations:

- `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:15` — `Category = "Server Management"`
- `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:18` — `Category = "Server Management"`
- `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:30` — `Category = "Server Management"`
- `Source/ServerManageLibrary/Public/ServerManageLibraryBP.h:21` — `Category = "Server Management"`
- `Source/ServerManageLibrary/Public/ServerManageLibraryBP.h:24` — `Category = "Server Management"`

The existing `EditAnyWhere` spelling was preserved. No source file was modified in this phase.

## 5. UE environment and reused BuildPlugin package — PASS

PowerShell 7 was used with the Launcher Installed Build:

    C:\Program Files\Epic Games\UE_5.8

`Build.version` reported Major 5, Minor 8, Patch 0. `InstalledBuild.txt` exists.

The existing package was reused because all requested hashes matched:

- BuildPlugin root: `D:\T\S58-20260723-131534`
- package root: `D:\T\S58-20260723-131534\P`
- BuildPlugin log: `82D0DF6B6D191B4E05936C3D187FE6EB74730738EF1943FE038C0464F103541D`
- packaged `.uplugin`: `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146`
- packaged `.modules`: `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274`

## 6. BuildPlugin and configuration results — PASS

The existing short-root BuildPlugin log reports all three requested configurations as successful:

| Configuration | BuildPlugin log result | Result |
| --- | --- | --- |
| UnrealEditor Win64 Development | `Result: Succeeded` | PASS |
| UnrealGame Win64 Development | `Result: Succeeded` | PASS |
| UnrealGame Win64 Shipping | `Result: Succeeded` | PASS |

Additional BuildPlugin gates:

- exit code: `0`
- `BUILD SUCCESSFUL`: present
- AutomationTool exit: `0 (Success)`
- UHT Category error count: `0`
- 260-character path error count: `0`

The absence of Game DLLs or Game `.modules` in the final package is recorded as package output information, not as a BuildPlugin target failure.

Separate integration/execution scope:

| Scope | Result |
| --- | --- |
| Real game project Development integration | NOT_TESTED |
| Real game project Shipping integration | NOT_TESTED |
| Packaged executable execution | NOT_TESTED |

## 7. Final package structure — FAIL for Fab structure; target build remains PASS

Final package top-level entries were:

    Binaries
    Intermediate
    Resources
    Source
    ServerManageTool.uplugin

| Package item | Result | Evidence |
| --- | --- | --- |
| `.uplugin` | PASS | present; `Installed: true`, `EngineVersion: "5.8.0"` |
| `Binaries\Win64` | PASS | present; complete file inventory in Section 8 |
| `Source` | PASS | present |
| `Resources` | PASS | present |
| `Config` | FAIL | absent; Fab structure requirement |
| `Content` | FAIL | absent; Fab structure requirement |
| `Docs` | FAIL | absent; product-quality gate |
| `.git` / `.github` | PASS | not included |
| `Intermediate` | PRESENT | present; not treated as a failure by existence alone |
| Game DLL / Game `.modules` | INFORMATION | not generated in the final package; not treated as a BuildPlugin target failure |

Package file count was 66 and total size was 213,653,840 bytes.

## 8. `Binaries\Win64` complete inventory — PASS

All paths are relative to `D:\T\S58-20260723-131534\P`.

| Relative path | Size | SHA-256 |
| --- | ---: | --- |
| `Binaries/Win64/UnrealEditor-ServerInfoSettingsModule.dll` | 70144 | `7D6BE42779C387FDA576047C0CA41F4BBC62E0024BF4BD691E16C91D29D61A75` |
| `Binaries/Win64/UnrealEditor-ServerInfoSettingsModule.pdb` | 61517824 | `AD82189CC3E42523A08CEFACC1D80E7D6233D27E49CC5C81EA6101104C45DD22` |
| `Binaries/Win64/UnrealEditor-ServerManageLibrary.dll` | 72192 | `0B03AEFD974B2E55DC6A8BFA67EC5EC114F034BA3428A2504B653DC7E4C3E367` |
| `Binaries/Win64/UnrealEditor-ServerManageLibrary.pdb` | 61575168 | `6AF1016454BDD8E37A7C5EF2DCABC978AAFA53C083F12F9350CEDE3CB1EBF737` |
| `Binaries/Win64/UnrealEditor-ServerModePlayMenu.dll` | 114688 | `0C69A26A388961F9FD9873DE39D2E51C73C298712D25D67F447C4D1ACFE1EF4D` |
| `Binaries/Win64/UnrealEditor-ServerModePlayMenu.pdb` | 61935616 | `6F736426694F89AD548EB1DC4A1E33D107DDFE79BD54660824582AC25BCB6BB3` |
| `Binaries/Win64/UnrealEditor.modules` | 256 | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |

## 9. Packaged `.modules` full JSON — PASS

The complete final `.modules` file is:

```json
{
  "BuildId": "55116800",
  "Modules":
  {
    "ServerInfoSettingsModule": "UnrealEditor-ServerInfoSettingsModule.dll",
    "ServerManageLibrary": "UnrealEditor-ServerManageLibrary.dll",
    "ServerModePlayMenu": "UnrealEditor-ServerModePlayMenu.dll"
  }
}
```

This is the Editor mapping. Game mappings were not generated in the final package, which is separate from the successful BuildPlugin target results in Section 6.

## 10. BuildPlugin detailed UBT/UBA logs — PASS

The short-root BuildPlugin log references these detailed logs:

| Target | Referenced path | Result |
| --- | --- | --- |
| UnrealEditor Win64 Development | `C:\Users\Origin\AppData\Roaming\Unreal Engine\AutomationTool\Logs\C+Program+Files+Epic+Games+UE_5.8\UBA-UnrealEditor-Win64-Development.txt` | preserved; SHA-256 `ACFECF8780E745B6480E8A5B7DFDE0CC07917E6F3BE6F5E7084E67E1654C3A19` |
| UnrealGame Win64 Development | `C:\Users\Origin\AppData\Roaming\Unreal Engine\AutomationTool\Logs\C+Program+Files+Epic+Games+UE_5.8\UBA-UnrealGame-Win64-Development.txt` | `NOT_PRESERVED`; hash not guessed |
| UnrealGame Win64 Shipping | `C:\Users\Origin\AppData\Roaming\Unreal Engine\AutomationTool\Logs\C+Program+Files+Epic+Games+UE_5.8\UBA-UnrealGame-Win64-Shipping.txt` | `NOT_PRESERVED`; hash not guessed |

The combined BuildPlugin log remains the authoritative evidence for the three target results.

## 11. Blueprint-only plugin load compatibility — PASS

Verification root: `D:\T\S58L-20260723-135846`.

Host project:

- project: `D:\T\S58L-20260723-135846\H\ServerManageToolBlueprintHost.uproject`
- final package copied to `H\Plugins\ServerManageTool`
- project C++ `Modules` property: absent
- enabled plugins: `ServerManageTool`, `PythonScriptPlugin`, `EditorScriptingUtilities`
- `GameDefaultMap` and `ServerDefaultMap`: `/Engine/Maps/Entry`

The Python marker JSON status is `PASS`, engine version is `5.8.0-55116800+++UE5+Release-5.8`, and the required plugin modules were observed loading:

- `ServerInfoSettingsModule`
- `ServerManageLibrary`
- `ServerModePlayMenu`

Compatibility scan results:

- missing module: 0
- incompatible module: 0
- compile request: 0
- C++ project-conversion request: 0
- fatal error: 0
- ensure: 0
- actual crash event: 0

Each log contains one normal UE crash-reporting abort-handler registration line; it is not a crash event.

## 12. Blueprint-only clean exit — PASS

The clean-exit harness used no `-ExecCmds=Quit`.

- PID: `65416`
- marker: `PASS`
- exit code: `0`
- timeout: `False`
- force termination: `False`
- host-project target processes after exit: `0`
- stdout/stderr were captured separately; stderr size was 0
- log reached `LogExit: Exiting.` and closed normally

## 13. Initial lifecycle observation — superseded as acceptance evidence

Status: `OBSERVED_PASS_SUPERSEDED`.

This initial observation is retained but is not authoritative for acceptance because its harness did not require the two-child/actual-port condition in the PASS predicate.

The lifecycle Python result was PASS and the parent exited normally.

- parent PID: `37972`
- parent exit code: `0`
- child PID `65612`: requested port `7777`, actual listen port `7777`, parent PID `37972`
- child PID `57904`: requested port `7778`, actual listen port `7778`, parent PID `37972`
- child cleanup: no forced cleanup
- final target child count: `0`
- monitor polls: `34`

The Python state transitions reached play start, held play for 15 seconds, ended play, waited 10 seconds, and requested editor quit.

## 14. Initial Simulate observation — superseded as acceptance evidence

Status: `OBSERVED_PASS_SUPERSEDED`.

This initial observation is retained but is not authoritative for acceptance because its harness did not require the two-child/actual-port condition in the PASS predicate.

The lifecycle Python result was PASS and the parent exited normally.

- parent PID: `21916`
- parent exit code: `0`
- child PID `17188`: requested port `7777`, actual listen port `7777`, parent PID `21916`
- child PID `59692`: requested port `7778`, actual listen port `7778`, parent PID `21916`
- child cleanup: no forced cleanup
- final target child count: `0`
- monitor polls: `34`

The start operation used `editor_play_simulate()`; end, wait, and quit completed normally.

## 15. Single strict ORPHAN run — trigger for repeatability investigation

Status: `HISTORICAL_TRIGGER` (retained; not the final five-run acceptance result).

This initial observation is retained but is not authoritative for acceptance because its harness did not include explicit 10-second post-parent-exit monitoring.

The ORPHAN Python result was PASS. The script did not call `editor_request_end_play()`; it requested editor quit while the play state was active.

- parent PID: `32604`
- parent exit code: `0`
- child PID `30428`: requested port `7777`, actual listen port `7777`, parent PID `32604`
- child PID `59952`: requested port `7778`, actual listen port `7778`, parent PID `32604`
- parent termination by harness: no
- child cleanup by harness: no
- orphan count after parent termination and bounded observation: `0`
- final target child count: `0`
- monitor polls: `25`

The parent and both child processes were gone at final verification, with no forced cleanup.

## 16. Previous `-ExecCmds=Quit` result retained as legacy harness evidence

The previous `-ExecCmds=Quit` result was not deleted. It remains a separate legacy-harness result and is not used as the clean-exit result in Section 12:

- previous log: `D:\T\S58-20260723-131534\BlueprintOnlyLoad.log`
- previous console transcript: `D:\T\S58-20260723-131534\BlueprintOnlyLoad.console.txt`
- previous result: hung after `[Cmd: Quit]`, then was force-terminated
- previous log SHA-256: `D3BF8E28D535162DA3953A9BBEE3F684FCB7218DA1BF179DA98232E31315FFCA`
- previous console SHA-256: `8B28BDAFE52E7AF2572475C9F3EC90258BD3F4F51B70531680E07C76BE38956D`

The new Python keep-alive clean-exit result supersedes that harness only for the clean-exit acceptance gate; the old evidence remains for reproducibility of the earlier failure.

## 17. Direct-server evidence — Phase 1 carry-forward, not rerun post-category

The following direct-server evidence is preserved from Phase 1. It was not rerun after the Category-only source change:

- single: PID 43312, requested/actual port 17777/17777
- multiple: PID 29680, requested/actual port 17777/17777
- multiple: PID 60304, requested/actual port 17778/17778
- conflict: PID 18192, requested port 17777, actual port 17779, alive during the 30-second check
- final matching target process count after cleanup: 0

The known requested-port conflict behavior remains a product blocker. Phase 1 hashes are retained:

- script: `B60C6B0C34D6E0B8453658E578086FDD132A425AF4281D852B625FB74BAC68CD`
- transcript: `FEE3788D16ECB24CCCA16251023BE165F797CAA3A65147BF221AA3A417104C0C`
- result JSON: `514423D405E422FB5C1262F7A0DC3868169DCD0C466A5F38DE97BB92006AABAB`
- `DirectSingle-17777.log`: `51DCB05FA8357A019CBA0990A37E41F708B5D809689C8DF11A76B4AE2298908D`
- `DirectMulti-17777.log`: `0D1A1C9C1B88C0B5AFCB8B1D5A77EBA622C777E77494841A3D1FD3E5B869AA63`
- `DirectMulti-17778.log`: `0C62C0AAD09EB7441E33FE80685BDFF1BCC43FC7F1E5385219F221B519BDBAE9`
- `DirectConflict-17777.log`: `AA3C61902CDBFC362D5DB0DECE3D17F8840BA946FE5B25796995AB1A10C1ABF9`

## 18. Remaining blockers — FAIL

1. Add and verify Fab-required `Config` content.
2. Add and verify Fab-required `Content` content where required by the product package.
3. Add user-facing product documentation under the package `Docs` requirement.
4. Test integration into a real game project for Development and Shipping.
5. Test execution of a packaged executable.
6. Resolve the known requested-port conflict behavior from Phase 1.
7. Review and correct the static delegate-unregister behavior identified by the baseline audit.

## 19. Evidence hashes — PASS

### Build/package evidence

| Evidence | SHA-256 |
| --- | --- |
| `D:\T\S58-20260723-131534\BuildPlugin-short-root.log` | `82D0DF6B6D191B4E05936C3D187FE6EB74730738EF1943FE038C0464F103541D` |
| packaged `ServerManageTool.uplugin` | `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146` |
| packaged `Binaries/Win64/UnrealEditor.modules` | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |
| detailed UBA UnrealEditor log | `ACFECF8780E745B6480E8A5B7DFDE0CC07917E6F3BE6F5E7084E67E1654C3A19` |

### Host/config evidence

| Evidence | SHA-256 |
| --- | --- |
| `H/ServerManageToolBlueprintHost.uproject` | `E94B69E442C4400A735EBD20AF3D525C44B47B3BCB8F9D6E52C8910057F978A5` |
| `H/Config/DefaultEngine.ini` | `2B9C6AE3F8C838A514C0C53ACD76F179B63FD7D0C2C5D635F92E54A454E918BE` |
| `H/Config/DefaultEditorPerProjectUserSettings.ini` | `E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C` |

### Blueprint-only evidence

| Evidence | SHA-256 |
| --- | --- |
| `BlueprintOnlyCleanExit.py` | `02548035C1195D0E439450FFAB13F872F2C1E2917EF11BB06D2DA9027FC997C9` |
| `RunBlueprintOnlyCleanExit.ps1` | `C70DE0A8138BC30B1D8E7B8FC70B99365195F37EF6F33B4335293A100FB89B98` |
| `BlueprintOnlyCleanExit.json` | `EB460D296355AD81BBE1836F37FC1BB5846C3834DE04DD97E5C18976F1FE60ED` |
| `BlueprintOnlyCleanExit.summary.json` | `FE261104493E758314860C4AF01933EE2FF9DA7307CD00461C3FCCC39CBCA30F` |
| `BlueprintOnlyCleanExit.log` | `9CCBD363B65ED6FFA3AB654438EA330EE2485BA0974CA9C5E9F61BE3F403F775` |
| `BlueprintOnlyCleanExit.stdout.txt` | `4A46059EA3EF6E09C83D39E1D339AA4DC66C905A28C93AF8146CF036F2D009DA` |
| `BlueprintOnlyCleanExit.stderr.txt` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |

### Lifecycle evidence

| Mode | Result JSON | Summary JSON | Log | Stdout | Stderr | Monitor |
| --- | --- | --- | --- | --- | --- | --- |
| PIE | `7CA734AF690648533602024D5A2025AC0FC116C11EA39A42BE7D25DBFCA37254` | `E0DD60CAA727AA700382A47C0F68E265B9606BBD8276C7BD9D60FE150C101F43` | `019B667BD77D360EDA3485BADDA43EB5D2D029992D14F38A0FA7E2539D4ADF35` | `0D752AD0DFEC17CA61CEDBD1E200A5432EAB045FC3AEF9F9F42D17CAD6C6D8C4` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` | `3DA149EBF71DECFDF0816CAAB46243C0100C9A68221E1ABDEE5FEFFC7E682029` |
| Simulate | `78C419560ED51AF509937168976550DBD95CCD12E21219C4BB55827D8ECB2976` | `A87A8B2DD65E1D7D0472BEEA01576FC71011F5225DC895CC53F9B4701EA1ABD4` | `7A7B71CD7A88898FAAFCCBAEEB0066135C99BA09250290BB5213C8109D3CED45` | `9AA42FEDE73A9A04773AE474CA0A8F58CAC209D2C1D738D41082FB2D4BF941CF` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` | `6D1E4102CAC72A8E8F0DEA2A44DCD609FA4275582FDC7C1328C67AD1209EDDE3` |
| ORPHAN | `5BCC36939CB61B76F7A25064EE794327D906E99CC6CBD1038C14D381585C4656` | `24CC8C195BBA57DD89C96715E5B9DC2106A5EB5DC6620B9D3E0B41DD055BAF11` | `8B59DB930D68F7653FE178668274BD9A2CE6239F5375CACE0556B49F1B2BF397` | `3D5418C4415866B271155A521F925B9A62D11063BA3BF92EA7457147AD5153B9` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` | `FF1D0992EF2C7F4CC6AC1A44F80610FE49AA7A339B98F092CE871992CC80296` |

### Harness source evidence

| Evidence | SHA-256 |
| --- | --- |
| `Lifecycle.py` | `41E20A4BA3E663D054BEBDD937EAF2272130D981EE6B1CEE3B685925B99EA8F3` |
| `RunLifecycle.ps1` | `676D5B768F08D6E14B26913249F555F298FB8665AE566BC5C1CB07EB749961F8` |

## 20. Exact commands and harness source

### 20.1 Blueprint-only invocation

```powershell
pwsh -NoLogo -NoProfile -File "D:\T\S58L-20260723-135846\RunBlueprintOnlyCleanExit.ps1"
```

### 20.2 Lifecycle invocations

```powershell
pwsh -NoLogo -NoProfile -File "D:\T\S58L-20260723-135846\RunLifecycle.ps1" -Mode PIE
pwsh -NoLogo -NoProfile -File "D:\T\S58L-20260723-135846\RunLifecycle.ps1" -Mode SIMULATE
pwsh -NoLogo -NoProfile -File "D:\T\S58L-20260723-135846\RunLifecycle.ps1" -Mode ORPHAN
```

### 20.3 `BlueprintOnlyCleanExit.py`全文

```python
import datetime
import json
import os
import traceback

import unreal

result_path = os.environ["SMT_RESULT_JSON"]

result = {
    "status": "RUNNING",
    "started_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "engine_version": None,
    "command_line": None,
    "keep_alive_before": None,
    "keep_alive_after": None,
    "error": None,
    "traceback": None,
}

try:
    result["engine_version"] = unreal.SystemLibrary.get_engine_version()
    result["command_line"] = unreal.SystemLibrary.get_command_line()
    result["keep_alive_before"] = (
        unreal.EditorPythonScripting.get_keep_python_script_alive()
    )
    result["status"] = "PASS"
except Exception as exc:
    result["status"] = "FAIL"
    result["error"] = str(exc)
    result["traceback"] = traceback.format_exc()
finally:
    result["finished_at_utc"] = (
        datetime.datetime.now(datetime.timezone.utc).isoformat()
    )

    with open(result_path, "w", encoding="utf-8") as output:
        json.dump(result, output, ensure_ascii=False, indent=2)

    unreal.log("SMT_BLUEPRINT_ONLY_MARKER_WRITTEN: " + result_path)
    unreal.EditorPythonScripting.set_keep_python_script_alive(False)
```

### 20.4 `RunBlueprintOnlyCleanExit.ps1`全文

```powershell
$ErrorActionPreference = "Stop"

$verifyRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$hostRoot = Join-Path $verifyRoot "H"
$hostProject = Join-Path $hostRoot "ServerManageToolBlueprintHost.uproject"
$pythonPath = Join-Path $verifyRoot "BlueprintOnlyCleanExit.py"
$resultPath = Join-Path $verifyRoot "BlueprintOnlyCleanExit.json"
$summaryPath = Join-Path $verifyRoot "BlueprintOnlyCleanExit.summary.json"
$logPath = Join-Path $verifyRoot "BlueprintOnlyCleanExit.log"
$stdoutPath = Join-Path $verifyRoot "BlueprintOnlyCleanExit.stdout.txt"
$stderrPath = Join-Path $verifyRoot "BlueprintOnlyCleanExit.stderr.txt"
$editorPath = "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"

function Get-HostProcessInstances {
    $items = @(Get-CimInstance Win32_Process | Where-Object {
        ($_.Name -eq "UnrealEditor-Cmd.exe" -or $_.Name -eq "UnrealEditor.exe") -and
        $_.CommandLine -and
        $_.CommandLine.Contains($hostProject)
    })
    return $items
}

function Get-ProcessEvidence {
    param([object]$CimProcess)

    $process = Get-Process -Id $CimProcess.ProcessId -ErrorAction SilentlyContinue
    $cpuTime = $null
    $workingSet = $null
    $startTime = $null
    if ($null -ne $process) {
        $cpuTime = $process.TotalProcessorTime.ToString()
        $workingSet = $process.WorkingSet64
        try {
            $startTime = $process.StartTime.ToUniversalTime().ToString("o")
        } catch {
            $startTime = $null
        }
    }

    return [ordered]@{
        name = $CimProcess.Name
        process_id = [int]$CimProcess.ProcessId
        parent_process_id = [int]$CimProcess.ParentProcessId
        command_line = $CimProcess.CommandLine
        cpu_time = $cpuTime
        working_set_bytes = $workingSet
        process_start_time_utc = $startTime
    }
}

function Get-TargetProcessEvidence {
    return @(Get-HostProcessInstances | ForEach-Object { Get-ProcessEvidence $_ })
}

$beforeProcesses = Get-TargetProcessEvidence
$process = [System.Diagnostics.Process]::new()
$process.StartInfo = [System.Diagnostics.ProcessStartInfo]::new()
$process.StartInfo.FileName = $editorPath
$process.StartInfo.WorkingDirectory = $hostRoot
$process.StartInfo.UseShellExecute = $false
$process.StartInfo.CreateNoWindow = $true
$process.StartInfo.RedirectStandardOutput = $true
$process.StartInfo.RedirectStandardError = $true
$process.StartInfo.ArgumentList.Add($hostProject)
$process.StartInfo.ArgumentList.Add("-unattended")
$process.StartInfo.ArgumentList.Add("-nop4")
$process.StartInfo.ArgumentList.Add("-nosplash")
$process.StartInfo.ArgumentList.Add("-nullrhi")
$process.StartInfo.ArgumentList.Add("-stdout")
$process.StartInfo.ArgumentList.Add("-FullStdOutLogOutput")
$process.StartInfo.ArgumentList.Add("-ExecutePythonScript=$pythonPath")
$process.StartInfo.ArgumentList.Add("-AbsLog=$logPath")
$process.StartInfo.Environment["SMT_RESULT_JSON"] = $resultPath

$startedAtUtc = [DateTime]::UtcNow
if (-not $process.Start()) {
    throw "Unable to start UnrealEditor-Cmd.exe"
}
$targetPid = $process.Id
$stdoutTask = $process.StandardOutput.ReadToEndAsync()
$stderrTask = $process.StandardError.ReadToEndAsync()
$deadlineUtc = $startedAtUtc.AddSeconds(300)
$timedOut = $false
$timeoutAtUtc = $null
$timeoutProcessEvidence = $null
$terminationPerformed = $false
$terminationReason = $null

while (-not $process.HasExited -and [DateTime]::UtcNow -lt $deadlineUtc) {
    Start-Sleep -Milliseconds 500
}

if (-not $process.HasExited) {
    $timedOut = $true
    $timeoutAtUtc = [DateTime]::UtcNow
    $identity = Get-CimInstance Win32_Process -Filter "ProcessId=$targetPid"
    if ($null -ne $identity -and $identity.Name -eq "UnrealEditor-Cmd.exe" -and $identity.CommandLine -and $identity.CommandLine.Contains($hostProject)) {
        $timeoutProcessEvidence = Get-ProcessEvidence $identity
        $process.Kill()
        $terminationPerformed = $true
        $terminationReason = "300-second timeout; exact host-project target identity verified"
        $process.WaitForExit(10000)
    } else {
        $terminationReason = "300-second timeout; target identity mismatch, no termination performed"
    }
}

$stdoutText = $stdoutTask.GetAwaiter().GetResult()
$stderrText = $stderrTask.GetAwaiter().GetResult()
[System.IO.File]::WriteAllText($stdoutPath, $stdoutText, [System.Text.UTF8Encoding]::new($false))
[System.IO.File]::WriteAllText($stderrPath, $stderrText, [System.Text.UTF8Encoding]::new($false))

$exitCode = $null
if ($process.HasExited) {
    $exitCode = $process.ExitCode
}
$afterProcesses = Get-TargetProcessEvidence
$marker = $null
$markerParseError = $null
if (Test-Path -LiteralPath $resultPath -PathType Leaf) {
    try {
        $marker = Get-Content -LiteralPath $resultPath -Raw | ConvertFrom-Json
    } catch {
        $markerParseError = $_.Exception.Message
    }
}
$logTail = if (Test-Path -LiteralPath $logPath -PathType Leaf) { @(Get-Content -LiteralPath $logPath -Tail 200) } else { @() }
$summary = [ordered]@{
    status = "RUNNING"
    started_at_utc = $startedAtUtc.ToString("o")
    timeout_deadline_utc = $deadlineUtc.ToString("o")
    timeout = $timedOut
    timeout_at_utc = if ($null -eq $timeoutAtUtc) { $null } else { $timeoutAtUtc.ToString("o") }
    pid = $targetPid
    command_line = @($editorPath, $hostProject, "-unattended", "-nop4", "-nosplash", "-nullrhi", "-stdout", "-FullStdOutLogOutput", "-ExecutePythonScript=$pythonPath", "-AbsLog=$logPath")
    before_processes = $beforeProcesses
    timeout_process = $timeoutProcessEvidence
    termination_performed = $terminationPerformed
    termination_reason = $terminationReason
    exit_code = $exitCode
    marker_path = $resultPath
    marker = $marker
    marker_parse_error = $markerParseError
    log_path = $logPath
    stdout_path = $stdoutPath
    stderr_path = $stderrPath
    log_tail_last_200_lines = $logTail
    after_processes = $afterProcesses
    host_target_process_count_after = $afterProcesses.Count
}
$compatibilityPass = $null -ne $marker -and $marker.status -eq "PASS"
$cleanExitPass = -not $timedOut -and $exitCode -eq 0 -and $afterProcesses.Count -eq 0
$summary.status = if ($compatibilityPass -and $cleanExitPass) { "PASS" } elseif ($compatibilityPass) { "BLUEPRINT_COMPATIBILITY_PASS_CLEAN_EXIT_FAIL" } else { "FAIL" }
[System.IO.File]::WriteAllText($summaryPath, ($summary | ConvertTo-Json -Depth 12), [System.Text.UTF8Encoding]::new($false))
Write-Output "BlueprintCompatibilityPass=$compatibilityPass"
Write-Output "BlueprintCleanExitPass=$cleanExitPass"
Write-Output "BlueprintExitCode=$exitCode"
Write-Output "BlueprintTimedOut=$timedOut"
Write-Output "BlueprintTargetProcessCountAfter=$($afterProcesses.Count)"
Write-Output "BlueprintSummaryPath=$summaryPath"
if (-not ($compatibilityPass -and $cleanExitPass)) {
    exit 1
}
exit 0
```

### 20.5 `Lifecycle.py`全文

```python
import datetime
import json
import os
import time
import traceback

import unreal


MODE = os.environ["SMT_MODE"]
RESULT_PATH = os.environ["SMT_RESULT_JSON"]
VALID_MODES = {"PIE", "SIMULATE", "ORPHAN"}

result = {
    "mode": MODE,
    "status": "RUNNING",
    "stage": "INITIALIZING",
    "started_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "play_requested_at_utc": None,
    "play_started_at_utc": None,
    "end_requested_at_utc": None,
    "play_ended_at_utc": None,
    "quit_requested_at_utc": None,
    "api_presence": {},
    "error": None,
    "traceback": None,
    "state_transitions": [],
}

subsystem = None
callback_handle = None
state = "INITIALIZING"
state_started = time.monotonic()
finished = False


def utc_now():
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


def transition(next_state):
    global state, state_started
    state = next_state
    state_started = time.monotonic()
    result["stage"] = next_state
    result["state_transitions"].append(
        {"state": next_state, "at_utc": utc_now()}
    )


def write_result():
    with open(RESULT_PATH, "w", encoding="utf-8") as output:
        json.dump(result, output, ensure_ascii=False, indent=2)


def api_available(name):
    value = getattr(subsystem, name, None)
    result["api_presence"][name] = callable(value)
    return callable(value)


def fail(exc):
    global finished
    if finished:
        return
    failure_status = (
        result["status"]
        if result["status"] == "BLOCKED_UE58_PYTHON_API"
        else "FAIL"
    )
    result["status"] = failure_status
    result["error"] = str(exc)
    result["traceback"] = traceback.format_exc()
    transition(failure_status)
    finished = True
    finalize()


def finalize():
    global callback_handle
    if callback_handle is not None:
        unreal.unregister_slate_post_tick_callback(callback_handle)
        callback_handle = None
    result["quit_requested_at_utc"] = utc_now()
    if result["status"] == "RUNNING":
        result["status"] = "PASS"
        transition("PASS")
    write_result()
    unreal.EditorPythonScripting.set_keep_python_script_alive(False)
    unreal.SystemLibrary.quit_editor()


def request_play():
    result["play_requested_at_utc"] = utc_now()
    if MODE == "SIMULATE":
        subsystem.editor_play_simulate()
    else:
        subsystem.editor_request_begin_play()
    transition("WAITING_FOR_PLAY")


def on_tick(_delta_seconds):
    try:
        elapsed = time.monotonic() - state_started
        if state == "WAIT_BEFORE_PLAY":
            if elapsed >= 5.0:
                request_play()
        elif state == "WAITING_FOR_PLAY":
            if subsystem.is_in_play_in_editor():
                result["play_started_at_utc"] = utc_now()
                transition("HOLDING_PLAY")
            elif elapsed > 30.0:
                raise RuntimeError("play did not start within 30 seconds")
        elif state == "HOLDING_PLAY":
            if elapsed >= 15.0:
                if MODE == "ORPHAN":
                    result["play_ended_at_utc"] = None
                    finalize()
                else:
                    result["end_requested_at_utc"] = utc_now()
                    subsystem.editor_request_end_play()
                    transition("WAITING_FOR_PLAY_END")
        elif state == "WAITING_FOR_PLAY_END":
            if not subsystem.is_in_play_in_editor():
                result["play_ended_at_utc"] = utc_now()
                transition("WAITING_AFTER_PLAY_END")
            elif elapsed > 30.0:
                raise RuntimeError("play did not end within 30 seconds")
        elif state == "WAITING_AFTER_PLAY_END":
            if elapsed >= 10.0:
                finalize()
    except Exception as exc:
        fail(exc)


try:
    if MODE not in VALID_MODES:
        raise RuntimeError("Unsupported SMT_MODE: " + MODE)
    unreal.EditorPythonScripting.set_keep_python_script_alive(True)
    subsystem = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    required_api_names = [
        "editor_request_begin_play",
        "editor_play_simulate",
        "editor_request_end_play",
        "is_in_play_in_editor",
    ]
    missing = [name for name in required_api_names if not api_available(name)]
    if missing:
        result["status"] = "BLOCKED_UE58_PYTHON_API"
        raise RuntimeError("Required UE 5.8 Python API missing: " + ", ".join(missing))
    callback_handle = unreal.register_slate_post_tick_callback(on_tick)
    transition("WAIT_BEFORE_PLAY")
except Exception as exc:
    fail(exc)
```

### 20.6 `RunLifecycle.ps1`全文

```powershell
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("PIE", "SIMULATE", "ORPHAN")]
    [string]$Mode
)

$ErrorActionPreference = "Stop"

$verifyRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$hostRoot = Join-Path $verifyRoot "H"
$hostProject = Join-Path $hostRoot "ServerManageToolBlueprintHost.uproject"
$pythonPath = Join-Path $verifyRoot "Lifecycle.py"
$resultPath = Join-Path $verifyRoot "$Mode.result.json"
$summaryPath = Join-Path $verifyRoot "$Mode.summary.json"
$logPath = Join-Path $verifyRoot "$Mode.log"
$stdoutPath = Join-Path $verifyRoot "$Mode.stdout.txt"
$stderrPath = Join-Path $verifyRoot "$Mode.stderr.txt"
$monitorPath = Join-Path $verifyRoot "$Mode.monitor.jsonl"
$editorPath = "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe"
$maxSeconds = if ($Mode -eq "ORPHAN") { 120 } else { 180 }
$hostProjectSlash = $hostProject.Replace('\', '/')

function Test-HostProjectCommandLine {
    param([string]$CommandLine)
    return $CommandLine -and ($CommandLine.Contains($hostProject) -or $CommandLine.Contains($hostProjectSlash))
}

function Get-PortOwners {
    $owners = @()
    foreach ($port in @(7777, 7778)) {
        $endpoints = @(Get-NetUDPEndpoint -LocalPort $port -ErrorAction SilentlyContinue)
        foreach ($endpoint in $endpoints) {
            $proc = Get-CimInstance Win32_Process -Filter "ProcessId=$($endpoint.OwningProcess)" -ErrorAction SilentlyContinue
            $owners += [ordered]@{
                local_address = $endpoint.LocalAddress
                local_port = [int]$endpoint.LocalPort
                owning_pid = [int]$endpoint.OwningProcess
                process_name = $proc.Name
                command_line = $proc.CommandLine
            }
        }
    }
    return @($owners)
}

function Get-CimProcesses {
    return @(Get-CimInstance Win32_Process)
}

function Get-RequestedPort {
    param([string]$CommandLine)
    if ([string]::IsNullOrWhiteSpace($CommandLine)) {
        return $null
    }
    $match = [regex]::Match($CommandLine, '(?i)(?:-port=|[?&]Port=|\bPort=)(\d+)')
    if ($match.Success) {
        return [int]$match.Groups[1].Value
    }
    return $null
}

function Get-TargetChildInstances {
    param([object[]]$Processes, [int]$ParentPid)
    return @($Processes | Where-Object {
        $_.Name -eq "UnrealEditor.exe" -and
        $_.ProcessId -ne $ParentPid -and
        (Test-HostProjectCommandLine $_.CommandLine) -and
        $_.CommandLine -match '(?i)(^|\s)-server(?:\s|$)'
    })
}

function Convert-ProcessEvidence {
    param([object]$CimProcess, [string]$Role)
    $process = Get-Process -Id $CimProcess.ProcessId -ErrorAction SilentlyContinue
    $startTime = $null
    if ($null -ne $process) {
        try {
            $startTime = $process.StartTime.ToUniversalTime().ToString("o")
        } catch {
            $startTime = $null
        }
    }
    $udpPorts = @(Get-NetUDPEndpoint -OwningProcess $CimProcess.ProcessId -ErrorAction SilentlyContinue | ForEach-Object {
        [ordered]@{
            local_address = $_.LocalAddress
            local_port = [int]$_.LocalPort
            remote_address = $_.RemoteAddress
            remote_port = [int]$_.RemotePort
            state = $_.State
        }
    })
    return [ordered]@{
        role = $Role
        process_id = [int]$CimProcess.ProcessId
        parent_process_id = [int]$CimProcess.ParentProcessId
        name = $CimProcess.Name
        command_line = $CimProcess.CommandLine
        requested_port = Get-RequestedPort $CimProcess.CommandLine
        actual_udp_ports = $udpPorts
        process_exists = $true
        process_start_time_utc = $startTime
    }
}

function Get-PollSnapshot {
    param([int]$ParentPid)
    $processes = Get-CimProcesses
    $parent = @($processes | Where-Object { $_.ProcessId -eq $ParentPid } | Select-Object -First 1)
    $children = @(Get-TargetChildInstances $processes $ParentPid)
    return [ordered]@{
        timestamp_utc = [DateTime]::UtcNow.ToString("o")
        mode = $Mode
        parent_pid = $ParentPid
        parent_process = if ($parent.Count -eq 0) { $null } else { Convert-ProcessEvidence $parent[0] "parent" }
        children = @($children | ForEach-Object { Convert-ProcessEvidence $_ "child" })
        child_count = $children.Count
        port_owners = @(Get-PortOwners)
    }
}

function Get-ExactChildren {
    $processes = Get-CimProcesses
    return @(Get-TargetChildInstances $processes $parentPid)
}

function Stop-ExactProcess {
    param([object]$CimProcess, [string]$Role)
    if ($null -eq $CimProcess) {
        return $false
    }
    $valid = ($CimProcess.Name -eq "UnrealEditor.exe" -or $CimProcess.Name -eq "UnrealEditor-Cmd.exe") -and
        (Test-HostProjectCommandLine $CimProcess.CommandLine)
    if ($Role -eq "child") {
        $valid = $valid -and $CimProcess.Name -eq "UnrealEditor.exe" -and $CimProcess.CommandLine -match '(?i)(^|\s)-server(?:\s|$)'
    }
    if (-not $valid) {
        return $false
    }
    $process = Get-Process -Id $CimProcess.ProcessId -ErrorAction SilentlyContinue
    if ($null -ne $process -and -not $process.HasExited) {
        $process.Kill()
        $process.WaitForExit(10000)
        return $true
    }
    return $false
}

$busyPorts = @(Get-PortOwners)
if ($busyPorts.Count -gt 0) {
    $blocked = [ordered]@{
        mode = $Mode
        status = "BLOCKED_PORT_IN_USE"
        port_owners = $busyPorts
        verification_root = $verifyRoot
    }
    [System.IO.File]::WriteAllText($summaryPath, ($blocked | ConvertTo-Json -Depth 8), [System.Text.UTF8Encoding]::new($false))
    Write-Output "LifecycleStatus=BLOCKED_PORT_IN_USE"
    exit 2
}

if (Test-Path -LiteralPath $monitorPath) {
    [System.IO.File]::Delete([System.IO.Path]::GetFullPath($monitorPath))
}

$process = [System.Diagnostics.Process]::new()
$process.StartInfo = [System.Diagnostics.ProcessStartInfo]::new()
$process.StartInfo.FileName = $editorPath
$process.StartInfo.WorkingDirectory = $hostRoot
$process.StartInfo.UseShellExecute = $false
$process.StartInfo.CreateNoWindow = $true
$process.StartInfo.RedirectStandardOutput = $true
$process.StartInfo.RedirectStandardError = $true
$process.StartInfo.ArgumentList.Add($hostProject)
$process.StartInfo.ArgumentList.Add("-unattended")
$process.StartInfo.ArgumentList.Add("-nop4")
$process.StartInfo.ArgumentList.Add("-nosplash")
$process.StartInfo.ArgumentList.Add("-nullrhi")
$process.StartInfo.ArgumentList.Add("-stdout")
$process.StartInfo.ArgumentList.Add("-FullStdOutLogOutput")
$process.StartInfo.ArgumentList.Add("-ExecutePythonScript=$pythonPath")
$process.StartInfo.ArgumentList.Add("-AbsLog=$logPath")
$process.StartInfo.Environment["SMT_MODE"] = $Mode
$process.StartInfo.Environment["SMT_RESULT_JSON"] = $resultPath

$startedAtUtc = [DateTime]::UtcNow
if (-not $process.Start()) {
    throw "Unable to start UnrealEditor.exe for $Mode"
}
$parentPid = $process.Id
$stdoutTask = $process.StandardOutput.ReadToEndAsync()
$stderrTask = $process.StandardError.ReadToEndAsync()
$deadlineUtc = $startedAtUtc.AddSeconds($maxSeconds)
$timedOut = $false
$parentTerminationPerformed = $false
$childCleanupPerformed = $false
$lastSnapshot = $null
$observationCount = 0

while ([DateTime]::UtcNow -lt $deadlineUtc) {
    $lastSnapshot = Get-PollSnapshot $parentPid
    [System.IO.File]::AppendAllText($monitorPath, (($lastSnapshot | ConvertTo-Json -Depth 10 -Compress) + [Environment]::NewLine), [System.Text.UTF8Encoding]::new($false))
    $observationCount++
    $markerExists = Test-Path -LiteralPath $resultPath -PathType Leaf
    if ($process.HasExited -and $markerExists -and $lastSnapshot.child_count -eq 0) {
        break
    }
    Start-Sleep -Milliseconds 500
}

if (-not $process.HasExited -or $null -eq $lastSnapshot -or $lastSnapshot.child_count -ne 0) {
    $timedOut = -not $process.HasExited
    $lastSnapshot = Get-PollSnapshot $parentPid
    [System.IO.File]::AppendAllText($monitorPath, (($lastSnapshot | ConvertTo-Json -Depth 10 -Compress) + [Environment]::NewLine), [System.Text.UTF8Encoding]::new($false))
    $parentCim = @(Get-CimProcesses | Where-Object { $_.ProcessId -eq $parentPid } | Select-Object -First 1)
    if ($parentCim.Count -gt 0) {
        $parentTerminationPerformed = Stop-ExactProcess $parentCim[0] "parent"
    }
    foreach ($child in @(Get-ExactChildren)) {
        if (Stop-ExactProcess $child "child") {
            $childCleanupPerformed = $true
        }
    }
    Start-Sleep -Milliseconds 500
    $lastSnapshot = Get-PollSnapshot $parentPid
    [System.IO.File]::AppendAllText($monitorPath, (($lastSnapshot | ConvertTo-Json -Depth 10 -Compress) + [Environment]::NewLine), [System.Text.UTF8Encoding]::new($false))
}

$stdoutText = $stdoutTask.GetAwaiter().GetResult()
$stderrText = $stderrTask.GetAwaiter().GetResult()
[System.IO.File]::WriteAllText($stdoutPath, $stdoutText, [System.Text.UTF8Encoding]::new($false))
[System.IO.File]::WriteAllText($stderrPath, $stderrText, [System.Text.UTF8Encoding]::new($false))
$exitCode = if ($process.HasExited) { $process.ExitCode } else { $null }
$finalProcesses = Get-CimProcesses
$finalParent = @($finalProcesses | Where-Object { $_.ProcessId -eq $parentPid })
$finalChildren = @(Get-TargetChildInstances $finalProcesses $parentPid)
$result = $null
$resultParseError = $null
if (Test-Path -LiteralPath $resultPath -PathType Leaf) {
    try {
        $result = Get-Content -LiteralPath $resultPath -Raw | ConvertFrom-Json
    } catch {
        $resultParseError = $_.Exception.Message
    }
}
$summary = [ordered]@{
    mode = $Mode
    verification_root = $verifyRoot
    host_project = $hostProject
    parent_pid = $parentPid
    parent_process_name = "UnrealEditor.exe"
    parent_exited = $process.HasExited
    parent_exit_code = $exitCode
    started_at_utc = $startedAtUtc.ToString("o")
    deadline_utc = $deadlineUtc.ToString("o")
    timed_out = $timedOut
    observation_count = $observationCount
    result_path = $resultPath
    result = $result
    result_parse_error = $resultParseError
    monitor_path = $monitorPath
    stdout_path = $stdoutPath
    stderr_path = $stderrPath
    log_path = $logPath
    parent_termination_performed = $parentTerminationPerformed
    child_cleanup_performed = $childCleanupPerformed
    final_parent_process_count = $finalParent.Count
    final_child_process_count = $finalChildren.Count
    final_child_processes = @($finalChildren | ForEach-Object { Convert-ProcessEvidence $_ "child" })
    last_snapshot = $lastSnapshot
}
$summary.status = if ($null -ne $result) { $result.status } else { "NO_RESULT" }
[System.IO.File]::WriteAllText($summaryPath, ($summary | ConvertTo-Json -Depth 12), [System.Text.UTF8Encoding]::new($false))
Write-Output "LifecycleMode=$Mode"
Write-Output "LifecycleStatus=$($summary.status)"
Write-Output "LifecycleParentPid=$parentPid"
Write-Output "LifecycleParentExitCode=$exitCode"
Write-Output "LifecycleTimedOut=$timedOut"
Write-Output "LifecycleFinalChildCount=$($finalChildren.Count)"
Write-Output "LifecycleSummaryPath=$summaryPath"
if ($summary.status -ne "PASS" -or -not $process.HasExited -or $finalChildren.Count -ne 0 -or $parentTerminationPerformed -or $childCleanupPerformed) {
    exit 1
}
exit 0
```

The first lifecycle harness iteration used multiline JSON for monitor records and a backslash-only path match. Those harness defects were corrected before the authoritative lifecycle reruns. The hashes in Section 19 are only for the corrected authoritative evidence.

## 21. Cleanup and final repository state — PASS

- current host `.uproject` parent Editor process count: `0`
- current host `.uproject` and `-server` child process count: `0`
- UDP 7777/7778: free after verification
- repository Binaries/Intermediate/Saved/DerivedDataCache/log/JSON/Python additions: none
- repository changed files: this report only
- `git diff --check`: PASS before commit

## 22. Final delivery fields

- start HEAD: `5c6fa1142f0bfc4761fb34ba21e37b3c82776e9f`
- end HEAD: supplied with the report commit in the delivery result
- package root: `D:\T\S58-20260723-131534\P`
- strict verification root: `D:\T\S58S-20260723-144412`; five-run ORPHAN repeatability root: `D:\T\S58O-20260723-152041`
- BuildPlugin 3target result: PASS / PASS / PASS
- Blueprint load compatibility: PASS
- Blueprint clean exit: PASS; PID 65416; exit 0; marker PASS; timeout false
- strict PIE: PASS; parent 55552; children 43804/65364; requested/actual 7777/7778; cleanup complete
- strict Simulate: PASS; parent 50388; children 17468/42480; requested/actual 7777/7778; cleanup complete
- strict ORPHAN repeatability: PASS; five runs; all strict-ready within 15 seconds; all post-parent cleanup checks complete
- final target process count: 0
- changed file: `Docs/Verification/FabPostCategory-UE5.8-Win64.md`
- Verification execution status: PASS
- Product readiness status: FAIL

## 23. Strict lifecycle acceptance rerun — PARTIAL

Authoritative strict verification root: `D:\T\S58S-20260723-144412`.

The strict harness preserved the existing startup, process filtering, 0.5-second compact-JSONL monitoring, and exact-target cleanup behavior. Its acceptance status is the logical AND of the Python result, same-snapshot two-child/actual-port acceptance, parent exit, cleanup, and ORPHAN post-parent-exit acceptance.

### PIE — STRICT_PASS

- status: `PASS`
- parent PID / exit code: `55552` / `0`
- accepted concurrent snapshot: `2026-07-23T05:52:47Z` (displayed local time in the JSON as `07/23/2026 05:52:47`)
- accepted child count: `2`
- child PID `43804`, ParentProcessId `55552`, requested `7777`, actual `7777`
- child PID `65364`, ParentProcessId `55552`, requested `7778`, actual `7778`
- first/last seen: PID 43804 `05:52:36`/`05:52:49` UTC; PID 65364 `05:52:36`/`05:52:49` UTC
- Python lifecycle fields: PASS; play request/start/end/quit fields all present; play start/end/PASS transitions present
- timeout: `False`
- forced parent cleanup: `False`
- forced child cleanup: `False`
- final target process count: `0`

### SIMULATE — STRICT_PASS

- status: `PASS`
- parent PID / exit code: `50388` / `0`
- accepted concurrent snapshot: `2026-07-23T05:53:59Z` (displayed local time in the JSON as `07/23/2026 05:53:59`)
- accepted child count: `2`
- child PID `17468`, ParentProcessId `50388`, requested `7777`, actual `7777`
- child PID `42480`, ParentProcessId `50388`, requested `7778`, actual `7778`
- first/last seen: PID 17468 `05:53:48`/`05:54:02` UTC; PID 42480 `05:53:48`/`05:54:02` UTC
- Python lifecycle fields: PASS; play request/start/end/quit fields all present; play start/end/PASS transitions present
- timeout: `False`
- forced parent cleanup: `False`
- forced child cleanup: `False`
- final target process count: `0`

### ORPHAN — FAIL

- status: `FAIL`
- parent PID / exit code: `58892` / `0`
- observed child PID `37460`, ParentProcessId `58892`, requested `7777`, actual `7777` not observed in any accepted concurrent snapshot
- observed child PID `50540`, ParentProcessId `58892`, requested `7778`, actual `7778`
- unique child PID first/last: PID 37460 `05:55:02`/`05:55:15` UTC; PID 50540 `05:55:02`/`05:55:15` UTC
- accepted concurrent snapshot: none
- Python lifecycle fields: PASS; play request/start/quit present; end request and play end null; PASS state present
- strict acceptance error: `No single snapshot satisfied exact two-child, parent-PID, requested-port, and actual-port acceptance`
- parent exit observed: `2026-07-23T05:55:21Z`
- post-parent observation started: `2026-07-23T05:55:21Z`
- post-parent observation ended: `2026-07-23T05:55:44Z`
- post-parent duration: `23.136` seconds
- post-parent poll count: `19`
- post-parent child count array: `0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0`
- post-parent max child count: `0`
- post-parent all-zero: `True`
- timeout: `False`
- forced parent cleanup: `False`
- forced child cleanup: `False`
- final target process count: `0`

ORPHAN therefore remains FAIL even though its parent-exit observation and cleanup predicates passed: the strict rule requires a single concurrent snapshot with actual UDP 7777 and 7778, and that snapshot did not occur.

## 24. Strict evidence hashes — PASS

All evidence below is under `D:\T\S58S-20260723-144412` unless otherwise stated.

| Evidence | SHA-256 |
| --- | --- |
| `Lifecycle.py` | `41E20A4BA3E663D054BEBDD937EAF2272130D981EE6B1CEE3B685925B99EA8F3` |
| `RunLifecycleStrict.ps1` | `8488A7A291FD42ADA9B1D1A0E4E9A96B830DFFB3C93FDBF375AB500E64BCA3DF` |
| `PIE.result.json` | `1E7F288948A402BEF2E6A6312C293C8331F4142EBDA83FC9CE698BBB582664BB` |
| `PIE.strict-summary.json` | `AB336226956ABA49FF3A2F5D3DDEAB89C8896DE1DF4DBA4E374671E288FC18CB` |
| `PIE.log` | `B2BE5A928FA37E94A0BA41B94C9F7043A930ADDF630A3A01D040A505F17DCA84` |
| `PIE.stdout.txt` | `CE61127E83F5D198246E893B18DDC3F46B7ED0B4EB5823FA2C3F82D2924DB0B6` |
| `PIE.stderr.txt` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |
| `PIE.monitor.jsonl` | `B7CF20FF28E65C42EDC6DB776DB25B4758773E4DB29FB2619AE2510FC9594C9F` |
| `SIMULATE.result.json` | `9C3F4281E70686735E6B3238633D881AEA80452B3FB69478E6718AB59E2B91BA` |
| `SIMULATE.strict-summary.json` | `5C31213D577EBB8EBE7BCDD12FD1B9D7AE294E823A5A93A2410E08CDFFEA4D7D` |
| `SIMULATE.log` | `9A09446B7659D0087A844EF94A21A8220F4A0D01E1599F24F990DA29B844F7BF` |
| `SIMULATE.stdout.txt` | `E50F501D7CDF065E1A895CDD4523F6C2727CD05AC2484524EBDB93B4E236ABFC` |
| `SIMULATE.stderr.txt` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |
| `SIMULATE.monitor.jsonl` | `C4765FDFA5CB363480E7EFCF0EC64773B19336FD4D9D9F44C7411F62FBE9473A` |
| `ORPHAN.result.json` | `862031A81AA7DE2376B90674A001E0421C1B930F2FA78AD698E430A5D2DF5F99` |
| `ORPHAN.strict-summary.json` | `ADCB1AE78B077EA4C57976301BD1081A4527EED18D46628C27D83C48529492BE` |
| `ORPHAN.log` | `9CDA03DD7786B7A0DC5D2A94C3B736DFF016E1CC3F1E8203D833DC3489C0D33D` |
| `ORPHAN.stdout.txt` | `33C44D7EC0CD95751D66BFD6BB6FDE57AF93C57BFEE8B43A6AC90A77B68FC8A4` |
| `ORPHAN.stderr.txt` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |
| `ORPHAN.monitor.jsonl` | `64EECB72D643148AF6EB2268B156E3BCE0E24CA108DD1BD15024B9F6B9A96C5E` |
| `H/ServerManageToolBlueprintHost.uproject` | `1D6EAF718E5516BC38FCC360102BC53E91CABDD194FADBF93D3A8CA09142049F` |
| `H/Config/DefaultEngine.ini` | `06249E6CA3793F52A28A67BC893E82627E0EB0EFF5CAE15802984C25DD665EE6` |
| `H/Config/DefaultEditorPerProjectUserSettings.ini` | `E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C` |
| `StrictFinalSummary.json` | `838639A700386E4665A7027869AB79684C26E4F435353620AA5A9D6EAFB39099` |

The full authoritative `Lifecycle.py` text is retained unchanged in Section 20.5 and has the SHA shown above. It was copied from `D:\T\S58L-20260723-135846\Lifecycle.py` without modification.

## 25. Strict lifecycle commands

```powershell
pwsh -NoLogo -NoProfile -File "D:\T\S58S-20260723-144412\RunLifecycleStrict.ps1" -Mode PIE
pwsh -NoLogo -NoProfile -File "D:\T\S58S-20260723-144412\RunLifecycleStrict.ps1" -Mode SIMULATE
pwsh -NoLogo -NoProfile -File "D:\T\S58S-20260723-144412\RunLifecycleStrict.ps1" -Mode ORPHAN
```

Each command used a separate result JSON, strict summary JSON, Editor log, stdout, stderr, and compact JSONL monitor. The mode was started only after the preceding mode had zero exact host processes and unused UDP 7777/7778.

## 26. `RunLifecycleStrict.ps1` authoritative全文

```powershell
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("PIE", "SIMULATE", "ORPHAN")]
    [string]$Mode
)

$ErrorActionPreference = "Stop"

$verifyRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$hostRoot = Join-Path $verifyRoot "H"
$hostProject = Join-Path $hostRoot "ServerManageToolBlueprintHost.uproject"
$hostProjectSlash = $hostProject.Replace('\', '/')
$pythonPath = Join-Path $verifyRoot "Lifecycle.py"
$resultPath = Join-Path $verifyRoot "$Mode.result.json"
$summaryPath = Join-Path $verifyRoot "$Mode.strict-summary.json"
$logPath = Join-Path $verifyRoot "$Mode.log"
$stdoutPath = Join-Path $verifyRoot "$Mode.stdout.txt"
$stderrPath = Join-Path $verifyRoot "$Mode.stderr.txt"
$monitorPath = Join-Path $verifyRoot "$Mode.monitor.jsonl"
$editorPath = "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe"
$maxSeconds = if ($Mode -eq "ORPHAN") { 150 } else { 180 }

function Test-HostProjectCommandLine {
    param([string]$CommandLine)
    return $CommandLine -and ($CommandLine.Contains($hostProject) -or $CommandLine.Contains($hostProjectSlash))
}

function Get-PortOwners {
    $owners = @()
    foreach ($port in @(7777, 7778)) {
        foreach ($endpoint in @(Get-NetUDPEndpoint -LocalPort $port -ErrorAction SilentlyContinue)) {
            $proc = Get-CimInstance Win32_Process -Filter "ProcessId=$($endpoint.OwningProcess)" -ErrorAction SilentlyContinue
            $owners += [ordered]@{
                local_address = $endpoint.LocalAddress
                port = [int]$endpoint.LocalPort
                owning_pid = [int]$endpoint.OwningProcess
                process_name = $proc.Name
                command_line = $proc.CommandLine
            }
        }
    }
    return @($owners)
}

function Get-CimProcesses {
    return @(Get-CimInstance Win32_Process)
}

function Get-RequestedPort {
    param([string]$CommandLine)
    if ([string]::IsNullOrWhiteSpace($CommandLine)) {
        return $null
    }
    $match = [regex]::Match($CommandLine, '(?i)(?:-port=|[?&]Port=|\bPort=)(\d+)')
    if ($match.Success) {
        return [int]$match.Groups[1].Value
    }
    return $null
}

function Get-TargetChildInstances {
    param([object[]]$Processes, [int]$ParentPid)
    return @($Processes | Where-Object {
        $_.Name -eq "UnrealEditor.exe" -and
        $_.ProcessId -ne $ParentPid -and
        (Test-HostProjectCommandLine $_.CommandLine) -and
        $_.CommandLine -match '(?i)(^|\s)-server(?:\s|$)'
    })
}

function Convert-ProcessEvidence {
    param([object]$CimProcess, [string]$Role)
    $process = Get-Process -Id $CimProcess.ProcessId -ErrorAction SilentlyContinue
    $startTime = $null
    if ($null -ne $process) {
        try {
            $startTime = $process.StartTime.ToUniversalTime().ToString("o")
        } catch {
            $startTime = $null
        }
    }
    $udpEndpoints = @(Get-NetUDPEndpoint -OwningProcess $CimProcess.ProcessId -ErrorAction SilentlyContinue | ForEach-Object {
        [ordered]@{
            local_address = $_.LocalAddress
            local_port = [int]$_.LocalPort
            remote_address = $_.RemoteAddress
            remote_port = [int]$_.RemotePort
            state = $_.State
        }
    })
    return [ordered]@{
        role = $Role
        process_id = [int]$CimProcess.ProcessId
        parent_process_id = [int]$CimProcess.ParentProcessId
        name = $CimProcess.Name
        command_line = $CimProcess.CommandLine
        requested_port = Get-RequestedPort $CimProcess.CommandLine
        actual_udp_endpoints = $udpEndpoints
        process_start_time_utc = $startTime
    }
}

function Get-TargetChildren {
    $processes = Get-CimProcesses
    return @(Get-TargetChildInstances $processes $parentPid)
}

function Get-PollSnapshot {
    param([int]$ParentPid)
    $processes = Get-CimProcesses
    $parent = @($processes | Where-Object { $_.ProcessId -eq $ParentPid } | Select-Object -First 1)
    $children = @(Get-TargetChildInstances $processes $ParentPid)
    return [ordered]@{
        timestamp_utc = [DateTime]::UtcNow.ToString("o")
        mode = $Mode
        parent_pid = $ParentPid
        parent_process = if ($parent.Count -eq 0) { $null } else { Convert-ProcessEvidence $parent[0] "parent" }
        child_count = $children.Count
        children = @($children | ForEach-Object { Convert-ProcessEvidence $_ "child" })
        udp_7777_7778_owners = @(Get-PortOwners)
    }
}

function Update-ChildTracking {
    param([hashtable]$Tracking, [object]$Snapshot)
    foreach ($child in @($Snapshot.children)) {
        $key = [string]$child.process_id
        if (-not $Tracking.ContainsKey($key)) {
            $Tracking[$key] = [ordered]@{
                process_id = [int]$child.process_id
                parent_process_id_values = @()
                first_seen_utc = $Snapshot.timestamp_utc
                last_seen_utc = $Snapshot.timestamp_utc
                requested_ports = @()
                actual_ports = @()
            }
        }
        $record = $Tracking[$key]
        $record.last_seen_utc = $Snapshot.timestamp_utc
        if ($record.parent_process_id_values -notcontains $child.parent_process_id) {
            $record.parent_process_id_values += [int]$child.parent_process_id
        }
        if ($null -ne $child.requested_port -and $record.requested_ports -notcontains $child.requested_port) {
            $record.requested_ports += [int]$child.requested_port
        }
        foreach ($endpoint in @($child.actual_udp_endpoints)) {
            if ($null -ne $endpoint -and $record.actual_ports -notcontains $endpoint.local_port) {
                $record.actual_ports += [int]$endpoint.local_port
            }
        }
    }
}

function Test-ConcurrentAcceptance {
    param([object]$Snapshot, [int]$ParentPid)
    $children = @($Snapshot.children)
    if ($children.Count -ne 2) { return $false }
    $pids = @($children | ForEach-Object { [int]$_.process_id })
    if ($pids[0] -eq $pids[1]) { return $false }
    if (@($children | Where-Object { $_.parent_process_id -ne $ParentPid }).Count -ne 0) { return $false }
    if (@($children | Where-Object { $null -eq $_.requested_port }).Count -ne 0) { return $false }
    $requested = @($children | ForEach-Object { [int]$_.requested_port } | Sort-Object)
    if (($requested -join ',') -ne '7777,7778') { return $false }
    $actual7777 = @($children | Where-Object { $_.requested_port -eq 7777 } | ForEach-Object { $_.actual_udp_endpoints } | Where-Object { $null -ne $_ } | ForEach-Object { [int]$_.local_port })
    $actual7778 = @($children | Where-Object { $_.requested_port -eq 7778 } | ForEach-Object { $_.actual_udp_endpoints } | Where-Object { $null -ne $_ } | ForEach-Object { [int]$_.local_port })
    if ($actual7777 -notcontains 7777 -or $actual7778 -notcontains 7778) { return $false }
    $actualExpectedPorts = @($actual7777 + $actual7778)
    if (@($actualExpectedPorts | Sort-Object -Unique).Count -ne 2) { return $false }
    if (@($children.requested_port | Sort-Object -Unique).Count -ne 2) { return $false }
    return $true
}

function Stop-ExactProcess {
    param([object]$CimProcess, [string]$Role)
    if ($null -eq $CimProcess) { return $false }
    $valid = ($CimProcess.Name -eq "UnrealEditor.exe" -or $CimProcess.Name -eq "UnrealEditor-Cmd.exe") -and (Test-HostProjectCommandLine $CimProcess.CommandLine)
    if ($Role -eq "child") {
        $valid = $valid -and $CimProcess.Name -eq "UnrealEditor.exe" -and $CimProcess.CommandLine -match '(?i)(^|\s)-server(?:\s|$)'
    }
    if (-not $valid) { return $false }
    $process = Get-Process -Id $CimProcess.ProcessId -ErrorAction SilentlyContinue
    if ($null -ne $process -and -not $process.HasExited) {
        $process.Kill()
        $process.WaitForExit(10000)
        return $true
    }
    return $false
}

function Test-RequiredField {
    param([object]$Object, [string]$PropertyName)
    $value = $Object.$PropertyName
    return $null -ne $value -and -not [string]::IsNullOrWhiteSpace([string]$value)
}

function Test-PythonAcceptance {
    param([object]$Result)
    if ($null -eq $Result -or $Result.status -ne 'PASS') { return $false }
    if (-not (Test-RequiredField $Result 'play_requested_at_utc')) { return $false }
    if (-not (Test-RequiredField $Result 'play_started_at_utc')) { return $false }
    if (-not (Test-RequiredField $Result 'quit_requested_at_utc')) { return $false }
    $states = @($Result.state_transitions | ForEach-Object { $_.state })
    if ($Mode -eq 'ORPHAN') {
        return $null -eq $Result.end_requested_at_utc -and $null -eq $Result.play_ended_at_utc -and $states -contains 'HOLDING_PLAY' -and $states -contains 'PASS'
    }
    return (Test-RequiredField $Result 'end_requested_at_utc') -and (Test-RequiredField $Result 'play_ended_at_utc') -and $states -contains 'WAITING_FOR_PLAY_END' -and $states -contains 'WAITING_AFTER_PLAY_END' -and $states -contains 'PASS'
}

$preflightPorts = @(Get-PortOwners)
if ($preflightPorts.Count -gt 0) {
    $blocked = [ordered]@{
        mode = $Mode
        status = 'BLOCKED_PORT_IN_USE'
        python_result_pass = $false
        concurrent_expected_children_observed = $false
        lifecycle_fields_pass = $false
        parent_exit_pass = $false
        final_process_cleanup_pass = $false
        orphan_post_parent_exit_pass = $false
        acceptance_errors = @('UDP 7777/7778 were already in use before mode start')
        preflight_port_owners = $preflightPorts
    }
    [System.IO.File]::WriteAllText($summaryPath, ($blocked | ConvertTo-Json -Depth 12), [System.Text.UTF8Encoding]::new($false))
    Write-Output "StrictLifecycleStatus=BLOCKED_PORT_IN_USE"
    exit 2
}

if (Test-Path -LiteralPath $monitorPath) {
    [System.IO.File]::Delete([System.IO.Path]::GetFullPath($monitorPath))
}

$process = [System.Diagnostics.Process]::new()
$process.StartInfo = [System.Diagnostics.ProcessStartInfo]::new()
$process.StartInfo.FileName = $editorPath
$process.StartInfo.WorkingDirectory = $hostRoot
$process.StartInfo.UseShellExecute = $false
$process.StartInfo.CreateNoWindow = $true
$process.StartInfo.RedirectStandardOutput = $true
$process.StartInfo.RedirectStandardError = $true
$process.StartInfo.ArgumentList.Add($hostProject)
$process.StartInfo.ArgumentList.Add('-unattended')
$process.StartInfo.ArgumentList.Add('-nop4')
$process.StartInfo.ArgumentList.Add('-nosplash')
$process.StartInfo.ArgumentList.Add('-nullrhi')
$process.StartInfo.ArgumentList.Add('-stdout')
$process.StartInfo.ArgumentList.Add('-FullStdOutLogOutput')
$process.StartInfo.ArgumentList.Add("-ExecutePythonScript=$pythonPath")
$process.StartInfo.ArgumentList.Add("-AbsLog=$logPath")
$process.StartInfo.Environment['SMT_MODE'] = $Mode
$process.StartInfo.Environment['SMT_RESULT_JSON'] = $resultPath

$startedAtUtc = [DateTime]::UtcNow
if (-not $process.Start()) { throw "Unable to start UnrealEditor.exe for $Mode" }
$parentPid = $process.Id
$stdoutTask = $process.StandardOutput.ReadToEndAsync()
$stderrTask = $process.StandardError.ReadToEndAsync()
$deadlineUtc = $startedAtUtc.AddSeconds($maxSeconds)
$timedOut = $false
$parentTerminationPerformed = $false
$childCleanupPerformed = $false
$parentExitObservedAtUtc = $null
$postParentStartUtc = $null
$postParentSnapshots = @()
$acceptedSnapshot = $null
$childTracking = @{}
$observationCount = 0
$lastSnapshot = $null

while ([DateTime]::UtcNow -lt $deadlineUtc) {
    if ($process.HasExited -and $null -eq $parentExitObservedAtUtc) {
        $parentExitObservedAtUtc = [DateTime]::UtcNow
        if ($Mode -eq 'ORPHAN') { $postParentStartUtc = $parentExitObservedAtUtc }
    }
    $lastSnapshot = Get-PollSnapshot $parentPid
    Update-ChildTracking $childTracking $lastSnapshot
    if ($null -eq $acceptedSnapshot -and (Test-ConcurrentAcceptance $lastSnapshot $parentPid)) {
        $acceptedSnapshot = $lastSnapshot
    }
    [System.IO.File]::AppendAllText($monitorPath, (($lastSnapshot | ConvertTo-Json -Depth 12 -Compress) + [Environment]::NewLine), [System.Text.UTF8Encoding]::new($false))
    $observationCount++
    if ($Mode -eq 'ORPHAN' -and $null -ne $parentExitObservedAtUtc) {
        $postParentSnapshots += $lastSnapshot
    }
    $markerExists = Test-Path -LiteralPath $resultPath -PathType Leaf
    if ($Mode -eq 'ORPHAN' -and $null -ne $postParentStartUtc) {
        $postDuration = ([DateTime]::UtcNow - $postParentStartUtc).TotalSeconds
        if ($markerExists -and $postDuration -ge 10.0 -and $postParentSnapshots.Count -ge 19) { break }
    } elseif ($Mode -ne 'ORPHAN' -and $process.HasExited -and $markerExists -and $lastSnapshot.child_count -eq 0) {
        break
    }
    Start-Sleep -Milliseconds 500
}

if ($null -eq $parentExitObservedAtUtc -and $process.HasExited) {
    $parentExitObservedAtUtc = [DateTime]::UtcNow
    if ($Mode -eq 'ORPHAN') { $postParentStartUtc = $parentExitObservedAtUtc }
}
if (-not $process.HasExited -or $null -eq $acceptedSnapshot -or ($Mode -eq 'ORPHAN' -and $postParentSnapshots.Count -lt 19)) {
    $timedOut = -not $process.HasExited
    $lastSnapshot = Get-PollSnapshot $parentPid
    Update-ChildTracking $childTracking $lastSnapshot
    [System.IO.File]::AppendAllText($monitorPath, (($lastSnapshot | ConvertTo-Json -Depth 12 -Compress) + [Environment]::NewLine), [System.Text.UTF8Encoding]::new($false))
    $parentCim = @(Get-CimProcesses | Where-Object { $_.ProcessId -eq $parentPid } | Select-Object -First 1)
    if ($parentCim.Count -gt 0) { $parentTerminationPerformed = Stop-ExactProcess $parentCim[0] 'parent' }
    foreach ($child in @(Get-TargetChildren)) {
        if (Stop-ExactProcess $child 'child') { $childCleanupPerformed = $true }
    }
    Start-Sleep -Milliseconds 500
    $lastSnapshot = Get-PollSnapshot $parentPid
    Update-ChildTracking $childTracking $lastSnapshot
    [System.IO.File]::AppendAllText($monitorPath, (($lastSnapshot | ConvertTo-Json -Depth 12 -Compress) + [Environment]::NewLine), [System.Text.UTF8Encoding]::new($false))
}

$stdoutText = $stdoutTask.GetAwaiter().GetResult()
$stderrText = $stderrTask.GetAwaiter().GetResult()
[System.IO.File]::WriteAllText($stdoutPath, $stdoutText, [System.Text.UTF8Encoding]::new($false))
[System.IO.File]::WriteAllText($stderrPath, $stderrText, [System.Text.UTF8Encoding]::new($false))
$exitCode = if ($process.HasExited) { $process.ExitCode } else { $null }
$finalProcesses = Get-CimProcesses
$finalParentProcesses = @($finalProcesses | Where-Object { $_.ProcessId -eq $parentPid -and $_.Name -eq 'UnrealEditor.exe' -and (Test-HostProjectCommandLine $_.CommandLine) })
$finalChildren = @(Get-TargetChildInstances $finalProcesses $parentPid)
$result = $null
$resultParseError = $null
if (Test-Path -LiteralPath $resultPath -PathType Leaf) {
    try { $result = Get-Content -LiteralPath $resultPath -Raw | ConvertFrom-Json } catch { $resultParseError = $_.Exception.Message }
}

$pythonResultPass = Test-PythonAcceptance $result
$lifecycleFieldsPass = $pythonResultPass
$parentExitPass = $process.HasExited -and $exitCode -eq 0 -and -not $parentTerminationPerformed
$finalProcessCleanupPass = $finalChildren.Count -eq 0 -and $finalParentProcesses.Count -eq 0
$orphanPlayStartedBeforeParentExit = $false
if ($Mode -eq 'ORPHAN' -and $null -ne $result -and $null -ne $parentExitObservedAtUtc -and (Test-RequiredField $result 'play_started_at_utc')) {
    try {
        $orphanPlayStartedBeforeParentExit = [DateTimeOffset]::Parse($result.play_started_at_utc).UtcDateTime -le $parentExitObservedAtUtc
    } catch {
        $orphanPlayStartedBeforeParentExit = $false
    }
}
$postParentEndedAtUtc = if ($postParentSnapshots.Count -gt 0) { [DateTime]::UtcNow } else { $null }
$postParentDuration = if ($null -ne $postParentStartUtc) { ([DateTime]::UtcNow - $postParentStartUtc).TotalSeconds } else { 0 }
$postParentChildCounts = @($postParentSnapshots | ForEach-Object { [int]$_.child_count })
$postParentAllZero = $Mode -ne 'ORPHAN' -or ($postParentChildCounts.Count -ge 19 -and @($postParentChildCounts | Where-Object { $_ -ne 0 }).Count -eq 0)
$postParentMax = if ($postParentChildCounts.Count -eq 0) { 0 } else { ($postParentChildCounts | Measure-Object -Maximum).Maximum }
$orphanPostParentExitPass = $Mode -ne 'ORPHAN' -or ($orphanPlayStartedBeforeParentExit -and $null -ne $parentExitObservedAtUtc -and $null -ne $postParentStartUtc -and $postParentDuration -ge 10.0 -and $postParentSnapshots.Count -ge 19 -and $postParentAllZero -and $postParentMax -eq 0 -and $finalChildren.Count -eq 0)
$acceptanceErrors = @()
if ($null -eq $acceptedSnapshot) { $acceptanceErrors += 'No single snapshot satisfied exact two-child, parent-PID, requested-port, and actual-port acceptance' }
if (-not $pythonResultPass) { $acceptanceErrors += 'Python lifecycle result fields/status/state transitions did not satisfy mode acceptance' }
if (-not $parentExitPass) { $acceptanceErrors += 'Parent Editor did not naturally exit with code 0 without harness termination' }
if (-not $finalProcessCleanupPass) { $acceptanceErrors += 'Final exact host parent/child process cleanup failed' }
if (-not $orphanPostParentExitPass) { $acceptanceErrors += 'ORPHAN post-parent-exit observation did not satisfy 10-second, 19-poll, all-zero acceptance' }
if ($Mode -eq 'ORPHAN' -and -not $orphanPlayStartedBeforeParentExit) { $acceptanceErrors += 'ORPHAN play start was not observed before parent Editor exit' }
$status = if ($null -ne $acceptedSnapshot -and $pythonResultPass -and $parentExitPass -and $finalProcessCleanupPass -and $orphanPostParentExitPass) { 'PASS' } else { 'FAIL' }
$acceptedChildren = if ($null -ne $acceptedSnapshot) { @($acceptedSnapshot.children) } else { @() }
$uniqueTracking = @($childTracking.Values | Sort-Object process_id)
$summary = [ordered]@{
    mode = $Mode
    status = $status
    verification_root = $verifyRoot
    host_project = $hostProject
    max_seconds = $maxSeconds
    python_result_pass = $pythonResultPass
    concurrent_expected_children_observed = $null -ne $acceptedSnapshot
    lifecycle_fields_pass = $lifecycleFieldsPass
    parent_exit_pass = $parentExitPass
    final_process_cleanup_pass = $finalProcessCleanupPass
    orphan_post_parent_exit_pass = $orphanPostParentExitPass
    acceptance_errors = @($acceptanceErrors)
    preflight_port_owners = $preflightPorts
    parent_pid = $parentPid
    parent_exit_code = $exitCode
    parent_exit_observed_at_utc = if ($null -eq $parentExitObservedAtUtc) { $null } else { $parentExitObservedAtUtc.ToString('o') }
    parent_termination_performed = $parentTerminationPerformed
    child_cleanup_performed = $childCleanupPerformed
    accepted_concurrent_snapshot = $acceptedSnapshot
    accepted_child_pids = @($acceptedChildren | ForEach-Object { [int]$_.process_id })
    accepted_requested_ports = @($acceptedChildren | ForEach-Object { [int]$_.requested_port } | Sort-Object)
    accepted_actual_ports = @($acceptedChildren | ForEach-Object { $_.actual_udp_endpoints } | ForEach-Object { [int]$_.local_port } | Sort-Object -Unique)
    accepted_parent_process_ids = @($acceptedChildren | ForEach-Object { [int]$_.parent_process_id })
    accepted_snapshot_at_utc = if ($null -eq $acceptedSnapshot) { $null } else { $acceptedSnapshot.timestamp_utc }
    unique_child_pids = @($uniqueTracking | ForEach-Object { [int]$_.process_id })
    child_pid_tracking = $uniqueTracking
    parent_exit_observation_started_at_utc = if ($null -eq $postParentStartUtc) { $null } else { $postParentStartUtc.ToString('o') }
    post_parent_exit_observation_started_at_utc = if ($null -eq $postParentStartUtc) { $null } else { $postParentStartUtc.ToString('o') }
    post_parent_exit_observation_ended_at_utc = if ($null -eq $postParentStartUtc) { $null } else { [DateTime]::UtcNow.ToString('o') }
    post_parent_exit_duration_seconds = [Math]::Round($postParentDuration, 3)
    post_parent_exit_poll_count = $postParentSnapshots.Count
    post_parent_exit_child_counts = @($postParentChildCounts)
    post_parent_exit_max_child_count = [int]$postParentMax
    post_parent_exit_all_zero = $postParentAllZero
    final_parent_process_count = $finalParentProcesses.Count
    final_child_process_count = $finalChildren.Count
    final_target_process_count = $finalParentProcesses.Count + $finalChildren.Count
    final_child_processes = @($finalChildren | ForEach-Object { Convert-ProcessEvidence $_ 'child' })
    result_path = $resultPath
    result = $result
    result_parse_error = $resultParseError
    monitor_path = $monitorPath
    log_path = $logPath
    stdout_path = $stdoutPath
    stderr_path = $stderrPath
    observation_count = $observationCount
    timed_out = $timedOut
}
[System.IO.File]::WriteAllText($summaryPath, ($summary | ConvertTo-Json -Depth 20), [System.Text.UTF8Encoding]::new($false))
Write-Output "StrictLifecycleMode=$Mode"
Write-Output "StrictLifecycleStatus=$status"
Write-Output "StrictPythonResultPass=$pythonResultPass"
Write-Output "StrictConcurrentChildren=$($null -ne $acceptedSnapshot)"
Write-Output "StrictParentPID=$parentPid"
Write-Output "StrictParentExitCode=$exitCode"
Write-Output "StrictFinalTargetProcessCount=$($summary.final_target_process_count)"
Write-Output "StrictSummaryPath=$summaryPath"
if ($status -ne 'PASS') { exit 1 }
exit 0
```
+## 27. ORPHAN repeatability and readiness timing — 5-run authoritative investigation — PASS

### 27.1 Scope, fixed inputs, and execution status

This investigation was executed on the pre-approved branch state after confirming the start gate: repository `D:\ghws\ServerManageToolPlugin`, branch `fix/ue58-uht-categories`, start HEAD and remote branch HEAD `5c6fa1142f0bfc4761fb34ba21e37b3c82776e9f`, divergence `0 0), clean working tree, PowerShell 7, UE root `C:\Program Files\Epic Games\UE_5.8`, UE Build.version MajorVersion 5 / MinorVersion 8, and existing `InstalledBuild.txt`.

The packaged input was reused because all required hashes matched: package root `D:\T\S58-20260723-131534\P`; BuildPlugin log SHA-256 `82D0DF6B6D191B4E05936C3D187FE6EB74730738EF1943FE038C0464F103541D`; packaged `.uplugin` SHA-256 `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146`; packaged `.modules` SHA-256 `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274`.

The isolated verification root was `D:\T\S58O-20260723-152041`. Five independent Blueprint-only host projects were created under `Run01` through `Run05`, each with the packaged plugin, `DefaultEngine.ini`, `DefaultEditorPerProjectUserSettings.ini`, and no C++ `Modules` entry. The only lifecycle behavior change was the ORPHAN hold from 15 seconds to `SMT_HOLD_SECONDS=30`; the harness used a maximum of 180 seconds, parent polling at 100 ms, post-parent polling at 250 ms, and compact one-line JSONL snapshots. Because the baseline lifecycle initializes `result` after `RESULT_PATH`, `HOLD_SECONDS` is declared immediately after `RESULT_PATH` and `result["hold_seconds"]` is recorded immediately after result initialization to avoid an undefined-name failure; the state transition change remains exactly one replacement from `elapsed >= 15.0` to `elapsed >= HOLD_SECONDS`.

A per-run warmup helper was used only to prime the independent host and was not counted as an ORPHAN run. Its marker was PASS; one warmup parent required exact host-path cleanup after the warmup process returned an unusable exit observation. The five authoritative ORPHAN runs below had no forced parent/child cleanup and were evaluated only from the ORPHAN process/UDP snapshots; log evidence is supplemental.

**Verification execution status: PASS.** All five runs were terminal and strict ORPHAN acceptance PASS. **Product readiness status: FAIL** remains unchanged.

### 27.2 Authoritative run results

| Run | Status | Classification | Parent PID / exit | Strict ready | Pre-parent polls / median interval | Post-parent duration / polls / child counts | Forced cleanup | Final target |
|---|---|---|---:|---|---:|---|---|---:|
| 1 | PASS | READY_WITHIN_15_SECONDS | 2788 / 0 | true at 10.431 s; ≤15 s=yes | 247 / 0.141 s | 10.285 s / 37 / all 0 (37 polls) | parent=no, child=no | 0 |
| 2 | PASS | READY_WITHIN_15_SECONDS | 38504 / 0 | true at 9.218 s; ≤15 s=yes | 244 / 0.142 s | 10.234 s / 36 / all 0 (36 polls) | parent=no, child=no | 0 |
| 3 | PASS | READY_WITHIN_15_SECONDS | 61152 / 0 | true at 9.437 s; ≤15 s=yes | 254 / 0.141 s | 10.033 s / 36 / all 0 (36 polls) | parent=no, child=no | 0 |
| 4 | PASS | READY_WITHIN_15_SECONDS | 54696 / 0 | true at 9.488 s; ≤15 s=yes | 254 / 0.141 s | 10.243 s / 37 / all 0 (37 polls) | parent=no, child=no | 0 |
| 5 | PASS | READY_WITHIN_15_SECONDS | 39988 / 0 | true at 9.8 s; ≤15 s=yes | 258 / 0.141 s | 10.262 s / 37 / all 0 (37 polls) | parent=no, child=no | 0 |

The post-parent child-count notation `all 0 (N polls)` is an exact sequence summary: every saved post-parent snapshot had child count zero. The five runs recorded 247/244/254/254/258 pre-parent polls with measured median intervals 0.140751/0.142184/0.140960/0.140929/0.140916 seconds. Every run satisfied the required frequency gate of at least 50 polls and median interval at most 0.5 seconds.

### 27.3 Child identity and port evidence

| Run | Child PID | ParentProcessId | Requested port | Actual UDP port | First seen UTC | Last seen UTC |
|---:|---:|---:|---:|---:|---|---|
| 1 | 63224 | 2788 | 7777 | 7777 | 2026-07-23T06:55:03.5615979Z | 2026-07-23T06:55:33.8075486Z |
| 1 | 72744 | 2788 | 7778 | 7778 | 2026-07-23T06:55:03.5615979Z | 2026-07-23T06:55:33.8075486Z |
| 2 | 72520 | 38504 | 7778 | 7778 | 2026-07-23T06:59:55.9195379Z | 2026-07-23T07:00:26.1146295Z |
| 2 | 38840 | 38504 | 7777 | 7777 | 2026-07-23T06:59:55.9195379Z | 2026-07-23T07:00:26.1146295Z |
| 3 | 69124 | 61152 | 7778 | 7778 | 2026-07-23T07:01:47.6950108Z | 2026-07-23T07:02:18.0658066Z |
| 3 | 54756 | 61152 | 7777 | 7777 | 2026-07-23T07:01:47.6950108Z | 2026-07-23T07:02:18.0658066Z |
| 4 | 38864 | 54696 | 7778 | 7778 | 2026-07-23T07:03:38.8546953Z | 2026-07-23T07:04:09.0128717Z |
| 4 | 42776 | 54696 | 7777 | 7777 | 2026-07-23T07:03:38.8546953Z | 2026-07-23T07:04:09.0128717Z |
| 5 | 67080 | 39988 | 7778 | 7778 | 2026-07-23T07:05:19.2354289Z | 2026-07-23T07:05:49.6073467Z |
| 5 | 69200 | 39988 | 7777 | 7777 | 2026-07-23T07:05:19.2354289Z | 2026-07-23T07:05:49.6073467Z |

Each run observed two distinct `UnrealEditor.exe` server children whose command lines contained that run's absolute host `.uproject` and an independent `-server` token. Actual ports were obtained from `Get-NetUDPEndpoint -OwningProcess <PID>` after the requested-port candidate was detected; both requested and actual values were independently retained in the snapshots.

| Run | Expected port | Child PID | First observed UTC | Play-start elapsed |
|---:|---:|---:|---|---:|
| 1 | 7777 | 63224 | 2026-07-23T06:55:13.4309096Z | 10.430 s |
| 1 | 7778 | 72744 | 2026-07-23T06:55:11.7435855Z | 8.743 s |
| 2 | 7777 | 38840 | 2026-07-23T07:00:03.9002284Z | 7.900 s |
| 2 | 7778 | 72520 | 2026-07-23T07:00:05.2180059Z | 9.218 s |
| 3 | 7777 | 54756 | 2026-07-23T07:01:57.4366548Z | 9.436 s |
| 3 | 7778 | 69124 | 2026-07-23T07:01:56.0993063Z | 8.099 s |
| 4 | 7777 | 42776 | 2026-07-23T07:03:47.2414482Z | 8.241 s |
| 4 | 7778 | 38864 | 2026-07-23T07:03:48.4879591Z | 9.487 s |
| 5 | 7777 | 69200 | 2026-07-23T07:05:28.7997234Z | 9.799 s |
| 5 | 7778 | 67080 | 2026-07-23T07:05:27.5259352Z | 8.525 s |

The expected-port elapsed values above are calculated from the saved `play_started_at_utc` and each expected-port first-observation timestamp. The harness also saved the raw timestamps in each summary and monitor JSONL. Every run reached strict readiness in one snapshot with distinct child PIDs, matching ParentProcessId, requested ports 7777/7778, and actual UDP ports 7777/7778.

### 27.4 Supplemental log evidence for ports 7777 and 7778

Log evidence was collected from every `H\Saved\Logs` log plus the harness editor log. The following table lists every extracted 7777/7778 line matching `Created socket`, `IpNetDriver listening on port`, or `Port=`; each row includes the filename, line number, file last-write time, and file SHA-256. These rows are supplemental and do not replace the process/UDP strict acceptance check.

| Run | Log filename | Line | File last-write UTC | File SHA-256 | Line text |
|---:|---|---:|---|---|---|
| 1 | ServerManageToolBlueprintHost_2.log | 32 | 2026-07-23T06:55:12.6271848Z | 0739AC636167FEDDD7C95C2BDFEE1F430E21E9ADEE5835D7246B1692DF96A6EC | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run01/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7778 -server -log"" |
| 1 | ServerManageToolBlueprintHost_2.log | 449 | 2026-07-23T06:55:12.6271848Z | 0739AC636167FEDDD7C95C2BDFEE1F430E21E9ADEE5835D7246B1692DF96A6EC | LogInit: Command Line: /Engine/Maps/Entry -Port=7778 -server -log |
| 1 | ServerManageToolBlueprintHost_2.log | 1383 | 2026-07-23T06:55:12.6271848Z | 0739AC636167FEDDD7C95C2BDFEE1F430E21E9ADEE5835D7246B1692DF96A6EC | [2026.07.23-06.55.11:707][  0]LogNet: Created socket for bind address: 0.0.0.0:7778 |
| 1 | ServerManageToolBlueprintHost_2.log | 1385 | 2026-07-23T06:55:12.6271848Z | 0739AC636167FEDDD7C95C2BDFEE1F430E21E9ADEE5835D7246B1692DF96A6EC | [2026.07.23-06.55.11:708][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7778 |
| 1 | ServerManageToolBlueprintHost.log | 32 | 2026-07-23T06:55:13.6815024Z | 29ABDB3C0E8EB9660194C07BE53730EA52140DE84923A2C823F333B567394B4C | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run01/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7777 -server -log"" |
| 1 | ServerManageToolBlueprintHost.log | 449 | 2026-07-23T06:55:13.6815024Z | 29ABDB3C0E8EB9660194C07BE53730EA52140DE84923A2C823F333B567394B4C | LogInit: Command Line: /Engine/Maps/Entry -Port=7777 -server -log |
| 1 | ServerManageToolBlueprintHost.log | 1382 | 2026-07-23T06:55:13.6815024Z | 29ABDB3C0E8EB9660194C07BE53730EA52140DE84923A2C823F333B567394B4C | [2026.07.23-06.55.12:745][  0]LogNet: Created socket for bind address: 0.0.0.0:7777 |
| 1 | ServerManageToolBlueprintHost.log | 1384 | 2026-07-23T06:55:13.6815024Z | 29ABDB3C0E8EB9660194C07BE53730EA52140DE84923A2C823F333B567394B4C | [2026.07.23-06.55.12:746][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7777 |
| 1 | ORPHAN.log | 3207 | 2026-07-23T06:55:37.2553634Z | 1A86BB776F3A9DED27830E5536A3366468CA73484FFBC7F4A6111E6813E774AF | [2026.07.23-06.55.03:536][581]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run01/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7777 -server -log |
| 1 | ORPHAN.log | 3208 | 2026-07-23T06:55:37.2553634Z | 1A86BB776F3A9DED27830E5536A3366468CA73484FFBC7F4A6111E6813E774AF | [2026.07.23-06.55.03:541][581]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run01/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7778 -server -log |
| 2 | ServerManageToolBlueprintHost_2.log | 32 | 2026-07-23T07:00:04.8067753Z | 7C6C34FB439C184FAF47D7FD3815344BC96FC83DC0E9F708977BFC883001AFCF | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run02/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7777 -server -log"" |
| 2 | ServerManageToolBlueprintHost_2.log | 449 | 2026-07-23T07:00:04.8067753Z | 7C6C34FB439C184FAF47D7FD3815344BC96FC83DC0E9F708977BFC883001AFCF | LogInit: Command Line: /Engine/Maps/Entry -Port=7777 -server -log |
| 2 | ServerManageToolBlueprintHost_2.log | 1383 | 2026-07-23T07:00:04.8067753Z | 7C6C34FB439C184FAF47D7FD3815344BC96FC83DC0E9F708977BFC883001AFCF | [2026.07.23-07.00.03:877][  0]LogNet: Created socket for bind address: 0.0.0.0:7777 |
| 2 | ServerManageToolBlueprintHost_2.log | 1385 | 2026-07-23T07:00:04.8067753Z | 7C6C34FB439C184FAF47D7FD3815344BC96FC83DC0E9F708977BFC883001AFCF | [2026.07.23-07.00.03:877][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7777 |
| 2 | ServerManageToolBlueprintHost.log | 32 | 2026-07-23T07:00:06.0523115Z | 4F692B927202E09C8F0D1C4BAE3ECF18C00721F33D7960FE9FAED24881F6E1E8 | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run02/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7778 -server -log"" |
| 2 | ServerManageToolBlueprintHost.log | 449 | 2026-07-23T07:00:06.0523115Z | 4F692B927202E09C8F0D1C4BAE3ECF18C00721F33D7960FE9FAED24881F6E1E8 | LogInit: Command Line: /Engine/Maps/Entry -Port=7778 -server -log |
| 2 | ServerManageToolBlueprintHost.log | 1382 | 2026-07-23T07:00:06.0523115Z | 4F692B927202E09C8F0D1C4BAE3ECF18C00721F33D7960FE9FAED24881F6E1E8 | [2026.07.23-07.00.04:928][  0]LogNet: Created socket for bind address: 0.0.0.0:7778 |
| 2 | ServerManageToolBlueprintHost.log | 1384 | 2026-07-23T07:00:06.0523115Z | 4F692B927202E09C8F0D1C4BAE3ECF18C00721F33D7960FE9FAED24881F6E1E8 | [2026.07.23-07.00.04:928][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7778 |
| 2 | ORPHAN.log | 3207 | 2026-07-23T07:00:29.2454524Z | 0FB605C634C82C6CB7AC1DBF95885A527167D7E813CFA92FA217D8FA5F95E964 | [2026.07.23-06.59.55:898][583]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run02/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7777 -server -log |
| 2 | ORPHAN.log | 3208 | 2026-07-23T07:00:29.2454524Z | 0FB605C634C82C6CB7AC1DBF95885A527167D7E813CFA92FA217D8FA5F95E964 | [2026.07.23-06.59.55:900][583]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run02/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7778 -server -log |
| 3 | ServerManageToolBlueprintHost_2.log | 32 | 2026-07-23T07:01:58.2162738Z | 6AA1EA078C8D4AFDF7E282F21A2090B3C5EC2D01D612A0FE318ED78184ED9748 | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run03/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7777 -server -log"" |
| 3 | ServerManageToolBlueprintHost_2.log | 449 | 2026-07-23T07:01:58.2162738Z | 6AA1EA078C8D4AFDF7E282F21A2090B3C5EC2D01D612A0FE318ED78184ED9748 | LogInit: Command Line: /Engine/Maps/Entry -Port=7777 -server -log |
| 3 | ServerManageToolBlueprintHost_2.log | 1382 | 2026-07-23T07:01:58.2162738Z | 6AA1EA078C8D4AFDF7E282F21A2090B3C5EC2D01D612A0FE318ED78184ED9748 | [2026.07.23-07.01.57:057][  0]LogNet: Created socket for bind address: 0.0.0.0:7777 |
| 3 | ServerManageToolBlueprintHost_2.log | 1384 | 2026-07-23T07:01:58.2162738Z | 6AA1EA078C8D4AFDF7E282F21A2090B3C5EC2D01D612A0FE318ED78184ED9748 | [2026.07.23-07.01.57:057][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7777 |
| 3 | ServerManageToolBlueprintHost.log | 32 | 2026-07-23T07:01:56.9923538Z | 7ED58BC1B7CAA90968181E6E4B97A25BBE940B676D5088D2B5EB184708DDCC7C | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run03/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7778 -server -log"" |
| 3 | ServerManageToolBlueprintHost.log | 449 | 2026-07-23T07:01:56.9923538Z | 7ED58BC1B7CAA90968181E6E4B97A25BBE940B676D5088D2B5EB184708DDCC7C | LogInit: Command Line: /Engine/Maps/Entry -Port=7778 -server -log |
| 3 | ServerManageToolBlueprintHost.log | 1383 | 2026-07-23T07:01:56.9923538Z | 7ED58BC1B7CAA90968181E6E4B97A25BBE940B676D5088D2B5EB184708DDCC7C | [2026.07.23-07.01.56:049][  0]LogNet: Created socket for bind address: 0.0.0.0:7778 |
| 3 | ServerManageToolBlueprintHost.log | 1385 | 2026-07-23T07:01:56.9923538Z | 7ED58BC1B7CAA90968181E6E4B97A25BBE940B676D5088D2B5EB184708DDCC7C | [2026.07.23-07.01.56:050][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7778 |
| 3 | ORPHAN.log | 3207 | 2026-07-23T07:02:22.0518852Z | F64DAEC24EC61E3608B2CD692ECEF37B64912230C3211138D8450CED4F01A47B | [2026.07.23-07.01.47:864][584]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run03/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7777 -server -log |
| 3 | ORPHAN.log | 3208 | 2026-07-23T07:02:22.0518852Z | F64DAEC24EC61E3608B2CD692ECEF37B64912230C3211138D8450CED4F01A47B | [2026.07.23-07.01.47:868][584]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run03/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7778 -server -log |
| 4 | ServerManageToolBlueprintHost_2.log | 32 | 2026-07-23T07:03:49.2000919Z | 303CD2B001FB44B22B4B00BA76D36BD39E59FB3DD77B639C34D7A14754C00E36 | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run04/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7778 -server -log"" |
| 4 | ServerManageToolBlueprintHost_2.log | 449 | 2026-07-23T07:03:49.2000919Z | 303CD2B001FB44B22B4B00BA76D36BD39E59FB3DD77B639C34D7A14754C00E36 | LogInit: Command Line: /Engine/Maps/Entry -Port=7778 -server -log |
| 4 | ServerManageToolBlueprintHost_2.log | 1382 | 2026-07-23T07:03:49.2000919Z | 303CD2B001FB44B22B4B00BA76D36BD39E59FB3DD77B639C34D7A14754C00E36 | [2026.07.23-07.03.48:269][  0]LogNet: Created socket for bind address: 0.0.0.0:7778 |
| 4 | ServerManageToolBlueprintHost_2.log | 1384 | 2026-07-23T07:03:49.2000919Z | 303CD2B001FB44B22B4B00BA76D36BD39E59FB3DD77B639C34D7A14754C00E36 | [2026.07.23-07.03.48:270][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7778 |
| 4 | ServerManageToolBlueprintHost.log | 32 | 2026-07-23T07:03:48.1105442Z | 2D55169A287118848593C68287F53AB3444BDC526292D1B2E0A05E109AB26598 | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run04/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7777 -server -log"" |
| 4 | ServerManageToolBlueprintHost.log | 449 | 2026-07-23T07:03:48.1105442Z | 2D55169A287118848593C68287F53AB3444BDC526292D1B2E0A05E109AB26598 | LogInit: Command Line: /Engine/Maps/Entry -Port=7777 -server -log |
| 4 | ServerManageToolBlueprintHost.log | 1383 | 2026-07-23T07:03:48.1105442Z | 2D55169A287118848593C68287F53AB3444BDC526292D1B2E0A05E109AB26598 | [2026.07.23-07.03.47:174][  0]LogNet: Created socket for bind address: 0.0.0.0:7777 |
| 4 | ServerManageToolBlueprintHost.log | 1385 | 2026-07-23T07:03:48.1105442Z | 2D55169A287118848593C68287F53AB3444BDC526292D1B2E0A05E109AB26598 | [2026.07.23-07.03.47:175][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7777 |
| 4 | ORPHAN.log | 3207 | 2026-07-23T07:04:12.7797666Z | 3BC2E39DABD6160DF9E6CE11BBD6555467A1F2D81035A8B4D74799314F51D94F | [2026.07.23-07.03.38:857][584]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run04/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7777 -server -log |
| 4 | ORPHAN.log | 3208 | 2026-07-23T07:04:12.7797666Z | 3BC2E39DABD6160DF9E6CE11BBD6555467A1F2D81035A8B4D74799314F51D94F | [2026.07.23-07.03.38:860][584]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run04/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7778 -server -log |
| 5 | ServerManageToolBlueprintHost_2.log | 32 | 2026-07-23T07:05:29.4161406Z | 71C17983E4816758034598E2D362B5C27FACA7B078DFEB0E1026A8E8B209D927 | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run05/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7777 -server -log"" |
| 5 | ServerManageToolBlueprintHost_2.log | 449 | 2026-07-23T07:05:29.4161406Z | 71C17983E4816758034598E2D362B5C27FACA7B078DFEB0E1026A8E8B209D927 | LogInit: Command Line: /Engine/Maps/Entry -Port=7777 -server -log |
| 5 | ServerManageToolBlueprintHost_2.log | 1382 | 2026-07-23T07:05:29.4161406Z | 71C17983E4816758034598E2D362B5C27FACA7B078DFEB0E1026A8E8B209D927 | [2026.07.23-07.05.28:499][  0]LogNet: Created socket for bind address: 0.0.0.0:7777 |
| 5 | ServerManageToolBlueprintHost_2.log | 1384 | 2026-07-23T07:05:29.4161406Z | 71C17983E4816758034598E2D362B5C27FACA7B078DFEB0E1026A8E8B209D927 | [2026.07.23-07.05.28:499][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7777 |
| 5 | ServerManageToolBlueprintHost.log | 32 | 2026-07-23T07:05:28.3809303Z | 0C93756E56E20B9B9FC9E1E3593EEE5512ACF9CD5EBD29203770751275AC882A | LogCsvProfiler: Display: Metadata set : commandline="" D:/T/S58O-20260723-152041/Run05/H/ServerManageToolBlueprintHost.uproject /Engine/Maps/Entry -Port=7778 -server -log"" |
| 5 | ServerManageToolBlueprintHost.log | 449 | 2026-07-23T07:05:28.3809303Z | 0C93756E56E20B9B9FC9E1E3593EEE5512ACF9CD5EBD29203770751275AC882A | LogInit: Command Line: /Engine/Maps/Entry -Port=7778 -server -log |
| 5 | ServerManageToolBlueprintHost.log | 1383 | 2026-07-23T07:05:28.3809303Z | 0C93756E56E20B9B9FC9E1E3593EEE5512ACF9CD5EBD29203770751275AC882A | [2026.07.23-07.05.27:454][  0]LogNet: Created socket for bind address: 0.0.0.0:7778 |
| 5 | ServerManageToolBlueprintHost.log | 1385 | 2026-07-23T07:05:28.3809303Z | 0C93756E56E20B9B9FC9E1E3593EEE5512ACF9CD5EBD29203770751275AC882A | [2026.07.23-07.05.27:454][  0]LogNet: Name:GameNetDriver Def:GameNetDriver IpNetDriver_0 IpNetDriver listening on port 7778 |
| 5 | ORPHAN.log | 3207 | 2026-07-23T07:05:53.554876Z | 2C08EB3C46583025FCFFF6B9653418E9164F1DB826ECCBE52CF0399EEC3A70A9 | [2026.07.23-07.05.19:404][584]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run05/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7777 -server -log |
| 5 | ORPHAN.log | 3208 | 2026-07-23T07:05:53.554876Z | 2C08EB3C46583025FCFFF6B9653418E9164F1DB826ECCBE52CF0399EEC3A70A9 | [2026.07.23-07.05.19:407][584]LogTemp: UnrealEditor vZXN®µ܂µ½: C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe "D:/T/S58O-20260723-152041/Run05/H/ServerManageToolBlueprintHost.uproject" /Engine/Maps/Entry -Port=7778 -server -log |

### 27.5 Parent exit and cleanup

The parent Editor exited naturally with exit code 0 in all five runs. Each run was monitored for at least 10.0 seconds and at least 20 post-parent polls; every saved child-count value was zero. No harness-forced parent cleanup or child cleanup was used in the authoritative runs, every run's final target parent/child process count was zero, and the aggregate final UDP 7777/7778 endpoint count was zero.

### 27.6 Aggregate and fixed final-cause decision

| Metric | Value |
|---|---:|
| Total runs | 5 |
| Terminal runs | 5 |
| Accepted runs | 5 |
| Strict-ready success rate | 1 |
| Ready within 15 seconds | 5 |
| Delayed 15–30 seconds | 0 |
| Monitor gap | 0 |
| Ports seen, not same snapshot | 0 |
| 7777 not ready | 0 |
| 7778 not ready | 0 |
| Readiness-failure classifications | 0 |
| Port reassignment | 0 |
| Harness frequency failure | 0 |
| Cleanup failure | 0 |
| First-ready elapsed min / median / max | 9.218 / 9.488 / 10.431 seconds |
| All post-parent cleanup PASS | true |
| Final target process count | 0 |
| Final UDP 7777/7778 endpoint count | 0 |
| Verification execution status | PASS |
| Product readiness status | FAIL |

The fixed decision rule selects **TRANSIENT_OBSERVATION_VARIANCE**: all five runs were strict-ready PASS, all five were ready within 15 seconds, and cleanup passed in all five runs. Therefore the previous single-run 7777 non-observation is not reproduced as a startup delay, monitoring gap, or intermittent server readiness failure under this authoritative five-run procedure. Existing product blockers remain unchanged: missing packaged Config/Content, insufficient user documentation, no real game-project integration verification, no packaged executable verification, requested-port conflict handling, and delegate unregister coverage.

### 27.7 Exact five-run commands

```powershell
pwsh -NoLogo -NoProfile -File "D:\T\S58O-20260723-152041\RunOrphanRepeat.ps1" -RunIndex 1 -RunRoot "D:\T\S58O-20260723-152041\Run01"
pwsh -NoLogo -NoProfile -File "D:\T\S58O-20260723-152041\RunOrphanRepeat.ps1" -RunIndex 2 -RunRoot "D:\T\S58O-20260723-152041\Run02"
pwsh -NoLogo -NoProfile -File "D:\T\S58O-20260723-152041\RunOrphanRepeat.ps1" -RunIndex 3 -RunRoot "D:\T\S58O-20260723-152041\Run03"
pwsh -NoLogo -NoProfile -File "D:\T\S58O-20260723-152041\RunOrphanRepeat.ps1" -RunIndex 4 -RunRoot "D:\T\S58O-20260723-152041\Run04"
pwsh -NoLogo -NoProfile -File "D:\T\S58O-20260723-152041\RunOrphanRepeat.ps1" -RunIndex 5 -RunRoot "D:\T\S58O-20260723-152041\Run05"
```

### 27.8 Complete evidence SHA-256 table

The complete generated evidence inventory is listed below. Warmup artifacts are included for transparency; they are setup evidence and are not part of the five-run ORPHAN acceptance result.

| Role | Path | SHA-256 |
|---|---|---|
| baseline Lifecycle.py | D:\T\S58L-20260723-135846\Lifecycle.py | 41E20A4BA3E663D054BEBDD937EAF2272130D981EE6B1CEE3B685925B99EA8F3 |
| package BuildPlugin log | D:\T\S58-20260723-131534\BuildPlugin-short-root.log | 82D0DF6B6D191B4E05936C3D187FE6EB74730738EF1943FE038C0464F103541D |
| package ServerManageTool.uplugin | D:\T\S58-20260723-131534\P\ServerManageTool.uplugin | 66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146 |
| package UnrealEditor.modules | D:\T\S58-20260723-131534\P\Binaries\Win64\UnrealEditor.modules | A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274 |
| RunOrphanRepeat.ps1 | D:\T\S58O-20260723-152041\RunOrphanRepeat.ps1 | 785682A650DE833CE29133920F1CA85D22ECEC84013EF08FFB7CA445DBF510B6 |
| Warmup.py | D:\T\S58O-20260723-152041\Warmup.py | 0067832D38F4C95999A2061E238BD9375928F4B41736D1A939D44D5ED45F1CF0 |
| WarmupEditor.ps1 | D:\T\S58O-20260723-152041\WarmupEditor.ps1 | 8010478F8263941CD78B8453C4FA8410597D52C639E9ADF29CA236D09B9705DA |
| OrphanRepeatFinalSummary.json | D:\T\S58O-20260723-152041\OrphanRepeatFinalSummary.json | 9D7F11AF2B7284ADC2AC0645A24F994BABDBF2AE147280B301487E79A32FF90B |
| Run1 LifecycleOrphan30.py | D:\T\S58O-20260723-152041\Run01\LifecycleOrphan30.py | 2821952C9C9D44AF805FC53E8C42D044EF4F216652D0315F89A5B1373B8EF0DF |
| Run1 result JSON | D:\T\S58O-20260723-152041\Run01\ORPHAN.result.json | 78512C043DC27BEE920B3770CBE78D413B6437969700EC57D72EB054FD2D90BD |
| Run1 summary JSON | D:\T\S58O-20260723-152041\Run01\ORPHAN.summary.json | B41F257A6566591ABEF33F9CE5D73AC93C70E1F0579855769EBB7DDB76348660 |
| Run1 monitor JSONL | D:\T\S58O-20260723-152041\Run01\ORPHAN.monitor.jsonl | 4E2257048A5F2639C3BA5B7786E57E8995E5EC317AD1ECDA48C40B522D02F5BB |
| Run1 Editor log | D:\T\S58O-20260723-152041\Run01\ORPHAN.log | 1A86BB776F3A9DED27830E5536A3366468CA73484FFBC7F4A6111E6813E774AF |
| Run1 stdout | D:\T\S58O-20260723-152041\Run01\ORPHAN.stdout.txt | B302C9887950154FF656EEA803DA8807D3BE59A820C52204AB9D9A072854D79B |
| Run1 stderr | D:\T\S58O-20260723-152041\Run01\ORPHAN.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run1 host uproject | D:\T\S58O-20260723-152041\Run01\H\ServerManageToolBlueprintHost.uproject | AE16F05433B43F61A4F981793F948AC2848D3A1B44086E27D03621959FB7E3FD |
| Run1 DefaultEngine.ini | D:\T\S58O-20260723-152041\Run01\H\Config\DefaultEngine.ini | 51C4516FAC5AE10526ECAF3F598FF3B3FC5244397DC5B31806FCB42386A071CE |
| Run1 DefaultEditorPerProjectUserSettings.ini | D:\T\S58O-20260723-152041\Run01\H\Config\DefaultEditorPerProjectUserSettings.ini | E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C |
| Run1 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.54.51.json | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.54.51.json | A7FC8E86707C3702F1D52D88CC14270B383D80212CC2E2A7688CB63115405722 |
| Run1 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.54.51.txt | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.54.51.txt | 27F6CCC15CCCE6603DCD9A80492FB7A474F0E4C278A60921F0D194F80146039D |
| Run1 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.55.05.json | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.55.05.json | BB469E15B07905FBCD90B9E41129D6A89F30280F61F63A3B00721C7A706167C4 |
| Run1 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.55.05.txt | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.55.05.txt | 50D0A2785CB7BE028214F6B6DDEDB903A8A6B7F1F5AFC16BB4CA01C27D06E57E |
| Run1 Saved/Logs/AutoSDKInfo.json | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\AutoSDKInfo.json | A8F6B1493907E395B7810902DAE7DB94C1FC045D6CF1CB8C33BBFD59B067A6D2 |
| Run1 Saved/Logs/AutoSDKInfo.txt | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\AutoSDKInfo.txt | A7F514FA28FECEFB964D09470558BBF5E9AC0AD07D92ABB221A93162D091E39D |
| Run1 Saved/Logs/ServerManageToolBlueprintHost_2.log | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\ServerManageToolBlueprintHost_2.log | 0739AC636167FEDDD7C95C2BDFEE1F430E21E9ADEE5835D7246B1692DF96A6EC |
| Run1 Saved/Logs/ServerManageToolBlueprintHost.log | D:\T\S58O-20260723-152041\Run01\H\Saved\Logs\ServerManageToolBlueprintHost.log | 29ABDB3C0E8EB9660194C07BE53730EA52140DE84923A2C823F333B567394B4C |
| Run2 LifecycleOrphan30.py | D:\T\S58O-20260723-152041\Run02\LifecycleOrphan30.py | 2821952C9C9D44AF805FC53E8C42D044EF4F216652D0315F89A5B1373B8EF0DF |
| Run2 result JSON | D:\T\S58O-20260723-152041\Run02\ORPHAN.result.json | AB2BD626F73F8118F788277FE85C5C2283889FA52B68ED53BBADC9DFFD08BFA3 |
| Run2 summary JSON | D:\T\S58O-20260723-152041\Run02\ORPHAN.summary.json | 1964E64AD23D823901BD09D4985E3FDE0A7F65FE4C1AA0236C27395C549536A7 |
| Run2 monitor JSONL | D:\T\S58O-20260723-152041\Run02\ORPHAN.monitor.jsonl | F41035C3D90411D07EADC166FE8905E7AFA69403716D6F1EE7BEE9666CC83DC9 |
| Run2 Editor log | D:\T\S58O-20260723-152041\Run02\ORPHAN.log | 0FB605C634C82C6CB7AC1DBF95885A527167D7E813CFA92FA217D8FA5F95E964 |
| Run2 stdout | D:\T\S58O-20260723-152041\Run02\ORPHAN.stdout.txt | F23C01963E7F6891B08B5D01D7DCC4CB085A9A5C2442CBF0B3680C079B95A23C |
| Run2 stderr | D:\T\S58O-20260723-152041\Run02\ORPHAN.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run2 host uproject | D:\T\S58O-20260723-152041\Run02\H\ServerManageToolBlueprintHost.uproject | AE16F05433B43F61A4F981793F948AC2848D3A1B44086E27D03621959FB7E3FD |
| Run2 DefaultEngine.ini | D:\T\S58O-20260723-152041\Run02\H\Config\DefaultEngine.ini | 923EC1A94ADBB959330E8C0ECA342233E0F7531EAF3FB969C004CC562EDC0D1C |
| Run2 DefaultEditorPerProjectUserSettings.ini | D:\T\S58O-20260723-152041\Run02\H\Config\DefaultEditorPerProjectUserSettings.ini | E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C |
| Run2 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.59.42.json | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.59.42.json | 31C01B80999EF837F6B4CA35DA5E8D7E1DC21EFEF59A1B90AB5961D8ED54F6F6 |
| Run2 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.59.42.txt | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.59.42.txt | 9852810EE97EB9BACD603FC4A3E86A30ED951A41A9D850C7C031BBE5B8AC3F6A |
| Run2 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.59.58.json | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.59.58.json | 8FFF2F146E26CFA43A76385C6821786414E0E933D4BB510F3D6A20A0D61F1FBC |
| Run2 Saved/Logs/AutoSDKInfo-backup-2026.07.23-06.59.58.txt | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-06.59.58.txt | 9829A010753D68CC3284AF6DEBFDCA762CB309BA8A0D1FC835A75980FB3697A1 |
| Run2 Saved/Logs/AutoSDKInfo.json | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\AutoSDKInfo.json | E680D7ADB47E099B2B092B66C290F53FE663249007F63A9F4D669D9206449D94 |
| Run2 Saved/Logs/AutoSDKInfo.txt | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\AutoSDKInfo.txt | 7BC3793A888252DEA6251D4D485D7C9982D4163D60B6E53CBDB807B5E61D2C76 |
| Run2 Saved/Logs/ServerManageToolBlueprintHost_2.log | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\ServerManageToolBlueprintHost_2.log | 7C6C34FB439C184FAF47D7FD3815344BC96FC83DC0E9F708977BFC883001AFCF |
| Run2 Saved/Logs/ServerManageToolBlueprintHost.log | D:\T\S58O-20260723-152041\Run02\H\Saved\Logs\ServerManageToolBlueprintHost.log | 4F692B927202E09C8F0D1C4BAE3ECF18C00721F33D7960FE9FAED24881F6E1E8 |
| Run2 WARMUP.result.json | D:\T\S58O-20260723-152041\Run02\WARMUP.result.json | 48AF0F06177A2F0C8488999467F5F211C35B97A146859ED8F35E3473573BD8E6 |
| Run2 WARMUP.summary.json | D:\T\S58O-20260723-152041\Run02\WARMUP.summary.json | 6059F0653D83A8AA72E12187564CC1233B958DFE5D3543543D30485B0B14A4EA |
| Run2 WARMUP.log | D:\T\S58O-20260723-152041\Run02\WARMUP.log | 120FA732D534BE1C932EDE018C825C7DEE539D98EE9FDB7FA03791D26EFD7F7E |
| Run2 WARMUP.stdout.txt | D:\T\S58O-20260723-152041\Run02\WARMUP.stdout.txt | 58DDAA392DB67D7A90DB28F5CAF100016EDDA3715F885055CD9319A4CCC77ECA |
| Run2 WARMUP.stderr.txt | D:\T\S58O-20260723-152041\Run02\WARMUP.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run3 LifecycleOrphan30.py | D:\T\S58O-20260723-152041\Run03\LifecycleOrphan30.py | 2821952C9C9D44AF805FC53E8C42D044EF4F216652D0315F89A5B1373B8EF0DF |
| Run3 result JSON | D:\T\S58O-20260723-152041\Run03\ORPHAN.result.json | CCA8F7A2C50048C4500BBEC1A6E0E3BB2A9DC74353644F4420DD092B86589993 |
| Run3 summary JSON | D:\T\S58O-20260723-152041\Run03\ORPHAN.summary.json | FA664119C9E1959C65F1202945DB26575E457647E8928F53065C84FB37BBA24E |
| Run3 monitor JSONL | D:\T\S58O-20260723-152041\Run03\ORPHAN.monitor.jsonl | 5F5F0BE015641E8A3B8E1C707C39536F7CFFBB887D4D59426D2B76DA3C5CFD6F |
| Run3 Editor log | D:\T\S58O-20260723-152041\Run03\ORPHAN.log | F64DAEC24EC61E3608B2CD692ECEF37B64912230C3211138D8450CED4F01A47B |
| Run3 stdout | D:\T\S58O-20260723-152041\Run03\ORPHAN.stdout.txt | 15A6412F0DB26B3B58E2823CBA3B6B5F8B230A08E2BDFCC68F289D025D4C5056 |
| Run3 stderr | D:\T\S58O-20260723-152041\Run03\ORPHAN.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run3 host uproject | D:\T\S58O-20260723-152041\Run03\H\ServerManageToolBlueprintHost.uproject | AE16F05433B43F61A4F981793F948AC2848D3A1B44086E27D03621959FB7E3FD |
| Run3 DefaultEngine.ini | D:\T\S58O-20260723-152041\Run03\H\Config\DefaultEngine.ini | AD75CC803FF1A9A1A1BF0EE67138E39C60A0CD2F71179F2AB8469E3CF938E8CB |
| Run3 DefaultEditorPerProjectUserSettings.ini | D:\T\S58O-20260723-152041\Run03\H\Config\DefaultEditorPerProjectUserSettings.ini | E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C |
| Run3 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.01.35.json | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.01.35.json | A01DE8B4CF1F49A32D89938D63758B062988D079EDB7937FA01B73C065B0F947 |
| Run3 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.01.35.txt | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.01.35.txt | 5EEF73144BF46AEEB3771E6FD07C611675D77E29D113CC3932632066AD82275F |
| Run3 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.01.50.json | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.01.50.json | 393BBE3FA4681DC939842FC99C39A18BCD063A36D2268E9854849424D7B35BBD |
| Run3 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.01.50.txt | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.01.50.txt | 20B49AFD9E91B8698A9566E025F4DD590C0DF6F7C4B37BAEB4E175429B8AD890 |
| Run3 Saved/Logs/AutoSDKInfo.json | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\AutoSDKInfo.json | D1EADE1EF2E95C7D2783C9498316C32AC78FF6D1AA5B256DD915D4A6CCE7C922 |
| Run3 Saved/Logs/AutoSDKInfo.txt | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\AutoSDKInfo.txt | E655F79B49A81BB19FCF6D4445EEA16633A6D77AE71E276F340527949876BB6F |
| Run3 Saved/Logs/ServerManageToolBlueprintHost_2.log | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\ServerManageToolBlueprintHost_2.log | 6AA1EA078C8D4AFDF7E282F21A2090B3C5EC2D01D612A0FE318ED78184ED9748 |
| Run3 Saved/Logs/ServerManageToolBlueprintHost.log | D:\T\S58O-20260723-152041\Run03\H\Saved\Logs\ServerManageToolBlueprintHost.log | 7ED58BC1B7CAA90968181E6E4B97A25BBE940B676D5088D2B5EB184708DDCC7C |
| Run3 WARMUP.result.json | D:\T\S58O-20260723-152041\Run03\WARMUP.result.json | AA06E1AE973357CC94CCEF1796DDD9D6418753F6CB66959BF67BA33374F939C8 |
| Run3 WARMUP.summary.json | D:\T\S58O-20260723-152041\Run03\WARMUP.summary.json | C5699D42DBE89173441557B170658175940E750606D3D997AEDF174F4B6305A0 |
| Run3 WARMUP.log | D:\T\S58O-20260723-152041\Run03\WARMUP.log | 23E0AEA4A0EB54118CACC5B8FD41B1F3C28324C57CB215230A5C922163A65B6C |
| Run3 WARMUP.stdout.txt | D:\T\S58O-20260723-152041\Run03\WARMUP.stdout.txt | 21D4FEAF446A33754673350FDD94A807CB1CAE2EB55F58738D9127D347F1F8B2 |
| Run3 WARMUP.stderr.txt | D:\T\S58O-20260723-152041\Run03\WARMUP.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run4 LifecycleOrphan30.py | D:\T\S58O-20260723-152041\Run04\LifecycleOrphan30.py | 2821952C9C9D44AF805FC53E8C42D044EF4F216652D0315F89A5B1373B8EF0DF |
| Run4 result JSON | D:\T\S58O-20260723-152041\Run04\ORPHAN.result.json | 2659367AF56981FFE4F5987D191C41236A8E8A12DAD1DEB473B7BD02EED026E2 |
| Run4 summary JSON | D:\T\S58O-20260723-152041\Run04\ORPHAN.summary.json | 15688F2F5E70F654555CE3EE6C654AF8070DB12756E08F1F46359FE2345B47EF |
| Run4 monitor JSONL | D:\T\S58O-20260723-152041\Run04\ORPHAN.monitor.jsonl | 3B422E0A7439E70313FFB79DC4168A808B40D851970814A34F6FF23E35553EB1 |
| Run4 Editor log | D:\T\S58O-20260723-152041\Run04\ORPHAN.log | 3BC2E39DABD6160DF9E6CE11BBD6555467A1F2D81035A8B4D74799314F51D94F |
| Run4 stdout | D:\T\S58O-20260723-152041\Run04\ORPHAN.stdout.txt | DDBC9FF0200CF210A71099085A4483D68C4681E204919F9B5D9F313B62A47E12 |
| Run4 stderr | D:\T\S58O-20260723-152041\Run04\ORPHAN.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run4 host uproject | D:\T\S58O-20260723-152041\Run04\H\ServerManageToolBlueprintHost.uproject | AE16F05433B43F61A4F981793F948AC2848D3A1B44086E27D03621959FB7E3FD |
| Run4 DefaultEngine.ini | D:\T\S58O-20260723-152041\Run04\H\Config\DefaultEngine.ini | 85289E0C805D6BCB2FDF38BDFB7AD8F3A1784082CD0A88FEB6BD79D071A1E0D2 |
| Run4 DefaultEditorPerProjectUserSettings.ini | D:\T\S58O-20260723-152041\Run04\H\Config\DefaultEditorPerProjectUserSettings.ini | E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C |
| Run4 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.03.27.json | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.03.27.json | 9D949BEC2E6BC5F9A9B9980E1EF8E40F3FC18CF80C8E66EAB25927761206FF94 |
| Run4 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.03.27.txt | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.03.27.txt | FAE991C21603FCAA0F64C4ABF9D1CBE763566BD98CF091964B5FB6B2998E2267 |
| Run4 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.03.41.json | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.03.41.json | 005C2321E72336F8C41AADA626CD1B454A5988ED23DA37B3A29F1F05E82E3E26 |
| Run4 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.03.41.txt | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.03.41.txt | AACC5E78F41ABD54A60930F1F63F4B0F9048B044BAFB136FC8DC498297511701 |
| Run4 Saved/Logs/AutoSDKInfo.json | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\AutoSDKInfo.json | 23E9D1C907CA701952407715A8829517E9B3D12818D8FA35AE146ECF64B6ED25 |
| Run4 Saved/Logs/AutoSDKInfo.txt | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\AutoSDKInfo.txt | 95A163582F69D7457BCDF1019DBD00CD778015232D5A393C4EF9FABE4F12BA60 |
| Run4 Saved/Logs/ServerManageToolBlueprintHost_2.log | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\ServerManageToolBlueprintHost_2.log | 303CD2B001FB44B22B4B00BA76D36BD39E59FB3DD77B639C34D7A14754C00E36 |
| Run4 Saved/Logs/ServerManageToolBlueprintHost.log | D:\T\S58O-20260723-152041\Run04\H\Saved\Logs\ServerManageToolBlueprintHost.log | 2D55169A287118848593C68287F53AB3444BDC526292D1B2E0A05E109AB26598 |
| Run4 WARMUP.result.json | D:\T\S58O-20260723-152041\Run04\WARMUP.result.json | F4DE1F895426ECB014462858156DE768EA614587A8B3BE3EEED79A3BCE5F0338 |
| Run4 WARMUP.summary.json | D:\T\S58O-20260723-152041\Run04\WARMUP.summary.json | 0F5CE3AC2BEAB74EE2007790FAC8CFC411D2444CE39FF20C26E7769D9B8F5BCF |
| Run4 WARMUP.log | D:\T\S58O-20260723-152041\Run04\WARMUP.log | E1DC363733A4C31A63C0607D08BF044D7E575022D0D05412198B88061AB5CAB8 |
| Run4 WARMUP.stdout.txt | D:\T\S58O-20260723-152041\Run04\WARMUP.stdout.txt | 160CF9C73ABA43BA5086538ED9B2EA0A6277D8CFA9D3A985D27CED55C3596B44 |
| Run4 WARMUP.stderr.txt | D:\T\S58O-20260723-152041\Run04\WARMUP.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run5 LifecycleOrphan30.py | D:\T\S58O-20260723-152041\Run05\LifecycleOrphan30.py | 2821952C9C9D44AF805FC53E8C42D044EF4F216652D0315F89A5B1373B8EF0DF |
| Run5 result JSON | D:\T\S58O-20260723-152041\Run05\ORPHAN.result.json | 3B58242C928653A2DC3903A93FFA2098C999DD13436C109178914EA445F979AD |
| Run5 summary JSON | D:\T\S58O-20260723-152041\Run05\ORPHAN.summary.json | 9F567AABFD3598FCD5C782765A491BEEE1FE0696032F5091BEB3B048DE6CA2EF |
| Run5 monitor JSONL | D:\T\S58O-20260723-152041\Run05\ORPHAN.monitor.jsonl | 7E80552CF46EB5CAA7BCD4EBDC8376B1B0EC402F90FB29F87EB80C29906F369B |
| Run5 Editor log | D:\T\S58O-20260723-152041\Run05\ORPHAN.log | 2C08EB3C46583025FCFFF6B9653418E9164F1DB826ECCBE52CF0399EEC3A70A9 |
| Run5 stdout | D:\T\S58O-20260723-152041\Run05\ORPHAN.stdout.txt | 59A58AA1571E4DF1FAE131C30A898BBC5BD44FF026DA9181FAE0346235F61EE2 |
| Run5 stderr | D:\T\S58O-20260723-152041\Run05\ORPHAN.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |
| Run5 host uproject | D:\T\S58O-20260723-152041\Run05\H\ServerManageToolBlueprintHost.uproject | AE16F05433B43F61A4F981793F948AC2848D3A1B44086E27D03621959FB7E3FD |
| Run5 DefaultEngine.ini | D:\T\S58O-20260723-152041\Run05\H\Config\DefaultEngine.ini | 681C1CA2FEC308BAB5D8C0C15C51AC069AC33F58CEF91378A439BD05BC8DCD19 |
| Run5 DefaultEditorPerProjectUserSettings.ini | D:\T\S58O-20260723-152041\Run05\H\Config\DefaultEditorPerProjectUserSettings.ini | E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C |
| Run5 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.05.07.json | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.05.07.json | D22D014D6A30CE08D9B01EF8FC8D922BAFF2809A4EEBD4A475F9BC5D7E09D2DE |
| Run5 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.05.07.txt | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.05.07.txt | B06315CD5561B777BF224BDC7A2235054B3EAE254B78E74414F0800C12A447D1 |
| Run5 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.05.21.json | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.05.21.json | EA55CD95DE40F3F2DB85C565EF51CAB6C08D156FF369EA52D763B1C01E61D5A1 |
| Run5 Saved/Logs/AutoSDKInfo-backup-2026.07.23-07.05.21.txt | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\AutoSDKInfo-backup-2026.07.23-07.05.21.txt | 7FC036BCF8CC859212914F41804922D15405DA390798DD318FFB07F3842217C8 |
| Run5 Saved/Logs/AutoSDKInfo.json | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\AutoSDKInfo.json | 7BAB0F5CEFEF55DEBC8ED5BCB12CAEE235F7F67B62D6074977183C04D55F35D3 |
| Run5 Saved/Logs/AutoSDKInfo.txt | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\AutoSDKInfo.txt | A846DC89DC6013353E6D052B387F8106943E7E61123A6DBD35DD9E8312617C50 |
| Run5 Saved/Logs/ServerManageToolBlueprintHost_2.log | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\ServerManageToolBlueprintHost_2.log | 71C17983E4816758034598E2D362B5C27FACA7B078DFEB0E1026A8E8B209D927 |
| Run5 Saved/Logs/ServerManageToolBlueprintHost.log | D:\T\S58O-20260723-152041\Run05\H\Saved\Logs\ServerManageToolBlueprintHost.log | 0C93756E56E20B9B9FC9E1E3593EEE5512ACF9CD5EBD29203770751275AC882A |
| Run5 WARMUP.result.json | D:\T\S58O-20260723-152041\Run05\WARMUP.result.json | BB36D84B45DFDBB7B1CA2D260788E3CFCD5DF4EE4CC81EFFB00EF06BD2F9BEBE |
| Run5 WARMUP.summary.json | D:\T\S58O-20260723-152041\Run05\WARMUP.summary.json | 99B10998DCC8FC603705A3C4177B9CA200FC2964D7BD49A4680AFCEDF316EE1B |
| Run5 WARMUP.log | D:\T\S58O-20260723-152041\Run05\WARMUP.log | EB49F55DD877DA1991ECFA137ACB856F6FFC04E4178086807D23633166CA7BD8 |
| Run5 WARMUP.stdout.txt | D:\T\S58O-20260723-152041\Run05\WARMUP.stdout.txt | AC2952DDBF6C6D28892F7229ACECFDD2E3778F3B347DD1FE33E54ED2F4D62829 |
| Run5 WARMUP.stderr.txt | D:\T\S58O-20260723-152041\Run05\WARMUP.stderr.txt | E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 |

### 27.9 LifecycleOrphan30.py — full source

The same `LifecycleOrphan30.py` source was copied into all five run roots; per-run hashes are listed above.

```python
import datetime
import json
import os
import time
import traceback

import unreal


MODE = os.environ["SMT_MODE"]
RESULT_PATH = os.environ["SMT_RESULT_JSON"]
HOLD_SECONDS = float(os.environ["SMT_HOLD_SECONDS"])
VALID_MODES = {"PIE", "SIMULATE", "ORPHAN"}

result = {
    "mode": MODE,
    "status": "RUNNING",
    "stage": "INITIALIZING",
    "started_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "play_requested_at_utc": None,
    "play_started_at_utc": None,
    "end_requested_at_utc": None,
    "play_ended_at_utc": None,
    "quit_requested_at_utc": None,
    "api_presence": {},
    "error": None,
    "traceback": None,
    "state_transitions": [],
}
result["hold_seconds"] = HOLD_SECONDS

subsystem = None
callback_handle = None
state = "INITIALIZING"
state_started = time.monotonic()
finished = False


def utc_now():
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


def transition(next_state):
    global state, state_started
    state = next_state
    state_started = time.monotonic()
    result["stage"] = next_state
    result["state_transitions"].append(
        {"state": next_state, "at_utc": utc_now()}
    )


def write_result():
    with open(RESULT_PATH, "w", encoding="utf-8") as output:
        json.dump(result, output, ensure_ascii=False, indent=2)


def api_available(name):
    value = getattr(subsystem, name, None)
    result["api_presence"][name] = callable(value)
    return callable(value)


def fail(exc):
    global finished
    if finished:
        return
    failure_status = (
        result["status"]
        if result["status"] == "BLOCKED_UE58_PYTHON_API"
        else "FAIL"
    )
    result["status"] = failure_status
    result["error"] = str(exc)
    result["traceback"] = traceback.format_exc()
    transition(failure_status)
    finished = True
    finalize()


def finalize():
    global callback_handle
    if callback_handle is not None:
        unreal.unregister_slate_post_tick_callback(callback_handle)
        callback_handle = None
    result["quit_requested_at_utc"] = utc_now()
    if result["status"] == "RUNNING":
        result["status"] = "PASS"
        transition("PASS")
    write_result()
    unreal.EditorPythonScripting.set_keep_python_script_alive(False)
    unreal.SystemLibrary.quit_editor()


def request_play():
    result["play_requested_at_utc"] = utc_now()
    if MODE == "SIMULATE":
        subsystem.editor_play_simulate()
    else:
        subsystem.editor_request_begin_play()
    transition("WAITING_FOR_PLAY")


def on_tick(_delta_seconds):
    try:
        elapsed = time.monotonic() - state_started
        if state == "WAIT_BEFORE_PLAY":
            if elapsed >= 5.0:
                request_play()
        elif state == "WAITING_FOR_PLAY":
            if subsystem.is_in_play_in_editor():
                result["play_started_at_utc"] = utc_now()
                transition("HOLDING_PLAY")
            elif elapsed > 30.0:
                raise RuntimeError("play did not start within 30 seconds")
        elif state == "HOLDING_PLAY":
            if elapsed >= HOLD_SECONDS:
                if MODE == "ORPHAN":
                    result["play_ended_at_utc"] = None
                    finalize()
                else:
                    result["end_requested_at_utc"] = utc_now()
                    subsystem.editor_request_end_play()
                    transition("WAITING_FOR_PLAY_END")
        elif state == "WAITING_FOR_PLAY_END":
            if not subsystem.is_in_play_in_editor():
                result["play_ended_at_utc"] = utc_now()
                transition("WAITING_AFTER_PLAY_END")
            elif elapsed > 30.0:
                raise RuntimeError("play did not end within 30 seconds")
        elif state == "WAITING_AFTER_PLAY_END":
            if elapsed >= 10.0:
                finalize()
    except Exception as exc:
        fail(exc)


try:
    if MODE not in VALID_MODES:
        raise RuntimeError("Unsupported SMT_MODE: " + MODE)
    unreal.EditorPythonScripting.set_keep_python_script_alive(True)
    subsystem = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    required_api_names = [
        "editor_request_begin_play",
        "editor_play_simulate",
        "editor_request_end_play",
        "is_in_play_in_editor",
    ]
    missing = [name for name in required_api_names if not api_available(name)]
    if missing:
        result["status"] = "BLOCKED_UE58_PYTHON_API"
        raise RuntimeError("Required UE 5.8 Python API missing: " + ", ".join(missing))
    callback_handle = unreal.register_slate_post_tick_callback(on_tick)
    transition("WAIT_BEFORE_PLAY")
except Exception as exc:
    fail(exc)
```

### 27.10 RunOrphanRepeat.ps1 — full source

```powershell
param(
    [Parameter(Mandatory = $true)]
    [ValidateRange(1, 5)]
    [int]$RunIndex,

    [Parameter(Mandatory = $true)]
    [string]$RunRoot
)

$ErrorActionPreference = 'Stop'
$Mode = 'ORPHAN'
$MaxSeconds = 180
$HoldSeconds = 30.0
$PreParentPollMilliseconds = 100
$PostParentPollMilliseconds = 250
$PostParentMinimumSeconds = 10.0
$PostParentMinimumPolls = 20
$Utf8NoBom = [System.Text.UTF8Encoding]::new($false)
$verifyRoot = [System.IO.Path]::GetFullPath((Split-Path -Parent $MyInvocation.MyCommand.Path))
$runRoot = [System.IO.Path]::GetFullPath($RunRoot)
$verifyPrefix = $verifyRoot.TrimEnd('\') + '\'
if (-not $runRoot.StartsWith($verifyPrefix, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw "RunRoot must be inside verifyRoot: $runRoot"
}

$hostRoot = Join-Path $runRoot 'H'
$hostProject = Join-Path $hostRoot 'ServerManageToolBlueprintHost.uproject'
$hostProjectSlash = $hostProject.Replace('\', '/')
$pythonPath = Join-Path $runRoot 'LifecycleOrphan30.py'
$resultPath = Join-Path $runRoot 'ORPHAN.result.json'
$summaryPath = Join-Path $runRoot 'ORPHAN.summary.json'
$monitorPath = Join-Path $runRoot 'ORPHAN.monitor.jsonl'
$logPath = Join-Path $runRoot 'ORPHAN.log'
$stdoutPath = Join-Path $runRoot 'ORPHAN.stdout.txt'
$stderrPath = Join-Path $runRoot 'ORPHAN.stderr.txt'
$logEvidencePath = Join-Path $runRoot 'ORPHAN.log-evidence.json'
$harnessErrorPath = Join-Path $runRoot 'ORPHAN.harness-error.txt'
$savedLogsRoot = Join-Path $hostRoot 'Saved\Logs'
$editorPath = 'C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe'
$processStartCache = @{}
$script:AuthoritativeChecked = @{}
$script:TargetProcessCache = @{}
$script:FastProcessCacheReady = $false

if (-not [System.IO.File]::Exists($hostProject)) { throw "Host project missing: $hostProject" }
if (-not [System.IO.File]::Exists($pythonPath)) { throw "LifecycleOrphan30.py missing: $pythonPath" }

trap {
    try { [System.IO.File]::WriteAllText($harnessErrorPath, ($_ | Out-String), $Utf8NoBom) } catch { }
    throw
}

function Write-JsonFile {
    param([string]$Path, [object]$Value, [int]$Depth = 30)
    $json = ConvertTo-Json -InputObject $Value -Depth $Depth
    [System.IO.File]::WriteAllText($Path, $json, $Utf8NoBom)
}

function Write-JsonLine {
    param([object]$Value)
    $json = ConvertTo-Json -InputObject $Value -Depth 30 -Compress
    [System.IO.File]::AppendAllText($monitorPath, $json + [Environment]::NewLine, $Utf8NoBom)
}

function Get-CimProcesses {
    param([int]$ParentPid = 0, [switch]$ForceRefresh)
    if ($ParentPid -le 0) { return @(Get-CimInstance Win32_Process -Filter "Name='UnrealEditor.exe'") }
    if ($ForceRefresh -or -not $script:FastProcessCacheReady) {
        $rows = @(Get-CimInstance Win32_Process -Filter "Name='UnrealEditor.exe' AND (ProcessId=$ParentPid OR ParentProcessId=$ParentPid)")
        foreach ($row in $rows) { $script:TargetProcessCache[[string]$row.ProcessId] = $row }
        $requestedPorts = @($script:TargetProcessCache.Values | Where-Object { $_.ParentProcessId -eq $ParentPid } | ForEach-Object { Get-RequestedPort $_.CommandLine })
        $script:FastProcessCacheReady = $requestedPorts -contains 7777 -and $requestedPorts -contains 7778
        return @($rows)
    }
    $alive = @()
    foreach ($cached in @($script:TargetProcessCache.Values)) {
        $process = Get-Process -Id $cached.ProcessId -ErrorAction SilentlyContinue
        if ($null -ne $process -and -not $process.HasExited) { $alive += $cached }
    }
    return @($alive)
}

function Test-HostProjectCommandLine {
    param([string]$CommandLine)
    if ([string]::IsNullOrWhiteSpace($CommandLine)) { return $false }
    return $CommandLine.Contains($hostProject) -or $CommandLine.Contains($hostProjectSlash)
}

function Get-RequestedPort {
    param([string]$CommandLine)
    if ([string]::IsNullOrWhiteSpace($CommandLine)) { return $null }
    $match = [regex]::Match($CommandLine, '(?i)(?:-port=|[?&]Port=|\bPort=)(\d+)')
    if ($match.Success) { return [int]$match.Groups[1].Value }
    return $null
}

function Get-TargetChildInstances {
    param([object[]]$Processes, [int]$ParentPid)
    $children = @()
    foreach ($process in $Processes) {
        if ($process.Name -eq 'UnrealEditor.exe' -and
            $process.ProcessId -ne $ParentPid -and
            (Test-HostProjectCommandLine $process.CommandLine) -and
            $process.CommandLine -match '(?i)(^|\s)-server(?:\s|$)') {
            $children += $process
        }
    }
    return @($children)
}

function Get-UdpEndpointsFromNetstat {
    $endpoints = @()
    foreach ($line in @(netstat -ano -p udp)) {
        $match = [regex]::Match([string]$line, '^\s*UDP\s+(.+):(\d+)\s+\S+\s+(\d+)\s*$')
        if (-not $match.Success) { continue }
        $endpoints += [ordered]@{
            LocalAddress = $match.Groups[1].Value
            LocalPort = [int]$match.Groups[2].Value
            RemoteAddress = $null
            RemotePort = 0
            State = $null
            OwningProcess = [int]$match.Groups[3].Value
        }
    }
    return @($endpoints)
}

function Get-PortOwners {
    param([object[]]$UdpEndpoints, [object[]]$Processes)
    $owners = @()
    $endpoints = if ($null -eq $UdpEndpoints) { @(Get-UdpEndpointsFromNetstat) } else { @($UdpEndpoints) }
    foreach ($endpoint in $endpoints) {
        if ($endpoint.LocalPort -ne 7777 -and $endpoint.LocalPort -ne 7778) { continue }
        $process = $null
        if ($null -ne $Processes) {
            foreach ($candidate in $Processes) {
                if ($candidate.ProcessId -eq $endpoint.OwningProcess) { $process = $candidate; break }
            }
        } else {
            $process = Get-CimInstance Win32_Process -Filter "ProcessId=$($endpoint.OwningProcess)" -ErrorAction SilentlyContinue
        }
        $owners += [ordered]@{
            local_address = $endpoint.LocalAddress
            port = [int]$endpoint.LocalPort
            owning_pid = [int]$endpoint.OwningProcess
            process_name = if ($null -eq $process) { $null } else { $process.Name }
            command_line = if ($null -eq $process) { $null } else { $process.CommandLine }
        }
    }
    return @($owners)
}

function Get-ProcessStartUtc {
    param([int]$ProcessId)
    if ($processStartCache.ContainsKey([string]$ProcessId)) { return $processStartCache[[string]$ProcessId] }
    $process = Get-Process -Id $ProcessId -ErrorAction SilentlyContinue
    if ($null -eq $process) { return $null }
    try { $value = $process.StartTime.ToUniversalTime().ToString('o') } catch { $value = $null }
    $processStartCache[[string]$ProcessId] = $value
    return $value
}

function Get-ProcessEvidence {
    param([object]$CimProcess, [string]$Role, [object[]]$UdpEndpoints, [string]$EndpointSource = 'netstat')
    $evidenceEndpoints = @()
    foreach ($endpoint in @($UdpEndpoints)) {
        if ($endpoint.OwningProcess -ne $CimProcess.ProcessId) { continue }
        $evidenceEndpoints += [ordered]@{
            local_address = $endpoint.LocalAddress
            local_port = [int]$endpoint.LocalPort
            remote_address = $endpoint.RemoteAddress
            remote_port = [int]$endpoint.RemotePort
            state = $endpoint.State
        }
    }
    return [ordered]@{
        role = $Role
        process_id = [int]$CimProcess.ProcessId
        parent_process_id = [int]$CimProcess.ParentProcessId
        name = $CimProcess.Name
        command_line = $CimProcess.CommandLine
        requested_port = Get-RequestedPort $CimProcess.CommandLine
        actual_udp_endpoints = @($evidenceEndpoints)
        actual_udp_endpoint_source = $EndpointSource
        process_start_time_utc = Get-ProcessStartUtc $CimProcess.ProcessId
    }
}

function Get-PythonResult {
    if (-not [System.IO.File]::Exists($resultPath)) { return $null }
    try { return ConvertFrom-Json -InputObject ([System.IO.File]::ReadAllText($resultPath)) } catch { return $null }
}

function Get-PollSnapshot {
    param(
        [int]$ParentPid,
        [DateTime]$TimestampUtc,
        [DateTime]$ProcessStartedAtUtc,
        [Nullable[DateTime]]$PlayStartedAtUtc
    )
    $processes = Get-CimProcesses $ParentPid
    $udpEndpoints = @(Get-UdpEndpointsFromNetstat)
    $parent = $null
    foreach ($process in $processes) {
        if ($process.ProcessId -eq $ParentPid) { $parent = $process; break }
    }
    $children = Get-TargetChildInstances $processes $ParentPid
    $childEvidence = @()
    foreach ($child in $children) {
        $evidence = Get-ProcessEvidence $child 'child' $udpEndpoints
        $requestedPort = Get-RequestedPort $child.CommandLine
        $candidateActual = @($evidence.actual_udp_endpoints | Where-Object { $_.local_port -eq $requestedPort })
        $checkedKey = [string]$child.ProcessId
        if (($requestedPort -eq 7777 -or $requestedPort -eq 7778) -and $candidateActual.Count -gt 0 -and -not $script:AuthoritativeChecked.ContainsKey($checkedKey)) {
            $authoritativeEndpoints = @(Get-NetUDPEndpoint -OwningProcess $child.ProcessId -ErrorAction SilentlyContinue)
            $script:AuthoritativeChecked[$checkedKey] = $true
            if ($authoritativeEndpoints.Count -gt 0) { $evidence = Get-ProcessEvidence $child 'child' $authoritativeEndpoints 'Get-NetUDPEndpoint' }
        }
        $childEvidence += $evidence
    }
    $playElapsed = $null
    if ($null -ne $PlayStartedAtUtc) {
        $playStartValue = [DateTime]$PlayStartedAtUtc
        $playElapsed = [Math]::Round(($TimestampUtc - $playStartValue).TotalSeconds, 3)
    }
    return [ordered]@{
        timestamp_utc = $TimestampUtc.ToString('o')
        elapsed_from_process_start_seconds = [Math]::Round(($TimestampUtc - $ProcessStartedAtUtc).TotalSeconds, 3)
        elapsed_from_play_start_seconds = $playElapsed
        play_started_at_utc = if ($null -eq $PlayStartedAtUtc) { $null } else { ([DateTime]$PlayStartedAtUtc).ToString('o') }
        mode = $Mode
        parent_pid = $ParentPid
        parent_process_exists = $null -ne $parent
        parent_process = if ($null -eq $parent) { $null } else { Get-ProcessEvidence $parent 'parent' $udpEndpoints }
        child_count = $children.Count
        children = @($childEvidence)
        udp_7777_7778_owners = @(Get-PortOwners $udpEndpoints $processes)
    }
}

function Update-ChildTracking {
    param([hashtable]$Tracking, [object]$Snapshot)
    foreach ($child in @($Snapshot.children)) {
        $key = [string]$child.process_id
        if (-not $Tracking.ContainsKey($key)) {
            $Tracking[$key] = [ordered]@{
                process_id = [int]$child.process_id
                parent_process_id_values = @()
                first_seen_utc = $Snapshot.timestamp_utc
                last_seen_utc = $Snapshot.timestamp_utc
                requested_ports = @()
                actual_ports = @()
                expected_port_first_observed = @{}
            }
        }
        $record = $Tracking[$key]
        $record.last_seen_utc = $Snapshot.timestamp_utc
        if ($record.parent_process_id_values -notcontains $child.parent_process_id) { $record.parent_process_id_values += [int]$child.parent_process_id }
        if ($null -ne $child.requested_port -and $record.requested_ports -notcontains $child.requested_port) { $record.requested_ports += [int]$child.requested_port }
        foreach ($endpoint in @($child.actual_udp_endpoints)) {
            if ($null -ne $endpoint -and $record.actual_ports -notcontains $endpoint.local_port) { $record.actual_ports += [int]$endpoint.local_port }
        }
    }
}

function Test-BothChildrenAliveSameSnapshot {
    param([object]$Snapshot)
    $children7777 = @($Snapshot.children | Where-Object { $_.requested_port -eq 7777 })
    $children7778 = @($Snapshot.children | Where-Object { $_.requested_port -eq 7778 })
    if ($children7777.Count -eq 0 -or $children7778.Count -eq 0) { return $false }
    return [int]$children7777[0].process_id -ne [int]$children7778[0].process_id
}

function Test-StrictReady {
    param([object]$Snapshot, [int]$ParentPid)
    $children = @($Snapshot.children)
    if ($children.Count -ne 2) { return $false }
    if ([int]$children[0].process_id -eq [int]$children[1].process_id) { return $false }
    foreach ($child in $children) {
        if ([int]$child.parent_process_id -ne $ParentPid) { return $false }
        if ($null -eq $child.requested_port) { return $false }
    }
    $requested = @($children | ForEach-Object { [int]$_.requested_port } | Sort-Object)
    if (($requested -join ',') -ne '7777,7778') { return $false }
    $actual7777 = @($children | Where-Object { $_.requested_port -eq 7777 } | ForEach-Object { $_.actual_udp_endpoints } | Where-Object { $null -ne $_ } | ForEach-Object { [int]$_.local_port })
    $actual7778 = @($children | Where-Object { $_.requested_port -eq 7778 } | ForEach-Object { $_.actual_udp_endpoints } | Where-Object { $null -ne $_ } | ForEach-Object { [int]$_.local_port })
    if ($actual7777 -notcontains 7777 -or $actual7778 -notcontains 7778) { return $false }
    return @($actual7777 + $actual7778 | Sort-Object -Unique).Count -eq 2
}

function Stop-ExactProcess {
    param([object]$CimProcess, [string]$Role)
    if ($null -eq $CimProcess) { return $false }
    $valid = $CimProcess.Name -eq 'UnrealEditor.exe' -and (Test-HostProjectCommandLine $CimProcess.CommandLine)
    if ($Role -eq 'child') { $valid = $valid -and $CimProcess.CommandLine -match '(?i)(^|\s)-server(?:\s|$)' }
    if (-not $valid) { return $false }
    $process = Get-Process -Id $CimProcess.ProcessId -ErrorAction SilentlyContinue
    if ($null -ne $process -and -not $process.HasExited) {
        $process.Kill()
        $process.WaitForExit(10000)
        return $true
    }
    return $false
}

function Test-RequiredField {
    param([object]$Object, [string]$PropertyName)
    if ($null -eq $Object) { return $false }
    $value = $Object.$PropertyName
    return $null -ne $value -and -not [string]::IsNullOrWhiteSpace([string]$value)
}

function Test-PythonAcceptance {
    param([object]$Result)
    if ($null -eq $Result -or $Result.status -ne 'PASS') { return $false }
    if ($Result.hold_seconds -ne $HoldSeconds) { return $false }
    if (-not (Test-RequiredField $Result 'play_requested_at_utc')) { return $false }
    if (-not (Test-RequiredField $Result 'play_started_at_utc')) { return $false }
    if (-not (Test-RequiredField $Result 'quit_requested_at_utc')) { return $false }
    if ($null -ne $Result.end_requested_at_utc -or $null -ne $Result.play_ended_at_utc) { return $false }
    $states = @($Result.state_transitions | ForEach-Object { $_.state })
    return $states -contains 'HOLDING_PLAY' -and $states -contains 'PASS'
}

function Get-Median {
    param([double[]]$Values)
    if ($Values.Count -eq 0) { return $null }
    $sorted = @($Values | Sort-Object)
    $middle = [int][Math]::Floor($sorted.Count / 2)
    if ($sorted.Count % 2 -eq 1) { return [Math]::Round($sorted[$middle], 6) }
    return [Math]::Round(($sorted[$middle - 1] + $sorted[$middle]) / 2.0, 6)
}

function Get-LogEvidence {
    $logFiles = @()
    if ([System.IO.Directory]::Exists($savedLogsRoot)) {
        foreach ($file in @(Get-ChildItem -LiteralPath $savedLogsRoot -Filter '*.log' -File -Recurse)) { $logFiles += $file.FullName }
    }
    if ([System.IO.File]::Exists($logPath) -and $logFiles -notcontains $logPath) { $logFiles += $logPath }
    $keywordPattern = '(?i)Created socket for bind address|IpNetDriver listening on port|\bbind\b|\blisten\b|Port=|\bError\b|\bWarning\b'
    $files = @()
    $matches = @()
    foreach ($path in $logFiles) {
        $hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $path).Hash
        $item = Get-Item -LiteralPath $path
        $lines = [System.IO.File]::ReadAllLines($path)
        $fileMatches = @()
        for ($lineIndex = 0; $lineIndex -lt $lines.Count; $lineIndex++) {
            $line = $lines[$lineIndex]
            if (-not [regex]::IsMatch($line, $keywordPattern)) { continue }
            $entry = [ordered]@{
                log_filename = $item.Name
                log_path = $path
                line_number = $lineIndex + 1
                line = $line
                file_last_write_time_utc = $item.LastWriteTimeUtc.ToString('o')
                file_sha256 = $hash
                expected_7777_line = $line.Contains('7777')
                expected_7778_line = $line.Contains('7778')
            }
            $fileMatches += $entry
            $matches += $entry
        }
        $files += [ordered]@{
            log_filename = $item.Name
            log_path = $path
            file_last_write_time_utc = $item.LastWriteTimeUtc.ToString('o')
            file_sha256 = $hash
            extracted_match_count = $fileMatches.Count
            matches = @($fileMatches)
        }
    }
    $evidence = [ordered]@{ files = @($files); matches = @($matches) }
    Write-JsonFile $logEvidencePath $evidence 30
    return $evidence
}

foreach ($path in @($resultPath, $summaryPath, $monitorPath, $logEvidencePath, $logPath, $stdoutPath, $stderrPath)) {
    if ([System.IO.File]::Exists($path)) { [System.IO.File]::Delete([System.IO.Path]::GetFullPath($path)) }
}

$preflightPortOwners = @(Get-PortOwners)
if ($preflightPortOwners.Count -gt 0) {
    $blocked = [ordered]@{
        run_index = $RunIndex
        status = 'BLOCKED_PORT_IN_USE'
        classification = 'HARNESS_INCONCLUSIVE'
        preflight_port_owners = $preflightPortOwners
        acceptance_errors = @('UDP 7777/7778 were already in use before this run')
    }
    Write-JsonFile $summaryPath $blocked 30
    Write-Output "RunIndex=$RunIndex"
    Write-Output 'Status=BLOCKED_PORT_IN_USE'
    exit 2
}

$process = [System.Diagnostics.Process]::new()
$process.StartInfo = [System.Diagnostics.ProcessStartInfo]::new()
$process.StartInfo.FileName = $editorPath
$process.StartInfo.WorkingDirectory = $hostRoot
$process.StartInfo.UseShellExecute = $false
$process.StartInfo.CreateNoWindow = $true
$process.StartInfo.RedirectStandardOutput = $true
$process.StartInfo.RedirectStandardError = $true
$process.StartInfo.ArgumentList.Add($hostProject)
$process.StartInfo.ArgumentList.Add('-unattended')
$process.StartInfo.ArgumentList.Add('-nop4')
$process.StartInfo.ArgumentList.Add('-nosplash')
$process.StartInfo.ArgumentList.Add('-nullrhi')
$process.StartInfo.ArgumentList.Add('-stdout')
$process.StartInfo.ArgumentList.Add('-FullStdOutLogOutput')
$process.StartInfo.ArgumentList.Add("-ExecutePythonScript=$pythonPath")
$process.StartInfo.ArgumentList.Add("-AbsLog=$logPath")
$process.StartInfo.Environment['SMT_MODE'] = $Mode
$process.StartInfo.Environment['SMT_HOLD_SECONDS'] = [string]$HoldSeconds
$process.StartInfo.Environment['SMT_RESULT_JSON'] = $resultPath

$startedAtUtc = [DateTime]::UtcNow
if (-not $process.Start()) { throw "Unable to start UnrealEditor.exe for Run$RunIndex" }
$parentPid = $process.Id
$actualProcessStartUtc = $startedAtUtc
try { $actualProcessStartUtc = (Get-Process -Id $parentPid -ErrorAction Stop).StartTime.ToUniversalTime() } catch { }
$stdoutTask = $process.StandardOutput.ReadToEndAsync()
$stderrTask = $process.StandardError.ReadToEndAsync()
$deadlineUtc = $startedAtUtc.AddSeconds($MaxSeconds)
$parentExitObservedAtUtc = $null
$parentTerminationPerformed = $false
$forcedChildCleanup = $false
$timedOut = $false
$postParentStartUtc = $null
$postParentSnapshots = @()
$preParentSnapshots = @()
$allSnapshots = @()
$childTracking = @{}
$bothChildrenAliveSameSnapshot = $false
$strictReadySnapshot = $null
$strictReadyAtUtc = $null
$playStartedAtUtc = $null
$unexpectedPortObserved = $false

while ([DateTime]::UtcNow -lt $deadlineUtc) {
    $nowUtc = [DateTime]::UtcNow
    $parentWasExited = $process.HasExited
    if ($parentWasExited -and $null -eq $parentExitObservedAtUtc) {
        $parentExitObservedAtUtc = $nowUtc
        $postParentStartUtc = $nowUtc
    }
    $pythonResult = Get-PythonResult
    if ($null -ne $pythonResult -and (Test-RequiredField $pythonResult 'play_started_at_utc')) {
        try { $playStartedAtUtc = [DateTimeOffset]::Parse($pythonResult.play_started_at_utc).UtcDateTime } catch { }
    }
    $isPreParent = $null -eq $parentExitObservedAtUtc
    $snapshot = Get-PollSnapshot $parentPid $nowUtc $actualProcessStartUtc $playStartedAtUtc
    $allSnapshots += $snapshot
    if ($isPreParent) { $preParentSnapshots += $snapshot } else { $postParentSnapshots += $snapshot }
    Update-ChildTracking $childTracking $snapshot
    if (Test-BothChildrenAliveSameSnapshot $snapshot) { $bothChildrenAliveSameSnapshot = $true }
    if ($null -eq $strictReadySnapshot -and (Test-StrictReady $snapshot $parentPid)) {
        $strictReadySnapshot = $snapshot
        $strictReadyAtUtc = [DateTime]::Parse($snapshot.timestamp_utc).ToUniversalTime()
    }
    foreach ($child in @($snapshot.children)) {
        foreach ($endpoint in @($child.actual_udp_endpoints)) {
            if ($null -ne $endpoint -and $endpoint.local_port -ge 7777 -and $endpoint.local_port -ne $child.requested_port) { $unexpectedPortObserved = $true }
        }
    }
    Write-JsonLine $snapshot
    if ($null -ne $parentExitObservedAtUtc) {
        $postDuration = ([DateTime]::UtcNow - $postParentStartUtc).TotalSeconds
        if ($postDuration -ge $PostParentMinimumSeconds -and $postParentSnapshots.Count -ge $PostParentMinimumPolls) { break }
    }
    if ($process.HasExited) { Start-Sleep -Milliseconds $PostParentPollMilliseconds } else { Start-Sleep -Milliseconds $PreParentPollMilliseconds }
}

if (-not $process.HasExited) {
    $timedOut = $true
    $parentCim = $null
    foreach ($candidate in @(Get-CimProcesses)) { if ($candidate.ProcessId -eq $parentPid) { $parentCim = $candidate; break } }
    if ($null -ne $parentCim) { $parentTerminationPerformed = Stop-ExactProcess $parentCim 'parent' }
    if ($null -eq $parentExitObservedAtUtc) { $parentExitObservedAtUtc = [DateTime]::UtcNow; $postParentStartUtc = $parentExitObservedAtUtc }
}

if ($process.HasExited) { try { $process.WaitForExit(10000) } catch { } }
$exitCode = if ($process.HasExited) { $process.ExitCode } else { $null }

if ($null -ne $parentExitObservedAtUtc -and $postParentSnapshots.Count -lt $PostParentMinimumPolls) {
    while (([DateTime]::UtcNow - $postParentStartUtc).TotalSeconds -lt $PostParentMinimumSeconds -or $postParentSnapshots.Count -lt $PostParentMinimumPolls) {
        $nowUtc = [DateTime]::UtcNow
        $pythonResult = Get-PythonResult
        if ($null -ne $pythonResult -and (Test-RequiredField $pythonResult 'play_started_at_utc')) {
            try { $playStartedAtUtc = [DateTimeOffset]::Parse($pythonResult.play_started_at_utc).UtcDateTime } catch { }
        }
        $snapshot = Get-PollSnapshot $parentPid $nowUtc $actualProcessStartUtc $playStartedAtUtc
        $postParentSnapshots += $snapshot
        $allSnapshots += $snapshot
        Update-ChildTracking $childTracking $snapshot
        Write-JsonLine $snapshot
        Start-Sleep -Milliseconds $PostParentPollMilliseconds
    }
}

$postParentChildCounts = @($postParentSnapshots | ForEach-Object { [int]$_.child_count })
$postParentDuration = if ($null -eq $postParentStartUtc) { 0.0 } else { ([DateTime]::UtcNow - $postParentStartUtc).TotalSeconds }
$postParentAllZero = $postParentSnapshots.Count -ge $PostParentMinimumPolls -and $postParentChildCounts.Count -gt 0 -and @($postParentChildCounts | Where-Object { $_ -ne 0 }).Count -eq 0

if (@($postParentChildCounts | Where-Object { $_ -ne 0 }).Count -gt 0) {
    foreach ($child in @(Get-TargetChildInstances (Get-CimProcesses) $parentPid)) {
        if (Stop-ExactProcess $child 'child') { $forcedChildCleanup = $true }
    }
    Start-Sleep -Milliseconds 500
}

$stdoutText = ''
$stderrText = ''
try { $stdoutText = $stdoutTask.GetAwaiter().GetResult() } catch { $stderrText += $_.Exception.Message }
try { $stderrText += $stderrTask.GetAwaiter().GetResult() } catch { $stderrText += $_.Exception.Message }
[System.IO.File]::WriteAllText($stdoutPath, $stdoutText, $Utf8NoBom)
[System.IO.File]::WriteAllText($stderrPath, $stderrText, $Utf8NoBom)

$finalProcesses = Get-CimProcesses
$finalParentCount = 0
foreach ($candidate in $finalProcesses) {
    if ($candidate.Name -eq 'UnrealEditor.exe' -and $candidate.ProcessId -eq $parentPid -and (Test-HostProjectCommandLine $candidate.CommandLine)) { $finalParentCount++ }
}
$finalChildren = Get-TargetChildInstances $finalProcesses $parentPid
$finalTargetProcessCount = $finalParentCount + $finalChildren.Count
$cleanupFailure = (-not $postParentAllZero) -or $forcedChildCleanup -or $finalTargetProcessCount -ne 0

$result = Get-PythonResult
$pythonResultPass = Test-PythonAcceptance $result
$orphanPlayStartedBeforeParentExit = $false
if ($null -ne $result -and $null -ne $parentExitObservedAtUtc -and (Test-RequiredField $result 'play_started_at_utc')) {
    try { $orphanPlayStartedBeforeParentExit = [DateTimeOffset]::Parse($result.play_started_at_utc).UtcDateTime -le $parentExitObservedAtUtc } catch { }
}

$preParentTimestamps = @($preParentSnapshots | ForEach-Object { [DateTime]::Parse($_.timestamp_utc).ToUniversalTime() })
$intervals = @()
for ($index = 1; $index -lt $preParentTimestamps.Count; $index++) { $intervals += ($preParentTimestamps[$index] - $preParentTimestamps[$index - 1]).TotalSeconds }
$medianInterval = Get-Median $intervals
$frequencyPass = $preParentSnapshots.Count -ge 50 -and $null -ne $medianInterval -and $medianInterval -le 0.5

$expected7777First = $null
$expected7778First = $null
foreach ($snapshot in $allSnapshots) {
    foreach ($child in @($snapshot.children)) {
        $actualPorts = @($child.actual_udp_endpoints | ForEach-Object { [int]$_.local_port })
        if ($child.requested_port -eq 7777 -and $actualPorts -contains 7777 -and $null -eq $expected7777First) {
            $expected7777First = [ordered]@{ observed_at_utc = $snapshot.timestamp_utc; elapsed_from_play_start_seconds = $snapshot.elapsed_from_play_start_seconds; process_id = [int]$child.process_id }
        }
        if ($child.requested_port -eq 7778 -and $actualPorts -contains 7778 -and $null -eq $expected7778First) {
            $expected7778First = [ordered]@{ observed_at_utc = $snapshot.timestamp_utc; elapsed_from_play_start_seconds = $snapshot.elapsed_from_play_start_seconds; process_id = [int]$child.process_id }
        }
    }
}
$expected7777Ever = $null -ne $expected7777First
$expected7778Ever = $null -ne $expected7778First
$strictReadyElapsed = if ($null -eq $strictReadySnapshot -or $null -eq $playStartedAtUtc) { $null } else { [Math]::Round(([DateTime]::Parse($strictReadySnapshot.timestamp_utc).ToUniversalTime() - $playStartedAtUtc).TotalSeconds, 3) }
$readyWithin15 = $null -ne $strictReadyElapsed -and $strictReadyElapsed -le 15.0
$readyWithin30 = $null -ne $strictReadyElapsed -and $strictReadyElapsed -le 30.0

$logEvidence = Get-LogEvidence
$log7777 = @($logEvidence.matches | Where-Object { $_.expected_7777_line -and $_.line -match '(?i)listen|bind|Port=' }).Count -gt 0
$log7778 = @($logEvidence.matches | Where-Object { $_.expected_7778_line -and $_.line -match '(?i)listen|bind|Port=' }).Count -gt 0

$classification = $null
if ($unexpectedPortObserved) {
    $classification = 'PORT_REASSIGNED'
} elseif (-not (@($childTracking.Values | Where-Object { $_.requested_ports -contains 7777 }).Count -gt 0) -or -not (@($childTracking.Values | Where-Object { $_.requested_ports -contains 7778 }).Count -gt 0)) {
    $classification = 'EXPECTED_CHILD_MISSING'
} elseif (-not $expected7777Ever -and -not $log7777) {
    $classification = 'PORT_7777_NOT_READY'
} elseif (-not $expected7778Ever -and -not $log7778) {
    $classification = 'PORT_7778_NOT_READY'
} elseif ((-not $expected7777Ever -or -not $expected7778Ever) -and ($log7777 -or $log7778)) {
    $classification = 'MONITOR_GAP_CONFIRMED_BY_LOG'
} elseif ($expected7777Ever -and $expected7778Ever -and ($null -eq $strictReadySnapshot)) {
    $classification = 'PORTS_SEEN_NOT_SAME_SNAPSHOT'
} elseif ($null -ne $strictReadyElapsed -and $strictReadyElapsed -gt 15.0 -and $strictReadyElapsed -le 30.0) {
    $classification = 'DELAYED_READY_15_TO_30_SECONDS'
} elseif ($null -ne $strictReadyElapsed -and $strictReadyElapsed -le 15.0) {
    $classification = 'READY_WITHIN_15_SECONDS'
} elseif (-not $frequencyPass) {
    $classification = 'HARNESS_FREQUENCY_FAIL'
} elseif ($expected7777Ever -and $expected7778Ever) {
    $classification = 'PORTS_SEEN_NOT_SAME_SNAPSHOT'
} elseif (-not $expected7777Ever) {
    $classification = 'PORT_7777_NOT_READY'
} else {
    $classification = 'PORT_7778_NOT_READY'
}

$acceptanceErrors = @()
if (-not $pythonResultPass) { $acceptanceErrors += 'Python result did not satisfy ORPHAN 30-second hold acceptance' }
if ($null -eq $playStartedAtUtc) { $acceptanceErrors += 'Python play start was not observed' }
if ($null -eq $strictReadySnapshot) { $acceptanceErrors += 'No strict ready same-snapshot condition was observed' }
if ($null -ne $strictReadyElapsed -and $strictReadyElapsed -gt 30.0) { $acceptanceErrors += 'Strict ready occurred after 30 seconds from play start' }
if (-not $process.HasExited -or $exitCode -ne 0 -or $parentTerminationPerformed -or $timedOut) { $acceptanceErrors += 'Parent Editor did not naturally exit with code 0 without timeout or forced termination' }
if (-not $frequencyPass) { $acceptanceErrors += 'Pre-parent monitor frequency did not satisfy 50 polls and median interval <= 0.5 seconds' }
if ($cleanupFailure) { $acceptanceErrors += 'Post-parent cleanup failure: child remained during monitoring or forced child cleanup was required' }
if (-not $orphanPlayStartedBeforeParentExit) { $acceptanceErrors += 'ORPHAN play start was not observed before parent Editor exit' }

$status = if ($pythonResultPass -and $null -ne $playStartedAtUtc -and $null -eq $result.end_requested_at_utc -and $null -eq $result.play_ended_at_utc -and $null -ne $strictReadyElapsed -and $strictReadyElapsed -le 30.0 -and $process.HasExited -and $exitCode -eq 0 -and -not $parentTerminationPerformed -and -not $timedOut -and $frequencyPass -and -not $cleanupFailure -and -not $forcedChildCleanup) { 'PASS' } else { 'FAIL' }

$tracking = @($childTracking.Values | Sort-Object process_id)
$summary = [ordered]@{
    run_index = $RunIndex
    status = $status
    classification = $classification
    verification_root = $verifyRoot
    run_root = $runRoot
    host_project = $hostProject
    mode = $Mode
    hold_seconds = $HoldSeconds
    max_seconds = $MaxSeconds
    parent_pid = $parentPid
    parent_exit_code = $exitCode
    parent_exit_observed_at_utc = if ($null -eq $parentExitObservedAtUtc) { $null } else { $parentExitObservedAtUtc.ToString('o') }
    python_result_pass = $pythonResultPass
    play_started_at_utc = if ($null -eq $playStartedAtUtc) { $null } else { $playStartedAtUtc.ToString('o') }
    end_requested_at_utc = if ($null -eq $result) { $null } else { $result.end_requested_at_utc }
    play_ended_at_utc = if ($null -eq $result) { $null } else { $result.play_ended_at_utc }
    pre_parent_poll_count = $preParentSnapshots.Count
    pre_parent_poll_intervals_seconds = @($intervals | ForEach-Object { [Math]::Round($_, 6) })
    pre_parent_poll_median_interval_seconds = $medianInterval
    monitor_frequency_pass = $frequencyPass
    both_children_alive_same_snapshot = $bothChildrenAliveSameSnapshot
    expected_7777_ever = $expected7777Ever
    expected_7778_ever = $expected7778Ever
    expected_7777_first_observed = $expected7777First
    expected_7778_first_observed = $expected7778First
    strict_ready_same_snapshot = $null -ne $strictReadySnapshot
    strict_ready_at_utc = if ($null -eq $strictReadyAtUtc) { $null } else { $strictReadyAtUtc.ToString('o') }
    strict_ready_elapsed_from_play_start_seconds = $strictReadyElapsed
    ready_within_15_seconds = $readyWithin15
    ready_within_30_seconds = $readyWithin30
    unexpected_port_observed = $unexpectedPortObserved
    child_tracking = $tracking
    log_listen_evidence = @($logEvidence.matches)
    log_evidence_path = $logEvidencePath
    post_parent_start_utc = if ($null -eq $postParentStartUtc) { $null } else { $postParentStartUtc.ToString('o') }
    post_parent_duration_seconds = [Math]::Round($postParentDuration, 3)
    post_parent_poll_count = $postParentSnapshots.Count
    post_parent_child_counts = @($postParentChildCounts)
    post_parent_all_zero = $postParentAllZero
    forced_parent_cleanup = $parentTerminationPerformed
    forced_child_cleanup = $forcedChildCleanup
    cleanup_failure = $cleanupFailure
    final_parent_process_count = $finalParentCount
    final_child_process_count = $finalChildren.Count
    final_target_process_count = $finalTargetProcessCount
    timed_out = $timedOut
    acceptance_errors = @($acceptanceErrors)
    lifecycle_result_path = $resultPath
    lifecycle_result = $result
    monitor_path = $monitorPath
    log_path = $logPath
    stdout_path = $stdoutPath
    stderr_path = $stderrPath
    observation_count = $allSnapshots.Count
}
Write-JsonFile $summaryPath $summary 40
Write-Output "RunIndex=$RunIndex"
Write-Output "Status=$status"
Write-Output "Classification=$classification"
Write-Output "ParentPID=$parentPid"
Write-Output "ParentExitCode=$exitCode"
Write-Output "StrictReady=$($null -ne $strictReadySnapshot)"
Write-Output "StrictReadyElapsed=$strictReadyElapsed"
Write-Output "PreParentPollCount=$($preParentSnapshots.Count)"
Write-Output "PreParentMedianInterval=$medianInterval"
Write-Output "PostParentDuration=$([Math]::Round($postParentDuration, 3))"
Write-Output "PostParentPollCount=$($postParentSnapshots.Count)"
Write-Output "FinalTargetProcessCount=$finalTargetProcessCount"
Write-Output "SummaryPath=$summaryPath"
if ($status -ne 'PASS') { exit 1 }
exit 0
```
