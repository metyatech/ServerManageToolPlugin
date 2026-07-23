# Post-category Verification: UE 5.8 / Win64

Verification date: 2026-07-23 (Asia/Tokyo)

This report records the Blueprint-only clean-exit and Server lifecycle verification requested for the existing `fix/ue58-uht-categories` branch. Source code was not changed. The only repository file changed by this phase is this report. All host projects, scripts, logs, JSON, monitor evidence, and package copies were kept outside the repository.

## 1. Verification execution status — PASS

All requested verification runners reached terminal results:

- the existing short-root BuildPlugin package was reused after exact SHA-256 verification;
- Blueprint-only plugin compatibility passed;
- Blueprint-only clean exit passed without force termination;
- Normal PIE, Simulate, and ORPHAN each reached a clean terminal result;
- each lifecycle run observed both requested `UnrealEditor.exe -server` children, actual UDP ports 7777 and 7778, parent exit code 0, no forced cleanup, and final child count 0.

The execution status is PASS because the requested verification was completed. Product/Fab readiness remains FAIL because the package is still missing required Fab structure and real-game-project integration and packaged-executable execution were not tested.

## 2. Product readiness status — FAIL

The five UE 5.8 UHT Category declarations are fixed, BuildPlugin reports success for all three requested targets, and the package loads and runs the requested host lifecycle. Fab release readiness is not established because `Config`, `Content`, and user-facing `Docs` are absent from the final package. Real game-project Development/Shipping integration and packaged executable execution remain untested. The known requested-port conflict behavior and static delegate-unregister concern also remain blockers.

## 3. Git baseline and scope — PASS

- repository: `D:\ghws\ServerManageToolPlugin`
- origin: `https://github.com/metyatech/ServerManageToolPlugin`
- branch: `fix/ue58-uht-categories`
- start HEAD: `c58810a98d58299777f089bcc59f794e1c6ed5ac`
- start `origin/fix/ue58-uht-categories`: `c58810a98d58299777f089bcc59f794e1c6ed5ac`
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

## 13. Normal PIE lifecycle — PASS

The lifecycle Python result was PASS and the parent exited normally.

- parent PID: `37972`
- parent exit code: `0`
- child PID `65612`: requested port `7777`, actual listen port `7777`, parent PID `37972`
- child PID `57904`: requested port `7778`, actual listen port `7778`, parent PID `37972`
- child cleanup: no forced cleanup
- final target child count: `0`
- monitor polls: `34`

The Python state transitions reached play start, held play for 15 seconds, ended play, waited 10 seconds, and requested editor quit.

## 14. Simulate lifecycle — PASS

The lifecycle Python result was PASS and the parent exited normally.

- parent PID: `21916`
- parent exit code: `0`
- child PID `17188`: requested port `7777`, actual listen port `7777`, parent PID `21916`
- child PID `59692`: requested port `7778`, actual listen port `7778`, parent PID `21916`
- child cleanup: no forced cleanup
- final target child count: `0`
- monitor polls: `34`

The start operation used `editor_play_simulate()`; end, wait, and quit completed normally.

## 15. Editor shutdown ORPHAN lifecycle — PASS

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

- start HEAD: `c58810a98d58299777f089bcc59f794e1c6ed5ac`
- end HEAD: supplied with the report commit in the delivery result
- package root: `D:\T\S58-20260723-131534\P`
- verification root: `D:\T\S58L-20260723-135846`
- BuildPlugin 3target result: PASS / PASS / PASS
- Blueprint load compatibility: PASS
- Blueprint clean exit: PASS; PID 65416; exit 0; marker PASS; timeout false
- PIE: PASS; parent 37972; children 65612/57904; requested/actual 7777/7778; cleanup complete
- Simulate: PASS; parent 21916; children 17188/59692; requested/actual 7777/7778; cleanup complete
- ORPHAN: PASS; parent 32604; children 30428/59952; requested/actual 7777/7778; orphan count 0; cleanup complete
- final target process count: 0
- changed file: `Docs/Verification/FabPostCategory-UE5.8-Win64.md`
- Product readiness status: FAIL
