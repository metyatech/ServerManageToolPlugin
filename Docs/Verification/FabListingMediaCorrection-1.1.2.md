# Fab Listing Media Correction — Server Manage Tool 1.1.2

## 1. Scope

This correction applies only the four advertising-copy and evidence-source review findings to the six existing media outputs. Product source, product documentation, version, release, tag, public ZIP, Fab Listing, and the original `FabListingMediaProduction-1.1.2.md` audit were not changed. No computer-use, image-generation tool, fake UI, stock image, third-party asset, network image, or external font was used.

Final verdict: `READY_FOR_LISTING_COPY`.

## 2. Start Git state

The new temporary clone was created on `master` from `98ef05f9912c627ee3df2a55d08047684000b5d0`. `origin/master` matched that SHA, divergence was `0 0`, and the temporary clone was clean before edits. The existing checkout remained on its pre-existing branch and was not used for edits.

## 3. Review findings

The four findings were reproduced before editing:

1. The common header contained `Version 1.1.2 · Fab listing media`.
2. The Local Launch composition used the same crop content as the Simulate asset and captioned it `Actual UE 5.8 PIE screen`.
3. The Local Launch status used `Ready`, which overstated `SMT_PORT_PREFLIGHT_PASSED` as server readiness.
4. The Cleanup composition used the installation tree as its large main screen.

The Blueprint copy also contained `Local Launch returns 127.0.0.1:7777+`; this was corrected as requested.

## 4. Changed media source

The prior `source/assets/ue-local-launch-console.png` had SHA-256 `D75C566EDE0F36686CDF225AFC5BC91C5D282A538A320812D86001AE9AC5D4FB`, identical to the prior Simulate crop. It now comes from the actual UE 5.8 Local Launch capture `R06-local-launch-active-verified` using crop `(110,535)-(1400,560)` and has SHA-256 `8F5C66B226734BEBB38EBE1488A22255001313DFC191524EE7370A4E89935B09`.

The prior Cleanup main asset was `source/assets/ue-plugin-tree.png`, SHA-256 `5009BAA720A545B134F8F88A2531DCCEEE5C353915AD023997F629465E57A0C7`. The new `source/assets/ue-cleanup-evidence.png` comes from actual post-End PIE capture `R08-simulate-after-stop-verified` using crop `(0,0)-(1500,760)` and has SHA-256 `788144296B758303076342D2243A2CF1BED46FAFBCC794842F50C39FCF2AC710`.

Both captures are from the public Server Manage Tool 1.1.2 package in the Blueprint-only `ServerManageToolDemo` Buyer Project. The Local Launch console crop excludes the console title/path and machine-name lines; the cleanup crop excludes desktop/private regions. Measured zero-process/zero-UDP values are shown beside the actual stopped Editor frame.

## 5. Global header correction

Before: `Version 1.1.2 · Fab listing media`

After: `Version 1.1.2`

The UE 5.8 Win64 badge remains on all six images. `Fab listing media`, `Preview`, and `Draft` do not appear in the final image source, Copy, README, manifest, or Rights metadata.

## 6. Local Launch evidence correction

Before: the Local Launch page displayed the Simulate crop.

After: it displays the actual Local Launch console validation crop from `R06-local-launch-active-verified`. The measured run evidence remains two managed children with requested/actual ports 7777 and 7778.

## 7. Preflight wording correction

Before: `Ready` / `SMT_PORT_PREFLIGHT_PASSED`.

After: `Ports Available` / `SMT_PORT_PREFLIGHT_PASSED`.

The page explicitly distinguishes the two markers:

- `SMT_PORT_PREFLIGHT_PASSED` means the required UDP ports were available before launch.
- `SMT_PORT_VALIDATION_PASSED` means requested and actual bound ports matched.

## 8. Cleanup evidence correction

Before main asset: installation tree.

After main asset: actual post-End PIE UE 5.8 Editor frame from `R08-simulate-after-stop-verified`, captioned `Actual post-End PIE cleanup evidence`.

The flow remains `Start PIE → 2 managed servers → End PIE → 0 managed processes → 0 UDP owners`. The installation tree remains only as the small Project Settings inset.

## 9. Blueprint copy correction

Before: `Local Launch returns 127.0.0.1:7777+`.

After: `Local Launch returns loopback ports starting at 7777`.

The Project Setting and null/missing map statements remain, as does the safety note that `Request Server Exit` should only be used in the server process.

## 10. Re-rendered final files

All six original filenames were re-rendered from the editable HTML/CSS/JavaScript source and the review Contact Sheet was refreshed.

## 11. Technical validation

All six files are JPEG, 2560x1440, 16:9, RGB/sRGB, non-alpha, orientation 1, corruption-free, unique, individually below 3 MB, and collectively below 25 MB. Final total is `1,614,230` bytes.

| File | Bytes | SHA-256 |
| --- | ---: | --- |
| ServerManageTool-Thumbnail.jpg | 254,120 | `909A8BC451403A4EA86F0965C9DA2BE7A45B6D9C01BF9457B5836254E4055D67` |
| ServerManageTool-01-Project-Settings.jpg | 292,178 | `288E7163F8A1128BFA5520313CEF1CD5EFA0D94603E539FD0C1CA79E30E85B71` |
| ServerManageTool-02-Blueprint-API.jpg | 337,362 | `D8221F2223F6335B22D30BA0B319EE23C57675853D9AD7CFD6E8A2E5DA306527` |
| ServerManageTool-03-Local-Launch.jpg | 240,589 | `D8B4D0C20482A28E5D9F12F5D2D1E86F5ACDE016B0F93F43B8A790606F679C08` |
| ServerManageTool-04-Port-Conflict.jpg | 256,787 | `CC106C6A7EA8D225CEDF905D85B322E6FEB9544C22307DA5EE18BE4A63B2700E` |
| ServerManageTool-05-Cleanup-Scope.jpg | 233,194 | `5FC5A91BAC4FBFF0E0B12CA4A4DAE848E3D16B0F90C369687F7AA536CBDA55BB` |

The authoritative values are in `Marketing/Fab/ServerManageTool/1.1.2/MediaManifest.json`.

## 12. Visual review

All six images and the refreshed `review/ContactSheet.jpg` were reviewed as actual images at 100%, 50%, and 25%. Titles and product purpose remain readable at 25%; body copy and evidence markers remain readable at 50%; important content remains within the 96px outer margin and 16:9 crop-safe region. No clipping, overlap, contrast failure, JPEG text breakdown, private information, or unrelated application was observed. Local Launch no longer appears to be Simulate, and Cleanup no longer duplicates the large installation tree.

Status: `PASS`.

## 13. Claim audit

All six images are `CLAIMS_ACCURATE`. Permitted claims remain limited to Project Settings integration, map-specific addresses, Project Setting mode, Local Launch during PIE, UDP all-port preflight, all-or-nothing launch, requested/actual port validation, End PIE and module-shutdown cleanup, Blueprint address lookup, server-process-only exit, and UE 5.8 Win64 verification. No image claims server readiness checks, production hosting, deployment, packaged dedicated-server generation, client auto-connect, retry, restart, port shifting, arbitrary per-server ports, or guaranteed OS exit status.

## 14. Rights audit

Status: `PASS`. Third-party assets, external fonts, downloaded icons, stock media, unknown assets, and decorative Unreal/Epic/Fab logos: `0`. The product icon and all UE screen crops are from the product repository or the test-owned UE 5.8 Buyer Project evidence.

## 15. Privacy audit

Status: `PASS`. Username, email, machine name, private URL, secret hostname, personal avatar, notification, browser tab, unrelated application, and absolute private path counts are `0` in the final six images. Example server addresses remain non-production placeholders.

## 16. Source grep gate

The editable source, Copy, README, Rights, and manifest contain these prohibited-string counts:

| String | Count |
| --- | ---: |
| `Fab listing media` | 0 |
| `Actual UE 5.8 PIE screen` | 0 |
| `>Ready<` | 0 |
| `Server Ready` | 0 |
| `Health Check` | 0 |

Required corrected strings are present: `Version 1.1.2`, `Ports Available`, `SMT_PORT_PREFLIGHT_PASSED`, `SMT_PORT_VALIDATION_PASSED`, `Actual UE 5.8 Local Launch evidence`, and `Actual post-End PIE cleanup evidence`.

## 17. Final gallery order

1. Thumbnail
2. Project Settings
3. Blueprint API
4. Local Launch
5. Port Conflict
6. Cleanup and Scope

## 18. Listing readiness

Global metadata text: `PASS`

Local Launch source accuracy: `PASS`

Preflight wording accuracy: `PASS`

Cleanup visual relevance: `PASS`

Blueprint copy: `PASS`

Technical requirements: `PASS`

Visual review: `PASS`

Claims: `PASS`

Rights: `PASS`

Privacy: `PASS`

Overall: `READY_FOR_LISTING_COPY`

## 19. Reproduction commands

Use an OS-temporary `<verifyRoot>` and the public package; do not use the existing checkout for Buyer Project captures.

```powershell
git clone --branch master https://github.com/metyatech/ServerManageToolPlugin.git <verifyRoot>\ServerManageToolPlugin
git -C <verifyRoot>\ServerManageToolPlugin fetch origin
pwsh -File <verifyRoot>\Automation\RenderMedia.ps1
python <verifyRoot>\Automation\GenerateCorrectionAudits.py
node --check <verifyRoot>\ServerManageToolPlugin\Marketing\Fab\ServerManageTool\1.1.2\source\scripts\media.js
git -C <verifyRoot>\ServerManageToolPlugin diff --check
```

The temporary evidence root contains the before/after hashes, source grep outputs, source mapping, render log, technical/visual/claims/rights/privacy audits, runtime evidence references, command log, and `Evidence-SHA256.txt`.

## 20. Evidence manifest

Evidence manifest: `Evidence/Evidence-SHA256.txt` under the temporary verification root. It contains 45 evidence entries and has SHA-256 `D84677E1EEC55098CE6C04689279F1D49277A8F58E3FE8FC63FE585F33A88166`. The six-image manifest is `Marketing/Fab/ServerManageTool/1.1.2/MediaManifest.json`, with six entries and total size `1,614,230` bytes.

The original `Docs/Verification/FabListingMediaProduction-1.1.2.md` was not changed. No Source, Config, Content, `.uplugin`, product documentation, release, tag, release asset, or Fab Listing input was changed.
