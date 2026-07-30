# Fab Pre-Listing Buyer Installation and Media Audit — Server Manage Tool 1.1.2

Audit date: 2026-07-30 (JST)  
Engine: Unreal Engine 5.8 installed build, Win64  
Audit evidence root: `D:\T\SMT-PRELIST-20260730-111704\Evidence`

## 1. Scope and verdict

This audit covers a buyer-perspective installation from the public fixed and versioned release ZIPs, a fresh Blueprint-only Unreal project, Project Settings, Local Launch, cleanup, a 7778 UDP conflict, and read-only discovery and review of Fab media candidates. No product source, product documentation, package, release, image, or remote release asset was changed.

Final verdicts:

| Area | Verdict |
| --- | --- |
| Public ZIP installation | `PASS_WITH_MINOR_FRICTION` |
| Project Settings / Server List UI | `PASS_WITH_MINOR_FRICTION` |
| Blueprint node search and exact null-map scenario | `NOT_CONFIRMED` |
| Local Launch / normal PIE lifecycle | `PASS` |
| Simulate regression | `PASS_WITH_MINOR_FRICTION` |
| 7778 conflict regression | `PASS` |
| Fab media technical readiness | `NO_CANONICAL_MEDIA_SET` |
| Fab claims audit | `BLOCKED` |
| Fab rights audit | `MANUAL_RIGHTS_CONFIRMATION_REQUIRED` |
| Privacy audit | `PASS` |
| Overall Fab listing readiness | **`NOT_READY_NO_MEDIA_SET`** |

The buyer-facing runtime path is usable for the tested editor workflow, but the listing is not ready because no canonical Server Manage Tool thumbnail/gallery set was identified. The absence of a canonical media set is an evidence gap, not evidence that unrelated images belong to this product.

## 2. Start Git state

The existing working checkout was preserved and not modified:

| Item | Value |
| --- | --- |
| Existing checkout | `D:\ghws\ServerManageToolPlugin` |
| Existing branch | `verify/real-game-packaging` |
| Existing HEAD | `ec69903ce95257be02a21020b37fca04ff04b0b1` |
| Existing working tree | clean |
| Remote | `https://github.com/metyatech/ServerManageToolPlugin.git` |
| Fetched `origin/master` | `6902d44cf1c0394612f6dde7e0176133badd5a18` |

The audit clone used for the report was created from `master` at `6902d44cf1c0394612f6dde7e0176133badd5a18`, had no pre-existing changes, and was clean before this report was added. The installed UE root was `C:\Program Files\Epic Games\UE_5.8`; `Build.version` reported major 5 and minor 8, and `Engine\Build\InstalledBuild.txt` existed.

## 3. Public release ZIP validation

Both URLs were fetched anonymously with HTTP status 200:

- Fixed: [ServerManageTool-Fab-Current.zip](https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip)
- Versioned: [ServerManageTool-1.1.2-UE5.8-Win64.zip](https://github.com/metyatech/ServerManageToolPlugin/releases/download/v1.1.2/ServerManageTool-1.1.2-UE5.8-Win64.zip)

Both files were 169,758 bytes and had SHA-256 `C1A043C3388520446DAB93B40FEFD6CE0E05F87D94544BB28A14B98098601443`. A byte-for-byte comparison passed. The ZIP had a single `ServerManageTool/` root, a direct root `.uplugin`, 34 entries, no mailmap, no verification report, and no PDB/intermediate repository metadata. Full inventory: `Evidence/ZipInventory.txt` and `Evidence/PublicDownloadValidation.json`.

## 4. Fresh buyer project

A new Blank, Blueprint-only, desktop, maximum-quality project with no starter content was created. The project did not reuse configuration, saved data, or derived data. The extracted versioned ZIP was installed as a project-local plugin under `Plugins/ServerManageTool`. The project `.uproject` had no C++ `Modules` property. Environment evidence: `Evidence/BuyerProjectEnvironment.json`.

The first setup attempt placed the ZIP one directory too high; this was corrected before verification. This is recorded as buyer setup friction, not a package defect.

## 5. Installation journey

The first opened artifact was the package `README.md`, followed by the User Guide index, Installation, Configuration, Local Launch, and QuickStart documents. The following were clear enough to complete the basic installation:

- project-local plugin location;
- enabling the plugin and restarting the editor;
- Project Settings location;
- Server Mode / Local Launch location;
- base port 7777 and sequential allocation;
- UDP preflight and all-or-nothing behavior;
- cleanup expectations and editor-only scope.

Minor friction: the settings page has no accompanying screenshot, and the first ZIP placement was one directory too high during setup. Buyer result: `PASS_WITH_MINOR_FRICTION`.

## 6. Project Settings and map journey

The normal editor UI opened Project Settings > Project > Servers. Two entries were created and displayed with:

```text
/Engine/Maps/Entry    127.0.0.1:19001
/Engine/Maps/Entry    127.0.0.1:19002
```

The UI path and server-list editing were confirmed. The guide examples use `/Game/Maps/Lobby` and `/Game/Maps/Match`. Minimal map creation produced `/Game/Lobby` and `/Game/Match` because the Save Level As folder-creation affordance was not immediately discoverable. Blueprint node search and the exact null-map runtime scenario were not confirmed; they are not claimed as passing. Evidence: `Evidence/BuyerScreenshots/04-project-settings-server-list.png` and `Evidence/BuyerInstallFindings.json`.

## 7. Local Launch / normal PIE

The tested Local Launch PIE produced exactly two managed server children:

| Item | Result |
| --- | --- |
| Parent editor PID | 45824 |
| Child PIDs | 43232, 37632 |
| ParentProcessId | 45824 for both children |
| Requested ports | 7777, 7778 |
| Actual UDP endpoints | `0.0.0.0:7777`, `0.0.0.0:7778` |
| Preflight pass markers | 1 |
| Child validation pass markers | 2 |
| Validation failures | 0 |
| Launch failures | 0 |
| Maximum matching process count | 3 including the editor |
| After End PIE: children | 0 |
| After End PIE: UDP owners | 0 |
| Forced cleanup | No |

The child validation markers were visible in the two server console windows; the parent log contained the preflight and launch markers. Evidence: `Evidence/RuntimeProcessEvidence.json`, `Evidence/RuntimeUdpEvidence.json`, and `Evidence/RuntimeMarkerExtract.txt`. Normal PIE / Local Launch verdict: `PASS`.

## 8. 7778 conflict regression

An independent holder bound `0.0.0.0:7778` before Local Launch. The editor emitted `SMT_PORT_PREFLIGHT_FAILED` with unavailable port 7778. Managed child count remained 0; no 7777 child and no shifted child were created. The holder was not terminated by the plugin and was removed only by its planned test cleanup. Final holder process and UDP owner counts were 0. Verdict: `PASS`. Evidence: `Evidence/Conflict7778Evidence.json`.

## 9. Buyer UX findings

The first-use path is understandable after reading the package README and User Guide. The main improvements recommended before listing are:

1. Add one screenshot showing Project Settings > Project > Servers.
2. State the exact project-local extraction path with a short tree example.
3. Add a concise map-creation note showing how to create `/Game/Maps/Lobby` and `/Game/Maps/Match`.
4. Add a Blueprint API discovery example and explicitly state that the null-map case is a prerequisite check.

The current documented limitations were preserved in the audit: no production server build/deploy, no health-check/retry/automatic restart, no configurable base port or automatic port shift, and no guaranteed OS exit status.

## 10. Fab media discovery

Read-only discovery covered the requested product repository, its `.verification` area, `D:\ghws\fab-listing-media`, `C:\Users\Origin\Downloads`, and `D:\T`, with paths matching the requested media-oriented patterns. Paths containing `SIWLiveFX` or `SIW` were excluded. `D:\ghws\fab-listing-media` and the product `.verification` directory were not present.

The inventory contained 77 matching image files, 7 distinct SHA-256 values, and one exact duplicate group of 71 copies of the bundled `Resources/Icon128.png`. Four buyer screenshots are audit evidence, not Fab media. One Downloads contact sheet belongs to an unrelated RuntimeAssetImport visual. No canonical Server Manage Tool Fab media set was found. Evidence: `Evidence/MediaInventory.csv`, `Evidence/MediaInventory.json`, and `Evidence/MediaDuplicateGroups.json`.

## 11. Canonical media set

`CANONICAL_SET_NOT_IDENTIFIED`.

The only product-specific image found was the bundled 128x128 `Resources/Icon128.png`. It is a plugin icon, not a listing gallery set. The 3840x2160 RuntimeAssetImport contact sheet is unrelated and must not be submitted for Server Manage Tool. Audit screenshots must also not be submitted.

No image was generated, edited, moved, renamed, or deleted during this audit.

## 12. Media technical validation

Fab’s official [asset file format and structure requirements](https://dev.epicgames.com/documentation/fab/asset-file-format-and-structure-requirements-in-fab) specify, for 2D gallery images, at least 1920x1080 pixels, PNG or JPEG format, less than 3 MB per image, and less than 25 MB total. The official [publisher get-started guidance](https://dev.epicgames.com/documentation/fab/publisher-get-started-in-fab) requires a thumbnail and at least one image or 3D preview for a listing.

Because no canonical submission set exists, thumbnail and gallery technical validation is blocked. There are zero validated submission images and zero validated 3D previews. The 128x128 icon would fail the 2D gallery minimum if submitted as gallery media. Verdict: `NO_CANONICAL_MEDIA_SET`.

## 13. Visual and readability audit

The product icon is a small blue product mark on a yellow background and contains no feature claim or version text. It is unsuitable as the complete listing gallery because it is 128x128 and does not demonstrate the workflow.

The Downloads contact sheet visibly shows an unrelated RuntimeAssetImport environment and props. It does not demonstrate Server Manage Tool and is excluded. The audit screenshots demonstrate the buyer UI but include editor chrome and are evidence-only. No listing media was accepted as a canonical product image.

## 14. Feature-claim audit

Allowed claims supported by the audited package and runtime evidence include map-specific server address configuration, Project Settings integration, Project Setting mode, Local Launch during PIE, all-port UDP preflight, all-or-nothing launch, expected/actual port validation, End PIE/module-shutdown cleanup, `Get Server Address`, and `Request Server Exit`.

The audit does not support claims of production server build/deploy/hosting, packaged dedicated-server auto-generation, client auto-connect, health checks, retry or automatic restart, configurable base port, automatic port shift, a dedicated `TargetType.Server` executable, or an OS exit-code guarantee. Since no canonical media set was identified, final image-to-claim matching remains blocked. Evidence: `Evidence/MediaClaimsAudit.json`.

## 15. Version consistency

The public versioned artifact name is `ServerManageTool-1.1.2-UE5.8-Win64.zip`. Its plugin descriptor reported Version 4, VersionName `1.1.2`, Friendly Name `Server Manage Tool`, publisher `metyatech`, and three modules. The fixed and versioned downloads were byte-identical. No mixed-version listing image or version label was identified.

## 16. Privacy audit

The inspected product icon and unrelated contact sheet showed no visible username, email, absolute path, machine name, private URL, IP address, token, API key, browser tab, notification, avatar, or secret address. Verdict: `PASS` for the inspected candidates. This does not make the unrelated contact sheet suitable for submission. Evidence: `Evidence/MediaPrivacyAudit.json`.

## 17. Rights and third-party elements

The bundled product icon has repository/package evidence as a product resource. The unrelated contact sheet contains third-party-looking asset content and Unreal Editor UI, but its license and submission permission were not established. It therefore remains `MANUAL_RIGHTS_CONFIRMATION_REQUIRED` and is excluded from the proposed listing set. Do not use it unless rights and the required non-inclusion caption are independently confirmed. Evidence: `Evidence/MediaRightsAudit.json`.

## 18. Per-image verdict table

| Candidate | Technical | Claims | Privacy | Rights | Final use |
| --- | --- | --- | --- | --- | --- |
| `Resources/Icon128.png` | Fails gallery dimensions: 128x128 | No feature claim | Pass | Bundled resource evidence | Source icon only; not gallery media |
| `RuntimeAssetImport-Fab-RawMedia-HQModels-20260727-164647-contact-sheet.png` | 3840x2160 and under 3 MB, but unrelated | Unverifiable for Server Manage Tool | No PII observed | Manual confirmation required | Exclude |
| `Evidence/BuyerScreenshots/*.png` | Audit screenshots, not listing media | Product UI evidence only | Audit scope | Audit-owned | Evidence only |

## 19. Missing media coverage

The canonical set should later cover, at minimum, a hero/value proposition, Project Settings / Server List, Project Setting mode / Blueprint API, Local Launch during PIE, UDP preflight and 7778 conflict prevention, End PIE/module-shutdown cleanup, and editor-only limitations. No images were created in this audit, so these are open content tasks rather than hidden outputs.

## 20. Listing readiness

The public package is installable and its tested Local Launch behavior is evidenced, but the Fab listing is **not ready**. The blocking condition is `NO_CANONICAL_MEDIA_SET`, which also blocks final claims-to-image matching. The unrelated contact sheet is not a substitute for product media.

## 21. Required actions before listing

1. Identify or produce an approved Server Manage Tool media set outside this audit.
2. Provide a 1920x1080-or-larger thumbnail/gallery set in PNG or JPEG, respecting the Fab per-image and total-size limits.
3. Confirm each image contains only verifiable Server Manage Tool claims and no unrelated third-party content.
4. Record rights provenance and any required Unreal/third-party disclosure captions.
5. Re-run the exact media inventory, technical, claim, privacy, and rights checks against the final selected files.
6. Separately complete Blueprint API discovery and the exact `/Game/Maps/Lobby` / `/Game/Maps/Match` null-map scenario before claiming that acceptance path.

## 22. Exact reproduction commands

The following commands describe the reproducible, read-only or staged checks. Replace `<verifyRoot>` with the evidence root used for the run.

```powershell
$fixed = 'https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip'
$versioned = 'https://github.com/metyatech/ServerManageToolPlugin/releases/download/v1.1.2/ServerManageTool-1.1.2-UE5.8-Win64.zip'
Invoke-WebRequest -Uri $fixed -OutFile '<verifyRoot>\PublicDownloads\ServerManageTool-Fab-Current.zip'
Invoke-WebRequest -Uri $versioned -OutFile '<verifyRoot>\PublicDownloads\ServerManageTool-1.1.2-UE5.8-Win64.zip'
Get-FileHash '<verifyRoot>\PublicDownloads\ServerManageTool-Fab-Current.zip' -Algorithm SHA256
Get-FileHash '<verifyRoot>\PublicDownloads\ServerManageTool-1.1.2-UE5.8-Win64.zip' -Algorithm SHA256
Expand-Archive '<verifyRoot>\PublicDownloads\ServerManageTool-1.1.2-UE5.8-Win64.zip' '<verifyRoot>\BuyerProject\SMTBuyerProject\Plugins'
```

For runtime verification, configure two Server List entries, select Server Mode > Local Launch, start PIE, record `SMT_PORT_PREFLIGHT_PASSED`, child command lines, `ParentProcessId`, UDP 7777/7778 ownership, and child validation markers, then end PIE and verify zero matching children and zero UDP owners. For the conflict case, bind 7778 with an independent holder before starting PIE and verify `SMT_PORT_PREFLIGHT_FAILED`, zero managed children, and no 7777 or shifted child. For media, run the read-only inventory with the specified roots and exclusions, then hash every evidence file.

## 23. Evidence manifest and final Git state

Evidence files are listed under `Evidence/`. The complete SHA-256 manifest is `Evidence/Evidence-SHA256.txt`; the manifest excludes its own line from self-hashing and records the SHA-256 of every other evidence file. Key evidence files are:

- `PublicDownloadValidation.json`
- `BuyerProjectEnvironment.json`
- `BuyerInstallFindings.json`
- `RuntimeProcessEvidence.json`
- `RuntimeUdpEvidence.json`
- `Conflict7778Evidence.json`
- `SimulateEvidence.json`
- `MediaInventory.csv` and `MediaInventory.json`
- `MediaTechnicalValidation.json`
- `MediaClaimsAudit.json`
- `MediaPrivacyAudit.json`
- `MediaRightsAudit.json`
- `MediaGalleryRecommendation.md`
- `BuyerScreenshots/*.png`

This report is the only repository file changed by this audit. The existing checkout remained clean and untouched. The final commit SHA and remote status are recorded after commit and push in the delivery report.

