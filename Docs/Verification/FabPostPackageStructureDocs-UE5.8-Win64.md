# Fab Package Structure and Documentation Verification — UE 5.8 Win64

> Superseded for the current Fab submission candidate by
> `FabPostContentPackLayout-UE5.8-Win64.md`.
>
> The candidate documented below used `Content/Documentation`. Its build,
> runtime, documentation, and ZIP evidence is retained as historical evidence,
> but that ZIP is no longer the current submission candidate. The current
> candidate uses `Content/ServerManageTool/Documentation`.

Verification date: 2026-07-27 (JST)
Verification root: D:\T\SMTFAB-20260727-153034

## 1. Scope and verdict

This audit adds Fab package structure and user documentation for Server Manage Tool 1.1.0. Product source logic is unchanged.

| Area | Verdict |
| --- | --- |
| Fab package structure | PASS |
| User documentation | PASS |
| Existing port-conflict implementation | PARTIAL_PACKAGED_TEST_BLOCKED (preserved) |
| Product readiness | FAIL |

Fab submission was not performed. Remaining product blockers are real game-project Development/Shipping integration, packaged executable behavior, requested exit-status propagation, EDITOR_STATUS_INCONSISTENT, and PARTIAL_PACKAGED_TEST_BLOCKED.

## 2. Official Fab structure target

The candidate ZIP contains exactly one root folder, ServerManageTool/, with Binaries, Config, Content, Docs, Resources, Source, README.md, and ServerManageTool.uplugin. Build Intermediate, PDBs, repository metadata, saved data, temporary harness files, and Docs/Verification are excluded.

Config/FilterPlugin.ini contains exactly /Config/..., /Content/Documentation/..., /Docs/UserGuide/..., and /README.md under one [FilterPlugin] section.

## 3. Start Git states

Central docs pre-sync: D:\ghws\unreal-plugin-docs, branch main, clean, local e8000d6d24e2af8f7d3894c6724427b93a72bc1f, remote https://github.com/metyatech/unreal-plugin-docs.git, remote main 7792a8930e6b4f61967aa4ffaa3f3c0f706c0342.

The requested git fetch origin followed by git merge --ff-only origin/main fast-forwarded one commit (e8000d6..7792a89). Merge commit, reset, rebase, and stash: none. After sync local and origin/main were 7792a8930e6b4f61967aa4ffaa3f3c0f706c0342, divergence 0 0, and the working tree was clean.

Plugin pre-task: branch fix/editor-delegate-cleanup, local/remote 04351188acc3e0c7f371ce13ac04ae382f9bca8e, divergence 0 0, clean. UE root C:\Program Files\Epic Games\UE_5.8, Build.version 5.8, InstalledBuild present. Created feat/fab-package-structure-docs from that exact HEAD.

## 4. Exact plugin changes

Commit 1: adfc6c179a1d54d5ca0f3d773eff1802e3cf322a — feat: add Fab package structure and metadata; files: ServerManageTool.uplugin, Config/FilterPlugin.ini, Content/Documentation/QuickStart.txt.

Commit 2: 963e090df95ddd2dd31c33d8586c6efababd5a47 — docs: add Server Manage Tool user guide; files: README.md and seven Docs/UserGuide pages.

No Source/**, Resources/**, .github/**, or protected verification report changed.

## 5. .uplugin metadata

JSON parse passed. Source values: Version=2, VersionName=1.1.0, Category=Networking, CreatedBy=Metyatech, CreatedByURL=https://github.com/metyatech, requested DocsURL and SupportURL, MarketplaceURL empty, and CanContainContent=true. Module definitions and protected version flags were preserved. BuildPlugin-generated EngineVersion/Installed changes exist only in package output.

## 6. Config

Config/FilterPlugin.ini passed exact-content validation and includes Config, Content documentation, user guide, and root README only. Docs/Verification is excluded.

## 7. Content

Content/Documentation/QuickStart.txt is non-empty English documentation containing product name, online/package docs paths, Project Settings, Server Mode, Get Server Address, Request Server Exit, 7777/list-order assignment, UDP preflight, no partial launch, and the production-server limitation. No unrelated asset or dummy .uasset was added.

## 8. Packaged user documentation

Seven pages exist: index.md, Installation.md, Configuration.md, BlueprintAPI.md, LocalLaunch.md, Troubleshooting.md, and ReleaseNotes.md. They contain the required overview, ten-step quick start, child links, installation/configuration/API/lifecycle/troubleshooting/version content.

README contains all required sections and explicitly documents Editor/PIE-only Local Launch, fixed 7777/list order, all entries, no automatic client connection, existing -server requirement, no production build/deploy/hosting, no OS exit-code guarantee, and unverified packaged executable behavior.

## 9. Central online documentation

Central commit 8ccbc33de99e5a00de0521cba24a536e73f830a2 (docs: update server manage tool for 1.1.0) changed only server-manage-tool/index.md and was pushed to origin/main.

URL https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/: HTTP 200; title Server Manage Tool | metyatech Unreal Engine Plugins; page-specific H1 Server Manage Tool found once; 1.1.0, UDP preflight, and all-or-nothing text present; stale phrase count 0; 404/not-found match 0.

## 10. BuildPlugin

Package: D:\T\SMTFAB-20260727-153034\BuildPluginPackage. Log: D:\T\SMTFAB-20260727-153034\BuildPlugin.log.

Exit code 0; UnrealEditor Win64 Development, UnrealGame Win64 Development, and UnrealGame Win64 Shipping all PASS; UHT Category errors 0; path-length errors 0; BUILD SUCCESSFUL present. Build log SHA-256: FCB3BE42DDB2622FFCF083784F9304DD35CE8910B125F514E9B7C1B629852148.

## 11. BuildPlugin package structure

Top-level: Binaries, Config, Content, Docs, Intermediate, README.md, Resources, Source, and ServerManageTool.uplugin. Required package paths exist; Docs/Verification, .git, .github, Saved, DerivedDataCache, and .vs do not. Build-only Intermediate/PDB files are removed by sanitization. Package descriptor has Version 2, VersionName 1.1.0, CanContainContent true, DocsURL, SupportURL, and all modules.

## 12. Blueprint-only clean load

Direct BuildPlugin package in new HostBuildPlugin with no C++ Modules property: PASS. Parent PID 10952, exit 0, three product module loads, missing/incompatible/compile/C++ conversion/fatal-ensure-crash counts all 0, timeout/forced termination false, final host process 0.

## 13. Normal PIE regression

PASS. Parent PID 59756, exit 0; children 54856 on requested/actual 7777/7777 and 57004 on 7778/7778, both ParentProcessId 59756; preflight PASS 1; validation PASS 2; validation FAIL 0; maximum child 2; EndPIE child 0; forced cleanup false; final UDP 0.

## 14. 7778 conflict regression

PASS for preflight-only acceptance. Holder PID 59444 exclusively held 7778; editor parent PID 43112; SMT_PORT_PREFLIGHT_FAILED once naming 7778; started_server_count=0; managed/shifted child counts 0; 7777 child not started; holder protected; planned cleanup left holder process/UDP 0; forced cleanup false.

Existing exit-status verification was not rerun or reclassified. Preserved classifications: EDITOR_STATUS_INCONSISTENT and PARTIAL_PACKAGED_TEST_BLOCKED.

## 15. Candidate sanitize

D:\ghws\fab-plugin-release-tools was clean but its schema requires Content/<PluginName> pack mode, incompatible with the requested Content/Documentation layout; adding its config would exceed allowed files. It was not changed or used.

Temporary sanitize produced D:\T\SMTFAB-20260727-153034\Candidate\ServerManageTool. PASS: exact eight top-level entries, 34 files, 348807 bytes, forbidden remaining entries 0.

## 16. Candidate ZIP

Output: C:\Users\Origin\Downloads\ServerManageTool-1.1.0-UE5.8-Win64.zip.

PASS: parse succeeded; root exactly ServerManageTool/; 34 entries/files; 348807 uncompressed bytes; 169045 ZIP bytes; nested ZIP, encrypted/password, traversal, duplicate normalized path, PDB, verification report, and repository metadata counts all 0.

ZIP SHA-256: 9B4F6353A1CFD5F9F995188E6082BCEDDA7F37384C58F707E49EA01FD4F75539.

## 17. Candidate ZIP re-extraction test

ZIP extracted to D:\T\SMTFAB-20260727-153034\CandidateExtract and loaded by separate Blueprint-only HostCandidateZip with no C++ Modules property. PASS: parent PID 68792, exit 0, three module loads, all missing/incompatible/compile/C++ conversion/fatal-ensure-crash counts 0, timeout/forced termination false, final host process 0.

## 18. Documentation validation

README, seven user-guide pages, and central target passed relative-link, duplicate-heading, empty-section, local Windows path, verification-root, PID, and SHA evidence checks. Broken local links 0; stale phrases 0. Existing protected Docs/Verification reports were neither changed nor packaged.

## 19. Process cleanup

Selection required recorded PID, expected Unreal executable, host .uproject command-line match, and -server for managed children. Final target Unreal process count 0, holder process count 0, UDP 7777/7778 endpoint count 0; no forced cleanup or unrelated termination.

## 20. Remaining blockers

Closed: Fab Config insufficiency, Fab Content insufficiency, and user documentation insufficiency.

Remaining Product readiness blockers: real game-project Development/Shipping integration unverified; packaged executable unverified; requested exit-status propagation unresolved; EDITOR_STATUS_INCONSISTENT; PARTIAL_PACKAGED_TEST_BLOCKED.

## 21. Evidence SHA-256

Complete manifest: D:\T\SMTFAB-20260727-153034\Evidence-SHA256.txt, containing 355 temporary evidence records. Manifest SHA-256: 0A001DEFEBFDBA1CF4FD20BFE3CB58392E87A6BB39557F33BAA577452DE9DF42.

| Artifact | SHA-256 |
| --- | --- |
| Source .uplugin | CB467CA7859A6098C9D740B23794AEAD3FBCF5EF07A3DE2A7AD0E1CA371C91F1 |
| Package .uplugin | AAF290E60209BC8E29C195F61A07D6C03C3554C7D6CC1A95AA5A5B07CDFC4607 |
| Content/Documentation/QuickStart.txt | 9EDB393242C7C09212163E64AF3DAA797B343B9BB75FBCD10372DAC6A56F1A27 |
| README.md | A46CF3C56A4AFFF84C812ED45E00784DFE1021303E499197B637780563786FB6 |
| Docs/UserGuide/index.md | 5F6EB2436DEE10606416A5E7A64BC9C46DEE7E14B7BA80024999C38F698B83A5 |
| Docs/UserGuide/Installation.md | 884D0D41B61D448B5EE2647656FDE20EA8B49ADEBFE41567B324806F530467E9 |
| Docs/UserGuide/Configuration.md | 6B8A16891A4298367D98B9E7840D00F10A09477256291DB3FB8980DB1319A4DF |
| Docs/UserGuide/BlueprintAPI.md | 24BE9A5E09B878347BDF1360B940CD83C54821779277464E6D13F72248F5130C |
| Docs/UserGuide/LocalLaunch.md | 94795C2D99D8D0CD230229CC12D46A22B02852F405A2CA9A4BD638EC4ED2F804 |
| Docs/UserGuide/Troubleshooting.md | E1F5AA113C935E217C6EC82ABAF46BF799E86A3043A71B38B8E10F5F27B67041 |
| Docs/UserGuide/ReleaseNotes.md | BC691CD6A824AE12DE553AC3C6F3E2D1A8FD82B8A71E3BE4370A511C780364A0 |
| Central index.md | F7A63B0189CE6ABE2FC1FD63E9513052E611D041A4C83B5B08428A18BE9E03C9 |
| Candidate ZIP | 9B4F6353A1CFD5F9F995188E6082BCEDDA7F37384C58F707E49EA01FD4F75539 |

## 22. Exact reproduction commands

Central sync: git -C D:\ghws\unreal-plugin-docs fetch origin; git -C D:\ghws\unreal-plugin-docs merge --ff-only origin/main.

Plugin branch: git -C D:\ghws\ServerManageToolPlugin switch -c feat/fab-package-structure-docs.

BuildPlugin: UE 5.8 RunUAT BuildPlugin with Plugin D:\ghws\ServerManageToolPlugin\ServerManageTool.uplugin, Package D:\T\SMTFAB-20260727-153034\BuildPluginPackage, TargetPlatforms Win64, and Rocket; log D:\T\SMTFAB-20260727-153034\BuildPlugin.log.

Runtime: pwsh -NoProfile -File D:\T\SMTFAB-20260727-153034\RunBlueprintOnlyCleanExit.ps1; pwsh -NoProfile -File D:\T\SMTFAB-20260727-153034\RunNormalLifecycle.ps1 -Mode PIE; pwsh -NoProfile -File D:\T\SMTFAB-20260727-153034\RunPortConflict.ps1.

Sanitize/ZIP: pwsh -NoProfile -File D:\T\SMTFAB-20260727-153034\SanitizeCandidate.ps1 with BuildPluginPackage and Candidate\ServerManageTool; pwsh -NoProfile -File D:\T\SMTFAB-20260727-153034\CreateCandidateZip.ps1 with Candidate and the requested Downloads ZIP; Expand-Archive to D:\T\SMTFAB-20260727-153034\CandidateExtract; run RunCandidateCleanLoad.ps1.

## 23. Final Git states

Central docs: branch main, local/remote HEAD 8ccbc33de99e5a00de0521cba24a536e73f830a2, divergence 0 0, working tree clean, pushed to origin/main.

Plugin before Commit 3: branch feat/fab-package-structure-docs, Commit 1 adfc6c179a1d54d5ca0f3d773eff1802e3cf322a, Commit 2 963e090df95ddd2dd31c33d8586c6efababd5a47, source diff 0, prohibited diff 0, working tree clean before adding this report.

Commit 3 uses docs: verify Fab package structure and documentation and contains only this report. Its final SHA, pushed plugin HEAD, final divergence, and final clean tree are supplied in the delivery handoff because inserting a commit's own SHA would require an amend or fourth commit.

Required final plugin state: remote origin/feat/fab-package-structure-docs, remote HEAD at Commit 3, divergence 0 0, clean working tree, no force push, merge, rebase, tag, release, PR, or Fab submission.
