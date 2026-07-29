# Server Manage Tool 1.1.1 Release Audit — UE 5.8 Win64

Verification date: 2026-07-29 JST

## 1. Scope and final decision

This audit covers the Server Manage Tool 1.1.1 metadata normalization, product-facing documentation correction, final BuildPlugin output, sanitized candidate ZIP, extracted-package runtime checks, and release preparation. No product behavior, Blueprint API, Source, Config, or Content behavior was changed.

Decision at report creation, before the GitHub Release was published:

- Metadata update: PASS
- Documentation consistency: PASS
- Product behavior changes: 0
- Final BuildPlugin: PASS
- Final candidate ZIP: PASS
- Fab submission readiness: READY_WITH_DISCLOSED_LIMITATIONS
- Fab submission: not performed
- GitHub Release publication: PENDING at report creation

## 2. Start Git state

All work was performed in fresh temporary clones under `D:\T\SMT111-20260729-125320`. Existing `D:\ghws` checkouts were not modified.

Plugin release clone:

- Remote: `https://github.com/metyatech/ServerManageToolPlugin`
- Branch: `master`
- Start HEAD: `ee76633b85885adeda88cb159b52e5f84a562eff`
- Start `origin/master`: `ee76633b85885adeda88cb159b52e5f84a562eff`
- Start working tree: clean
- Product preparation commit: `638aff716d422413e760469318e316fb22dc035f`

Central documentation release clone:

- Remote: `https://github.com/metyatech/unreal-plugin-docs.git`
- Branch: `main`
- Start HEAD: `8ccbc33de99e5a00de0521cba24a536e73f830a2`
- Start `origin/main`: `8ccbc33de99e5a00de0521cba24a536e73f830a2`
- Start working tree: clean
- Documentation commit: `083a7db1f3e4c2635cc4fb3db670415b7024dde5`

The existing checkouts were read-only checked and remained clean:

- `D:\ghws\ServerManageToolPlugin`: branch `verify/real-game-packaging`, HEAD `ec69903ce95257be02a21020b37fca04ff04b0b1`, clean.
- `D:\ghws\unreal-plugin-docs`: branch `main`, HEAD `8ccbc33de99e5a00de0521cba24a536e73f830a2`, clean.

Before creating `v1.1.1`, the existing `v1.1.0` tag resolved to annotated tag object `a1d2640e65b5dd8d917eb85f2e4c9eb581a686f4` and commit `ee76633b85885adeda88cb159b52e5f84a562eff`. The published v1.1.0 asset was 169,126 bytes with SHA-256 `BA8420ADEA1CD4A0B3EAEA6DF35F16E269F4D06CCAD00E9C4614160BB4A2405D`.

## 3. Exact source and documentation changes

The product preparation commit changed exactly these five files:

- `README.md`
- `Docs/UserGuide/index.md`
- `Docs/UserGuide/Installation.md`
- `Docs/UserGuide/ReleaseNotes.md`
- `ServerManageTool.uplugin`

The central documentation commit changed exactly `server-manage-tool/index.md`.

No `Source/**`, `Config/**`, or `Content/**` file changed. Existing `Docs/Verification/**` files were not changed. `git diff --check` passed for both commits.

## 4. Descriptor change

Only the requested descriptor fields changed:

| Field | Before | After |
| --- | --- | --- |
| `Version` | `2` | `3` |
| `VersionName` | `1.1.0` | `1.1.1` |
| `CreatedBy` | `Metyatech` | `metyatech` |

`FileVersion`, `FriendlyName`, `Description`, `Category`, URLs, module definitions, `CanContainContent`, and all other descriptor fields were preserved. The exact descriptor diff is recorded in `Evidence/DescriptorDiff.txt`.

## 5. Product-facing documentation consistency

The current-facing documentation now identifies version 1.1.1, records the lowercase publisher metadata, and states that no product behavior or Blueprint API changed.

The corrected verification scope is explicit:

- Blueprint-only UE 5.8 Win64 host plugin load.
- Real C++ game-project Development integration.
- Real C++ game-project Shipping integration.
- Packaged Development `AddressAndExit` execution.
- Packaged Shipping `AddressAndExit` execution.

The following limitation remains explicit: a dedicated `TargetType.Server` executable is not provided or verified. Product-facing files contain no case-sensitive `Metyatech` display name. The historical 1.1.0 release notes remain preserved.

## 6. Central documentation publication

Central documentation commit:

- Commit: `083a7db1f3e4c2635cc4fb3db670415b7024dde5`
- Message: `docs: update Server Manage Tool to 1.1.1`
- Push: `origin/main` completed
- Anonymous URL: <https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/>
- HTTP status: `200`
- Public page checks: version `1.1.1`, lowercase publisher reference, verification scope correction, dedicated `TargetType.Server` limitation, and historical 1.1.0 entry present

## 7. Unreal Engine and BuildPlugin

UE root: `C:\Program Files\Epic Games\UE_5.8`.

- `Build.version`: MajorVersion `5`, MinorVersion `8`, PatchVersion `0`
- `InstalledBuild.txt`: present
- BuildPlugin exit code: `0`
- `UnrealEditor Win64 Development`: `Result: Succeeded`
- `UnrealGame Win64 Development`: `Result: Succeeded`
- `UnrealGame Win64 Shipping`: `Result: Succeeded`
- UHT Category error matches: `0`
- path-length error matches: `0`
- `BUILD SUCCESSFUL`: present
- `Binaries\Win64`: present
- `UnrealEditor.modules`: present
- Build log SHA-256: `0FC016127CEA283AAE4B2A6C5EC559F05FE1C3AC9E056B795724E18243457BD2`

Exact command:

    RunUAT.bat BuildPlugin -Plugin=D:\T\SMT111-20260729-125320\ServerManageToolPlugin\ServerManageTool.uplugin -Package=D:\T\SMT111-20260729-125320\Build\BuildPluginPackage -TargetPlatforms=Win64 -Rocket

## 8. Final candidate ZIP

The candidate was sanitized from the BuildPlugin package. `Intermediate`, `Saved`, `DerivedDataCache`, PDB files, repository metadata, and `Docs/Verification` were excluded.

- Candidate ZIP: `C:\Users\Origin\Downloads\ServerManageTool-1.1.1-UE5.8-Win64.zip`
- SHA-256: `AFA1FEA37D289482051C880D735341083623FFEA1445F07346EBDE3D6BAA36F9`
- ZIP bytes: `169563`
- File count: `34`
- Uncompressed bytes: `350082`
- Central directory entries: `34`
- Root: `ServerManageTool/`
- Root folder count: `1`
- traversal entries: `0`
- encrypted entries: `0`
- duplicate normalized paths: `0`
- PDB entries: `0`
- `Docs/Verification` entries: `0`
- required top-level entries: PASS

The complete extracted inventory and validation are recorded in `D:\T\SMT111-20260729-125320\Evidence\Zip\zip-inventory.json` and `D:\T\SMT111-20260729-125320\Evidence\Zip\zip-validation.json`.

The Fab fixed-name asset was made by byte-for-byte copy, not recompression. Its staged path is `D:\T\SMT111-20260729-125320\ReleaseAssets\ServerManageTool-Fab-Current.zip`; it has the same SHA-256 and byte count as the versioned ZIP.

## 9. Blueprint-only package load

The same candidate ZIP was extracted to `D:\T\SMT111-20260729-125320\CandidateExtract` and loaded into a Blueprint-only host with no C++ `Modules` property.

- Three plugin modules loaded: PASS
- Missing modules: `0`
- Incompatible modules: `0`
- Compile requests: `0`
- C++ conversion requests: `0`
- Fatal/ensure/crash matches: `0`
- Parent exit code: `0`
- Timeout: false
- Forced termination: false
- Final host process count: `0`

Result: PASS.

## 10. Normal PIE regression

- Parent PID: `4016`
- Child PIDs: `37440`, `69868`
- Requested ports: `7777`, `7778`
- Actual UDP endpoints: `37440:7777`, `69868:7778`
- ParentProcessId for both children: `4016`
- `SMT_PORT_PREFLIGHT_PASSED`: `1`
- `SMT_PORT_VALIDATION_PASSED`: `2`
- `SMT_PORT_VALIDATION_FAILED`: `0`
- Maximum child count: `2`
- Final child count: `0`
- Final UDP owner count: `0`
- Parent exit code: `0`
- Timeout: false
- Forced termination: false

Result: PASS.

## 11. Simulate regression

Simulate completed with parent PID `14408`, maximum child count `2`, one preflight PASS, two validation PASS markers, zero validation FAIL markers, final child/UDP counts `0`, exit code `0`, timeout false, and forced termination false.

Result: PASS.

## 12. ORPHAN regression

ORPHAN completed with parent PID `12132`, maximum child count `2`, one preflight PASS, two validation PASS markers, zero validation FAIL markers, and a post-parent monitoring window of at least 10 seconds with final child/UDP counts `0`. Parent exit code was `0`; timeout and forced termination were false.

Result: PASS.

## 13. 7778 conflict regression

An independent exclusive UDP holder owned port `7778` before PIE.

- Holder PID: `45880`
- Editor parent PID: `45588`
- `SMT_PORT_PREFLIGHT_FAILED`: `1`
- Unavailable port: `7778`
- Managed child maximum: `0`
- Shifted child snapshots: `0`
- Final managed child count: `0`
- Holder remained alive and owned the endpoint before planned cleanup
- Holder endpoint count after planned cleanup: `0`
- Forced termination: false
- Editor exit code: `0`

The existing classifications were not changed or re-run as exit-status claims:

- Editor exit-status — `EDITOR_STATUS_INCONSISTENT`
- Port conflict implementation — `PARTIAL_PACKAGED_TEST_BLOCKED`

Result: PASS for preflight/no-partial-start behavior.

## 14. Previously completed real-project and packaged verification

The existing verified report `Docs/Verification/FabPostRealGamePackaging-UE5.8-Win64.md` established:

- Real C++ game-project Development integration: PASS
- Real C++ game-project Shipping integration: PASS
- Packaged Development `AddressAndExit`: PASS
- Packaged Shipping `AddressAndExit`: PASS

This 1.1.1 change contains no Source or runtime behavior change, so those completed verification results remain applicable. The dedicated `TargetType.Server` limitation remains and no such target was added.

## 15. Disclosed product limitations

- Local Launch is Editor/PIE only.
- The project must already support its own server behavior.
- The plugin does not build, package, deploy, or host a production server.
- A dedicated `TargetType.Server` executable is not provided or verified.
- Do not rely on a specific operating-system exit code after shifted-port detection.
- Editor exit-status classification remains `EDITOR_STATUS_INCONSISTENT`.
- Port conflict implementation classification remains `PARTIAL_PACKAGED_TEST_BLOCKED`.

## 16. Evidence SHA-256

Pre-report evidence manifest:

- Path: `D:\T\SMT111-20260729-125320\Evidence-SHA256-pre-report.txt`
- Entry count: `93`
- Bytes: `14031`
- SHA-256: `456FF501040C1B186C1B8B67B57527C5AB0E727CE9507FD6EC7766F55576C1EF`

Selected evidence hashes are recorded in the manifest. A final post-release manifest will be generated after the two GitHub Release assets and all anonymous download checks complete.

## 17. Release publication status at report creation

The product preparation and central documentation commits were pushed. The `v1.1.1` annotated tag and GitHub Release were intentionally not created until this report commit was complete.

Pending items at report creation:

- Push `docs: record Server Manage Tool 1.1.1 release` to `master`.
- Create annotated tag `v1.1.1` targeting the final report commit.
- Publish `Server Manage Tool 1.1.1` with exactly two assets.
- Verify the three anonymous download URLs and `releases/latest`.

## 18. Exact reproduction commands

From the temporary release root:

    git -C D:\T\SMT111-20260729-125320\ServerManageToolPlugin fetch origin --tags --prune
    git -C D:\T\SMT111-20260729-125320\unreal-plugin-docs fetch origin --tags --prune
    RunUAT.bat BuildPlugin -Plugin=D:\T\SMT111-20260729-125320\ServerManageToolPlugin\ServerManageTool.uplugin -Package=D:\T\SMT111-20260729-125320\Build\BuildPluginPackage -TargetPlatforms=Win64 -Rocket
    pwsh -NoLogo -NoProfile -File D:\T\SMT111-20260729-125320\Scripts\SanitizeAndPackage.ps1 -BuildPackageRoot D:\T\SMT111-20260729-125320\Build\BuildPluginPackage -CandidateRoot D:\T\SMT111-20260729-125320\Candidate2\ServerManageTool -ZipPath D:\T\SMT111-20260729-125320\CandidateZip2\ServerManageTool-1.1.1-UE5.8-Win64.zip
    python D:\T\SMT111-20260729-125320\Scripts\ValidateFinalZip.py --zip D:\T\SMT111-20260729-125320\CandidateZip\ServerManageTool-1.1.1-UE5.8-Win64.zip --extract-root D:\T\SMT111-20260729-125320\CandidateExtract2 --evidence-root D:\T\SMT111-20260729-125320\Evidence\Zip2
    pwsh -NoLogo -NoProfile -File D:\T\SMT111-20260729-125320\Scripts\RunBlueprintOnlyCleanExit.ps1
    pwsh -NoLogo -NoProfile -File D:\T\SMT111-20260729-125320\Scripts\RunNormalLifecycle.ps1 -Mode PIE
    pwsh -NoLogo -NoProfile -File D:\T\SMT111-20260729-125320\Scripts\RunNormalLifecycle.ps1 -Mode SIMULATE
    pwsh -NoLogo -NoProfile -File D:\T\SMT111-20260729-125320\Scripts\RunNormalLifecycle.ps1 -Mode ORPHAN
    pwsh -NoLogo -NoProfile -File D:\T\SMT111-20260729-125320\Scripts\RunPortConflict.ps1

## 19. Final Git state at report creation

- Product preparation commit pushed to `origin/master`: PASS
- Central documentation commit pushed to `origin/main`: PASS
- Product audit report commit: PENDING at report creation
- `v1.1.1` tag: PENDING at report creation
- GitHub Release: PENDING at report creation
- Force push: not used
- PR: not created
- Fab submission: not performed
