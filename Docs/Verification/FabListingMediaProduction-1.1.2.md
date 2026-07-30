# Fab Listing Media Production — Server Manage Tool 1.1.2

## 1. Scope

This audit covers a new Fab thumbnail, five gallery images, their editable HTML/CSS/JavaScript source, technical manifests, claim review, rights/privacy review, and buyer-facing UE 5.8 verification. No product source, configuration, content, `.uplugin`, user guide, tag, release, release asset, or Fab input was changed.

Verdict: `READY_FOR_LISTING_COPY`.

## 2. Start Git state

The fresh temporary clone was created from `origin/master` at `79c30f07ceb013296d39b3a1fa2a53c393cd1d96`. Branch was `master`, local and remote heads matched, and the clone was clean before the media-only changes. The existing checkout was not used for edits and remained unchanged.

## 3. Public package validation

The fixed public ZIP returned HTTP 200 and matched SHA-256 `C1A043C3388520446DAB93B40FEFD6CE0E05F87D94544BB28A14B98098601443`. Archive root is `ServerManageTool/`; the manifest reports Version `4`, VersionName `1.1.2`, and CreatedBy `metyatech`. `.mailmap`, `Docs/Verification`, PDB, and Intermediate entries were absent. Full evidence: `Evidence/PublicDownloadValidation.json`.

## 4. Buyer project

The fresh Blueprint-only `ServerManageToolDemo` project used UE 5.8, Desktop target, Blank template, no Starter Content, and no C++ `Modules` property. The public package was installed at the project-local `Plugins/ServerManageTool` location. `/Game/Maps/Lobby` and `/Game/Maps/Match` were created and saved. PythonScriptPlugin and EditorScriptingUtilities were enabled editor-only for verification. Evidence: `Evidence/BuyerProjectEnvironment.json`.

## 5. Blueprint API discovery

Normal UE 5.8 Blueprint Editor search found `Get Server Address` and `Request Server Exit`. `Get Server Address` exposes a Map input and two nodes were placed. `Request Server Exit` was placed but never executed. The graph compiled successfully. Raw captures show both search results and the compiled graph. Evidence: `Evidence/BlueprintNodeDiscovery.json`.

## 6. Project Setting results

In `SERVER_ProjectSetting` mode, Lobby returned `lobby.example.test:9001` and Match returned `match.example.test:9002`. The call did not auto-connect a client. Evidence: `Evidence/ProjectSettingResults.json` and the actual Project Settings screen in `Evidence/RawScreenshots/Canonical/R02-project-settings-server-list.png`.

## 7. Null and missing map results

Null Map returned an empty string. An unregistered/missing map also returned an empty string and produced the implementation's expected missing-map log. The commandlet wrapper reported the expected error-level log for the negative cases; the values and Blueprint API behavior passed. Evidence: `Evidence/NullMapResults.json`.

## 8. Simulate verification

Simulate was selected independently through the UE 5.8 Play Mode menu, then started with the Play control. The monitor observed a maximum of two managed children and two UDP owners, requested/actual ports 7777 and 7778, one preflight PASS, two validation PASS records, and zero validation FAIL records. After the explicit stop, a direct query recorded child count 0 and UDP owner count 0. No forced cleanup was used. Evidence: `Evidence/SimulateEvidence.json`, `Evidence/SimulateEvidence-snapshots.json`, and `Evidence/RawScreenshots/Canonical/R09-simulate-selected.png`.

## 9. Local Launch verification

Server Mode > Local Launch was selected in the UE 5.8 Play menu. The monitor observed exactly two managed children, both with the buyer project path and parent PID 9000. Requested and actual ports were 7777 and 7778. Maximum child count was 2 and maximum product UDP owner count was 2. After End PIE, child count and UDP owner count were both 0. Evidence: `Evidence/LocalLaunchEvidence.json`, `Evidence/LocalLaunchEvidence-snapshots.json`, and `Evidence/RawScreenshots/Canonical/R05-server-mode-local-launch.png`.

## 10. Conflict verification

An independent holder bound UDP 7778 before PIE. The actual UE Output Log showed:

`SMT_PORT_PREFLIGHT_FAILED unavailable_ports=7778 server_count=2 started_server_count=0 rollback_count=0`

Managed child count and product UDP owner count remained 0. The holder stayed outside product cleanup and was closed only by its planned test cleanup. Evidence: `Evidence/Conflict7778Evidence.json`, `Evidence/Conflict7778Evidence-snapshots.json`, and `Evidence/RawScreenshots/Canonical/R07-port-conflict-output.png`.

## 11. Raw capture process

Nine canonical raw captures were retained under the temporary Evidence root. Each is an actual UE 5.8 screen or a lossless crop of one, with desktop taskbar/notification/private-path regions excluded from the canonical crop. The nine IDs are R01 through R09 in `Evidence/RawScreenshotManifest.json`.

## 12. Design system

Final media uses local HTML/CSS/JavaScript, Segoe UI/Arial/sans-serif, a dark blue panel system, product-icon blue/yellow accents, and simple measured process/port diagrams. No network image, external font, stock asset, generated image, or fake Unreal UI was used.

## 13. Canonical media set

Canonical directory: `Marketing/Fab/ServerManageTool/1.1.2/`.

The six Fab candidates are the thumbnail plus gallery images 01 through 05 under `final/`. `review/ContactSheet.jpg` is review-only and is not counted as a submission image. Editable source is under `source/html/`, `source/css/`, `source/scripts/`, and `source/assets/`.

## 14. Per-image copy

1. Thumbnail — “Reliable Local Server Workflows for Unreal Engine PIE”; map-specific addresses, all-port preflight, managed cleanup; UE 5.8 Win64 badge.
2. Project Settings — “Configure Your Server List”; map-to-address configuration and project-local installation.
3. Blueprint API — “Resolve Server Addresses in Blueprint”; Project Setting lookup, Local Launch lookup, empty string for null/missing maps, and server-process-only exit note.
4. Local Launch — “Launch the Complete Local Server Group”; all-port preflight, requested/actual ports, and the two supported log markers.
5. Port Conflict — “Prevent Partial Launches”; 7778 unavailable, preflight failure, and managed children 0.
6. Cleanup and Scope — “Clean Editor Testing Workflows”; End PIE/module-shutdown cleanup and Editor/PIE-only boundary.

## 15. Technical validation

All six final files are JPEG, 2560x1440, RGB/sRGB, under 3 MB each, and under 25 MB total. Total size is `1,710,928` bytes. Corruption, duplicate, alpha, crop-safe, 25% preview, and 50% preview checks passed. Full per-file data is in `Marketing/Fab/ServerManageTool/1.1.2/MediaManifest.json` and `Evidence/FinalMediaTechnicalValidation.json`.

| File | Bytes | SHA-256 |
| --- | ---: | --- |
| ServerManageTool-Thumbnail.jpg | 256,495 | `8055E1C7ADC08E864EFB2B5213B8384CDE61CEC7C32DA9A4BF4738832653CC05` |
| ServerManageTool-01-Project-Settings.jpg | 295,240 | `82B574AA519C93B5E42473A090A1F955B033AD9316523A10D6CC162B9D31B348` |
| ServerManageTool-02-Blueprint-API.jpg | 336,387 | `B2EE5641C3AE9E7C0BDA05CA4AEA37ACF40FED550512F8ADE13936A5C81DD050` |
| ServerManageTool-03-Local-Launch.jpg | 274,395 | `6568EBD680EB2E2A179D91C271ABA785A7581BD88BD807E9CF0E8B53403C55BF` |
| ServerManageTool-04-Port-Conflict.jpg | 259,994 | `1E36D98806A5F34147A16BEA815FB4EBA65091E51B9011F9635FEC5F82B63A39` |
| ServerManageTool-05-Cleanup-Scope.jpg | 288,417 | `665B7AD84FE665B0F1D4B9EE1004E26921BB5F4E4F47ECEF98345E1238A24AE5` |

## 16. Visual review

The six rendered images were reviewed at 100%, 50%, and 25%. Titles, copy, port values, actual UI crops, and workflow boundaries remain readable. Important content stays inside the 96px outer margin and central crop-safe area. Status: `PASS`. Evidence: `Evidence/FinalMediaVisualReview.md` and `review/ContactSheet.jpg`.

## 17. Feature-claim audit

All six images are classified `CLAIMS_ACCURATE`. No image claims production hosting, deployment, packaged dedicated-server generation, client auto-connect, health checks, retry, automatic restart, configurable base ports, arbitrary per-server ports, automatic port shifting, selective launch, guaranteed OS exit status, or Fab-exclusive functionality. Evidence: `Evidence/FinalMediaClaimsAudit.json`.

## 18. Rights audit

Rights status is `PASS`. Allowed elements are the product icon, actual UE 5.8 Editor UI, temporary Windows console evidence, text, basic shapes, lines, arrows, and measured values. Third-party assets, external fonts, downloaded icon packs, stock media, and decorative Unreal/Epic/Fab logos are absent. Evidence: `Marketing/Fab/ServerManageTool/1.1.2/Rights.md` and `Evidence/FinalMediaRightsAudit.json`.

## 19. Privacy audit

Privacy status is `PASS`. Final media contains no username, email, machine name, absolute local path, private URL, personal avatar, old publisher name, `Udon-Tobira`, secret IP/hostname, unrelated product, browser tab, or notification. Example addresses are non-production placeholders. Evidence: `Evidence/FinalMediaPrivacyAudit.json`.

## 20. Final gallery order

1. Thumbnail
2. Project Settings
3. Blueprint API
4. Local Launch
5. Port Conflict
6. Cleanup and Scope

## 21. Fab requirements

The required six files are present, JPEG, 2560x1440, 16:9, sRGB/RGB, individually below 3 MB, and collectively below 25 MB. The thumbnail and five gallery roles are explicit in the manifest. No Fab input, upload, submission, release, tag, or release asset was changed.

## 22. Listing media readiness

Buyer Blueprint UX: `PASS`

Simulate independent verification: `PASS`

Canonical media set: `PASS`

Thumbnail: `READY`

Gallery: `READY`

Technical requirements: `PASS`

Claims: `PASS`

Rights: `PASS`

Privacy: `PASS`

Overall: `READY_FOR_LISTING_COPY`

## 23. Reproduction commands

Use an OS-temporary `<verifyRoot>` and the public ZIP URL; do not use the existing checkout for buyer captures.

```powershell
$verifyRoot = '<verifyRoot>'
$plugin = Join-Path $verifyRoot 'ServerManageToolPlugin'
$buyer = Join-Path $verifyRoot 'ServerManageToolDemo'
$zip = Join-Path $verifyRoot 'PublicDownloads\ServerManageTool-Fab-Current.zip'
Invoke-WebRequest 'https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip' -OutFile $zip
Get-FileHash $zip -Algorithm SHA256
```

Open the Blueprint-only buyer project with UE 5.8, select Server Mode > Local Launch, run PIE, and record the two managed children and UDP endpoints. Select Play Mode > Simulate independently and repeat. For the conflict run, bind UDP 7778 with an independent holder before PIE, confirm `SMT_PORT_PREFLIGHT_FAILED`, then stop PIE and close only the holder created by the test. Render from `source/html/index.html` through a local HTTP server with Chromium at 2560x1440 and verify the six outputs against `MediaManifest.json`.

## 24. Evidence manifest

The Evidence manifest is `Evidence/Evidence-SHA256.txt`. It contains the SHA-256 for every temporary evidence file except the manifest itself; the final run contains 150 evidence entries and has SHA-256 `C93D0140E806D637CAB01F24AA83D9CB3DCAE8EAB5718F7FD15344A97094A5B3`. The canonical media manifest is `Marketing/Fab/ServerManageTool/1.1.2/MediaManifest.json` with 6 final-image entries and total size `1,710,928` bytes.
