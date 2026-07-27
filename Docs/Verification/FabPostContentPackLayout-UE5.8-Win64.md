# Fab Content Pack Layout Verification — UE 5.8 Win64

Verification date: 2026-07-27 (JST)
Verification root: `D:\T\SMTPACK-20260727-163158`

## 1. Scope and verdict

This follow-up moves the packaged Quick Start document into the plugin-named
Content Pack directory required by the current Fab candidate. Product Source,
the plugin descriptor, and runtime behavior were not changed.

| Area | Verdict |
| --- | --- |
| Fab Content Pack layout | PASS |
| Fab package structure | PASS |
| User documentation | PASS |
| Editor exit-status | EDITOR_STATUS_INCONSISTENT (preserved) |
| Port conflict implementation | PARTIAL_PACKAGED_TEST_BLOCKED (preserved) |
| Product readiness | FAIL |

Fab was not submitted. The current candidate closes the Content Pack directory
layout blocker only.

## 2. Reason for follow-up

The previous candidate placed Quick Start at `Content/Documentation/QuickStart.txt`.
The current candidate uses the plugin-named path
`Content/ServerManageTool/Documentation/QuickStart.txt`.

## 3. Start Git states

Plugin repository:

- Remote: `https://github.com/metyatech/ServerManageToolPlugin`
- Start branch: `feat/fab-package-structure-docs`
- Start local and remote HEAD: `7e31ce8b8b9f776de3666fd0d82bf102c860a30f`
- Start divergence: `0 0`
- Start working tree: clean
- Work branch: `fix/fab-content-pack-layout`, created from the start HEAD

Central documentation repository:

- Remote: `https://github.com/metyatech/unreal-plugin-docs`
- Branch: `main`
- Local and `origin/main` HEAD: `8ccbc33de99e5a00de0521cba24a536e73f830a2`
- Divergence: `0 0`
- Working tree: clean

Environment:

- Unreal Engine root: `C:\Program Files\Epic Games\UE_5.8`
- Build version: 5.8
- `InstalledBuild.txt`: present

## 4. Exact changes

The product change is the exact Git move:

```text
Content/Documentation/QuickStart.txt
Content/ServerManageTool/Documentation/QuickStart.txt
```

The first commit also changes `Config/FilterPlugin.ini`, the README Quick
Start link, and the Quick Start self-reference. No UserGuide file contained
the old path, so no UserGuide file was changed. The second commit contains
this report and the superseded notice added to the historical report.

Source diff: 0 files. `ServerManageTool.uplugin` diff: 0 files. Resources and
all protected verification reports other than the allowed historical notice
were unchanged.

## 5. Content Pack directory

Old Content path: `Content/Documentation/QuickStart.txt`.

New Content path:

```text
Content/ServerManageTool/Documentation/QuickStart.txt
```

The repository Content root contains exactly one directory, `ServerManageTool`.
`Content/Documentation` is absent. The new Quick Start is non-empty and retains
the required product, online documentation, packaged documentation, settings,
Server Mode, Blueprint API, port assignment, Server List, UDP preflight,
all-or-nothing launch, and production-server limitation guidance.

## 6. FilterPlugin

`Config/FilterPlugin.ini` contains exactly one section, no BOM, and a trailing
newline:

```ini
[FilterPlugin]
/Config/...
/Content/ServerManageTool/Documentation/...
/Docs/UserGuide/...
/README.md
```

The old FilterPlugin entry count is 0. The new plugin-named entry count is 1.
`Docs/Verification` is not included.

## 7. Documentation path updates

The product documentation validation scope was README, `Docs/UserGuide`,
`Config`, and `Content`, excluding verification reports as required.

- Old path references: 0
- New exact Quick Start references: 2 (README and Quick Start)
- UserGuide files changed for path references: none
- Relative Markdown link failures: 0
- Duplicate headings: 0
- Empty sections: 0
- Windows local paths in user-facing docs: 0
- PID/SHA evidence in user-facing docs: 0

The historical report retains its old inventory and evidence. Its title is
followed by a notice identifying it as superseded for the current candidate.

## 8. Previous candidate preservation

The previous Downloads ZIP matched the required old SHA-256 before replacement:

```text
9B4F6353A1CFD5F9F995188E6082BCEDDA7F37384C58F707E49EA01FD4F75539
```

It was copied before replacement to:

```text
D:\T\SMTPACK-20260727-163158\PreviousCandidate-Content-Documentation.zip
```

The preserved copy has the same SHA-256. The Downloads candidate was replaced
only after that check, and the new SHA differs.

## 9. BuildPlugin

BuildPlugin command root: `D:\T\SMTPACK-20260727-163158`.

- Package: `D:\T\SMTPACK-20260727-163158\BuildPluginPackage`
- Log: `D:\T\SMTPACK-20260727-163158\BuildPlugin.log`
- Exit code: 0
- UnrealEditor Win64 Development: succeeded
- UnrealGame Win64 Development: succeeded
- UnrealGame Win64 Shipping: succeeded
- UHT Category errors: 0
- Path-length errors: 0
- `BUILD SUCCESSFUL`: present
- Build log SHA-256: `A13EA13B21FE629183F65818E124CE65C5861E1D8C0B070D0AD41ADE4F23C959`

## 10. BuildPlugin package structure

The BuildPlugin package top level is:

```text
Binaries
Config
Content
Docs
Intermediate
Resources
Source
README.md
ServerManageTool.uplugin
```

`Intermediate` is recorded as BuildPlugin output and is removed from the
candidate. `Content` has one direct directory, `ServerManageTool`, and contains
the new Quick Start path. The old Content path and `Docs/Verification` are
absent. Repository metadata is absent.

## 11. Blueprint-only clean load

The direct BuildPlugin package was copied to a new Blueprint-only host with
Server Manage Tool, PythonScriptPlugin, and EditorScriptingUtilities enabled.
Both direct and candidate hosts have no C++ `Modules` property.

Evidence: `BuildPluginPackageCleanLoad.summary.json`.

- Product module loads: 3
- Missing modules: 0
- Incompatible modules: 0
- Compile requests: 0
- C++ conversion requests: 0
- Fatal/ensure/crash: 0
- Parent exit code: 0
- Timeout: false
- Forced termination: false
- Final host process: 0
- New Quick Start present: yes
- Old Quick Start absent: yes

## 12. Candidate sanitize

`D:\ghws\fab-plugin-release-tools` was rechecked read-only and was clean. Its
Content Pack validator supports `Content/ServerManageTool`, but its mandatory
publisher copyright precondition does not match the existing Source headers.
Satisfying that precondition would require a prohibited Source change, so the
tool was not run against the product repository.

A temporary sanitize script under the verification root applied the same
allowlist and exclusion rules. Candidate output:

```text
D:\T\SMTPACK-20260727-163158\Candidate\ServerManageTool
```

Candidate top level is exactly `Binaries`, `Config`, `Content`, `Docs`,
`README.md`, `Resources`, `Source`, and `ServerManageTool.uplugin`. It contains
34 files and 348,918 uncompressed bytes. Intermediate, Saved,
DerivedDataCache, Git metadata, `.github`, `.vs`, PDBs, and `Docs/Verification`
are absent.

## 13. Candidate ZIP

Current candidate:

```text
C:\Users\Origin\Downloads\ServerManageTool-1.1.0-UE5.8-Win64.zip
```

- SHA-256: `E2467EA57F54C8C591C04C229651B49C457071A3D26A2781C7D72855547FF914`
- ZIP bytes: 169,134
- Uncompressed bytes: 348,918
- ZIP file entries: 34
- File entries: 34
- Root: exactly `ServerManageTool/`
- Old Content path entries: 0
- New Quick Start entries: 1
- Nested ZIP: 0
- Encrypted entries: 0
- Traversal entries: 0
- Duplicate normalized paths: 0
- PDB entries: 0
- Verification report entries: 0
- Repository metadata entries: 0

Required paths including the descriptor, FilterPlugin, new Quick Start,
UserGuide index, README, Resources, Source, Binaries, and Config are present.

## 14. Candidate ZIP re-extraction

The final ZIP was extracted to:

```text
D:\T\SMTPACK-20260727-163158\CandidateExtract
```

The extraction has one plugin root. The new Quick Start exists and the old path
does not. A fresh Blueprint-only host loaded this extracted candidate with:

- Product module loads: 3
- Missing/incompatible modules: 0/0
- Compile/C++ conversion requests: 0/0
- Fatal/ensure/crash: 0
- Exit code: 0
- Timeout: false
- Forced termination: false
- Final host process: 0

Evidence: `CandidateZipCleanLoad.summary.json`.

## 15. Normal PIE regression

The re-extracted candidate was used with two `/Engine/Maps/Entry` Server List
entries.

- Parent PID: 48744
- Child PIDs: 73368 (`-Port=7777`, actual UDP 7777) and 48364 (`-Port=7778`, actual UDP 7778)
- Both child `ParentProcessId` values: 48744
- `SMT_PORT_PREFLIGHT_PASSED`: 1
- Validation passed: 2
- Validation failed: 0
- Maximum matching child count: 2
- EndPIE child count: 0
- Forced cleanup: none
- Final UDP 7777/7778 owners: 0

Evidence: `Normal-PIE.summary.json`, `Normal-PIE.monitor.jsonl`, and
`Normal-PIE.log`.

## 16. 7778 conflict regression

An independent exclusive UDP holder occupied port 7778. The re-extracted
candidate reported `SMT_PORT_PREFLIGHT_FAILED` once with unavailable port 7778,
`started_server_count=0`, and no shifted child. Maximum managed child count was
0; the 7777 child was not started. The holder was alive with one endpoint before
planned harness cleanup and was not terminated by the plugin. After planned
harness cleanup, holder process and UDP owner counts were 0. Timeout and forced
termination were false.

- Holder PID: 39696
- Editor parent PID: 59040
- Existing exit-status classification: `EDITOR_STATUS_INCONSISTENT` (not rerun)
- Port conflict classification: `PARTIAL_PACKAGED_TEST_BLOCKED` (preserved)

Evidence: `PortConflict.summary.json`, `PortConflict.monitor.jsonl`, and
`PortConflict.log`.

## 17. Central docs check

Central docs contained 0 references to the old path, so it was not modified,
committed, or pushed. Its HEAD remains
`8ccbc33de99e5a00de0521cba24a536e73f830a2`, with divergence `0 0` and a clean
working tree.

## 18. Documentation validation

Local product documentation validation passed with old path count 0, new exact
Quick Start reference count 2, broken relative links 0, duplicate headings 0,
empty sections 0, local path violations 0, and PID/SHA violations 0.

The online documentation check passed:

- URL: <https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/>
- HTTP status: 200
- Title: `Server Manage Tool | metyatech Unreal Engine Plugins`
- Version 1.1.0: present
- UDP preflight: present
- all-or-nothing launch: present
- Old Content path: 0

## 19. Process cleanup

All harnesses identify cleanup targets by recorded PID, expected executable,
host project path, and `-server` identity for managed children. At the final
check, matching UnrealEditor processes were 0, holder processes were 0, and UDP
7777/7778 residual owners were 0. No unrelated process was terminated and no
forced cleanup was used.

## 20. Remaining blockers

The following remain intentionally open:

- Real game-project Development integration unverified
- Real game-project Shipping integration unverified
- Packaged executable unverified
- Requested exit-status propagation unresolved
- Editor exit-status `EDITOR_STATUS_INCONSISTENT`
- Port conflict implementation `PARTIAL_PACKAGED_TEST_BLOCKED`

The Content Pack directory layout blocker is closed.

## 21. Evidence SHA-256

The complete temporary evidence manifest is:

```text
D:\T\SMTPACK-20260727-163158\Evidence-SHA256.txt
```

Manifest SHA-256: `CB5F222E76AC768E9B547F344375BDF743B3502882B8225A5BFE6177D496B6C9`.

Selected evidence hashes:

| Evidence | SHA-256 |
| --- | --- |
| Preserved old ZIP | `9B4F6353A1CFD5F9F995188E6082BCEDDA7F37384C58F707E49EA01FD4F75539` |
| Current ZIP | `E2467EA57F54C8C591C04C229651B49C457071A3D26A2781C7D72855547FF914` |
| BuildPlugin log | `A13EA13B21FE629183F65818E124CE65C5861E1D8C0B070D0AD41ADE4F23C959` |
| Candidate `.uplugin` | `AAF290E60209BC8E29C195F61A07D6C03C3554C7D6CC1A95AA5A5B07CDFC4607` |
| Candidate Quick Start | `00175FDFD985B4D478040B527689077894A11EE6A588D737ED3A0AC52CDA5EF1` |

## 22. Exact reproduction commands

The following commands reproduce the main gates using the recorded verification
root (temporary harness files are outside the repository):

```powershell
git -C D:\ghws\ServerManageToolPlugin switch fix/fab-content-pack-layout
git -C D:\ghws\ServerManageToolPlugin diff --check

& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  "-Plugin=D:\ghws\ServerManageToolPlugin\ServerManageTool.uplugin" `
  "-Package=D:\T\SMTPACK-20260727-163158\BuildPluginPackage" `
  -TargetPlatforms=Win64 `
  -Rocket

pwsh -NoLogo -NoProfile -File D:\T\SMTPACK-20260727-163158\RunBlueprintOnlyCleanExit.ps1
pwsh -NoLogo -NoProfile -File D:\T\SMTPACK-20260727-163158\SanitizeCandidate.ps1 `
  -PackageRoot D:\T\SMTPACK-20260727-163158\BuildPluginPackage `
  -CandidateRoot D:\T\SMTPACK-20260727-163158\Candidate\ServerManageTool `
  -SummaryPath D:\T\SMTPACK-20260727-163158\CandidateSanitize.summary.json
pwsh -NoLogo -NoProfile -File D:\T\SMTPACK-20260727-163158\RunCandidateCleanLoad.ps1
pwsh -NoLogo -NoProfile -File D:\T\SMTPACK-20260727-163158\RunNormalLifecycle.ps1 -Mode PIE
pwsh -NoLogo -NoProfile -File D:\T\SMTPACK-20260727-163158\RunPortConflict.ps1
```

The Downloads ZIP was replaced only after the pre-replacement SHA matched the
historical candidate and the new temporary ZIP passed direct parsing.

## 23. Final Git states

The work branch is `fix/fab-content-pack-layout`, created from the required
start HEAD. The intended two commits are:

```text
fix: use plugin-named Fab content pack
docs: verify Fab content pack layout
```

Commit IDs, remote branch reachability, divergence, and final cleanliness are
reported in the delivery handoff after the two commits and push. No amend,
rebase, squash, merge commit, force push, PR, tag, release, or Fab submission
was performed.
