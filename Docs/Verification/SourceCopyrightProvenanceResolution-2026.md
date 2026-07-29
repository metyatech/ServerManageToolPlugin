# Server Manage Tool Source Copyright Provenance Resolution — 2026

## 1. Scope

This resolution records the publisher's identity-continuity declaration, preserves the existing Git history, adds a repository `.mailmap`, reclassifies the 17 current `Source/**` files, and normalizes their first copyright line. It also records the unchanged prior audit findings and the license boundary for the 1.1.2 release.

The previous audit report remains unchanged at `Docs/Verification/SourceCopyrightProvenanceAudit-2026.md`. No historical commit, author, commit SHA, existing tag, release, or release asset was rewritten or replaced.

## 2. Previous blocker

The previous verdict was `BLOCKED_MANUAL_PROVENANCE_CONFIRMATION_REQUIRED` because all 17 current Source files descended from the initial bulk import authored by `Udon-Tobira`, while no identity continuity or rights record had been provided. The previous report's SHA-256 is `CF4C26E8B7BDCCD212673559110D95216E0C53E56DBFBDDC9BA1A12B5B034C91`.

## 3. Publisher declaration

On 2026-07-29 JST, the repository owner provided this declaration:

> `Udon-Tobira` is the former GitHub username/account name of the same individual currently using `metyatech`. Commits under both names are continuous development by the same individual, not a third-party rights transfer.

This is recorded as identity continuity, not as a transfer of copyright between unrelated developers. The machine-readable record is `publisher-declaration.json` in the temporary evidence root.

## 4. Identity continuity finding

The declaration resolves the prior historical-author ambiguity. `Udon-Tobira` and `metyatech` are the same individual's former and current GitHub identities. The Git history remains authoritative as originally recorded: historical commits continue to show `Udon-Tobira`, and no author metadata or commit SHA was changed.

The current canonical identity was obtained from the latest non-bot Source commit, not invented: `metyatech <metyatech@gmail.com>` from commit `b198cb9920f8a6feb4c6b43eab756a124ddfd571`.

## 5. GitHub repository identity confirmation

The product remote is `https://github.com/metyatech/ServerManageToolPlugin`, with default branch `master`. GitHub API identity lookup resolves `metyatech` to `https://github.com/metyatech`. The repository is public and remains at the same owner/repository identity; no repository redirect or ownership change was required for this resolution.

## 6. Raw contributor identities

Before adding `.mailmap`, a clean same-HEAD probe clone produced:

```text
10  Udon-Tobira <146440502+Udon-Tobira@users.noreply.github.com>
 4  metyatech <metyatech@gmail.com>
```

These are the raw Source-history identities. The initial Source import remains authored and committed by `Udon-Tobira`; the later Source changes are authored by `metyatech`.

## 7. Mailmap canonicalization

The repository root now contains exactly:

```text
metyatech <metyatech@gmail.com> Udon-Tobira <146440502+Udon-Tobira@users.noreply.github.com>
```

`.mailmap` changes display attribution only. It does not rewrite history, alter author metadata, or change any commit SHA. With Git's supported `git log --use-mailmap --format="%aN <%aE>" --all -- Source` API, the 14 Source commits display as:

```text
14  metyatech <metyatech@gmail.com>
```

Git for Windows `2.55.0.windows.3` rejects the explicitly requested `git shortlog -sne --all --use-mailmap -- Source` spelling with exit 129 (`unknown option '(NULL)'`). The raw result was therefore verified in a clean same-HEAD clone before `.mailmap`, and the supported `git log --use-mailmap` output was used for canonicalization evidence. The complete command output is `mailmap-results.txt`.

## 8. Epic template comparison — retained prior result

The prior audit compared the implementation with the installed UE 5.8 Plugin Browser and Editor templates. It found only normal Unreal module, Build.cs, ToolMenus, and Blueprint-library boilerplate. Targeted searches found no substantial match for the product's distinctive markers or implementation. The prior comparison report recorded no substantial Epic implementation reuse; that result is retained and is not being reinterpreted as a third-party contribution.

## 9. Third-party dependency — retained prior result

The prior audit found no `ThirdParty`, `External`, or `Vendor` source directory, no repository binary dependency, and no unknown Build.cs module. The package DLLs are the three named UnrealEditor plugin module outputs. No third-party source or binary dependency requiring a separate license review was detected.

## 10. Per-file reclassification

The publisher declaration resolves the historical identity for every current Source file. `A` means generated Unreal/template structure with no substantive Epic implementation; `C` means standard Unreal boilerplate surrounding `metyatech` product declarations or logic. No file remains D, E, or F.

| Relative path | Class | Short basis |
| --- | --- | --- |
| `Source/ServerInfoSettingsModule/Private/ServerInfoSettings.cpp` | A | Generated translation unit; no substantive external implementation |
| `Source/ServerInfoSettingsModule/Private/ServerInfoSettingsModule.cpp` | A | Standard module startup/shutdown boilerplate only |
| `Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h` | C | Product settings schema and properties |
| `Source/ServerInfoSettingsModule/Public/ServerInfoSettingsModule.h` | A | Standard `IModuleInterface` declaration |
| `Source/ServerInfoSettingsModule/ServerInfoSettingsModule.Build.cs` | A | Standard UBT module wrapper and dependency shape |
| `Source/ServerManageLibrary/Private/ServerManageLibrary.cpp` | C | Product expected-port validation and runtime behavior |
| `Source/ServerManageLibrary/Private/ServerManageLibraryBP.cpp` | C | Product Blueprint map/address and exit behavior |
| `Source/ServerManageLibrary/Public/ServerManageLibrary.h` | C | Product runtime API declarations |
| `Source/ServerManageLibrary/Public/ServerManageLibraryBP.h` | C | Product Blueprint API declarations |
| `Source/ServerManageLibrary/ServerManageLibrary.Build.cs` | A | Standard UBT dependency declaration |
| `Source/ServerModePlayMenu/Private/ServerModePlayMenu.cpp` | C | Product menu, preflight, launch, and lifecycle behavior |
| `Source/ServerModePlayMenu/Private/ServerModeSetting.cpp` | C | Product editor setting initialization |
| `Source/ServerModePlayMenu/Private/ServerProcess.cpp` | C | Product managed server process lifecycle |
| `Source/ServerModePlayMenu/Private/ServerProcess.h` | C | Product managed process type |
| `Source/ServerModePlayMenu/Public/ServerModePlayMenu.h` | C | Product module state and delegate API |
| `Source/ServerModePlayMenu/Public/ServerModeSetting.h` | C | Product play-mode setting definition |
| `Source/ServerModePlayMenu/ServerModePlayMenu.Build.cs` | A | Standard UBT dependency declaration |

Final counts: A `6`, C `11`, D `0`, E `0`, F `0`.

## 11. Copyright normalization policy

All 17 Source files now begin with the lowercase `metyatech` notice:

```cpp
// Copyright 2024-2026 metyatech. All Rights Reserved.
```

The 7 `.cpp`, 7 `.h`, and 3 `.Build.cs` files each changed in exactly one first-line header replacement. The evidence confirms:

- Source files changed: 17;
- header-only files: 17;
- header-only failures: 0;
- old Epic notice remaining: 0;
- Unreal placeholder remaining: 0;
- `Metyatech` case-variant remaining in the changed headers: 0;
- BOM preservation failures: 0;
- final-newline preservation failures: 0;
- runtime, API, and Build.cs dependency changes: 0.

The old notices were not evidence of Epic implementation ownership. The prior template comparison and identity declaration support the normalized All Rights Reserved notice.

## 12. Repository license state

No `LICENSE`, `LICENSE.md`, `COPYING`, or custom OSS license was added. The repository remains public and source-accessible, but it is not described as Open Source and no OSS license is claimed. Source uses All Rights Reserved notices. Fab distribution terms remain the Fab Standard License; this task does not reproduce or invent that license text.

## 13. Fab submission impact

The historical provenance blocker is resolved. The package can proceed through BuildPlugin, runtime regression, and release verification with the disclosed limitation that no dedicated `TargetType.Server` executable is provided or verified. Fab input or submission is not performed by this task.

## 14. Final decision

`Provenance blocker: RESOLVED`

`Identity continuity: PASS`

`Copyright normalization: PASS`

The identity declaration resolves the only manual provenance blocker from the previous audit. No third-party contributor requiring a rights transfer remains unresolved. Product behavior, Blueprint API, runtime logic, and dependency lists remain unchanged by the normalization.

## 15. Evidence hashes

The temporary evidence manifest is generated after all evidence is collected. It includes the raw contributor check, publisher declaration, source old/new hashes, metadata checks, build/package/runtime evidence, and release URL checks. The final manifest path and SHA-256 are recorded in the 1.1.2 release audit report.

## 16. Reproduction commands

Use a fresh temporary root and preserve existing checkouts:

```powershell
$Root = 'D:\T\SMT112-<timestamp>'
$Plugin = Join-Path $Root 'ServerManageToolPlugin'
$Docs = Join-Path $Root 'unreal-plugin-docs'
git clone --branch master --single-branch https://github.com/metyatech/ServerManageToolPlugin.git $Plugin
git -C $Plugin fetch origin --tags
git clone --branch main --single-branch https://github.com/metyatech/unreal-plugin-docs.git $Docs
git -C $Docs fetch origin --tags
git -C $Plugin shortlog -sne --all -- Source
git -C $Plugin log --use-mailmap --format="%aN <%aE>" --all -- Source
git -C $Plugin log --format="%an <%ae>" --all -- Source
git -C $Plugin rev-list --all -- Source
git -C $Plugin diff --check
```

The complete command output, including the Git 2.55 shortlog option limitation and its supported equivalent, is stored outside the repository under the temporary evidence root.
