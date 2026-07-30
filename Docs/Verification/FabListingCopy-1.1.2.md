# Fab Listing Copy Audit — Server Manage Tool 1.1.2

## 1. Scope and verdict

This audit creates and verifies the English Fab Listing copy for Server Manage Tool 1.1.2. It covers listing fields, long description, Technical Details, features and workflow, limitations, FAQ, media captions, category and tags, Standard License pricing, public source/binary disclosure, AI/mature/forum/activation selections, Project File Link, documentation/support links, competitor research, character counts, claim safety, and the submission checklist.

Only the following new files were created in the isolated temporary clone:

- Marketing/Fab/ServerManageTool/1.1.2/listing/ListingCopy.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/ListingFields.json
- Marketing/Fab/ServerManageTool/1.1.2/listing/TechnicalDetails.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/FAQ.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/MediaCaptions.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/PricingDecision.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/CompetitivePricingResearch.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/PublicSourceDisclosure.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/SubmissionChecklist.md
- Docs/Verification/FabListingCopy-1.1.2.md

Verdict:

    Listing copy: PASS
    Technical details: PASS
    FAQ: PASS
    Media mapping: PASS
    Claims and limitations: PASS
    Public source/binary disclosure: PASS
    License and pricing recommendation: PASS
    Character counts: PASS
    Fab draft readiness: READY_FOR_FAB_DRAFT_INPUT
    Fab login, UI input, upload, save, review submission: NOT PERFORMED

## 2. Start Git state

Work used a fresh temporary clone. The existing checkout at the user workspace was not edited.

| Field | Value |
| --- | --- |
| Repository | ServerManageToolPlugin |
| Remote | https://github.com/metyatech/ServerManageToolPlugin.git |
| Branch | master |
| Local HEAD | 7204b056bc1bf910a9d2641b9d23999b41fe064c |
| origin/master | 7204b056bc1bf910a9d2641b9d23999b41fe064c |
| Divergence | 0 0 |
| Working tree | clean |
| Starting source diff | none |

The current HEAD contains the previously verified 1.1.2 package and corrected six-image media set. No existing source, uplugin, README, user guide, verification report, or media file was modified by this task.

## 3. Official Fab requirements reviewed

The following official Epic documentation was reviewed on 2026-07-30 JST:

- Publishing Assets for Sale or Free Download in Fab: https://dev.epicgames.com/documentation/fab/publishing-assets-for-sale-or-free-download-in-fab?lang=en-US
- Licenses and Pricing in Fab: https://dev.epicgames.com/documentation/fab/licenses-and-pricing-in-fab?lang=en-US
- Asset File Format and Structure Requirements in Fab: https://dev.epicgames.com/documentation/fab/asset-file-format-and-structure-requirements-in-fab?lang=en-US
- Publisher Get Started in Fab: https://dev.epicgames.com/documentation/fab/publisher-get-started-in-fab

Applied requirements:

- Title, narrative description, category, subcategory, tags, media, technical details, support, and review selections are represented in the draft.
- The Code Plugin package has a uplugin descriptor, Source, Content, Config, and code modules.
- The Project File Link points to a ZIP containing one plugin root.
- The six media files are 2560x1440 JPEGs, each below 3 MB and below the 25 MB total gallery limit.
- Fab Standard License is selected with both Personal and Professional prices.
- Mature content, AI, forum-post, and activation choices are explicit.
- Fab input and submission remain outside this task.

## 4. Product fact sources

Facts were cross-checked against:

- ServerManageTool.uplugin
- README.md
- Docs/UserGuide/index.md
- Docs/UserGuide/Configuration.md
- Docs/UserGuide/LocalLaunch.md
- Docs/UserGuide/BlueprintAPI.md
- Docs/UserGuide/Troubleshooting.md
- Docs/UserGuide/ReleaseNotes.md
- Docs/Verification/FabRelease-1.1.2-UE5.8-Win64.md
- Docs/Verification/SourceCopyrightProvenanceResolution-2026.md
- Marketing/Fab/ServerManageTool/1.1.2/MediaManifest.json
- The current public release ZIP

Measured source facts:

- Source files: 17
- C++ source files: 7
- header files: 7
- Build.cs files: 3
- Unreal modules: 3
- Editor modules: 1
- Runtime modules: 2
- UCLASS declarations: 3
- USTRUCT declarations: 1
- BlueprintCallable functions: 2
- Blueprint functions: Get Server Address and Request Server Exit

The uplugin descriptor reports Version 4, VersionName 1.1.2, FriendlyName Server Manage Tool, CreatedBy metyatech, CanContainContent true, and the three named modules.

## 5. Market and pricing review

Twelve public Fab listings were reviewed:

- Eight in Network & Multiplayer.
- Four in Engine Tools.

The sample includes voice, PlayFab, replication, party, server administration, server browser, HTTP, editor utility, asset tags, async actions, and batch editing products. It is directional rather than a complete market survey.

Visible price handling was conservative:

- Four sampled pages visibly showed Free.
- Eight sampled pages showed a license selector or no numeric amount in the fetched public view.
- No hidden or inferred paid price was recorded.

The full public-page table, tags, ratings, positioning, and URLs are in Marketing/Fab/ServerManageTool/1.1.2/listing/CompetitivePricingResearch.md. The product is positioned as a focused Editor/PIE server-process workflow, not as replication, online services, voice, matchmaking, hosting, deployment, or production infrastructure.

## 6. Title and short description

| Field | Text | Count | Gate |
| --- | --- | ---: | --- |
| Title | Server Manage Tool | 18 | PASS; within the official 30-character guidance |
| Short description | Configure map-specific server addresses and launch validated local server groups during Unreal Engine PIE with all-port preflight and managed cleanup. | 150 | PASS; within the 160-character listing gate |

The copy avoids unsupported promotional superlatives and does not use easy, powerful, ultimate, or seamless.

## 7. Long description structure

The long description is stored in ListingCopy.md and in ListingFields.json. Its structure is:

1. What it does.
2. Key features.
3. Typical workflow.
4. Blueprint API.
5. Requirements and scope.
6. Limitations.
7. Source and release transparency.
8. Documentation and support.
9. 1.1.2 changelog.

Measured long-description length is 5,302 characters. The text uses the buyer’s workflow as the organizing structure and keeps the production-server boundary adjacent to the requirements.

## 8. Features and workflow claims

The following claims are supported by the source and current verification records:

- Map-specific entries are configured in Project Settings > Project > Servers.
- Project Setting mode returns configured addresses.
- Local Launch starts the configured local server group at PIE begin.
- Local Launch starts at fixed base port 7777 and follows Server List order.
- All required UDP ports are preflighted before a managed process starts.
- An unavailable required port rejects the complete launch attempt.
- Expected-versus-actual runtime port validation is recorded.
- Managed processes are cleared at End PIE and module shutdown.
- Get Server Address and Request Server Exit are the two Blueprint-callable functions.

The copy does not claim:

- automatic client connection;
- health checks;
- retries or automatic restarts;
- selective entry launch;
- port shifting;
- production build, packaging, deployment, or hosting;
- a dedicated TargetType.Server executable;
- a guaranteed operating-system exit code;
- replication or an online-service backend.

## 9. Technical Details

Technical Details are in TechnicalDetails.md. The package fact table records:

- Unreal Engine 5.8.
- Verified Win64 platform.
- Unreal Engine Code Plugin distribution.
- Three modules: one Editor and two Runtime.
- Seventeen Source files.
- Two BlueprintCallable functions.
- One packaged Content documentation file.
- No detected third-party dependency in Build.cs or the public release package.

The statement “Network Replication: Not provided by the plugin” is intentional. The plugin manages local PIE server processes and address resolution; it does not implement gameplay replication.

## 10. FAQ

FAQ.md contains exactly nine buyer-facing questions:

1. Production dedicated-server build or hosting.
2. Existing Unreal project compatibility.
3. Blueprint-only host use.
4. Local Launch port assignment.
5. Required UDP port conflict behavior.
6. Automatic client connection.
7. Health checks, retries, and restarts.
8. Open-source/license boundary.
9. Documentation and support.

Each answer is direct and repeats the relevant boundary where a buyer could otherwise infer unsupported functionality.

## 11. Category, subcategory, and tags

Recommended selections:

- Product type: Tools & Plugins.
- Subcategory: Network & Multiplayer.
- Ordered tags: Plugin, CodePlugin, Blueprint, Multiplayer, Network, Server, Dedicated, Editor, Tool, Development.

The selected labels were observed on public Fab pages in the competitor sample. Testing was not selected because it was not observed in the reviewed public pages. The Fab UI remains authoritative for the final selectable tag set; no Fab UI was accessed in this task.

## 12. License and pricing

Recommended license and prices:

| Selection | Value |
| --- | --- |
| License | Fab Standard License |
| Personal | USD 9.99 |
| Professional | USD 29.99 |
| Base currency | USD |
| Tax/VAT | Fab may apply taxes or VAT |

Fab’s published pricing documentation was used for the tier and preset-price checks. The price recommendation reflects the focused Editor/PIE scope, verified Win64 package, three modules, two Blueprint functions, packaged documentation, public source inspection, and public prebuilt release files. It does not present the public release ZIP as free or open source.

## 13. AI, mature, forum, and activation selections

Recommended draft selections:

| Field | Selection |
| --- | --- |
| Generated with AI | No |
| Allows usage with AI | No |
| NoAI tag | Enabled |
| Mature content | Not Mature |
| Promotional content | No |
| Forum post | No forum post |
| Activation | Manual activation |

No image-generation tool or third-party asset was used for the six final media images. The media rights audit records actual product UI, actual Unreal Editor evidence, local text/shapes, and the product icon only.

## 14. Public source and binary disclosure

The exact buyer-facing disclosure is stored in PublicSourceDisclosure.md and repeated in the long description:

The source repository and prebuilt release files are publicly accessible. The repository does not grant an open-source license.

Purchases through Fab are provided under the Fab Standard License and directly support continued development and maintenance.

Links:

- Source: https://github.com/metyatech/ServerManageToolPlugin
- Release ZIP: https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip
- Documentation: https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/
- Support: https://github.com/metyatech/ServerManageToolPlugin/issues

The public source link is source-access disclosure, not an OSS grant. The Fab Standard License remains the buyer license.

## 15. Media mapping

Upload order, captions, alt text, rights, and privacy checks are stored in MediaCaptions.md.

| Order | Role | File | Bytes | SHA-256 |
| ---: | --- | --- | ---: | --- |
| 0 | Thumbnail | ServerManageTool-Thumbnail.jpg | 254,120 | 909A8BC451403A4EA86F0965C9DA2BE7A45B6D9C01BF9457B5836254E4055D67 |
| 1 | Gallery | ServerManageTool-01-Project-Settings.jpg | 292,178 | 288E7163F8A1128BFA5520313CEF1CD5EFA0D94603E539FD0C1CA79E30E85B71 |
| 2 | Gallery | ServerManageTool-02-Blueprint-API.jpg | 337,362 | D8221F2223F6335B22D30BA0B319EE23C57675853D9AD7CFD6E8A2E5DA306527 |
| 3 | Gallery | ServerManageTool-03-Local-Launch.jpg | 240,589 | D8B4D0C20482A28E5D9F12F5D2D1E86F5ACDE016B0F93F43B8A790606F679C08 |
| 4 | Gallery | ServerManageTool-04-Port-Conflict.jpg | 256,787 | CC106C6A7EA8D225CEDF905D85B322E6FEB9544C22307DA5EE18BE4A63B2700E |
| 5 | Gallery | ServerManageTool-05-Cleanup-Scope.jpg | 233,194 | 5FC5A91BAC4FBFF0E0B12CA4A4DAE848E3D16B0F90C369687F7AA536CBDA55BB |

Total final media bytes: 1,614,230. All six are 2560x1440 JPEGs. Every manifest entry records claims, rights, and privacy as PASS.

## 16. Character counts

The machine-readable evidence is Evidence/ListingCharacterCounts.json outside the repository.

| Item | Count | Limit/reference | Result |
| --- | ---: | ---: | --- |
| Title | 18 | 30 guidance | PASS |
| Short description | 150 | 160 listing gate | PASS |
| Long description | 5,302 | buyer-readability review | PASS |
| FAQ questions | 9 | requested 6–9 | PASS |
| Ordered tags | 10 | observed-label set | PASS |

## 17. Claims audit

Automated claims audit result: PASS.

Checks passed:

- required positive claims were found in the source-backed copy;
- fixed port 7777 and Server List order were present;
- preflight and no-partial-launch behavior were present;
- End PIE and module-shutdown cleanup were present;
- the TargetType.Server limitation was present;
- production build/deploy/host limitations were present;
- automatic client connection, health-check, retry, restart, and port-shift limitations were present;
- open-source licensing was not claimed;
- no banned promotional terms were found.

The audit files record the exact required-claim list and no missing claims.

## 18. Transparency audit

Transparency audit result: PASS.

- The required source/binary disclosure text is exact in the long description and PublicSourceDisclosure.md.
- Source repository and public release ZIP links are present.
- The public release SHA-256 is recorded.
- The copy does not describe the repository as Open Source.
- The copy does not grant MIT, Apache, BSD, or another OSS license.
- Fab Standard License is stated as the buyer license.
- The public ZIP is described as a release artifact, not as a free/open-source alternative.

## 19. Submission checklist

SubmissionChecklist.md contains the exact draft input sequence, media upload order, technical/legal checks, preview checks, and submit decision. It explicitly instructs the publisher to confirm tags in the Fab selector, verify the public ZIP hash before using Project File Link, and re-review title, description, images, and technical details before submitting.

The checklist records that Fab login, UI input, upload, draft save, review submission, and forum-post creation were not performed.

## 20. Final readiness

Offline evidence and copy readiness:

    Listing copy: PASS
    Technical Details: PASS
    FAQ: PASS
    Category/subcategory: PASS
    Observed tag labels: PASS; UI confirmation pending
    Standard License/pricing: PASS
    AI/mature/forum/activation selections: PASS
    Public source/binary disclosure: PASS
    Media mapping and claims: PASS
    Character counts: PASS
    Links: PASS; all four audited URLs returned HTTP 200
    Fab draft input: READY
    Fab submission: NOT PERFORMED

Final decision:

    READY_FOR_FAB_DRAFT_INPUT

This status does not mean Fab has accepted or published the listing. The publisher must still enter the fields, confirm the current Fab selectors, upload the six images, preview the result, save a draft, resolve any Fab validation/moderation feedback, and submit through Fab when ready.

## 21. Reproduction commands

Use a new temporary root and do not edit the existing checkout.

    $Root = '<temp-root>'
    $Repo = Join-Path $Root 'ServerManageToolPlugin'
    git clone --branch master --single-branch https://github.com/metyatech/ServerManageToolPlugin.git $Repo
    git -C $Repo fetch origin
    git -C $Repo status --short
    git -C $Repo rev-parse HEAD
    git -C $Repo rev-parse origin/master
    git -C $Repo rev-list --left-right --count HEAD...origin/master
    py -3 (Join-Path $Root 'CollectEvidence.py')
    py -3 (Join-Path $Root 'AuditListing.py')
    git -C $Repo diff --check
    git -C $Repo status --short

The verification scripts used in this task are outside the repository under the temporary root. The public release hash can be independently checked with:

    $Zip = Join-Path $Root 'PublicDownloads\ServerManageTool-Fab-Current.zip'
    Invoke-WebRequest https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip -OutFile $Zip
    Get-FileHash -Algorithm SHA256 $Zip

No BuildPlugin run was needed for this copy-only change because source and package files were not modified. The current public release ZIP was downloaded and validated against the existing 1.1.2 release evidence and current master HEAD.

## 22. Evidence manifest

Temporary evidence is stored below the isolated root outside Git:

- Evidence/GitState.json
- Evidence/ProductFactMatrix.json
- Evidence/SourceCounts.json
- Evidence/PublicZipValidation.json
- Evidence/MediaMappingAudit.json
- Evidence/OfficialFabSources.json
- Evidence/CompetitiveListings.json
- Evidence/ListingCharacterCounts.json
- Evidence/ListingClaimsAudit.json
- Evidence/ListingTransparencyAudit.json
- Evidence/ListingLinkAudit.json
- Evidence/PricingAnalysis.json
- Evidence/TagState.json
- Evidence/Evidence-SHA256.txt

Public release package evidence:

- SHA-256: C1A043C3388520446DAB93B40FEFD6CE0E05F87D94544BB28A14B98098601443
- ZIP files: 34
- ZIP uncompressed bytes: 350,308
- ZIP compressed file bytes: 162,924
- one top-level plugin root: ServerManageTool
- Source files: 17
- Content files: 1
- Config present: yes
- Win64 binaries present: yes
- uplugin present: yes

Evidence/Evidence-SHA256.txt is generated after the final offline audit and excludes the report itself to avoid a self-referential hash. Its SHA-256 is 5FEE177C5C1A0A01CA1D7F854BABAC6D06A42FD8FE9D9222E09E216F760160B6.
