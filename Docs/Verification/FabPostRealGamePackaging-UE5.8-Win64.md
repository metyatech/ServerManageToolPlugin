# Real C++ Game Integration and Packaging Verification — UE 5.8 Win64

Verification date: 2026-07-27 (JST)
Verification root: `D:\T\SMTREAL-20260727-171727`

## 1. Scope and verdict

The current Fab candidate ZIP was installed into a repository-external C++
game project and verified through Editor target build, Game Development and
Shipping builds, BuildCookRun Development and Shipping archives, and packaged
AddressAndExit execution.

The packaged game `-server` control was attempted with the required Game target.
It reported `is_dedicated_server=false` and never owned UDP 17777. Adding a
`TargetType.Server` target would be required to satisfy that acceptance test,
but that is explicitly prohibited in this task. The stop condition was applied;
Shipping dedicated/mismatch/invalid-marker tests were not run.

| Area | Verdict |
| --- | --- |
| Real C++ game-project Development integration | PASS |
| Real C++ game-project Shipping integration | PASS |
| Packaged Development game executable | PASS (AddressAndExit) |
| Packaged Shipping game executable | PASS (AddressAndExit) |
| Packaged game executable dedicated mode | BLOCKED: Game target is not dedicated |
| Packaged dedicated-server `TargetType.Server` executable | NOT_TESTED |
| Editor exit-status | EDITOR_STATUS_INCONSISTENT (preserved) |
| Port conflict implementation | PARTIAL_PACKAGED_TEST_BLOCKED (preserved) |
| Product readiness | FAIL |

No product Source, `.uplugin`, candidate ZIP, Engine installation, or existing
repository file other than this report was changed.

## 2. Start Git state

Plugin repository:

- Remote: `https://github.com/metyatech/ServerManageToolPlugin`
- Start branch: `fix/fab-content-pack-layout`
- Start local and remote HEAD: `026d006b51e0d61f97b868b0455d1f7e2bb615da`
- Start divergence: `0 0`
- Start working tree: clean
- Verification branch: `verify/real-game-packaging`, created from the start HEAD

Environment:

- Unreal Engine root: `C:\Program Files\Epic Games\UE_5.8`
- `Build.version`: `MajorVersion=5`, `MinorVersion=8`
- `InstalledBuild.txt`: present

## 3. Candidate ZIP identity

Candidate:

```text
C:\Users\Origin\Downloads\ServerManageTool-1.1.0-UE5.8-Win64.zip
```

- SHA-256: `E2467EA57F54C8C591C04C229651B49C457071A3D26A2781C7D72855547FF914`
- ZIP bytes: 169,134
- File entries: 34
- Root directories: exactly `ServerManageTool/`
- Root `.uplugin`: present
- `Source`, `Binaries`, `Config`, `Content`, `Docs`, `Resources`: present
- New Quick Start: present
- Old Content path: absent
- `Intermediate`: absent
- PDB: 0
- `Docs/Verification`: absent
- Repository metadata: absent
- Nested/encrypted/traversal/duplicate-normalized entries: 0/0/0/0

The candidate ZIP was parsed and used without modification or replacement.

## 4. Temporary real C++ project

Project root:

```text
D:\T\SMTREAL-20260727-171727\Host
```

Project: `ServerManageToolIntegrationHost`.

The host contains the requested `.uproject`, Game and Editor Target.cs files,
runtime module Build.cs and implementation, GameInstance integration code, and
the required Config files. The Game target uses `ServerManageLibrary` and
`ServerInfoSettingsModule`; it does not depend on `ServerModePlayMenu` and no
Server target was added.

## 5. Candidate plugin extraction

The candidate was extracted to:

```text
D:\T\SMTREAL-20260727-171727\CandidateExtract\ServerManageTool
```

It was copied to:

```text
D:\T\SMTREAL-20260727-171727\Host\Plugins\ServerManageTool
```

Source and destination both contain 34 files. Relative path, size, and SHA-256
comparison passed with mismatch count 0.

Selected matching hashes:

| File | SHA-256 |
| --- | --- |
| `ServerManageTool.uplugin` | `AAF290E60209BC8E29C195F61A07D6C03C3554C7D6CC1A95AA5A5B07CDFC4607` |
| `Source/ServerManageLibrary/Public/ServerManageLibraryBP.h` | `BA76C7871424DB4EEBCDF181FB3604F2AA0A8A41541309523D69A24926C0645C` |
| `Source/ServerManageLibrary/Private/ServerManageLibrary.cpp` | `4D06734827ECD3B4260E2ECBD201E7AD4C1F8A86EE2933638CB4F0948985646A` |
| `Source/ServerManageLibrary/ServerManageLibrary.Build.cs` | `C69143D5C06831A2ED6C55F2514A69DED491D31932ADDE3E757CA57B5F48AC1A` |
| `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h` | `168482E573E3FC02AA3FCB96A4AA07127E3EBAE59256278BD6760766C86906D5` |
| `Binaries/Win64/UnrealEditor-ServerManageLibrary.dll` | `A2766D78A09CE867B248BEB7E57D83779E676174DE91E6163099DFBD9307B01D` |
| `Binaries/Win64/UnrealEditor-ServerInfoSettingsModule.dll` | `C9B449DC84766D199557419F8B3FFB02CCD7C7E89CB8C9C764DEC508895D99F1` |
| `Content/ServerManageTool/Documentation/QuickStart.txt` | `00175FDFD985B4D478040B527689077894A11EE6A588D737ED3A0AC52CDA5EF1` |

## 6. Editor target integration

Editor target:

- Target: `ServerManageToolIntegrationHostEditor`
- Configuration: Win64 Development
- Exit code: 0
- Host module compile/link: PASS
- Candidate plugin compile/link: PASS
- UHT errors: 0
- Category errors: 0
- Unresolved externals: 0
- Receipt: `Host/Binaries/Win64/ServerManageToolIntegrationHostEditor.target`

The first temporary runner attempt failed before UBT because of an incorrect
`cmd.exe` quote construction. The runner was corrected outside the repository;
the final build above is the authoritative result.

## 7. Integration map

The Editor public Python API created and saved:

```text
/Game/Maps/IntegrationMap
```

- Python process exit code: 0
- Forced termination: false
- Map asset: `Host/Content/Maps/IntegrationMap.umap`
- Map bytes: 8,460
- Map SHA-256: `AFE79ACB00075F8B587ADEFA677BA61D3C320F361416ADE0621C37637BB8D328`
- Fatal/ensure/crash: 0

## 8. Development game build

- Target: `ServerManageToolIntegrationHost`
- Target type: Game
- Configuration: Win64 Development
- Exit code: 0
- Host runtime compile/link: PASS
- Runtime plugin integration: PASS
- Editor-only module build error: 0
- UHT/Category/unresolved external errors: 0
- Receipt: `Host/Binaries/Win64/ServerManageToolIntegrationHost.target`

## 9. Shipping game build

- Target: `ServerManageToolIntegrationHost`
- Target type: Game
- Configuration: Win64 Shipping
- Exit code: 0
- Host runtime compile/link: PASS
- Runtime plugin integration: PASS
- Editor-only module build error: 0
- UHT/Category/unresolved external errors: 0
- Receipt: `Host/Binaries/Win64/ServerManageToolIntegrationHost-Win64-Shipping.target`

## 10. Development packaging

BuildCookRun archive:

```text
D:\T\SMTREAL-20260727-171727\Package\Development
```

- UAT exit code: 0
- Build/cook/stage/pak/archive: PASS
- `AutomationTool exiting with ExitCode=0`: present
- Game executable: `Windows/ServerManageToolIntegrationHost\Binaries\Win64\ServerManageToolIntegrationHost.exe`
- Executable bytes: 339,679,232
- Executable SHA-256: `F17FB81160C16CF43A639EF303DE57F64BCB8586ED1F9ACFF1E362AE15D79DCA`
- IoStore `.ucas` bytes/SHA: 123,484,480 / `053494EE1DA48DB37917C0EDE497297348B93E2A7DE1E2A0CEAAE98C45EF6A15`
- IoStore `.utoc` bytes/SHA: 121,630 / `2519D29B6AEC7E9E048355DDB7635588B7D8AFCED8323BB0E7BDF6802FB03604`
- Legacy `.pak` bytes/SHA: 10,650,678 / `DFD0267B1112FD6E40C62B2542BF8F82C9BA13CC084AB3431FC28CE1F66AF5F3`
- UnrealEditor executable: absent from archive
- ServerModePlayMenu Editor binary: absent from archive

## 11. Shipping packaging

BuildCookRun archive:

```text
D:\T\SMTREAL-20260727-171727\Package\Shipping
```

- UAT exit code: 0
- Build/cook/stage/pak/archive: PASS
- `AutomationTool exiting with ExitCode=0`: present
- Game executable: `Windows/ServerManageToolIntegrationHost\Binaries\Win64\ServerManageToolIntegrationHost-Win64-Shipping.exe`
- Executable bytes: 172,002,304
- Executable SHA-256: `3E0BC19C29BAF1E492D374BD4D7D225E7072CD3E9260494BD38D444451A2467C`
- IoStore `.ucas` bytes/SHA: 123,484,480 / `053494EE1DA48DB37917C0EDE497297348B93E2A7DE1E2A0CEAAE98C45EF6A15`
- IoStore `.utoc` bytes/SHA: 121,630 / `2519D29B6AEC7E9E048355DDB7635588B7D8AFCED8323BB0E7BDF6802FB03604`
- Legacy `.pak` bytes/SHA: 10,642,987 / `3A7B4F0BD0E30E8997CA86454DD31832ED654BCDD987D61241D0611DCB014D1E`
- UnrealEditor executable: absent from archive
- ServerModePlayMenu Editor binary: absent from archive

## 12. Development AddressAndExit execution

Packaged Development AddressAndExit passed:

- Result status: PASS
- Process exit code: 0
- Timeout: false
- Forced termination: false
- Configured address: `integration.example.test:9010`
- Missing address: empty
- Null map address: empty
- `ServerManageLibrary` loaded: true
- `ServerInfoSettingsModule` loaded: true
- `ServerModePlayMenu` loaded: false
- `GetServerAddress` found/callable/pure: true/true/true
- `RequestServerExit` found/callable: true/true
- `RequestServerExit` scheduled: true
- Final process/UDP: 0/0

## 13. Shipping AddressAndExit execution

Packaged Shipping AddressAndExit passed with the same API and address contract:

- Result status: PASS
- Build configuration recorded: Shipping
- Process exit code: 0
- Timeout/forced termination: false/false
- Configured address: `integration.example.test:9010`
- Missing/null address: empty/empty
- Runtime modules loaded: true/true
- Editor module loaded: false
- Blueprint metadata: PASS
- `RequestServerExit` scheduled: true
- Final process/UDP: 0/0

## 14. Development packaged dedicated mode

The required Game executable control was attempted with:

```text
-server -Port=17777 -ServerManageExpectedPort=17777
-SMTIntegrationMode=ServerHold
```

Observed:

- Launch PID: 66456
- Spawned matching executable PID/result PID: 53064
- Target count maximum: 2
- Result status: FAIL
- `is_dedicated_server`: false
- UDP 17777 owner: none
- Actual port: none
- Validation marker: 0
- Timeout: true
- Forced termination: true
- Final process/UDP: 0/0

The Game receipt is `TargetType=Game`. With this target, the packaged process
does not become a dedicated server merely from `-server`; satisfying
`is_dedicated_server=true` and UDP ownership requires a dedicated Server target.
Adding that target is prohibited and is the explicit stop condition.

## 15. Shipping packaged dedicated mode

Not run. The Development result established that the required Game-target
dedicated control cannot satisfy the acceptance condition without a prohibited
`TargetType.Server` target. Repeating the same blocked path in Shipping would
not add valid evidence.

## 16. Packaged mismatch observations

Not run. A meaningful mismatch requires a working packaged dedicated-mode
server that owns or shifts UDP 17777. The required dedicated-mode precondition
failed in Development, so no requested/actual/exit-code mismatch classification
is claimed.

Existing classifications remain unchanged:

```text
Editor exit-status — EDITOR_STATUS_INCONSISTENT
Port conflict implementation — PARTIAL_PACKAGED_TEST_BLOCKED
```

## 17. Packaged invalid-marker observations

Not run. The invalid-marker run depends on the same packaged dedicated-mode
control and is therefore covered by the stop condition. No exit code is
invented or classified for this unexecuted case.

## 18. Runtime module and Editor-module separation

Receipt and archive evidence show:

- Editor receipt target type: `Editor`; `ServerModePlayMenu` Editor binary present
- Game Development receipt target type: `Game`; `ServerModePlayMenu` absent from build products
- Game Shipping receipt target type: `Game`; `ServerModePlayMenu` absent from build products
- Packaged AddressAndExit runtime module state: `ServerManageLibrary=true`, `ServerInfoSettingsModule=true`, `ServerModePlayMenu=false`
- Packaged archives contain no UnrealEditor executable or ServerModePlayMenu Editor binary

The runtime API is therefore integrated into both Game configurations without
linking the Editor-only module.

## 19. Process cleanup

AddressAndExit runs ended naturally with no forced termination. The failed
Development ServerHold run was cleaned only by recorded candidate executable
PIDs whose executable name, map, integration arguments, and `-server` identity
matched. No unrelated Unreal, game, or PowerShell process was terminated.

Final cleanup check:

- Matching packaged target processes: 0
- UDP 17777/17778 owners: 0
- Holder processes: 0

## 20. Closed blockers

The following evidence-backed blockers are closed:

- Real C++ game-project Development integration unverified
- Real C++ game-project Shipping integration unverified
- Packaged Development AddressAndExit executable unverified
- Packaged Shipping AddressAndExit executable unverified

The packaged dedicated-mode requirement remains open and is not conflated with
a dedicated `TargetType.Server` executable.

## 21. Remaining blockers

- Packaged game executable dedicated mode blocked by Game target semantics
- Packaged dedicated-server `TargetType.Server` executable unverified
- Shipping dedicated/mismatch/invalid-marker observations not run
- Requested exit-status propagation unresolved
- Editor exit-status `EDITOR_STATUS_INCONSISTENT`
- Port conflict implementation `PARTIAL_PACKAGED_TEST_BLOCKED`

## 22. Evidence SHA-256

The complete temporary evidence manifest is:

```text
D:\T\SMTREAL-20260727-171727\Evidence-SHA256.txt
```

The manifest contains 820 candidate or temporary evidence files, including the
candidate ZIP, extracted candidate, host source/targets, map, build and package
logs/receipts, runtime results/logs/monitors, and this task's temporary harness
files. It is 161,221 bytes and has SHA-256
`5C9A32C316290A3EA855187009657E9CE549E8D2DB8188DD590ACD23676F4A07`.

Selected evidence:

| Evidence | SHA-256 |
| --- | --- |
| Candidate ZIP | `E2467EA57F54C8C591C04C229651B49C457071A3D26A2781C7D72855547FF914` |
| IntegrationMap.umap | `AFE79ACB00075F8B587ADEFA677BA61D3C320F361416ADE0621C37637BB8D328` |
| Development executable | `F17FB81160C16CF43A639EF303DE57F64BCB8586ED1F9ACFF1E362AE15D79DCA` |
| Shipping executable | `3E0BC19C29BAF1E492D374BD4D7D225E7072CD3E9260494BD38D444451A2467C` |
| Development package pak | `DFD0267B1112FD6E40C62B2542BF8F82C9BA13CC084AB3431FC28CE1F66AF5F3` |
| Shipping package pak | `3A7B4F0BD0E30E8997CA86454DD31832ED654BCDD987D61241D0611DCB014D1E` |

## 23. Exact reproduction commands

The main gates use the temporary scripts under the verification root:

```powershell
pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunBuild.ps1 `
  -TargetKind Editor -Configuration Development `
  -OutputDirectory D:\T\SMTREAL-20260727-171727\Build\Editor\Development

pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunBuild.ps1 `
  -TargetKind Game -Configuration Development `
  -OutputDirectory D:\T\SMTREAL-20260727-171727\Build\Game\Development

pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunBuild.ps1 `
  -TargetKind Game -Configuration Shipping `
  -OutputDirectory D:\T\SMTREAL-20260727-171727\Build\Game\Shipping

pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunMapCreation.ps1
pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunPackage.ps1 -Configuration Development
pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunPackage.ps1 -Configuration Shipping

pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunPackagedIntegration.ps1 `
  -Configuration Development -TestMode AddressAndExit
pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunPackagedIntegration.ps1 `
  -Configuration Shipping -TestMode AddressAndExit
pwsh -NoLogo -NoProfile -File D:\T\SMTREAL-20260727-171727\Scripts\RunPackagedIntegration.ps1 `
  -Configuration Development -TestMode ServerHold
```

The final command is the documented blocked case; its exact PID cleanup and
failure evidence are retained. Shipping ServerHold, mismatch, and invalid
commands were intentionally not run after the stop condition.

## 24. Final Git state

The verification branch is `verify/real-game-packaging`, based on
`026d006b51e0d61f97b868b0455d1f7e2bb615da`. The only repository change is this
report. The final commit SHA, remote reachability, divergence, clean state, and
push result are recorded in the delivery handoff after the report commit. No
amend, rebase, squash, merge, force push, PR, tag, release, or Fab submission
was performed.
