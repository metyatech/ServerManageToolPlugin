# Fab post-port-conflict verification — UE 5.8 Win64

## 1. Scope and verdict

This report is the authoritative rerun for the port-conflict diagnostic-marker
completion and the required markerless direct-server regression on
`fix/port-conflict-fail-fast`. It uses a fresh packaged plugin and a fresh
Blueprint-only UE 5.8 host under `D:\T\SMTPFC-20260723-201902`.

Final verdict:

- Editor UDP preflight — `PASS`
- Atomic all-or-nothing launch — `PASS`
- Runtime mismatch detection — `PASS`
- Runtime clean termination — `PASS`
- Requested exit status propagation — mismatch `EDITOR_STATUS_0_REPRODUCED`; invalid `EDITOR_STATUS_OTHER` with exit `3`
- Port conflict implementation — `PARTIAL_PACKAGED_TEST_BLOCKED`
- Product readiness status — `FAIL`

The implementation detects the mismatch, emits the complete marker, requests a
clean exit with status `2`, preserves the holder, leaves no shifted-port
residue, and passes matching and markerless controls. Five independent Editor
mismatch runs reproduced exit code `0`; three independent invalid-marker runs
reproduced exit code `3`. A temporary dedicated-server comparison was blocked
by the installed engine distribution, so no platform-level conclusion is made.

Product-readiness blockers remain: Fab Config is incomplete, Fab Content is
incomplete, user documentation is incomplete, real game-project Development
and Shipping integration is unverified, the packaged executable is unverified,
and Editor BeginPIE/EndPIE delegate unregister is insufficient. Port-conflict
behavior is not a blocker.

## 2. Start Git state

The requested start gate was checked before any change.

| Item | Observed value |
| --- | --- |
| Repository | `D:\ghws\ServerManageToolPlugin` |
| Origin | `https://github.com/metyatech/ServerManageToolPlugin` (`metyatech/ServerManageToolPlugin`) |
| Branch | `fix/port-conflict-fail-fast` |
| Starting local HEAD | `045cd1c5435e1f55c84457babed083fdd861253e` |
| Starting remote HEAD | `045cd1c5435e1f55c84457babed083fdd861253e` |
| Divergence | `0 0` |
| Starting working tree | clean |
| PowerShell | `7.6.1` |
| UE root | `C:\Program Files\Epic Games\UE_5.8` |
| Build.version | MajorVersion `5`, MinorVersion `8` |
| InstalledBuild.txt | present at `C:\Program Files\Epic Games\UE_5.8\Engine\Build\InstalledBuild.txt` |

No amend, rebase, squash, merge, force push, pull request, tag, release, or
Fab submission was performed.

## 3. Exact source changes

The source-only commit is:

```text
3e287df2bea2b74ff991c7ff5c48cec3c209b890
fix: complete port conflict diagnostics
```

Commit URL:
`https://github.com/metyatech/ServerManageToolPlugin/commit/3e287df2bea2b74ff991c7ff5c48cec3c209b890`

The commit contains exactly these two files and no report:

- `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp`
- `Source/ServerManageLibrary/Private/ServerManageLibrary.cpp`

The delta from the required starting HEAD is four insertions and four
deletions. It only:

- completes the invalid expected-port marker;
- completes the port-mismatch marker; and
- adds `map`, `requested_port`, and `final_managed_server_count=0` to the
  existing module-level rollback marker.

No preflight, process-launch, ticker, dedicated-server decision, port scheme,
map/port mapping, delegate, Blueprint API, Build.cs, uplugin, Config, Content,
README, CI, package script, termination method, or markerless early-return
logic was changed in this commit. `git diff --check` passed before commit.

## 4. Design rationale

The existing Local Launch design remains compositional:

1. Editor-side UDP preflight probes every configured server port before any
   child process is created.
2. A failure stops the launch before `CreateProc`; therefore a conflict in
   either configured port cannot leave a partially launched pair.
3. A successful preflight creates children in configured map order and rolls
   back all already-created children if a later `ServerProcess` is invalid.
4. Each dedicated child receives its requested port and an optional
   `ServerManageExpectedPort` value.
5. The dedicated-server validator compares the actual `GameNetDriver` port to
   the requested port and requests a clean exit on mismatch.

The validator does not follow a shifted port, rewrite the expected port, call a
fatal path, abort, force exit, terminate a process, or start another process to
obtain exit code `2`.

## 5. Editor UDP preflight

At BeginPIE, Local Launch probes each configured port using UE's socket
subsystem, a unique UDP socket, an any-address endpoint, disabled reuse, and
bind. The probe socket is released before child launch. The existing markers
were not changed:

```text
SMT_PORT_PREFLIGHT_PASSED
SMT_PORT_PREFLIGHT_FAILED
```

The fresh host configuration contained two `/Engine/Maps/Entry` entries. Each
normal lifecycle run emitted exactly one `SMT_PORT_PREFLIGHT_PASSED`; neither
conflict run emitted a pass marker. Each conflict run emitted exactly one
`SMT_PORT_PREFLIGHT_FAILED` naming the unavailable port.

## 6. Atomic all-or-nothing launch

The two independent conflict runs demonstrate the atomic property:

- holding `0.0.0.0:7777` stopped both requested children before launch;
- holding `0.0.0.0:7778` stopped both requested children before launch;
- neither run emitted a shifted child, validation marker, or module-level
  launch-failure marker; and
- the holder stayed alive until evidence collection and was then disposed by
  the harness.

The three normal runs each launched exactly two children, one on `7777` and one
on `7778`, and each child validated the port it was assigned.

## 7. ServerProcess launch-result handling

The existing `ServerProcess::IsValid()` result is consumed at module level. If
it is false, already-created managed servers are cleared and the function
returns without creating later entries. The requested static rollback marker is
now:

```text
SMT_SERVER_PROCESS_LAUNCH_FAILED map=<map> requested_port=<port> rollback_count=<count> final_managed_server_count=0
```

The source uses `ServerMap.MapName`. A `CreateProc` failure was not forced for
this verification because both conflict cases stop in preflight. Runtime
rollback trigger:

```text
NOT_TRIGGERED_IN_THIS_VERIFICATION
```

## 8. Server-side actual-port validation

The validator runs only for a dedicated server with
`ServerManageExpectedPort=` present. It waits for a world with a known
`GameNetDriver` local port, then emits one pass or failure marker and removes
its ticker. A matching child emitted, for example:

```text
SMT_PORT_VALIDATION_PASSED expected_port=7777 actual_port=7777 world=Entry pid=41832
```

The direct mismatch run reproduced UE's shift from requested `17777` to actual
`17778`. The complete failure marker and clean-exit request are documented in
section 18. The markerless direct-server control omitted the expected-port
argument and emitted no validator marker.

## 9. Diagnostic marker contract

The mismatch marker is one parseable line and contains all required fields:

```text
SMT_PORT_VALIDATION_FAILED expected_port=<expected> actual_port=<actual> world=<world> pid=<pid> action=request_clean_exit requested_status=2 reason=port_mismatch
```

The invalid expected-port marker is one parseable line and preserves unknown
actual/world values:

```text
SMT_PORT_VALIDATION_FAILED expected_port=<expected> actual_port=unknown world=unknown pid=<pid> action=request_clean_exit requested_status=2 reason=invalid_expected_port
```

The mismatch path immediately retains:

```cpp
FPlatformMisc::RequestExitWithStatus(
    false,
    2,
    TEXT("ServerManageExpectedPort does not match bound port"));
```

Static source checks passed for the invalid marker, mismatch marker, rollback
marker, and the unchanged `SMT_PORT_PREFLIGHT_PASSED`,
`SMT_PORT_PREFLIGHT_FAILED`, and `SMT_PORT_VALIDATION_PASSED` contracts.

## 10. BuildPlugin results

The requested reproducible command was:

```powershell
$stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$verifyRoot = "D:\T\SMTPFC-$stamp"
$packageRoot = Join-Path $verifyRoot "P"
$buildLog = Join-Path $verifyRoot "BuildPlugin.log"

& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  "-Plugin=D:\ghws\ServerManageToolPlugin\ServerManageTool.uplugin" `
  "-Package=$packageRoot" `
  -TargetPlatforms=Win64 `
  -Rocket *> $buildLog

$buildExitCode = $LASTEXITCODE
```

The authoritative execution used `D:\T\SMTPFC-20260723-201902` and recorded
the same UAT arguments in `BuildPlugin.log`.

| Gate | Result |
| --- | --- |
| BuildPlugin exit code | `0` |
| UnrealEditor Win64 Development | `Result: Succeeded` |
| UnrealGame Win64 Development | `Result: Succeeded` |
| UnrealGame Win64 Shipping | `Result: Succeeded` |
| UHT Category errors | `0` |
| path-length errors over 260 | `0` |
| `BUILD SUCCESSFUL` | present |

## 11. Package results

| Item | Result |
| --- | --- |
| Package root | `D:\T\SMTPFC-20260723-201902\P` |
| File count | `66` |
| Total size | `226120015` bytes |
| Final uplugin | `P\ServerManageTool.uplugin`, present |
| Win64 binaries | `P\Binaries\Win64`, present |
| modules file | `P\Binaries\Win64\UnrealEditor.modules`, present |
| uplugin SHA-256 | `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146` |
| `.modules` SHA-256 | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |

## 12. Blueprint-only clean load

The fresh host was:

```text
D:\T\SMTPFC-20260723-201902\H\ServerManageToolPortConflictCompletionHost.uproject
```

It contained no C++ `Modules` property and enabled exactly these plugins:

- `ServerManageTool`
- `PythonScriptPlugin`
- `EditorScriptingUtilities`

`DefaultEngine.ini` contained the two `/Engine/Maps/Entry` server entries at
`127.0.0.1:19001` and `127.0.0.1:19002`. The user settings selected
`SERVER_LocalLaunch`.

The existing Python keep-alive clean-load harness passed:

| Check | Result |
| --- | --- |
| plugin module load | `3` enabled and loaded |
| missing module | `0` |
| incompatible module | `0` |
| compile request | `0` |
| C++ conversion request | `0` |
| fatal/ensure/crash failure | `0` (normal CrashReportClient startup lines excluded) |
| Blueprint marker | `PASS` |
| parent PID / exit code | `45548 / 0` |
| timeout | `false` |
| forced termination | `false` |
| final host process count | `0` |

## 13. Normal PIE regression

PIE was run once with the fresh package and host.

| Item | Result |
| --- | --- |
| status | `PASS` |
| parent PID / exit | `52952 / 0`, natural exit |
| child PID / ParentProcessId | `41832 / 52952`, `75768 / 52952` |
| requested / actual ports | `7777 / 7777`, `7778 / 7778` |
| `SMT_PORT_PREFLIGHT_PASSED` / failed | `1 / 0` |
| child validation pass / fail | `2 / 0` |
| launch-failure markers | `0` |
| readiness elapsed | `5.000` seconds, within 30 seconds |
| forced cleanup | `false` |
| parent/child after natural completion | `0 / 0` |
| final UDP 7777/7778 owners | `0 / 0` |

The child command lines contained `-Port=7777 -ServerManageExpectedPort=7777`
and `-Port=7778 -ServerManageExpectedPort=7778`, respectively.

## 14. Simulate regression

Simulate was run once with the same fresh package and host.

| Item | Result |
| --- | --- |
| status | `PASS` |
| parent PID / exit | `71324 / 0`, natural exit |
| child PID / ParentProcessId | `68016 / 71324`, `992 / 71324` |
| requested / actual ports | `7777 / 7777`, `7778 / 7778` |
| `SMT_PORT_PREFLIGHT_PASSED` / failed | `1 / 0` |
| child validation pass / fail | `2 / 0` |
| launch-failure markers | `0` |
| readiness elapsed | `5.000` seconds, within 30 seconds |
| forced cleanup | `false` |
| parent/child after natural completion | `0 / 0` |
| final UDP 7777/7778 owners | `0 / 0` |

## 15. ORPHAN regression

ORPHAN was run once with the same fresh package and host.

| Item | Result |
| --- | --- |
| status | `PASS` |
| parent PID / exit | `78800 / 0`, natural exit |
| child PID / ParentProcessId | `74264 / 78800`, `70064 / 78800` |
| requested / actual ports | `7777 / 7777`, `7778 / 7778` |
| `SMT_PORT_PREFLIGHT_PASSED` / failed | `1 / 0` |
| child validation pass / fail | `2 / 0` |
| launch-failure markers | `0` |
| readiness elapsed | `5.000` seconds, within 30 seconds |
| forced cleanup | `false` |
| parent/child after natural completion | `0 / 0` |
| final UDP 7777/7778 owners | `0 / 0` |

## 16. Preflight conflict 7777

An independent .NET `UdpClient` held `0.0.0.0:7777` with exclusive address use
before PIE began. Holder evidence:

| Item | Result |
| --- | --- |
| holder PID | `77876` |
| holder command line | `"C:\Program Files\PowerShell\7\pwsh.exe" -NoProfile -File D:\T\SMTPFC-20260723-201902\RunConflict.ps1 -Port 7777 -RunRoot D:\T\SMTPFC-20260723-201902` |
| holder start time | `2026-07-23T11:30:09.5228664Z` |
| endpoint | `0.0.0.0:7777` |
| first seen | `2026-07-23T11:30:11.0785053Z` |
| last seen | `2026-07-23T11:30:59.3333334Z` |
| parent PID / exit | `78780 / 0`, natural exit |
| `SMT_PORT_PREFLIGHT_FAILED` | `1` for unavailable `7777` |
| `SMT_PORT_PREFLIGHT_PASSED` | `0` |
| managed child count | `0` |
| shifted server count | `0` |
| validation pass/fail | `0 / 0` |
| holder alive before cleanup | `true` |
| timeout / forced cleanup | `false / false` |
| holder cleanup final process/UDP | `0 / 0` |

## 17. Preflight conflict 7778

This was an independent run with `7777` free and an independent holder on
`0.0.0.0:7778`.

| Item | Result |
| --- | --- |
| holder PID | `77896` |
| holder command line | `"C:\Program Files\PowerShell\7\pwsh.exe" -NoProfile -File D:\T\SMTPFC-20260723-201902\RunConflict.ps1 -Port 7778 -RunRoot D:\T\SMTPFC-20260723-201902` |
| holder start time | `2026-07-23T11:31:09.1078484Z` |
| endpoint | `0.0.0.0:7778` |
| first seen | `2026-07-23T11:31:10.988356Z` |
| last seen | `2026-07-23T11:32:01.6762559Z` |
| parent PID / exit | `74308 / 0`, natural exit |
| `SMT_PORT_PREFLIGHT_FAILED` | `1` for unavailable `7778` |
| `SMT_PORT_PREFLIGHT_PASSED` | `0` |
| managed child count including 7777 | `0` |
| shifted server count | `0` |
| validation pass/fail | `0 / 0` |
| holder alive before cleanup | `true` |
| timeout / forced cleanup | `false / false` |
| holder cleanup final process/UDP | `0 / 0` |

## 18. Direct mismatch race guard

The direct command was run with an independent holder on `17777`:

```text
C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe
D:\T\SMTPFC-20260723-201902\H\ServerManageToolPortConflictCompletionHost.uproject
/Engine/Maps/Entry
-Port=17777
-ServerManageExpectedPort=17777
-server
-unattended
-nullrhi
-nosplash
-log
-AbsLog=D:\T\SMTPFC-20260723-201902\Mismatch-17777.log
```

| Item | Result |
| --- | --- |
| holder PID / endpoint | `71900 / 0.0.0.0:17777` |
| holder start / first seen / last seen | `2026-07-23T11:34:21.9509626Z` / `2026-07-23T11:34:23.0809705Z` / `2026-07-23T11:34:35.5135439Z` |
| mismatch server PID | `75308` |
| requested / actual port | `17777 / 17778` |
| complete marker count | `1` |
| pass marker count | `0` |
| complete marker | `SMT_PORT_VALIDATION_FAILED expected_port=17777 actual_port=17778 world=Entry pid=75308 action=request_clean_exit requested_status=2 reason=port_mismatch` |
| requested clean-exit status | `2` |
| observed process exit code | `0` |
| classification | `EDITOR_STATUS_0_REPRODUCED` for the initial single-run observation |
| timeout / forced termination | `false / false` |
| natural terminal result | `true` |
| holder unaffected | `true` before planned holder cleanup |
| shifted-port residue | `0` |
| final target process/UDP after holder cleanup | `0 / 0` |

The requested code path is preserved exactly as
`FPlatformMisc::RequestExitWithStatus(false, 2, ...)`. This initial single-run
observation was superseded by the five-run repeatability section below; it is
retained here as historical evidence and is not called a platform limitation.

## 19. Direct matching control

After the mismatch holder was released, the same direct server command was run
with `17777` free.

| Item | Result |
| --- | --- |
| server PID | `61912` |
| requested / actual port | `17777 / 17777` |
| `SMT_PORT_VALIDATION_PASSED` / failed | `1 / 0` |
| alive after validation for at least 5 seconds | `true` |
| harness explicit cleanup | `true` |
| forced cleanup | `false` |
| final target process/UDP | `0 / 0` |

The harness reports process exit code `-1` because the process was explicitly
cleaned up after the five-second control window; this is not a plugin exit
failure.

## 20. Markerless direct-server control

The required new control omitted `ServerManageExpectedPort` completely:

```text
C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe
D:\T\SMTPFC-20260723-201902\H\ServerManageToolPortConflictCompletionHost.uproject
/Engine/Maps/Entry
-Port=17777
-server
-unattended
-nullrhi
-nosplash
-log
-AbsLog=D:\T\SMTPFC-20260723-201902\Markerless-17777.log
```

| Item | Result |
| --- | --- |
| server PID | `41112` |
| requested / actual port | `17777 / 17777` |
| validation pass/fail marker count | `0 / 0` |
| expected-port argument in command line | absent |
| normal Editor alive at 10 seconds | `true` |
| server alive for at least 10 seconds | `true` |
| client-process validator | not applicable; no client process was launched |
| plugin exit request | none observed |
| harness explicit cleanup | `true` |
| forced cleanup | `false` |
| final target process/UDP | `0 / 0` |

The markerless log contains no port-validation pass/fail category marker. The
harness reports process exit code `-1` because it explicitly cleaned up after
the ten-second control window.

## 21. Process cleanup and safety

Cleanup was identity-gated. A process was eligible only when all applicable
conditions matched:

- PID was recorded by the current harness;
- executable name was the expected Unreal executable;
- command line contained the absolute host `.uproject` path; and
- a server cleanup target contained the independent `-server` argument.

The conflict holders were never selected for plugin cleanup and remained alive
until their planned disposal point. The final scan found:

| Check | Result |
| --- | --- |
| target Unreal host parent processes | `0` |
| target managed server processes | `0` |
| target direct server processes | `0` |
| holder processes after planned cleanup | `0` |
| UDP owners on 7777, 7778, 17777, 17778 | `0` |
| unrelated Unreal processes terminated | `0` |

The final scan's own PowerShell process contained the host path in its command
line while performing the scan; it was not an Unreal target and was excluded
from the target-process count.

## 22. Evidence SHA-256 and reproduction commands

All evidence below is outside the repository under
`D:\T\SMTPFC-20260723-201902`. No temporary script, log, JSON, host, or
package was added to Git.

### Evidence hashes

| Evidence file | SHA-256 |
| --- | --- |
| `BuildPlugin.log` | `4E58586A5E9EB05B290DCA43DB7EF46C3BF4166742B86302EACE3AC0DC5EA1EF` |
| `P\ServerManageTool.uplugin` | `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146` |
| `P\Binaries\Win64\UnrealEditor.modules` | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |
| `BlueprintOnlyCleanExit.py` | `02548035C1195D0E439450FFAB13F872F2C1E2917EF11BB06D2DA9027FC997C9` |
| `RunBlueprintOnlyCleanExit.ps1` | `BB4DAEF1D7182ECEA9423D79761C9ABC33C125549CFF37A567A5114D96B08CA7` |
| `BlueprintOnlyCleanExit.json` | `EF410F97F0644BC762E9A564C75CBEC5BE725A650DE240D3E760CD8988634AC3` |
| `BlueprintOnlyCleanExit.summary.json` | `96567792841BF7A3FB0F4C448E99F35B47A0ACA13CA34C5A576E4A540504209A` |
| `BlueprintOnlyCleanExit.log` | `6C6B6094650D221333D4F08EF66C35C361070B5BE212903EE2F4223C12256C49` |
| `Lifecycle.py` | `41E20A4BA3E663D054BEBDD937EAF2272130D981EE6B1CEE3B685925B99EA8F3` |
| `RunLifecycle.ps1` | `1A2FB57BA827CB481371638A2A411979FD994B38878962C86C5688E3A3EDDB40` |
| `PIE.result.json` | `01098D52DBF0A7A81A96BE51ADA83BF61B27D5904231FADDDD8AD533BFF61EC0` |
| `PIE.summary.json` | `181E083F0F7CA1DEAA0541CEEAA7783BE730A8C49F4650DF407FB006A9C77DA1` |
| `PIE.log` | `FE91B968A2E304EB642AA226894E03E68A52963C9CC77CD5300B85D5C9349D7D` |
| `PIE.monitor.jsonl` | `E8338D7348FF8944074B7E22E91B2A152177847C30ED216342CF96102616EDB7` |
| `SIMULATE.result.json` | `EFE6C0C358B58C84F6B515B169B4759B6408766DA1C4BBE03F155B55AA8166ED` |
| `SIMULATE.summary.json` | `4E7AB9501422334DD327A5E9E55535B061F59F592A592163B1DF146669939B36` |
| `SIMULATE.log` | `A31C8BAFE180FF2FEAA0568C41458F509228300B842103153B4F50EED096204D` |
| `SIMULATE.monitor.jsonl` | `C71BDEE4DBF8C844660045CB5A38F96C2A67B22772831AE1BA16599F9B63E629` |
| `ORPHAN.result.json` | `2B53DB1A362DADC946F759C030DBBF3252C044DFDBA5EACB7CEE60E84B41E477` |
| `ORPHAN.summary.json` | `79E34D42859ED2246DE249DFCFE7560D546221D3434E03503ACEB1F57227DF56` |
| `ORPHAN.log` | `7986FF0C8585B958A6FBB66A63B9483B32ADA7D5E996736599752021CE0FCFEB` |
| `ORPHAN.monitor.jsonl` | `5387AEE2D9CBEA3648FCF6A45E1F9BF320AD22D6F924E322FA9E9B4B901E129A` |
| `RunConflict.ps1` | `92AC5615491D0B8FC349DC0BDB6C961D8F99FAE0DE04E5CA9B33871DDF6CCFE7` |
| `Conflict-7777.summary.json` | `C9C4E5B5D331AA95F943AA0EB3A172245B864B242106593ADF0E0669C03872EE` |
| `Conflict-7777.holder.json` | `DE25F647A7A57634D5CFCC3B603CE25BCBBE2853ED50CC8B15763CB2475D1984` |
| `Conflict-7777.log` | `58D592ACC36AF3189E65E00995E168F3F5B886C9BDF40F0FCB950926CB60F6E4` |
| `Conflict-7778.summary.json` | `676BF36C307E559B94A51574E5406EAAF24FDD9ECCE1EC57C75F57A5190B1B2A` |
| `Conflict-7778.holder.json` | `AC5DF382FD9529173B0B8698BBC7AB7B06A58626E75DA7514A2DD9E5BBDD66F0` |
| `Conflict-7778.log` | `5DCA91194C6C2C3237763ED88B55B79902416AA4FA87A0C948FBF843A9E00EAA` |
| `RunDirectTests.ps1` | `915AC4E94EBF7CB2A93B9BE9B1A2D616F671F5BFE9006BABEEBCE96C9B6AA944` |
| `Mismatch-17777.summary.json` | `D9D9AB28BB40D966F7A9149DE910194F706B1B4614120355DE7EFCD27FC3955D` |
| `Mismatch-17777.holder.json` | `D3A75D113FDDB2D3CA3146E01E66F20F18F035E07573DA32F43B3BD25778FBAB` |
| `Mismatch-17777.log` | `866ED492C5443D14FFECFD1C690014287108E6AD8C6AA3019C6F55298B3940E4` |
| `Control-17777.summary.json` | `FE5C1B30B3A106901116BD22F4877CDA9371853AB2460C058B7DAAD19A217CC7` |
| `Control-17777.log` | `B2DB71267F6A7C0D41F085063F23AFC3CAAC6E34B5DD2B1C053447FCF5BFFD4E` |
| `Markerless-17777.summary.json` | `DA54F475FB756708D66F382F0A76ADA2FC5F7B43158A089F6D32816BA1B39981` |
| `Markerless-17777.log` | `1CCB9E333AA3A8E38F3CEF8426B957234DEE0E9A71E41F665B97664C94B9FC0C` |
| `H\ServerManageToolPortConflictCompletionHost.uproject` | `B29745F88005E1582DB123CDB37A388E56401AEFB83C712CFFB7F88FAC51E782` |
| `H\Config\DefaultEngine.ini` | `8BFC6DA387B750434FBFCCF3300AF294041B4F7A40BBE4925701A132596E1D39` |
| `H\Config\DefaultEditorPerProjectUserSettings.ini` | `E2C72B8DF57840731443AA3AC34F7DDDF8E0311CD394D648840CC18E03F8753C` |
| `FinalSummary.json` | `52EFA931A8BB7080D822779DD24944D53B7EDD905A2F9339E5779EAA21468784` |

The previous report's correct design evidence is retained in sections 4–9. The
previous package root and older conflict evidence remain historical only; the
fresh root and hashes above are authoritative for this report.

### Complete reproduction commands

BuildPlugin:

```powershell
& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  "-Plugin=D:\ghws\ServerManageToolPlugin\ServerManageTool.uplugin" `
  "-Package=D:\T\SMTPFC-20260723-201902\P" `
  -TargetPlatforms=Win64 `
  -Rocket *> D:\T\SMTPFC-20260723-201902\BuildPlugin.log
```

Blueprint clean load:

```powershell
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunBlueprintOnlyCleanExit.ps1
```

Normal lifecycle:

```powershell
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunLifecycle.ps1 -Mode PIE
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunLifecycle.ps1 -Mode SIMULATE
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunLifecycle.ps1 -Mode ORPHAN
```

Each lifecycle script starts the host with `Lifecycle.py`, holds the configured
play state, records parent/child snapshots, and waits for natural completion.

Preflight conflicts, including independent holder start and planned disposal:

```powershell
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunConflict.ps1 -Port 7777 -RunRoot D:\T\SMTPFC-20260723-201902
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunConflict.ps1 -Port 7778 -RunRoot D:\T\SMTPFC-20260723-201902
```

`RunConflict.ps1` creates an independent .NET `UdpClient`, binds
`0.0.0.0:<Port>`, writes PID/command-line/start/endpoint/first-seen/last-seen
metadata, starts PIE only after ownership verification, records the holder as
alive, then disposes that holder in its `finally` cleanup after evidence is
written. The two commands are separate runs; `7777` is checked free before the
7778 run.

Direct mismatch, matching, and markerless controls:

```powershell
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunDirectTests.ps1 -Mode Mismatch -RunRoot D:\T\SMTPFC-20260723-201902
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunDirectTests.ps1 -Mode Control -RunRoot D:\T\SMTPFC-20260723-201902
pwsh -NoProfile -File D:\T\SMTPFC-20260723-201902\RunDirectTests.ps1 -Mode Markerless -RunRoot D:\T\SMTPFC-20260723-201902
```

For `Mismatch`, the harness starts the independent holder before the exact
direct command, records the shifted port and complete marker, does not force
terminate the server, verifies holder survival, then disposes the holder. For
`Control`, it requires the matching pass marker and five seconds of survival
before explicit identity-gated cleanup. For `Markerless`, it omits
`ServerManageExpectedPort`, requires ten seconds of server survival and zero
validation markers, then performs the same explicit cleanup.

Static marker checks:

```powershell
rg -n "SMT_PORT_VALIDATION_FAILED|actual_port=unknown|world=unknown|action=request_clean_exit|requested_status=2|reason=invalid_expected_port" Source/ServerManageLibrary/Private/ServerManageLibrary.cpp
rg -n "SMT_SERVER_PROCESS_LAUNCH_FAILED|map=%s|requested_port=%d|rollback_count=%d|final_managed_server_count=0" Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp
git diff --check
```

## 23. Final Git state and remaining blockers

The report-only commit is created with:

```text
docs: clarify port mismatch exit status
```

Its exact SHA and commit URL are recorded by the final `git rev-parse HEAD`
and are included in the final task handoff because a commit cannot contain its
own hash without changing its tree. The source commit is
`3e287df2bea2b74ff991c7ff5c48cec3c209b890`; the report is the only file in the
report commit.

Final required state after push:

| Item | Result |
| --- | --- |
| branch | `fix/port-conflict-fail-fast` |
| changed files across the two commits | the two permitted source files and `Docs/Verification/FabPostPortConflict-UE5.8-Win64.md` |
| `git diff --check` | `PASS` |
| remote | `origin/fix/port-conflict-fail-fast` |
| force push | not used |
| final divergence | `0 0` |
| final working tree | clean |
| repository temporary artifacts | none |
| final target Unreal processes | `0` |
| final target UDP owners on 7777/7778/17777/17778 | `0` |

Final classification is updated by sections 24–31:

```text
Verification execution status — PASS
Requested exit status propagation — EDITOR_STATUS_0_REPRODUCED for mismatch; EDITOR_STATUS_OTHER for invalid marker
Port conflict implementation — PARTIAL_PACKAGED_TEST_BLOCKED
Product readiness status — FAIL
```

The evidence establishes repeated executable behavior for the Editor test paths,
but the packaged-server comparison required by the fixed rule was not
available from this installed engine distribution. No official UE platform
limitation is asserted.

Remaining product blockers are Fab Config, Fab Content, user documentation,
real game-project Development/Shipping integration, packaged executable
verification, and Editor BeginPIE/EndPIE delegate unregister. Port-conflict
behavior is excluded from that blocker list.

## 24. UnrealEditor mismatch exit-status repeatability

Five fully independent runs were executed under the new root
`D:\T\SMTPFX-20260723-225338`. Each run used the existing package
`D:\T\SMTPFC-20260723-201902\P`, the new Blueprint-only host, a separate
PowerShell holder process, and a fresh run directory. The first harness attempt
was archived under `Evidence\InitialHarnessRuns`; it had a harness-only
single-string indexing defect and is not included below. Run01–Run05 are the
corrected authoritative runs.

| Run | Server PID | Holder PID | Requested/actual | Requested status | Observed exit | Marker | Natural exit | Forced termination | Holder survived | Shifted residue | Final process/UDP |
| --- | ---: | ---: | --- | ---: | ---: | ---: | --- | --- | --- | ---: | ---: |
| 01 | 74040 | 52292 | 17777/17778 | 2 | 0 | 1 complete | yes | no | yes | 0 | 0/0 |
| 02 | 75104 | 58316 | 17777/17778 | 2 | 0 | 1 complete | yes | no | yes | 0 | 0/0 |
| 03 | 50340 | 48560 | 17777/17778 | 2 | 0 | 1 complete | yes | no | yes | 0 | 0/0 |
| 04 | 74092 | 60984 | 17777/17778 | 2 | 0 | 1 complete | yes | no | yes | 0 | 0/0 |
| 05 | 44608 | 38380 | 17777/17778 | 2 | 0 | 1 complete | yes | no | yes | 0 | 0/0 |

Every marker had the required parseable shape; the PID field matched the run's
server PID:

```text
SMT_PORT_VALIDATION_FAILED expected_port=17777 actual_port=17778 world=Entry pid=<run server pid> action=request_clean_exit requested_status=2 reason=port_mismatch
```

The holder was `pwsh.exe`, with command line of the following form and
run-specific ready/stop/metadata paths:

```text
"C:\Program Files\PowerShell\7\pwsh.exe" -NoProfile -File D:\T\SMTPFX-20260723-225338\EditorStatusHolder.ps1 -Port 17777 -ReadyPath <run>\holder.ready -StopPath <run>\holder.stop -MetadataPath <run>\holder.json
```

Holder metadata:

| Run | Start UTC | Endpoint | First seen UTC | Last seen UTC | Cleanup UTC |
| --- | --- | --- | --- | --- | --- |
| 01 | `2026-07-23T13:59:33.3905153Z` | `0.0.0.0:17777` | `2026-07-23T13:59:33.4022899Z` | `2026-07-23T13:59:48.2151326Z` | `2026-07-23T13:59:48.0411662Z` |
| 02 | `2026-07-23T13:59:51.5448652Z` | `0.0.0.0:17777` | `2026-07-23T13:59:51.5546144Z` | `2026-07-23T14:00:14.8178768Z` | `2026-07-23T14:00:14.6590313Z` |
| 03 | `2026-07-23T14:00:17.485404Z` | `0.0.0.0:17777` | `2026-07-23T14:00:17.5009906Z` | `2026-07-23T14:01:04.5109494Z` | `2026-07-23T14:01:04.3483476Z` |
| 04 | `2026-07-23T14:01:06.9789749Z` | `0.0.0.0:17777` | `2026-07-23T14:01:06.9902448Z` | `2026-07-23T14:01:21.259446Z` | `2026-07-23T14:01:21.1451721Z` |
| 05 | `2026-07-23T14:01:25.1938246Z` | `0.0.0.0:17777` | `2026-07-23T14:01:25.2037304Z` | `2026-07-23T14:01:39.6823389Z` | `2026-07-23T14:01:39.5789127Z` |

Aggregate:

| Measure | Result |
| --- | --- |
| observed exit-code distribution | `0: 5` |
| actual shifted-port distribution | `17778: 5` |
| complete-marker success | `5/5` |
| natural exit | `5/5` |
| cleanup success | `5/5` |
| duration min / median / max | `11.4885124 / 11.9680821 / 44.002811` seconds |

## 25. UnrealEditor invalid-marker exit-status repeatability

Three independent runs omitted NetDriver mismatch by passing
`-ServerManageExpectedPort=invalid` with no UDP holder.

| Run | Server PID | Marker | Requested status | Observed exit | Natural exit | Forced termination | Final process/UDP |
| --- | ---: | --- | ---: | ---: | --- | --- | --- |
| 01 | 77372 | 1 complete | 2 | 3 | yes | no | 0/0 |
| 02 | 43344 | 1 complete | 2 | 3 | yes | no | 0/0 |
| 03 | 28320 | 1 complete | 2 | 3 | yes | no | 0/0 |

Each marker was:

```text
SMT_PORT_VALIDATION_FAILED expected_port=invalid actual_port=unknown world=unknown pid=<run server pid> action=request_clean_exit requested_status=2 reason=invalid_expected_port
```

Aggregate exit-code distribution is `3: 3`; marker success is `3/3`, natural
exit is `3/3`, and final process/UDP cleanup is `0/0` for every run. This
separates the invalid-input startup path from the NetDriver mismatch path:
mismatch consistently observed `0`, while invalid input consistently observed
`3`.

## 26. Temporary dedicated-server host and build

The temporary host was created outside the repository at:

```text
D:\T\SMTPFX-20260723-225338\PackagedServer\Host
```

It contained the requested `.uproject`, game and server Target.cs files,
minimal module Build.cs/cpp, and `DefaultEngine.ini`. The committed plugin was
copied only through a `git archive` of commit
`1c2d3d1ddcda8071675a4bef9a3f3ba7ec15c18d`; the working tree was not copied.

Server target result:

```text
exit code: 6
classification: INSTALLED_ENGINE_SERVER_TARGET_UNAVAILABLE
reason: Server targets are not currently supported from this engine distribution.
```

This is the installed-engine limitation category requested by the procedure.
No Engine source, UE installation, SDK, repository source, or target design was
changed.

## 27. Packaged dedicated-server exit-status comparison

Because the Server target build was classified
`INSTALLED_ENGINE_SERVER_TARGET_UNAVAILABLE`, the conditional BuildCookRun
step was not executed:

```text
packaged server classification: PACKAGED_STATUS_NOT_TESTED
```

There is no packaged server executable, server executable SHA-256, runtime DLL
SHA-256, packaged invalid-marker result, packaged mismatch result, or packaged
matching-control result. No result was inferred from the Editor runs.

The conditional BuildCookRun command was:

```powershell
& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun `
  "-project=D:\T\SMTPFX-20260723-225338\PackagedServer\Host\ServerManageToolExitHost.uproject" `
  -noP4 -utf8output -server -noclient -serverplatform=Win64 `
  -serverconfig=Development -target=ServerManageToolExitHostServer -build `
  -cook -stage -pak -archive `
  "-archivedirectory=D:\T\SMTPFX-20260723-225338\PackagedServer\Archive" `
  -map=/Engine/Maps/Entry
```

## 28. Final exit-status classification

The fixed classifications are applied without asserting an official platform
limitation:

| Surface | Classification | Evidence |
| --- | --- | --- |
| Editor mismatch | `EDITOR_STATUS_0_REPRODUCED` | five runs, all exit `0` |
| Editor invalid marker | `EDITOR_STATUS_OTHER` | three runs, all exit `3` |
| Packaged server | `PACKAGED_STATUS_NOT_TESTED` | installed engine rejected Server target |
| Requested exit-status propagation | not propagated as `2` in either Editor path | mismatch `0`, invalid `3` |

The Editor behavioral sub-result is `PARTIAL_EDITOR_EXIT_STATUS`: mismatch
detection, natural exit, holder protection, and cleanup pass, but Editor exit
status `2` does not. Under the final fixed rule, because Editor exit `2` is not
met and the packaged dedicated-server comparison is blocked, the final port
conflict implementation result is:

```text
Port conflict implementation — PARTIAL_PACKAGED_TEST_BLOCKED
```

This phase does not claim `PASS`, `EDITOR_STATUS_2_PROPAGATED`,
`PACKAGED_STATUS_2_PROPAGATED`, or a platform limitation.

## 29. Additional evidence SHA-256

All new evidence is under `D:\T\SMTPFX-20260723-225338` and is absent from
the repository.

### Harness, host, archive, and build evidence

| File | SHA-256 |
| --- | --- |
| `EditorStatusHolder.ps1` | `9B9931C7D3F1D19F43BC52353C08C03133F6A3D3D7E73DE4D67A1CE3BD1207DF` |
| `RunEditorStatus.ps1` | `A8C0DA675961B90F00A31B18AF6580F2AFEECB349FC84AB9EFCCA9C106516BD1` |
| `EditorHost\ServerManageToolExitStatusEditorHost.uproject` | `0E609A7539FE275A1890BE68F03E45149CD1C138F48A0C8E3C6D4B22DE76476F` |
| `EditorHost\Config\DefaultEngine.ini` | `EDABEBF02CDC6F703F09AB8F8865BFBBD650393C34F51BB886E2068143BBB7A9` |
| `PackagedServer\ServerManageTool-source.zip` | `1540B3FFA682C34B8BE980CD31D098D8139C4D8EB88A7487D48952C587C3CA50` |
| `PackagedServer\ServerTargetBuild.log` | `66541DB9A78999DB38CC2F8E83F96886738CD7ABD5386409A1412CC45A1138AC` |
| `PackagedServer\ServerTargetBuild.stderr.log` | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |
| `Evidence\FinalExitStatusSummary.json` | `5AA1EB497B1616CB2E380B3D4C993EC76C9E950F34279EEDC45C0FEFEEB2B3FE` |

### Temporary C++ host evidence

| File | SHA-256 |
| --- | --- |
| `PackagedServer\Host\ServerManageToolExitHost.uproject` | `FA0E7A4D104B4C6CE118643CA8F5350988D132DCDD21B4D6DBAF6D3485DDCF86` |
| `PackagedServer\Host\Source\ServerManageToolExitHost.Target.cs` | `C80A45DEE3B2C617D8153D7D5E2D2027B22521FCFBC78FC1FDB093C47181D00B` |
| `PackagedServer\Host\Source\ServerManageToolExitHostServer.Target.cs` | `F7E43D0B0FCD0C980D937DF8B4329778435780E629C48A58458771CC8BED365E` |
| `PackagedServer\Host\Source\ServerManageToolExitHost\ServerManageToolExitHost.Build.cs` | `E1A4505A9BB2952EF932B2C259C5970A0DFE880B192543EF673ECA8548E6E8A2` |
| `PackagedServer\Host\Source\ServerManageToolExitHost\ServerManageToolExitHost.cpp` | `BA92DE3703ACA90C84A24E9915B798734AA6497AD8A485EEF04C0AF4C8D23D77` |
| `PackagedServer\Host\Config\DefaultEngine.ini` | `F6314F7F4202A555BBD9981D192E2508CBD6D305A8DB1A20C095A103743F18CA` |

### Package and eight port-conflict-related source files

| File | SHA-256 |
| --- | --- |
| Existing `BuildPlugin.log` | `4E58586A5E9EB05B290DCA43DB7EF46C3BF4166742B86302EACE3AC0DC5EA1EF` |
| Existing `ServerManageTool.uplugin` | `66620607E4F2CBFD625E4C08C95CEA081E1B75748D8BEB732ED9F4DC455CF146` |
| Existing `UnrealEditor.modules` | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |
| Existing `UnrealEditor-ServerManageLibrary.dll` | `2B62B52375C211E9B5210F6F48EEC2FD32E80D8C0AE7955E0EB8588BDD49BA8A` |
| Existing `UnrealEditor-ServerInfoSettingsModule.dll` | `39DF8F3E60F5CB838A8C9F7D2D6489B0BF5550C9085DED55B2AA07967183FAC8` |
| Existing `UnrealEditor-ServerModePlayMenu.dll` | `3CEFAB6F75A528BAD72FE9F948DE5964C882B5CEABD91EBB7FB6ADD53ADFCEBB` |
| `Source\ServerModePlayMenu\Private\ServerModePlayMenu.cpp` | `9B244895C836867CC06A84CF03288EEAEF3CDD2F1357A77FD34D420243C9CBB0` |
| `Source\ServerModePlayMenu\Public\ServerModePlayMenu.h` | `7625DBAEBBF06362D87EDB705E12A23C9FFA1D95575AA6ACE7F0C54012D47E00` |
| `Source\ServerModePlayMenu\Private\ServerProcess.cpp` | `5F9958A560FBE1D4437622298D48686ABCBB84A5130276610E4B7C7F93EE77E5` |
| `Source\ServerModePlayMenu\Private\ServerProcess.h` | `05AB9A15C790B711BE636B6761D057B28FA4F0FD1105D5889C8508012AD61360` |
| `Source\ServerModePlayMenu\ServerModePlayMenu.Build.cs` | `21BDC784AF379A4A871FB6E3353A754A2B8B24569FD1BA82F19B22169030C213` |
| `Source\ServerManageLibrary\Private\ServerManageLibrary.cpp` | `4D06734827ECD3B4260E2ECBD201E7AD4C1F8A86EE2933638CB4F0948985646A` |
| `Source\ServerManageLibrary\Public\ServerManageLibrary.h` | `BBEC1587967AD5F8F0AA0B601B64F1F837AB0BD97884A23D30A3FF0DB855EE1B` |
| `Source\ServerManageLibrary\ServerManageLibrary.Build.cs` | `C69143D5C06831A2ED6C55F2514A69DED491D31932ADDE3E757CA57B5F48AC1A` |

### Editor mismatch and invalid run evidence

| Evidence | SHA-256 values |
| --- | --- |
| Mismatch Run01 | result `C4E220567DD33C05D497AF6FC1F07E177203A75C1473CE1C57EB668321AC3DAB`; log `01B74FD60B84CF44A3A8894B38DDB3F7413A25379FF63828DADD0E51D049E742`; stdout `0CBD02186C58B5FE6133A94536C119EF15EDCA2FCCDC3E3DFA52517BEB486E80`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855`; holder `C02AA1BA36EAF25ABE931B75DA0CA3BE30D43E64D39B7EBD514C5CF983CFF319` |
| Mismatch Run02 | result `163AA631E84CA65BBD12E942F933AD94F1EDF1E2A67C3A6D3FD9409133764E66`; log `3280C233262FA999354D08BF39089558542DAF3553B6D51A5FC4C32148413F67`; stdout `B555EEFAAC0D6D577EEEEFFDE33326854FB6403C5B69A335F068AC74ACF84359`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855`; holder `16AC3CA19EEAF96628C424E66123F78CF11353B9E303D2E362C9CEDA9EDFEDAA` |
| Mismatch Run03 | result `85561CD58D81AC87AB70D1903495ACDD4E53E37D2D0FF009A98B74B4DA128059`; log `766367752D48091157A0B7935E33C162D54C89AF435615767C67DEB188523477`; stdout `7313798D2CA34AD285F98D172C6A6F153FF05A9AE5465D983E0B232ED9509127`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855`; holder `54BCD588F5E172D0F3B9914E1469AF7E5A1400067A2A12CD82E467397881EF4A` |
| Mismatch Run04 | result `87FC5C82F2D0243FA956A4CC45FCB4B3F1C2B42A9607940172ACC9CD8B8A25A7`; log `C167FAE0F81CACA8A4A08C0ABB07D4CD06E8A6AE1DB004EA09EA8A9DC0D061FB`; stdout `9A9CA80A5F82C3F179ACC56FFF8FB7F96C0A05F52E01A720A29EFC091663AA6C`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855`; holder `1D7B2433045984C7223610475A6CA0B082F7814168058C327A31C6C302047C34` |
| Mismatch Run05 | result `4822EE588DC7113EA6D85E4602175E793B44142293CC1529647695F42F0DA332`; log `139C849E7130967D219AA29C9B5749DB85AA416456E030C9C2FE1C6AB6630E02`; stdout `7370A099D55905FFBBAF4FDE0BDA6CB69D38DF30A73413B33340129AFED62C43`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855`; holder `6064035EF3568D3106E1339F29448677A626446EEAD071035031E12C658293E5` |
| Invalid Run01 | result `D1A889299823678C7E0D6F01D8250D7D6A0493635EA6D03ADFDAE58F4C50E856`; log `80D07CDA1795BB2EA55EB1B503A44BAC2D7D2089A9950BC9A982C5B75A111329`; stdout `FBB53614B7018C23F8999324C4AFCD3096EFD4357C336F195023B147BB67CFEC`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |
| Invalid Run02 | result `1392FDFA9CE9C5D8A44F93EDCDB951CC19D10122FAE5347F9DE7FF60EF4182AF`; log `11490B8EC348C257A338CC6FBEB7C6EFE5004BD9D59ABA24F420C7114DF58D15`; stdout `190EB1B8A173B3ACE6EEF7F1EB593DE7A789186FC3D56F89338AFFD414DDE2CC`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |
| Invalid Run03 | result `FF9E30428364721D1BC0BABBF986D193EBBF1A0B0BAE297E78A813CEE9C97689`; log `B5C84268A5E5ED6BA3A5812530965CD40A03F445CC13F294EABB35D83BB216C4`; stdout `C63E5B4D33B817E16ACE94278C7DE765A2046023EB6989CF92B2A5416B612819`; stderr `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |

## 30. Exact reproduction commands

Create the root only when it does not exist:

```powershell
$stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$verifyRoot = "D:\T\SMTPFX-$stamp"
```

Editor mismatch runs:

```powershell
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Mismatch -RunIndex 1 -VerifyRoot <verifyRoot>
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Mismatch -RunIndex 2 -VerifyRoot <verifyRoot>
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Mismatch -RunIndex 3 -VerifyRoot <verifyRoot>
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Mismatch -RunIndex 4 -VerifyRoot <verifyRoot>
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Mismatch -RunIndex 5 -VerifyRoot <verifyRoot>
```

Each command starts a separate PowerShell holder that exclusively binds
`0.0.0.0:17777`, confirms ownership, launches the direct command with
`-ServerManageExpectedPort=17777`, waits up to 60 seconds, verifies holder
survival after server exit, signals only the recorded holder PID for cleanup,
and writes run JSON/log/stdout/stderr/holder evidence.

Editor invalid-marker runs:

```powershell
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Invalid -RunIndex 1 -VerifyRoot <verifyRoot>
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Invalid -RunIndex 2 -VerifyRoot <verifyRoot>
pwsh -NoProfile -File <verifyRoot>\RunEditorStatus.ps1 -Mode Invalid -RunIndex 3 -VerifyRoot <verifyRoot>
```

These omit the UDP holder and launch the same host with
`-ServerManageExpectedPort=invalid`.

Archive and server target:

```powershell
git -C D:\ghws\ServerManageToolPlugin archive --format=zip `
  --output="<verifyRoot>\PackagedServer\ServerManageTool-source.zip" HEAD

& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" `
  ServerManageToolExitHostServer Win64 Development `
  "-Project=<verifyRoot>\PackagedServer\Host\ServerManageToolExitHost.uproject" `
  -WaitMutex -NoHotReloadFromIDE
```

BuildCookRun and all packaged-server invalid/mismatch/matching commands are
conditional on a successful Server target build and therefore were not run.

## 31. Final Git state

The report is the only permitted repository file changed in this phase. No
source, uplugin, Config, Content, README, CI, or generated artifact was
modified in the repository.

| Item | Result before this report commit |
| --- | --- |
| start HEAD | `1c2d3d1ddcda8071675a4bef9a3f3ba7ec15c18d` |
| branch | `fix/port-conflict-fail-fast` |
| source changes in this phase | `0` |
| report change | `Docs/Verification/FabPostPortConflict-UE5.8-Win64.md` only |
| `git diff --check` | `PASS` |
| final target Unreal processes | `0` |
| final target UDP owners 17777/17778 | `0` |
| requested commit | `docs: clarify port mismatch exit status` |
| push target | `origin/fix/port-conflict-fail-fast` |
| force push | not used |

The report commit SHA and URL are recorded in the final task handoff after the
commit is created. The final post-push checks must show remote HEAD equal to
local HEAD, divergence `0 0`, and a clean working tree.
