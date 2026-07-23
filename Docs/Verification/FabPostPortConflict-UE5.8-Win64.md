# Fab post-port-conflict verification — UE 5.8 Win64

## 1. Scope and verdict

This report is the authoritative rerun for the port-conflict diagnostic-marker
completion and the required markerless direct-server regression on
`fix/port-conflict-fail-fast`. It uses a fresh packaged plugin and a fresh
Blueprint-only UE 5.8 host under `D:\T\SMTPFC-20260723-201902`.

Final verdict:

- Verification execution status — `PASS`
- Port conflict implementation — `PASS_WITH_PLATFORM_EXIT_CODE_LIMITATION`
- Product readiness status — `FAIL`

The implementation detects the mismatch, emits the complete marker, requests a
clean exit with status `2`, preserves the holder, leaves no shifted-port
residue, and passes matching and markerless controls. UE 5.8 Win64
`UnrealEditor.exe` observed exit code `0` after the requested status `2`; this
is recorded as a platform limitation and was not addressed with force exit,
process termination, or a source-side exit-code workaround.

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
| classification | `PLATFORM_EXIT_CODE_LIMITATION` |
| timeout / forced termination | `false / false` |
| natural terminal result | `true` |
| holder unaffected | `true` before planned holder cleanup |
| shifted-port residue | `0` |
| final target process/UDP after holder cleanup | `0 / 0` |

The requested code path is preserved exactly as
`FPlatformMisc::RequestExitWithStatus(false, 2, ...)`. UE 5.8 Win64's normal
Editor process returned `0` after the request, so no source change was made to
force `2`. The race-guard behavior passes all behavioral conditions.

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
docs: complete port conflict verification
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

Final classification:

```text
Verification execution status — PASS
Port conflict implementation — PASS_WITH_PLATFORM_EXIT_CODE_LIMITATION
Product readiness status — FAIL
```

Known platform limitation, separated from product blockers:

```text
UE 5.8 Win64 UnrealEditor.exe may return process exit code 0 after RequestExitWithStatus(false, 2, ...)
```

Remaining product blockers are Fab Config, Fab Content, user documentation,
real game-project Development/Shipping integration, packaged executable
verification, and Editor BeginPIE/EndPIE delegate unregister. Port-conflict
behavior is excluded from that blocker list.
