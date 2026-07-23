# Post-category Verification: UE 5.8 / Win64

Verification date: 2026-07-23 (Asia/Tokyo)

This report covers the exact five-category source change and the post-change verification. No source change was made in response to the new BuildPlugin failure. Temporary projects, logs, JSON, and scripts were kept outside the repository.

## 1. Verification execution status — FAIL

The five UE 5.8 UHT Category errors were removed by the specified diff. UHT completed, but BuildPlugin stopped with exit code 6 because UnrealBuildTool rejected four action paths longer than 260 characters. Per the execution gate, no further source or runtime plugin changes were attempted.

The complete direct-server reproduction script from the baseline report was extracted verbatim and executed successfully. Blueprint-only load, normal PIE, Simulate, and Editor-shutdown orphan checks were blocked by the failed BuildPlugin prerequisite.

## 2. Product readiness status — FAIL

The category fix is technically correct for the reported UHT errors, but the product is not ready for Fab release. The post-category package was not compiled because of the path-length failure, Game/Shipping coverage was not reached, the plugin package was not loaded into a Blueprint-only project, and the known port-conflict behavior remains unchanged.

## 3. Git baseline — PASS

- origin: https://github.com/metyatech/ServerManageToolPlugin
- Phase 1 start HEAD: 4d054375512c7e40dc3d11646091fc1d9d771170
- Phase 1 end HEAD: 5f52a6210c670cf073134574d5e80ed9ec4c7e85
- Phase 1 commit: docs: complete Fab baseline reproduction
- Phase 2 start HEAD: 5f52a6210c670cf073134574d5e80ed9ec4c7e85
- Phase 2 source-fix commit: d67cac1 (full commit URL is supplied in the delivery message)
- current branch during this report: fix/ue58-uht-categories
- fix branch was absent locally and remotely before creation
- no merge, force push, tag, release, PR, or Fab submission was performed

The final report commit changes only this report. Its final HEAD is supplied in the delivery message.

## 4. Exact source change — PASS

Only the requested five declarations changed:

- Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:15
  - UPROPERTY(Config, EditAnywhere, Category = "Server Management")
- Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:18
  - UPROPERTY(Config, EditAnywhere, Category = "Server Management")
- Source/ServerInfoSettingsModule/Public/ServerInfoSettings.h:30
  - UPROPERTY(Config, EditAnyWhere, Category = "Server Management")
- Source/ServerManageLibrary/Public/ServerManageLibraryBP.h:21
  - UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server Management")
- Source/ServerManageLibrary/Public/ServerManageLibraryBP.h:24
  - UFUNCTION(BlueprintCallable, Category = "Server Management")

The existing EditAnyWhere spelling was preserved. No function name, type, return value, module structure, Build.cs, uplugin, copyright, map, process, delegate, port, README, Config, Content, CI, or template comment changed.

Commit 1 contains exactly the two headers and these five additions/five removals.

## 5. UE environment — PASS

PowerShell 7 was used. UE_5_8_ROOT was unset, so the specified fallback was used:

    C:\Program Files\Epic Games\UE_5.8

Build.version reported MajorVersion 5, MinorVersion 8, PatchVersion 0. InstalledBuild.txt exists and contains UE_5.8, so this was the Launcher Installed Build.

## 6. BuildPlugin — FAIL

The required post-category command ran with combined stdout/stderr in one log.

- temporary audit root: <auditRoot>
- exit code: 6
- BuildPlugin log SHA-256: 92CAF8BB7830DBB4B61FA6783C33DF34B4D06E8031F6BDD8BA0846EFA2503DA3
- detailed UBT log SHA-256: 0C5C9FC79A4BAABC00F8AA2C8191DCB4D6E407E38F4F8CB341CC1011502023BC
- UHT Category errors: no longer present
- UHT result: completed header parsing and code generation
- BuildPlugin result: Failed (OtherCompilationError)

The new consequential failure was:

    BuildException: The following action paths are longer than 260 characters. Please move the engine to a directory with a shorter path.

The rejected action paths were:

- 262 characters: ServerInfoSettingsModule/Module.ServerInfoSettingsModule.cpp.dep.json
- 261 characters: ServerInfoSettingsModule/Module.ServerInfoSettingsModule.cpp.obj.rsp
- 263 characters: ServerInfoSettingsModule/UnrealEditor-ServerInfoSettingsModule.dll.rsp
- 263 characters: ServerInfoSettingsModule/UnrealEditor-ServerInfoSettingsModule.lib.rsp

The log contained no remaining compiler error or Category error. The four long-path entries and the BuildException are the consequential warning/error evidence. The attempted target was UnrealEditor Win64 Development.

## 7. Development Editor — FAIL

Development Editor was attempted as UnrealEditor Win64 Development. UHT completed, but the target failed before compilation/action execution because of the four path-length checks. No successful Editor binary result is claimed.

## 8. Development Game — BLOCKED

Development Game was not reached. BuildPlugin stopped during the Development Editor target and did not produce a successful package from which an UnrealGame Win64 Development target could be verified.

## 9. Shipping Game — BLOCKED

Shipping Game was not reached. BuildPlugin stopped before an UnrealGame Win64 Shipping target or Shipping module mapping could be verified.

## 10. Package contents — FAIL

The failed package staging root was <auditRoot>/BuildPlugin/HostProject/Plugins/ServerManageTool. Observed entries were:

| Entry | Result |
| --- | --- |
| ServerManageTool.uplugin | present; staging copy only |
| Source | present |
| Resources | present |
| Config | present as generated FilterPlugin.ini |
| Docs | present in staging |
| Intermediate | present; failed-build intermediates |
| Binaries | absent |
| Content | absent |
| .modules files | none found |
| Installed | false |
| EngineVersion | absent |
| module list | ServerModePlayMenu (Editor), ServerInfoSettingsModule (Runtime), ServerManageLibrary (Runtime) |

The staging copy also contained .git metadata. Because no compiled Binaries or .modules files were produced, this staging tree is not a releasable plugin package.

## 11. Blueprint-only load — BLOCKED

The BuildPlugin-success prerequisite was not met. The Blueprint-only project was not created or launched, so plugin load, missing/incompatible modules, compile request, C++ conversion request, log result, and warning result are all unverified.

## 12. Normal PIE lifecycle — BLOCKED

The Blueprint-only load prerequisite was not met. No plugin-managed normal PIE run occurred, so no parent PID, child PID, port, or child cleanup result is claimed.

## 13. Simulate lifecycle — BLOCKED

The Blueprint-only load prerequisite was not met. No plugin-managed Simulate run occurred, so no parent PID, child PID, port, or cleanup result is claimed.

## 14. Editor shutdown orphan — BLOCKED

The plugin-managed shutdown test was not run because BuildPlugin and Blueprint-only load were blocked. The direct-server validation's final target process count of zero is separate evidence and is not an Editor-shutdown orphan result.

## 15. Port-conflict baseline carried forward — FAIL

The exact direct-server reproduction script was rerun after the category fix:

- single: PID 43312, requested/actual 17777/17777
- multiple: PID 29680, requested/actual 17777/17777
- multiple: PID 60304, requested/actual 17778/17778
- conflict: PID 18192, requested 17777, actual 17779, alive during the 30-second check
- final matching target processes after forced cleanup and 10 seconds: 0

The category fix did not alter the known auto-port-change behavior. This remains a product blocker.

## 16. Remaining blockers — FAIL

1. Resolve the UE 5.8 BuildPlugin path-length failure without changing unrelated source behavior.
2. Rerun BuildPlugin and verify a successful compiled package, including Binaries and .modules files.
3. Verify UnrealEditor Win64 Development, UnrealGame Win64 Development, and UnrealGame Win64 Shipping separately.
4. Verify Game/Shipping module mappings contain ServerInfoSettingsModule and ServerManageLibrary and exclude Editor-only ServerModePlayMenu.
5. Run Blueprint-only load, normal PIE, Simulate, and Editor-shutdown orphan checks after package success.
6. Resolve the requested-port conflict policy; current behavior changes 17777 to 17779 and leaves the process alive.
7. Address Fab structural requirements and release-quality gates recorded in the baseline report.

## 17. Evidence table — PASS

All paths below are relative to the temporary post-category root unless stated otherwise.

| Evidence | SHA-256 or result |
| --- | --- |
| BuildPlugin.log | 92CAF8BB7830DBB4B61FA6783C33DF34B4D06E8031F6BDD8BA0846EFA2503DA3 |
| UBA-UnrealEditor-Win64-Development.txt | 0C5C9FC79A4BAABC00F8AA2C8191DCB4D6E407E38F4F8CB341CC1011502023BC |
| direct validation script copied from baseline report | B60C6B0C34D6E0B8453658E578086FDD132A425AF4281D852B625FB74BAC68CD |
| direct validation transcript | FEE3788D16ECB24CCCA16251023BE165F797CAA3A65147BF221AA3A417104C0C |
| direct validation result JSON | 514423D405E422FB5C1262F7A0DC3868169DCD0C466A5F38DE97BB92006AABAB |
| DirectSingle-17777.log | 51DCB05FA8357A019CBA0990A37E41F708B5D809689C8DF11A76B4AE2298908D |
| DirectMulti-17777.log | 0D1A1C9C1B88C0B5AFCB8B1D5A77EBA622C777E77494841A3D1FD3E5B869AA63 |
| DirectMulti-17778.log | 0C62C0AAD09EB7441E33FE80685BDFF1BCC43FC7F1E5385219F221B519BDBAE9 |
| DirectConflict-17777.log | AA3C61902CDBFC362D5DB0DECE3D17F8840BA946FE5B25796995AB1A10C1ABF9 |
| post-category final target process count | 0 |
| source diff check | PASS; exactly two headers and five declarations |

## 18. Exact reproduction commands — PASS

Run from the repository root in PowerShell 7. The BuildPlugin command used for this verification was:

```powershell
$ErrorActionPreference = "Stop"
$repoRoot = (Get-Location).Path
$ueRoot = $env:UE_5_8_ROOT
if ([string]::IsNullOrWhiteSpace($ueRoot)) {
    $ueRoot = "C:\Program Files\Epic Games\UE_5.8"
}
$stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$auditRoot = Join-Path $env:TEMP "ServerManageToolPlugin-FabPostCategory-$stamp"
$buildRoot = Join-Path $auditRoot "BuildPlugin"
$buildLog = Join-Path $auditRoot "BuildPlugin.log"
New-Item -ItemType Directory -Path $auditRoot -Force | Out-Null
& "$ueRoot\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin "-Plugin=$repoRoot\ServerManageTool.uplugin" "-Package=$buildRoot" -TargetPlatforms=Win64 -Rocket *> $buildLog
$exitCode = $LASTEXITCODE
Write-Output "BuildPluginExitCode=$exitCode"
Get-FileHash -Algorithm SHA256 -LiteralPath $buildLog
```

For the full direct-server reproduction script, use Section 18 of the baseline report: FabBaseline-UE5.8-Win64.md, anchor 18-exact-reproduction-commands--pass. The script was extracted verbatim into a temporary .ps1 and executed for this post-category validation; no shortened replacement was used.
