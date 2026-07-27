# Server Manage Tool 1.1.0 Release Audit — UE 5.8 Win64

Verification date: 2026-07-27 JST

## 1. Scope and final decision

This release audit integrates the verified real-game packaging branch into a
release branch, rebuilds the plugin with Unreal Engine 5.8, creates a
sanitized final candidate ZIP, validates a re-extracted Blueprint-only host,
and runs Normal PIE and 7778 conflict smoke tests.

Final decision:

- Release branch integration — PASS
- Master integration — PENDING until push
- Final BuildPlugin — PASS
- Final Fab candidate ZIP — PASS
- Public project file link — PENDING until GitHub Release
- Fab submission readiness — READY_WITH_DISCLOSED_LIMITATIONS

No product feature or implementation change was made during this release
operation. No Fab submission was performed.

## 2. Start Git state

Existing checkout was checked without changing it:

- Repository: D:\ghws\ServerManageToolPlugin
- Remote: https://github.com/metyatech/ServerManageToolPlugin
- Current branch: verify/real-game-packaging
- Local HEAD: ec69903ce95257be02a21020b37fca04ff04b0b1
- origin/verify/real-game-packaging:
  ec69903ce95257be02a21020b37fca04ff04b0b1
- origin/master: b8373fb9d39da8ebc5bf51dd668f5b9bf3f19c1b
- Existing checkout divergence: 0 0
- Existing checkout working tree: clean
- Existing checkout stash count: 0
- Merge base: 67cae225ff9d616f3bac4709dc951ba7a829cdd2
- Verification branch ahead of merge base: 23 commits
- Master ahead of merge base: 1 independent commit
- Master independent commit: docs: use central plugin documentation
- v1.1.0 local tag at start: absent

All release work was performed in:

D:\T\SMTREL-20260727-184114\repo

## 3. Master divergence

The release clone was created from GitHub and fetched with tags and prune.
The fetched refs matched the required start state:

- origin/master: b8373fb9d39da8ebc5bf51dd668f5b9bf3f19c1b
- origin/verify/real-game-packaging:
  ec69903ce95257be02a21020b37fca04ff04b0b1
- v1.1.0 tag: absent
- GitHub Release v1.1.0: absent
- Clone working tree: clean

## 4. Release merge

Release branch:

- Branch: release/1.1.0
- Start HEAD: b8373fb9d39da8ebc5bf51dd668f5b9bf3f19c1b
- Start tree: 314d0f6b9a43fc18e14b63f3936e20e9fe3f2655

The verified branch was merged with a normal no-ff merge. The only conflicts
were the explicitly permitted README.md and ServerManageTool.uplugin files.
Both were resolved by taking the verification branch side.

- README conflict resolution: verification branch version selected
- ServerManageTool.uplugin conflict resolution: verification branch version selected
- Other conflicts: 0
- Unmerged paths: 0
- Cached diff check: PASS

## 5. Tree identity proof

Before the merge commit:

- Index tree: 35b4004ddd9de25b13b436ae27021f5ceaf56792
- Verification tree: 35b4004ddd9de25b13b436ae27021f5ceaf56792
- Index equals verification tree: PASS

Merge commit:

- SHA: 5dff3f3c1360ffc594fc9e2d87a3545e928b2e67
- Parent 1: b8373fb9d39da8ebc5bf51dd668f5b9bf3f19c1b
- Parent 2: ec69903ce95257be02a21020b37fca04ff04b0b1
- Tree: 35b4004ddd9de25b13b436ae27021f5ceaf56792
- Verification tree equals merge tree: PASS
- Verification branch is an ancestor: PASS
- Master start commit is an ancestor: PASS
- git diff origin/verify/real-game-packaging..release/1.1.0: 0

The final product tree is therefore byte-for-byte identical to the verified
branch tree. Product Source additional changes: 0.

Descriptor validation after merge:

- Version: 2
- VersionName: 1.1.0
- Category: Networking
- CanContainContent: true
- DocsURL: https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/
- SupportURL: https://github.com/metyatech/ServerManageToolPlugin/issues
- MarketplaceURL: empty

README central documentation URL: present.

## 6. Included implementation history

The release contains the complete verified branch history, including the
previous category, port conflict, package structure, content pack layout,
delegate cleanup, and real C++ game integration verification commits.

No implementation commit was created during this release operation.

## 7. Final BuildPlugin

Environment:

- Unreal Engine root: C:\Program Files\Epic Games\UE_5.8
- Build.version MajorVersion: 5
- Build.version MinorVersion: 8
- InstalledBuild.txt: present
- RunUAT.bat: present
- UnrealEditor.exe: present

Build output:

- Log: D:\T\SMTREL-20260727-184114\Build\BuildPlugin.log
- Package: D:\T\SMTREL-20260727-184114\Build\BuildPluginPackage
- Final authoritative exit code: 0
- BUILD SUCCESSFUL: 1
- AutomationTool ExitCode=0: 1
- UnrealEditor Win64 Development: succeeded
- UnrealGame Win64 Development: succeeded
- UnrealGame Win64 Shipping: succeeded
- UHT error count: 0
- Category error count: 0
- Path-length error count: 0
- Final .uplugin: present
- Binaries: present
- Source: present

The first attempt ended with exit code 10 because a transient
UnrealBuildTool mutex instance conflicted after the Editor target. No
UnrealBuildTool process remained, and the same gate was rerun without source
changes. The second run is the authoritative PASS.

## 8. Final package structure

BuildPlugin output contained:

- Binaries
- Config
- Content
- Docs
- Intermediate
- README.md
- Resources
- Source
- ServerManageTool.uplugin

The descriptor and package source were validated before sanitization. The
candidate ZIP intentionally excludes BuildPlugin Intermediate output and PDB
files.

## 9. Final candidate sanitize

The read-only release-tools checkout was verified clean:

- Path: D:\ghws\fab-plugin-release-tools
- Branch: master
- HEAD: a04dcfffc8c59ca12d87334e8e0e6302c27c82c7
- Working tree: clean
- Tool repository modifications: 0

The release tool could not be run because the plugin repository does not
contain its required FabPluginRelease.json configuration. The documented
temporary PowerShell fallback was used:

D:\T\SMTREL-20260727-184114\Scripts\SanitizeAndPackage.ps1

Sanitized candidate:

D:\T\SMTREL-20260727-184114\Candidate\ServerManageTool

Candidate top-level is exactly:

- Binaries
- Config
- Content
- Docs
- README.md
- Resources
- Source
- ServerManageTool.uplugin

Excluded from the candidate:

- Intermediate
- Saved
- DerivedDataCache
- .git
- .github
- .vs
- PDB files
- Docs/Verification

## 10. Final ZIP

Final candidate:

C:\Users\Origin\Downloads\ServerManageTool-1.1.0-UE5.8-Win64.zip

- File count: 34
- ZIP bytes: 169,126
- Uncompressed bytes: 348,918
- SHA-256: BA8420ADEA1CD4A0B3EAEA6DF35F16E269F4D06CCAD00E9C4614160BB4A2405D
- Root: ServerManageTool/
- Root folder count: 1
- Root .uplugin: present
- Content/ServerManageTool/Documentation/QuickStart.txt: present
- Old Content/Documentation path: absent
- Docs/Verification: absent
- PDB: 0
- Intermediate: 0
- Repository metadata: 0
- Duplicate normalized paths: 0
- Path traversal entries: 0
- Encrypted entries: 0
- Central directory count matches archive: PASS

Complete inventory:

D:\T\SMTREL-20260727-184114\Evidence\FinalZipInventory.txt

The previous Downloads ZIP was checked before replacement:

- Previous SHA-256: E2467EA57F54C8C591C04C229651B49C457071A3D26A2781C7D72855547FF914
- Backup: D:\T\SMTREL-20260727-184114\PreviousVerifiedCandidate.zip
- Backup SHA-256: E2467EA57F54C8C591C04C229651B49C457071A3D26A2781C7D72855547FF914

## 11. ZIP re-extraction load

The final ZIP was extracted to:

D:\T\SMTREL-20260727-184114\CandidateExtract

Blueprint-only host:

D:\T\SMTREL-20260727-184114\HostCandidate

The host .uproject has no C++ Modules property. Enabled plugins are
ServerManageTool, PythonScriptPlugin, and EditorScriptingUtilities.

Load result:

- Parent PID: 30432
- Parent exit code: 0
- Product module load count: 3
- ServerManageLibrary: 1
- ServerInfoSettingsModule: 1
- ServerModePlayMenu: 1
- Missing module count: 0
- Incompatible module count: 0
- Compile request count: 0
- C++ conversion request count: 0
- Fatal/ensure/crash count: 0
- Timeout: false
- Forced termination: false
- Final host process count: 0

Result: PASS.

## 12. Normal PIE smoke

The re-extracted candidate was installed into the Blueprint-only host. The
temporary host user settings selected SERVER_LocalLaunch.

- Parent PID: 50156
- Parent exit code: 0
- Preflight PASS count: 1
- Child PIDs: 72352 and 70368
- Child requested ports: 7777 and 7778
- Child actual ports: 7777 and 7778
- ParentProcessId: 50156 for both children
- Validation PASS count: 2
- Validation FAIL count: 0
- Maximum child count: 2
- EndPIE final child count: 0
- EndPIE final UDP owner count: 0
- Timeout: false
- Forced termination: false

Result: PASS.

## 13. 7778 conflict smoke

An independent exclusive UDP holder was bound to port 7778 before PIE.

- Holder PID: 61812
- Holder alive and endpoint present before cleanup: true / 1
- Parent PID: 1180
- Parent exit code: 0
- SMT_PORT_PREFLIGHT_FAILED count: 1
- unavailable port: 7778
- started server count: 0
- managed child count: 0
- shifted child count: 0
- Maximum child count: 0
- Forced termination: false
- Holder alive after planned cleanup: false
- Holder UDP endpoint after planned cleanup: 0
- Final child count: 0
- Final UDP owner count including planned holder cleanup: 0

Existing classifications remain unchanged:

- Editor exit-status — EDITOR_STATUS_INCONSISTENT
- Port conflict implementation — PARTIAL_PACKAGED_TEST_BLOCKED

Result: PASS for the preflight/no-partial-start smoke. The existing exit-status
classification was not re-run or changed.

## 14. Previously completed real-game integration

The prior verified report remains:

Docs/Verification/FabPostRealGamePackaging-UE5.8-Win64.md

That verification established:

- Real C++ game-project Development integration: PASS
- Real C++ game-project Shipping integration: PASS
- Packaged Development AddressAndExit: PASS
- Packaged Shipping AddressAndExit: PASS

Its disclosed dedicated Game-target limitation is retained. No TargetType.Server
target was added in this release operation.

## 15. Public documentation

Public documentation URL:

https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/

The descriptor DocsURL and README central documentation link both point to the
URL above. The final ZIP contains user documentation but does not contain
Docs/Verification.

## 16. Disclosed limitations

- Local Launch is Editor/PIE only.
- The project must already support its own server behavior.
- The plugin does not build, package, deploy, or host a production server.
- A dedicated TargetType.Server executable is not provided or verified.
- Do not rely on a specific operating-system exit code after shifted-port detection.
- Editor exit-status classification remains EDITOR_STATUS_INCONSISTENT.
- Port conflict implementation classification remains PARTIAL_PACKAGED_TEST_BLOCKED.

These are product-scope and documented limitations, not hidden release
blockers.

## 17. Fab submission readiness

Release branch integration — PASS.

Master integration — PENDING until the release branch fast-forward is pushed
to master.

Final BuildPlugin — PASS.

Final Fab candidate ZIP — PASS.

Public project file link — PENDING until the GitHub Release is published.

Fab submission readiness — READY_WITH_DISCLOSED_LIMITATIONS.

Fab submission: not performed.

## 18. Evidence SHA-256

Complete evidence manifest:

D:\T\SMTREL-20260727-184114\Evidence-SHA256.txt

- Temporary evidence file count: 290
- Manifest bytes: 49,347
- Manifest SHA-256: C5F792EABBC6521FED9447FADBA3DD961FCB9C7A07A3D1AA595B9CEED29D238B

Selected evidence:

- Final ZIP: BA8420ADEA1CD4A0B3EAEA6DF35F16E269F4D06CCAD00E9C4614160BB4A2405D
- Previous ZIP: E2467EA57F54C8C591C04C229651B49C457071A3D26A2781C7D72855547FF914
- Final ZIP validation: see FinalZipValidation.json
- Final ZIP inventory: see FinalZipInventory.txt
- BuildPlugin log: see Build/BuildPlugin.log
- Blueprint-only summary: see Evidence/BlueprintOnlyCleanExit.summary.json
- Normal PIE summary: see Scripts/Normal-PIE.summary.json
- 7778 conflict summary: see Scripts/PortConflict.summary.json

## 19. Exact reproduction commands

From the temporary release clone:

    git -C D:\T\SMTREL-20260727-184114\repo fetch origin --tags --prune
    git -C D:\T\SMTREL-20260727-184114\repo switch -c release/1.1.0 origin/master
    git -C D:\T\SMTREL-20260727-184114\repo merge --no-ff --no-commit origin/verify/real-game-packaging
    git -C D:\T\SMTREL-20260727-184114\repo checkout --theirs -- README.md ServerManageTool.uplugin
    git -C D:\T\SMTREL-20260727-184114\repo add README.md ServerManageTool.uplugin
    git -C D:\T\SMTREL-20260727-184114\repo commit -m "release: integrate Server Manage Tool 1.1.0"

Final BuildPlugin:

    RunUAT.bat BuildPlugin -Plugin=D:\T\SMTREL-20260727-184114\repo\ServerManageTool.uplugin -Package=D:\T\SMTREL-20260727-184114\Build\BuildPluginPackage -TargetPlatforms=Win64 -Rocket

Sanitize and package:

    pwsh -NoLogo -NoProfile -File D:\T\SMTREL-20260727-184114\Scripts\SanitizeAndPackage.ps1 -BuildPackageRoot D:\T\SMTREL-20260727-184114\Build\BuildPluginPackage -CandidateRoot D:\T\SMTREL-20260727-184114\Candidate\ServerManageTool -ZipPath D:\T\SMTREL-20260727-184114\CandidateZip\ServerManageTool-1.1.0-UE5.8-Win64.zip

ZIP validation and re-extraction:

    pwsh -NoLogo -NoProfile -File D:\T\SMTREL-20260727-184114\Scripts\ValidateFinalZip.ps1 -ZipPath C:\Users\Origin\Downloads\ServerManageTool-1.1.0-UE5.8-Win64.zip -ExtractRoot D:\T\SMTREL-20260727-184114\CandidateExtract -EvidenceRoot D:\T\SMTREL-20260727-184114\Evidence
    pwsh -NoLogo -NoProfile -File D:\T\SMTREL-20260727-184114\Scripts\RunBlueprintOnlyCleanExit.ps1
    pwsh -NoLogo -NoProfile -File D:\T\SMTREL-20260727-184114\Scripts\RunNormalLifecycle.ps1 -Mode PIE
    pwsh -NoLogo -NoProfile -File D:\T\SMTREL-20260727-184114\Scripts\RunPortConflict.ps1

## 20. Final Git/tag/release state

At report creation, before the release branch push, tag, and GitHub Release:

- Release merge commit: 5dff3f3c1360ffc594fc9e2d87a3545e928b2e67
- Release report commit: PENDING
- release/1.1.0 remote push: PENDING
- master fast-forward push: PENDING
- v1.1.0 annotated tag: PENDING
- GitHub Release: PENDING
- Public asset URL: PENDING

The final handoff records the release report commit, final master and release
branch SHA, tag target, GitHub Release URL, public asset URL, and anonymous
download hash. This report is not included in the candidate ZIP.
