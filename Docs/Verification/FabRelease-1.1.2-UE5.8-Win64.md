# Server Manage Tool 1.1.2 Release Audit — UE 5.8 Win64

## 1. Scope and verdict

This audit covers the 1.1.2 source-provenance resolution, copyright-header normalization, `.mailmap`, metadata and user-facing documentation update, UE 5.8 Win64 BuildPlugin output, sanitized candidate ZIP, central documentation publication, and runtime regression checks. No product behavior, Blueprint API, Config, Content, Build.cs dependency, or runtime implementation was changed.

Current pre-release verdict:

```text
Provenance blocker: RESOLVED
Identity continuity: PASS
Copyright normalization: PASS
Source behavior changes: 0
Blueprint API changes: 0
Final BuildPlugin: PASS
Final candidate ZIP: PASS
Fab submission readiness: READY_WITH_DISCLOSED_LIMITATIONS
Fab submission: not performed
```

The final GitHub Release and asset postflight are performed after this report commit so the annotated `v1.1.2` tag can point to this report commit. The pre-publication pending items are recorded in Section 15.

## 2. Start Git state

The existing checkouts were not edited. Work used the fresh root `D:\T\SMT112-20260729-155350`.

| Repository | Start branch | Start SHA | Expected remote | Start tree |
| --- | --- | --- | --- | --- |
| ServerManageToolPlugin | `master` | `dd4ccf325c2929c38e060d19832274632deca4b7` | `dd4ccf325c2929c38e060d19832274632deca4b7` | clean |
| unreal-plugin-docs | `main` | `083a7db1f3e4c2635cc4fb3db670415b7024dde5` | `083a7db1f3e4c2635cc4fb3db670415b7024dde5` | clean |

The central docs commit was pushed as `963acf8279bc492824b9c8a9b5a924253cbe8755` with message `docs: update Server Manage Tool to 1.1.2`. The product preparation commit is `081bfff` (`release: normalize Server Manage Tool source provenance for 1.1.2`).

The prior report `Docs/Verification/SourceCopyrightProvenanceAudit-2026.md` was not modified.

## 3. Publisher declaration and provenance resolution

On 2026-07-29 JST, the repository owner confirmed that `Udon-Tobira` is the former GitHub username/account name of the same individual currently using `metyatech`. The two names represent continuous development by one individual, not a third-party rights transfer.

The resolution is recorded in `Docs/Verification/SourceCopyrightProvenanceResolution-2026.md`. The canonical identity is `metyatech <metyatech@gmail.com>`, taken from the latest non-bot Source commit. `.mailmap` was added without changing historical author fields or commit SHAs.

## 4. Contributors and mailmap evidence

Raw Source history, verified in a clean same-HEAD probe clone before `.mailmap`:

```text
10  Udon-Tobira <146440502+Udon-Tobira@users.noreply.github.com>
 4  metyatech <metyatech@gmail.com>
```

`.mailmap`:

```text
metyatech <metyatech@gmail.com> Udon-Tobira <146440502+Udon-Tobira@users.noreply.github.com>
```

The supported `git log --use-mailmap --format="%aN <%aE>" --all -- Source` display groups all 14 Source commits as `metyatech <metyatech@gmail.com>`. Git for Windows 2.55 rejects the requested `git shortlog ... --use-mailmap` option spelling; the limitation and raw/equivalent outputs are preserved in `mailmap-results.txt`.

## 5. Source classification and header-only proof

The 17 Source files were reclassified A `6`, C `11`, D `0`, E `0`, F `0`. The prior Epic template comparison found only standard Unreal boilerplate and no substantive Epic implementation reuse. The prior dependency scan found no third-party source or binary dependency.

Every Source file now begins with:

```cpp
// Copyright 2024-2026 metyatech. All Rights Reserved.
```

Evidence from the pre-commit tree comparison:

- 17 Source files changed;
- every file changed by exactly one first-line replacement;
- header-only files: 17;
- header-only failures: 0;
- Epic notice remaining: 0;
- Unreal placeholder remaining: 0;
- BOM and final-newline preservation failures: 0;
- runtime/API/Build.cs dependency changes: 0.

The complete old/new SHA-256 and byte-preservation table is `source-header-audit.json`; the exact diff is `source-commit-diff.txt`.

## 6. Descriptor and documentation changes

`ServerManageTool.uplugin` changes are limited to:

```json
"Version": 4,
"VersionName": "1.1.2",
"CreatedBy": "metyatech"
```

`CreatedBy` was already lowercase and remains unchanged. FriendlyName, Description, Category, URLs, content flag, modules, loading phases, and all other descriptor fields are unchanged.

Product-facing changes are limited to the current version and release explanation in `README.md`, `Docs/UserGuide/index.md`, `Docs/UserGuide/Installation.md`, and the new 1.1.2 section in `Docs/UserGuide/ReleaseNotes.md`. The 1.1.1 history remains intact. No Open Source claim or license text was added.

Central documentation `server-manage-tool/index.md` was updated in its dedicated commit `963acf8279bc492824b9c8a9b5a924253cbe8755`. The published page returned HTTP 200 and contained Version 1.1.2, the 1.1.2 history entry, identity continuity, no behavior/API changes, the `TargetType.Server` limitation, and existing limitations.

## 7. BuildPlugin

Engine: Unreal Engine 5.8 installed build, Win64.

BuildPlugin result:

| Gate | Result |
| --- | --- |
| Authoritative exit code | 0 |
| `BUILD SUCCESSFUL` | 1 occurrence |
| UnrealEditor Win64 Development | PASS |
| UnrealGame Win64 Development | PASS |
| UnrealGame Win64 Shipping | PASS |
| UHT Category errors | 0 |
| Path-length errors | 0 |
| Plugin `Binaries/Win64` | present |
| Plugin `Source` | present |
| Final `.uplugin` | Version 4 / 1.1.2 |

Build log SHA-256: `6076A489BEC9CD2051AB655B5258EB46769157E332DDF39EF8B2EAFF3578CDA3`.

## 8. Candidate ZIP

The sanitized candidate was created from the BuildPlugin output without including repository metadata or `.mailmap`:

```text
C:\Users\Origin\Downloads\ServerManageTool-1.1.2-UE5.8-Win64.zip
```

| Property | Value |
| --- | ---: |
| SHA-256 | `C1A043C3388520446DAB93B40FEFD6CE0E05F87D94544BB28A14B98098601443` |
| ZIP bytes | 169,758 |
| Central-directory entries | 34 |
| File count | 34 |
| Uncompressed bytes | 350,308 |
| Root folder count | 1 (`ServerManageTool`) |

ZIP validation PASS: required top-level entries are present; traversal, encrypted entries, duplicate normalized names, wrong-root entries, PDBs, `Intermediate`, `Docs/Verification`, `.mailmap`, and license files are absent. The root `.uplugin` is correct.

## 9. ZIP Source notice check

The extracted candidate contains exactly 17 Source files. All 17 have the new lowercase `metyatech` notice; Epic notice count is 0 and Unreal placeholder count is 0. `.mailmap` is absent from the ZIP as required. No LICENSE was added.

## 10. Blueprint-only load

The new package was extracted into a new Blueprint-only UE 5.8 host with no C++ `Modules` property. Enabled plugins were `ServerManageTool`, `PythonScriptPlugin`, and `EditorScriptingUtilities`.

| Check | Result |
| --- | ---: |
| Product module loads | 3 |
| Missing modules | 0 |
| Incompatible modules | 0 |
| Compile requests | 0 |
| C++ conversion requests | 0 |
| Fatal/ensure/crash count | 0 |
| Parent exit code | 0 |
| Timeout / forced termination | false / false |
| Final host process count | 0 |

Blueprint-only load: PASS.

## 11. Normal PIE

The first attempt is retained as a disclosed harness timing observation: it exited normally with child maximum 2, preflight 1, validation failures 0, and final child/UDP 0, but one child validation marker arrived after the fixed hold window. The same gate was rerun once after confirming no process or UDP residue.

The acceptance rerun passed:

| Parent PID | Exit | Max child count | Preflight PASS | Validation PASS | Validation FAIL | Final child | Final UDP |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 32944 | 0 | 2 | 1 | 2 | 0 | 0 | 0 |

Normal PIE: PASS. No forced termination was used.

## 12. Simulate

| Parent PID | Exit | Max child count | Preflight PASS | Validation PASS | Validation FAIL | Final child | Final UDP |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 72124 | 0 | 2 | 1 | 2 | 0 | 0 | 0 |

Simulate: PASS. No timeout or forced termination.

## 13. ORPHAN regression

| Parent PID | Exit | Max child count | Preflight PASS | Validation PASS | Validation FAIL | Final child | Final UDP |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 58068 | 0 | 2 | 1 | 2 | 0 | 0 | 0 |

The harness continued its post-parent monitoring window and found no matching child or UDP owner. ORPHAN: PASS.

## 14. 7778 conflict regression

An independent exclusive UDP holder owned port 7778 before the PIE run. The holder remained alive and retained its endpoint while the plugin rejected the launch.

| Check | Result |
| --- | ---: |
| Holder PID | 10560 |
| Parent PID | 70808 |
| `SMT_PORT_PREFLIGHT_FAILED` | 1 |
| unavailable port 7778 | PASS |
| managed child maximum | 0 |
| shifted child count | 0 |
| holder alive before planned cleanup | true |
| holder endpoint before cleanup | 1 |
| holder alive after planned cleanup | false |
| holder UDP endpoint after cleanup | 0 |
| forced termination | false |

Conflict regression: PASS. Existing classification remains `EDITOR_STATUS_INCONSISTENT` and `PARTIAL_PACKAGED_TEST_BLOCKED`; this release does not alter that classification.

## 15. Pre-release pending items

At the moment this report is committed, the following publication operations are intentionally still pending:

- push product `master` and verify divergence `0 0`;
- create annotated tag `v1.1.2` on this final report commit;
- publish GitHub Release `Server Manage Tool 1.1.2`;
- attach `ServerManageTool-1.1.2-UE5.8-Win64.zip` and byte-for-byte `ServerManageTool-Fab-Current.zip`;
- verify authenticated-free versioned and `releases/latest` download URLs and asset SHA equality.

Fab input or submission is not performed.

## 16. Evidence manifest

Evidence is stored only below the temporary audit root, outside Git. The final `Evidence-SHA256.txt` manifest is generated after release postflight and includes build, package, source, identity, runtime, web, tag, release, and download evidence. Its final path and SHA-256 are supplied in the final handoff.

## 17. Final Git and release reproduction commands

```powershell
$Root = 'D:\T\SMT112-<timestamp>'
$Plugin = Join-Path $Root 'ServerManageToolPlugin'
$Docs = Join-Path $Root 'unreal-plugin-docs'
$UE = 'C:\Program Files\Epic Games\UE_5.8'

git -C $Plugin fetch origin --tags
git -C $Docs fetch origin --tags
git -C $Plugin diff --check
git -C $Plugin diff HEAD^ HEAD -- Source
& "$UE\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin `
  "-Plugin=$Plugin\ServerManageTool.uplugin" `
  "-Package=$Root\BuildPlugin\Package" `
  -TargetPlatforms=Win64 `
  -Rocket

py -3 "$Root\Scripts\ValidateFinalZip.py" `
  --zip 'ServerManageTool-1.1.2-UE5.8-Win64.zip' `
  --extract-root "$Root\CandidateExtract" `
  --evidence-root "$Root\Evidence\Zip"

pwsh -NoLogo -NoProfile -File "$Root\Runtime\Scripts\RunBlueprintOnlyCleanExit.ps1"
pwsh -NoLogo -NoProfile -File "$Root\Runtime\Scripts\RunNormalLifecycle.ps1" -Mode PIE
pwsh -NoLogo -NoProfile -File "$Root\Runtime\Scripts\RunNormalLifecycle.ps1" -Mode SIMULATE
pwsh -NoLogo -NoProfile -File "$Root\Runtime\Scripts\RunNormalLifecycle.ps1" -Mode ORPHAN
pwsh -NoLogo -NoProfile -File "$Root\Runtime\Scripts\RunPortConflict.ps1"

git -C $Plugin push origin master
git -C $Plugin tag -a v1.1.2 -m 'Server Manage Tool 1.1.2'
git -C $Plugin push origin v1.1.2
gh release create v1.1.2 --repo metyatech/ServerManageToolPlugin `
  --title 'Server Manage Tool 1.1.2' `
  --notes-file "$Root\ReleaseNotes-1.1.2.md" `
  'ServerManageTool-1.1.2-UE5.8-Win64.zip' `
  'ServerManageTool-Fab-Current.zip'
```

## 18. Final release readiness

After the pending publication commands complete and their URL/hash postflight passes, the release status is:

```text
Provenance blocker: RESOLVED
Identity continuity: PASS
Copyright normalization: PASS
Source behavior changes: 0
Blueprint API changes: 0
Final BuildPlugin: PASS
Final candidate ZIP: PASS
Fab submission readiness: READY_WITH_DISCLOSED_LIMITATIONS
Fab submission: not performed
```
