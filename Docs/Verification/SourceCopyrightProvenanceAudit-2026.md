# Server Manage Tool Source Copyright and Provenance Audit — 2026

## 1. Scope

This audit covers the current `Source/**` tree of `metyatech/ServerManageToolPlugin` at `bace78ef851a3dc29be79fa709e073363bfa1b50`, before Fab submission. It inventories source files, records notices and hashes, follows Git history and blame, compares the implementation with the locally installed Unreal Engine 5.8 templates, searches public code for distinctive markers, scans dependencies and packaged binaries, and proposes—but does not apply—copyright changes.

The audit intentionally changed no product source, header, configuration, content, plugin metadata, README, user guide, release, tag, or asset. The only repository change from this task is this report.

**Final verdict: `BLOCKED_MANUAL_PROVENANCE_CONFIRMATION_REQUIRED`**

The blocking fact is historical provenance: all 17 current Source files descend from a bulk import authored and committed by `Udon-Tobira`, while the repository has no explicit license, rights-transfer record, or redistribution permission. No third-party dependency or copied implementation was identified, but absence of a public-code match is not rights evidence.

## 2. Start Git state

The pre-existing checkout was inspected read-only and was not used for edits:

| Checkout | Branch | HEAD | Working tree |
| --- | --- | --- | --- |
| Existing `D:\ghws\ServerManageToolPlugin` | `verify/real-game-packaging` | `ec69903ce95257be02a21020b37fca04ff04b0b1` | clean |
| Fresh audit clone | `master` | `bace78ef851a3dc29be79fa709e073363bfa1b50` | clean |

The audit clone remote is `https://github.com/metyatech/ServerManageToolPlugin.git`. At the start, `HEAD` and `origin/master` were both `bace78ef851a3dc29be79fa709e073363bfa1b50`, with divergence `0 0`. The clone was made below the task temporary root; no reset, force operation, or existing-checkout mutation was used.

The `v1.1.0` tag resolves to `ee76633b85885adeda88cb159b52e5f84a562eff`, and `v1.1.1` resolves to the audit HEAD. Existing releases were read-only checked: both are published, non-draft, non-prerelease releases. Their assets were not changed.

## 3. Audit limitations

Git records authorship and commit identity, not copyright ownership, employment status, assignment, or permission to redistribute. The initial Source import is a single bulk commit, so Git alone cannot establish whether the imported implementation was independently authored, derived from a sample, or transferred to `metyatech`.

The installed UE 5.8 build has no `Samples` directory at either `<UE_ROOT>\Samples` or `<UE_ROOT>\Engine\Samples`; comparison therefore uses the installed Plugin Browser and Editor template files and targeted Engine-tree searches. Public GitHub code search and web search are indexing-dependent and cannot prove that no private, deleted, unindexed, or non-public source exists. No full Source or Engine tree was copied into the evidence set.

## 4. Source inventory

The inventory found 17 files matching the requested extensions: 7 `.cpp`, 7 `.h`, and 3 `.Build.cs` files, totaling 871 lines. No `.hpp`, `.c`, `.cc`, `.inl`, or `Target.cs` files are present under `Source/**`.

The complete machine-readable inventory is `source-inventory.json`; the review-friendly export is `source-inventory.csv`. Each row records relative path, SHA-256, line count, first non-empty line, current notice, `git log --follow` introducing commit, author and committer, dates, history authors/committers, blame line counts, classification, and recommendation.

## 5. Header summary

| Current first-line/header state | Count |
| --- | ---: |
| Unreal placeholder (`Fill out your copyright notice...`) | 8 |
| Epic notice (`Copyright Epic Games, Inc. All Rights Reserved.`) | 9 |
| `metyatech` notice | 0 |
| Other notice | 0 |
| No notice | 0 |

The placeholder and Epic notice are treated as template/header observations only. Neither is treated as proof that the implementation belongs to Epic or `metyatech`.

## 6. Git history and contributors

All 17 current files trace through `git log --follow --diff-filter=A --reverse` to:

- commit `20a50146d4bad4e872aeb7578d4315ee93590ad9`, `add ServerModePlayMenu`;
- author and committer `Udon-Tobira <146440502+Udon-Tobira@users.noreply.github.com>`;
- author and commit date `2024-11-20T12:08:16+09:00`;
- a bulk addition of 23 files and 799 lines, including the earlier `ServerModeLibrary` lineage.

The later history contains renames from `ServerModeLibrary` to `ServerInfoLibrary` and then `ServerManageLibrary`, map/settings fixes, `RequestServerExit`, UE 5.8 category fixes, port-conflict fail-fast changes, and editor delegate cleanup. There are no merge commits touching `Source/**`.

| Author identity | Source-touching commits | Current Source files touched | First author date | Last author date | Login / rights finding |
| --- | ---: | ---: | --- | --- | --- |
| `Udon-Tobira <146440502+Udon-Tobira@users.noreply.github.com>` | 10 | 17 | 2024-11-20 | 2025-02-25 | GitHub user lookup was unresolved; no transfer or license evidence in Git |
| `metyatech <metyatech@gmail.com>` | 4 | 10 | 2026-07-23 | 2026-07-27 | GitHub login `metyatech` resolves to `https://github.com/metyatech`; no historical rights transfer is recorded |

The contributor evidence is in `contributors.json`; the complete history, initial-file evidence, rename evidence, shortlog, and merge check are in `git-history-summary.txt`. Because a non-`metyatech` contributor is present and is not resolved to a known rights record, every current file is conservatively class F.

## 7. Unreal template comparison

The comparison used files under `C:\Program Files\Epic Games\UE_5.8\Engine`, including the Plugin Browser `Basic` and `BlueprintLibrary` templates and the Editor `PluginModule` templates. It did not alter the engine and did not copy the engine source.

| Product file | UE 5.8 template | Normalized similarity | Finding |
| --- | --- | ---: | --- |
| `ServerModePlayMenu.Build.cs` | Plugin Browser Basic Build.cs | 0.7416 | Standard UBT shape and Epic header; product module/dependency names are distinct |
| `ServerModePlayMenu.h` | Plugin Browser Basic module header | 0.4512 | Standard module boilerplate; product declarations are distinct |
| `ServerModePlayMenu.cpp` | Plugin Browser Basic module implementation | 0.0206 | Only minimal module/ToolMenus boilerplate overlaps |
| `ServerManageLibraryBP.h` | Plugin Browser Blueprint library header | 0.1877 | Standard Blueprint library shape |
| `ServerManageLibraryBP.cpp` | Plugin Browser Blueprint library implementation | 0.0150 | No substantive shared implementation |
| `ServerInfoSettingsModule.cpp` | Editor PluginModule template | 0.1015 | No shared non-empty lines in the comparison |
| `ServerInfoSettingsModule.Build.cs` | Editor PluginModule Build.cs template | 0.2743 | Generic UBT structure only |

The raw paths, hashes, shared lines, and interpretation are in `unreal-template-comparison.json`. Similarity to generated plugin boilerplate is not treated as a third-party-derived implementation finding.

## 8. Epic code similarity findings

Targeted searches in the local UE 5.8 Engine tree found no matches for the distinctive product markers `SMT_PORT_PREFLIGHT_PASSED`, `SMT_PORT_PREFLIGHT_FAILED`, `SMT_SERVER_PROCESS_LAUNCH_FAILED`, `SMT_PORT_VALIDATION_PASSED`, `SMT_PORT_VALIDATION_FAILED`, `ServerManageExpectedPort`, `CanBindUdpPort`, `FServerModePlayMenuModule::OnBeginPIE`, `FServerModePlayMenuModule::OnEndPIE`, `ServerProcesses`, `RegisterSeverInfoSetting`, or `RequestServerExit`.

`GetServerAddress` had nine generic matches in WebRTC, Portal, Engine, and Avalanche files. This is an API-name collision, not evidence of copied Server Manage Tool logic; it requires no source attribution change by itself. The targeted comparison found no substantial Epic implementation reused by the product. The Epic header on nine files is retained pending the separate provenance decision.

## 9. Public-code similarity findings

GitHub code search covered the five `SMT_*` markers plus `ServerManageExpectedPort`, `CanBindUdpPort`, `FServerModePlayMenuModule`, `ServerProcesses.clear()`, `RegisterSeverInfoSetting`, `RequestServerExit`, `ServerMapSettingPtr`, and `FormatPorts`. Results were limited to this repository and `metyatech/unreal-plugin-docs`; no external repository result was found. The repository result example is [`ServerModePlayMenu.cpp`](https://github.com/metyatech/ServerManageToolPlugin/blob/bace78ef851a3dc29be79fa709e073363bfa1b50/Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp), and the documentation result is [`server-manage-tool/index.md`](https://github.com/metyatech/unreal-plugin-docs/blob/083a7db1f3e4c2635cc4fb3db670415b7024dde5/server-manage-tool/index.md).

The evidence file records query-by-query results and zero external repositories. GitHub search is not an originality guarantee: private, deleted, unindexed, or rate-limited content may be absent. No external code, license, date, or overlap could therefore be assigned from these searches.

## 10. Dependencies and third-party files

The repository scan found no `ThirdParty`, `External`, or `Vendor` directories, no repository `.dll`, `.lib`, `.a`, `.so`, or `.dylib`, and no root `LICENSE`, `NOTICE`, or `COPYING` file. The three Build.cs files reference only Unreal Engine standard modules and the two repository modules:

| Product module | Public dependencies | Private dependencies | Dynamic dependencies |
| --- | --- | --- | --- |
| `ServerInfoSettingsModule` | `Core` | `CoreUObject`, `Engine`, `Slate`, `SlateCore` | none |
| `ServerManageLibrary` | `Core`, `ServerInfoSettingsModule`, conditional `ServerModePlayMenu` | `CoreUObject`, `Engine`, `Slate`, `SlateCore`, `Sockets` | none |
| `ServerModePlayMenu` | `Core`, `ServerInfoSettingsModule` | `Projects`, `InputCore`, `EditorFramework`, `UnrealEd`, `ToolMenus`, `CoreUObject`, `Engine`, `Slate`, `SlateCore`, `Sockets` | none |

The inspected v1.1.1 package is `ServerManageTool-1.1.1-UE5.8-Win64.zip`, 169,563 bytes, SHA-256 `AFA1FEA37D289482051C880D735341083623FFEA1445F07346EBDE3D6BAA36F9`. Its module outputs are:

| Package entry | Bytes | SHA-256 |
| --- | ---: | --- |
| `UnrealEditor-ServerInfoSettingsModule.dll` | 70,144 | `8BB40E3FC65C3B1397D2ADB12208BADB7FFC1CC020EDFB14EA9A1C4387A7F9C7` |
| `UnrealEditor-ServerManageLibrary.dll` | 96,768 | `0F704C0E270B75BB5E901288734AE096DE887AF2997EF21082C0BECB9144DE28` |
| `UnrealEditor-ServerModePlayMenu.dll` | 122,880 | `CBFC486D49E4E66473A31A282702D7EEEBD9E60E6FD399A4810258AC996B754F` |
| `UnrealEditor.modules` | 256 | `A22450BB210DEB8BCDFC1DF22F28CCF81CA448406C813FAFFD69EC22BE689274` |

The package contains no license or notice entry. These are named UnrealEditor plugin module outputs, not evidence of an embedded third-party library. Full scan results are in `dependencies-and-license.json`.

## 11. Per-file classification table

Classification codes are the requested A–F scheme. `F` is used whenever the evidence is insufficient to approve ownership or derivation, even if the file resembles normal Unreal-generated boilerplate.

| Relative path | Lines | Current header | SHA-256 | Introducing commit | Introducing author | History commits | Class | Recommendation |
| --- | ---: | --- | --- | --- | --- | ---: | --- | --- |
| `Source/ServerInfoSettingsModule/Private/ServerInfoSettings.cpp` | 3 | placeholder | `A19F9C16411FD99E8A39DD74D24EC480EBE00A501FD79E40403712597FE312C1` | `20a5014` | Udon-Tobira | 1 | F | retain; review |
| `Source/ServerInfoSettingsModule/Private/ServerInfoSettingsModule.cpp` | 22 | Epic | `FBE59B9B5F9A294427EB925BFC99126AE572F65CDE8F29EB813163482003A7E0` | `20a5014` | Udon-Tobira | 1 | F | retain; review |
| `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h` | 32 | placeholder | `168482E573E3FC02AA3FCB96A4AA07127E3EBAE59256278BD6760766C86906D5` | `20a5014` | Udon-Tobira | 2 | F | retain; review |
| `Source/ServerInfoSettingsModule/Public/ServerInfoSettingsModule.h` | 14 | Epic | `8FD846E69AE525E23886D6BAD83D3CC56B81EF2FD2FBFF07A110082D8814ED9B` | `20a5014` | Udon-Tobira | 1 | F | retain; review |
| `Source/ServerInfoSettingsModule/ServerInfoSettingsModule.Build.cs` | 53 | Epic | `95FD200D3FCE23390339B8CE569EEFD0E50AA34381AD20298ED4BF6D9332EABC` | `20a5014` | Udon-Tobira | 1 | F | retain; review |
| `Source/ServerManageLibrary/Private/ServerManageLibrary.cpp` | 104 | Epic | `4D06734827ECD3B4260E2ECBD201E7AD4C1F8A86EE2933638CB4F0948985646A` | `20a5014` | Udon-Tobira | 8 | F | retain; review |
| `Source/ServerManageLibrary/Private/ServerManageLibraryBP.cpp` | 53 | placeholder | `DCA53B87139B74EF10D0FE6B2B73ED073DB84767DAFE0222AF8710F1D3FD0221` | `20a5014` | Udon-Tobira | 8 | F | retain; review |
| `Source/ServerManageLibrary/Public/ServerManageLibrary.h` | 22 | Epic | `BBEC1587967AD5F8F0AA0B601B64F1F837AB0BD97884A23D30A3FF0DB855EE1B` | `20a5014` | Udon-Tobira | 7 | F | retain; review |
| `Source/ServerManageLibrary/Public/ServerManageLibraryBP.h` | 26 | placeholder | `BA76C7871424DB4EEBCDF181FB3604F2AA0A8A41541309523D69A24926C0645C` | `20a5014` | Udon-Tobira | 8 | F | retain; review |
| `Source/ServerManageLibrary/ServerManageLibrary.Build.cs` | 60 | Epic | `C69143D5C06831A2ED6C55F2514A69DED491D31932ADDE3E757CA57B5F48AC1A` | `20a5014` | Udon-Tobira | 7 | F | retain; review |
| `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp` | 251 | Epic | `9F280D1142D027B5B67307CD5B417D7C1C19C4C25E72FC00E98CA666204BCDEC` | `20a5014` | Udon-Tobira | 6 | F | retain; review |
| `Source/ServerModePlayMenu/Private/ServerModeSetting.cpp` | 7 | placeholder | `40E602EE2A6F6542FBAE2A08BB92C079FBAB908D49B3295D8B57F99BF47CAB13` | `20a5014` | Udon-Tobira | 1 | F | retain; review |
| `Source/ServerModePlayMenu/Private/ServerProcess.cpp` | 69 | placeholder | `5F9958A560FBE1D4437622298D48686ABCBB84A5130276610E4B7C7F93EE77E5` | `20a5014` | Udon-Tobira | 2 | F | retain; review |
| `Source/ServerModePlayMenu/Private/ServerProcess.h` | 25 | placeholder | `05AB9A15C790B711BE636B6761D057B28FA4F0FD1105D5889C8508012AD61360` | `20a5014` | Udon-Tobira | 2 | F | retain; review |
| `Source/ServerModePlayMenu/Public/ServerModePlayMenu.h` | 33 | Epic | `6E81109D1214624A776CA9E1FB45D2E95504A30E412B7C3E30765623EF6BF828` | `20a5014` | Udon-Tobira | 3 | F | retain; review |
| `Source/ServerModePlayMenu/Public/ServerModeSetting.h` | 37 | placeholder | `711BD95DF4E103111DA87F585BB59787FA5A0E3E39AACA5DCC5B05482D0B113B` | `20a5014` | Udon-Tobira | 1 | F | retain; review |
| `Source/ServerModePlayMenu/ServerModePlayMenu.Build.cs` | 60 | Epic | `21BDC784AF379A4A871FB6E3353A754A2B8B24569FD1BA82F19B22169030C213` | `20a5014` | Udon-Tobira | 2 | F | retain; review |

Counts: A `0`, B `0`, C `0`, D `0`, E `0`, F `17`.

## 12. Manual-review questions

Fab submission should remain blocked until the rights owner answers these questions with durable evidence:

1. Who is `Udon-Tobira`, and did that person or organization author the initial 23-file import?
2. Was the imported implementation independently written, or derived from an Epic sample, template, tutorial, another repository, or employer-owned code?
3. If Udon-Tobira contributed code, is there a written assignment, employment-rights record, contributor agreement, or explicit redistribution permission to `metyatech`?
4. What license governs the Source and the packaged plugin, and does it explicitly permit commercial Fab distribution, modification, and redistribution?
5. Are the nine Epic notices intended only as Unreal-generated boilerplate, or do any files contain Epic-derived code requiring retention and attribution under a separate license?
6. Can the rights owner approve a file-by-file notice policy and a root/package license notice before submission?

Until these are answered, all 17 files remain `F` and no notice replacement is safe.

## 13. Proposed copyright patch

No patch was applied. The proposal is recorded in `proposed-copyright-patch.md`.

The safe-to-normalize set is empty. After manual rights confirmation, each approved `metyatech`-owned file may receive the exact C++ notice `// Copyright 2026 metyatech. All Rights Reserved.` (or the corresponding comment form for a future C# file). The current Epic and Unreal placeholder notices should be retained until that decision is documented. A blanket replacement is not recommended.

The 17 exact paths requiring individual review are the paths in Section 11. This audit did not alter any of them.

## 14. License state

The repository is public and source-accessible, but it is not confirmed open-source:

- root `LICENSE`, `NOTICE`, and `COPYING` files are absent;
- GitHub API reports `license: null` for `metyatech/ServerManageToolPlugin`;
- README contains no license grant or redistribution permission;
- the v1.1.1 package contains no license/notice entry;
- no explicit permission for commercial Fab use, copying, modification, or redistribution was found.

The inspected Build.cs dependencies are Unreal Engine standard modules plus the two repository modules; no repository-owned third-party dependency was found. This is a license gap, not evidence that the product is third-party code.

## 15. Fab submission impact

The source provenance and licensing state are a Fab submission blocker. Do not normalize or remove notices, add a `metyatech` copyright claim, or submit the package until the historical contribution and redistribution rights are confirmed. The audit did not find an independent third-party dependency license blocker, so the correct blocker category is manual provenance confirmation rather than third-party-license action.

## 16. Final decision

`BLOCKED_MANUAL_PROVENANCE_CONFIRMATION_REQUIRED`

Evidence supports these limited conclusions: no external public-code match was found for the distinctive markers; no third-party source or binary dependency was found; Unreal-generated boilerplate similarity is present; and all current Source files have a historical non-`metyatech` author. The evidence does not support a safe copyright-header normalization or a Fab redistribution approval.

## 17. Reproduction commands

Use a fresh temporary root and do not edit the existing checkout:

```powershell
$AuditRoot = Join-Path $env:TEMP 'SMT-CPAUDIT-<timestamp>'
$Repo = Join-Path $AuditRoot 'ServerManageToolPlugin'
$Evidence = Join-Path $AuditRoot 'Evidence'
git clone --branch master --single-branch https://github.com/metyatech/ServerManageToolPlugin.git $Repo
git -C $Repo fetch origin --tags
git -C $Repo status --short --branch
git -C $Repo rev-parse HEAD
git -C $Repo rev-parse origin/master
py -3 (Join-Path $AuditRoot 'Scripts\RunSourceInventory.py')
py -3 (Join-Path $AuditRoot 'Scripts\CompareUnrealTemplates.py')
git -C $Repo log --follow --diff-filter=A --reverse -- Source/<file>
git -C $Repo blame --line-porcelain -- Source/<file>
git -C $Repo shortlog -sne --all -- Source
gh search code 'SMT_PORT_PREFLIGHT_PASSED' --limit 100
gh search code 'ServerManageExpectedPort' --limit 100
gh api repos/metyatech/ServerManageToolPlugin --jq '{license:.license,visibility:.visibility,default_branch:.default_branch}'
Get-FileHash (Join-Path $env:USERPROFILE 'Downloads\ServerManageTool-1.1.1-UE5.8-Win64.zip') -Algorithm SHA256
```

The complete audit command list is in the temporary `Evidence/command-log.txt`. The evidence scripts and files are outside the repository and must not be added to Git.

## 18. Evidence hashes

Temporary evidence root: `Evidence/` under the audit root. The manifest contains 10 evidence files and excludes itself. Manifest SHA-256: `AA921F78B425966F2292469CEDA1958A31D084ADAEC376868B403B9E08AE1ACF`.

| Evidence file | SHA-256 |
| --- | --- |
| `command-log.txt` | `CC3C6151F2B0D2E218506945EC3AE9909B3859C84BBCA8B8D5D08C054D8B6FE6` |
| `contributors.json` | `1A6031CE42E0AA55D473AD9776F1927C13E6A16C82AFE493255A603A12BA4F28` |
| `dependencies-and-license.json` | `A4172CEA7AA06A16309407E20F71765B40B168925CE893B04D42ED4AB6307FA3` |
| `engine-environment.json` | `54F3AAE8DC67AB514DC0B5315981C4F87B3D839D5A56B54B244ABFCBF25A823A` |
| `git-history-summary.txt` | `868762CF6394493FA664E0872E04DCA9BC865FA353DB8BEC6DAC4CE854791CEC` |
| `proposed-copyright-patch.md` | `E4FF50E18727666CB4B46362F50C060EB5A9042BC801A94A15FB6698406FC08A` |
| `public-code-search.json` | `0FA8309AB8DA36A30F676B6608686E10F9987F829DB5D6084791BDCE6E2DBB20` |
| `source-inventory.csv` | `DF6A63DBFB4F22AB8C08C77B7A24D36090662EFAA0ECBE144DFA2E7877A0F2CF` |
| `source-inventory.json` | `054DCF27009D7E6369165F339FED7C836D84CD4C7167C4D50561C198ACA321F1` |
| `unreal-template-comparison.json` | `9B74151D21B06C6F497F3495F2D696FC6C83CA9FA687E8A82180DBC1F0282B90` |

The audit clone was checked with `git diff --check`; only this report is allowed to enter the repository. Source, Config, Content, plugin metadata, README, and user-guide diffs remain zero. Releases and tags remain unchanged.
