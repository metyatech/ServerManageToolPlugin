# Fab Listing Copy Correction Audit — Server Manage Tool 1.1.2

## 1. Scope

This correction updates only the five Listing files required to resolve four review findings:

1. Replace “validated local server groups” with wording that separates launch management, port preflight, port validation, and cleanup without implying server readiness or health monitoring.
2. Align Personal and Professional tier wording with the current Fab documentation and Standard License summary.
3. Replace the internal compressed-entry total with the actual public ZIP file size.
4. Represent NoAI as derived metadata associated with the AI-usage selection, not as an independently verified UI switch.

Product Source, Config, Content, uplugin, README, user guide, release/package/media files, version, tags, prices, GitHub Release, tag, public ZIP, and the original listing audit were not changed.

## 2. Start Git state

The existing checkout was not edited. Work used a fresh temporary clone.

| Field | Value |
| --- | --- |
| Repository | ServerManageToolPlugin |
| Remote | https://github.com/metyatech/ServerManageToolPlugin.git |
| Temporary clone branch | master |
| Temporary clone start HEAD | f6d0018fa78a85fe1cc103ccf395b514473694ab |
| origin/master at start | f6d0018fa78a85fe1cc103ccf395b514473694ab |
| Start divergence | 0 0 |
| Start working tree | clean |
| Existing checkout branch | verify/real-game-packaging |
| Existing checkout HEAD | ec69903ce95257be02a21020b37fca04ff04b0b1 |
| Existing checkout working tree | clean |

The repository was fetched before the start-state gate. The remote did not advance beyond the expected SHA.

## 3. Review findings

| Finding | Before | Correction |
| --- | --- | --- |
| Short description | Configure map-specific server addresses and launch validated local server groups during Unreal Engine PIE with all-port preflight and managed cleanup. | Configure map-specific server addresses and launch managed local server groups during Unreal Engine PIE with all-port preflight, port validation, and cleanup. |
| Tier explanation | The Personal tier is for Fab’s Personal license audience; Professional is priced separately for commercial teams. | Personal is for buyers who have not generated more than USD 100,000 in gross revenue from commercial activity during the last 12 months. Professional is for buyers who have generated more than USD 100,000 in gross revenue from commercial activity during the last 12 months. Buyers should select the tier that matches their own revenue situation. Both tiers grant the same scope of rights. |
| ZIP size | Public release ZIP compressed file bytes: 162,924 | Public release ZIP bytes: 169,758; Public release ZIP uncompressed bytes: 350,308 |
| AI metadata | Independent no_ai_tag boolean | Allows usage with AI: No, plus an explanatory ai_metadata_note; no independent UI switch is assumed |

The 162,924 value remains useful only as the ZIP central-directory entries’ compressed-size sum in temporary evidence. It is no longer presented as the buyer-facing ZIP file size.

## 4. Current official Fab pricing and license rules

The current official sources reviewed on 2026-07-30 JST were:

- Licenses and Pricing in Fab: https://dev.epicgames.com/documentation/fab/licenses-and-pricing-in-fab?lang=en-US
- Fab Standard License summary: https://www.fab.com/eula

The current rules used in the correction are:

- Fab Standard License requires both Personal and Professional price tiers.
- Personal is for buyers who have not generated more than USD 100,000 in gross revenue from commercial activity during the last 12 months.
- Professional is for buyers who have generated more than USD 100,000 in gross revenue from commercial activity during the last 12 months.
- The buyer chooses the appropriate tier based on the buyer’s own revenue situation.
- Both Personal and Professional tiers grant the same scope of rights.
- Publishers set base prices in USD; VAT and additional tax may apply in some regions.
- USD 9.99 and USD 29.99 are valid prices in the current $0–$100 preset range.
- Fab describes NoAI as a metadata tag and requires Standard License compatibility for that tag. This correction does not treat NoAI as an independently verified UI input switch.

No product price was changed:

| Tier | Price |
| --- | ---: |
| Personal | USD 9.99 |
| Professional | USD 29.99 |

## 5. Short Description correction

The Short Description now reads:

Configure map-specific server addresses and launch managed local server groups during Unreal Engine PIE with all-port preflight, port validation, and cleanup.

The wording distinguishes:

- all-port UDP preflight before launch;
- requested-versus-actual port validation;
- managed cleanup at End PIE and module shutdown.

It does not state or imply server readiness, health checks, gameplay validation, or service-availability monitoring.

## 6. Personal/Professional tier correction

The old audience-oriented sentence was removed. The new sentence uses the current revenue basis, time period, revenue measure, and equal-rights distinction:

Personal is for buyers who have not generated more than USD 100,000 in gross revenue from commercial activity during the last 12 months. Professional is for buyers who have generated more than USD 100,000 in gross revenue from commercial activity during the last 12 months. Buyers should select the tier that matches their own revenue situation. Both tiers grant the same scope of rights.

The copy does not describe Personal as non-commercial, Professional as merely a commercial license, or either tier as changing product features or support.

## 7. ZIP byte-size correction

The public release was anonymously re-downloaded after the correction work began.

| Check | Result |
| --- | --- |
| HTTP status | 200 |
| ZIP file bytes | 169,758 |
| SHA-256 | C1A043C3388520446DAB93B40FEFD6CE0E05F87D94544BB28A14B98098601443 |
| File count | 34 |
| Uncompressed bytes | 350,308 |
| Root | ServerManageTool |

Technical Details now presents the actual ZIP file bytes and uncompressed bytes. The internal compressed-entry sum of 162,924 is not used as a buyer-facing ZIP size.

## 8. AI/NoAI metadata correction

ListingFields.json now retains:

- generated_with_ai: false
- allows_usage_with_ai: false

The independent no_ai_tag boolean was removed. It was replaced with:

    ai_metadata_note: Allows usage with AI is set to No; Fab applies the corresponding NoAI metadata.

SubmissionChecklist.md now instructs the publisher to:

- select Generated with AI: No;
- select Allows usage with AI: No;
- confirm that Fab applies the NoAI metadata from the AI-usage selection;
- confirm the exact current Fab UI label during draft input;
- avoid assuming a separate NoAI switch exists.

The copy distinguishes product AI capability, image-generation provenance, and Fab’s AI-usage metadata.

## 9. Changed files

Only these five existing Listing files and this new correction report are changed:

- Marketing/Fab/ServerManageTool/1.1.2/listing/ListingCopy.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/ListingFields.json
- Marketing/Fab/ServerManageTool/1.1.2/listing/TechnicalDetails.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/PricingDecision.md
- Marketing/Fab/ServerManageTool/1.1.2/listing/SubmissionChecklist.md
- Docs/Verification/FabListingCopyCorrection-1.1.2.md

FAQ.md, MediaCaptions.md, CompetitivePricingResearch.md, and PublicSourceDisclosure.md were not changed because the correction did not require them.

Final SHA-256 values:

| File | SHA-256 |
| --- | --- |
| ListingCopy.md | 7E9F9D8C3E1F200CF26F28042F6417AD47E45A145FD59376683F3B4649D8FFF9 |
| ListingFields.json | 5EE08EB3BD9D0965184EECCEFD6658F08FD3FA8F5FF5B8083BF45F18E3D6D5A8 |
| TechnicalDetails.md | 37E171643A2ED7ED2F573ED52DB8931BC944E2E2A30A92FD16989770ECE3D8B9 |
| PricingDecision.md | 8DEC75E895D2A3619541E35EAC5D255335F1FF655206419EB900BE19F3B767FA |
| SubmissionChecklist.md | 8C1C67A07693C7D34E5767E8BEE73012001675A64B9A03E21199119A3B657A76 |

## 10. Character-count validation

| Item | Value | Gate | Result |
| --- | ---: | ---: | --- |
| Title | 18 | 30 or fewer | PASS |
| Short Description | 158 | 160 or fewer | PASS |
| Long Description | 5,302 | unchanged from original | PASS |
| FAQ questions | 9 | requested 6–9 | PASS |
| Tags | 10 | unchanged | PASS |

## 11. JSON validation

ListingFields.json validation:

- JSON parse: PASS
- duplicate JSON keys: 0
- UTF-8 decode: PASS
- raw control characters: 0
- unsupported HTML: 0
- emoji: 0
- character_counts matches measured values: PASS
- no_ai_tag field absent: PASS
- ai_metadata_note present: PASS

## 12. Claims audit

The canonical Listing files were searched after editing.

Old expressions:

- validated local server groups: 0
- Professional is priced separately for commercial teams: 0
- Public release ZIP compressed file bytes: 0
- no_ai_tag true: 0

Required new expressions:

- managed local server groups: present
- all-port preflight: present
- port validation: present
- Public release ZIP bytes: present
- 169,758: present
- Allows usage with AI: present

The claims audit found no disallowed positive claim. Mentions of health checks, production hosting, open source, retries, and similar terms remain only as limitations, questions, or verification cautions.

Final claims status:

    CLAIMS_ACCURATE

## 13. Pricing and license audit

- Fab Standard License: PASS
- Personal price USD 9.99: PASS
- Professional price USD 29.99: PASS
- Current revenue-threshold wording: PASS
- Current 12-month period: PASS
- Gross revenue from commercial activity: PASS
- Personal not described as non-commercial: PASS
- Professional not reduced to a commercial-only label: PASS
- Equal rights stated: PASS
- No feature or support difference claimed between tiers: PASS
- Public source/binary does not replace the Fab buyer license: PASS

Final pricing/license status:

    PRICING_AND_LICENSE_PASS

## 14. Public source transparency audit

The existing exact disclosure remains intact:

The source repository and prebuilt release files are publicly accessible. The repository does not grant an open-source license.

Purchases through Fab are provided under the Fab Standard License and directly support continued development and maintenance.

The public source and release links remain unchanged. The repository is not called Open Source and no OSS grant is added.

Transparency status:

    PASS

## 15. Link and public ZIP validation

The unchanged public links were checked:

| Link | Result |
| --- | --- |
| Source repository | HTTP 200 |
| Project File Link | HTTP 200 |
| Online documentation | HTTP 200 |
| Support issue tracker | HTTP 200 |

The Project File Link remains:

https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip

The public ZIP SHA-256 and byte-level validation are recorded in PublicZipValidation.json.

## 16. Unchanged product and media state

The following remained unchanged:

- Source/**
- Config/**
- Content/**
- ServerManageTool.uplugin
- README.md
- Docs/UserGuide/**
- final media
- media source
- review ContactSheet
- MediaManifest.json
- Copy.md
- Rights.md
- existing Docs/Verification/FabListingCopy-1.1.2.md

All six final-media SHA-256 values match the before state. The original listing audit SHA-256 matches its HEAD blob and is unchanged:

    6099FF2C861EE35F7980D13D6628F1789C99DB035B3F66E6D5E2DB443588D882

## 17. Final readiness

Correction results:

    Short Description: PASS
    Pricing tier explanation: PASS
    ZIP size terminology: PASS
    AI field mapping: PASS
    JSON parse: PASS
    Character counts: PASS
    Claims: PASS
    Pricing and license: PASS
    Public source transparency: PASS
    Links and public ZIP: PASS
    Overall: READY_FOR_FAB_DRAFT_INPUT
    Fab input: not performed
    Fab submission: not performed

The source and package were not rebuilt because this correction changes only listing documentation and metadata copy. The public ZIP was independently revalidated and is unchanged.

## 18. Reproduction commands

Use a fresh temporary root and preserve the existing checkout.

    $Root = '<temp-root>'
    $Repo = Join-Path $Root 'ServerManageToolPlugin'
    git clone --branch master --single-branch https://github.com/metyatech/ServerManageToolPlugin.git $Repo
    git -C $Repo fetch origin
    git -C $Repo rev-parse HEAD
    git -C $Repo rev-parse origin/master
    git -C $Repo rev-list --left-right --count HEAD...origin/master
    Invoke-WebRequest https://github.com/metyatech/ServerManageToolPlugin/releases/latest/download/ServerManageTool-Fab-Current.zip -OutFile (Join-Path $Root 'PublicDownloads\ServerManageTool-Fab-Current.zip')
    py -3 (Join-Path $Root 'CollectBefore.py')
    py -3 (Join-Path $Root 'AuditCorrection.py')
    git -C $Repo diff --check
    git -C $Repo diff --name-only HEAD

Fab login, Draft input, media upload, Draft save, review submission, and Fab submission are intentionally excluded.

## 19. Evidence manifest

Temporary evidence is outside Git under the isolated root:

- Evidence/GitState.json
- Evidence/BeforeListingHashes.json
- Evidence/OfficialFabPricingRules.json
- Evidence/PublicZipValidation.json
- Evidence/ListingCharacterCounts.json
- Evidence/ListingFieldsParse.json
- Evidence/ListingClaimsAudit.json
- Evidence/ListingPricingLicenseAudit.json
- Evidence/ListingTransparencyAudit.json
- Evidence/SourceTextSearchBefore.txt
- Evidence/SourceTextSearchAfter.txt
- Evidence/SourceTextSearchSummary.json
- Evidence/ChangedFiles.txt
- Evidence/MediaBeforeHashes.json
- Evidence/MediaAfterHashes.json
- Evidence/MediaUnchangedAudit.json
- Evidence/UnchangedState.json
- Evidence/CommandLog.txt
- Evidence/Evidence-SHA256.txt

The final Evidence-SHA256.txt is generated after all evidence is stable, excludes itself and this correction report to avoid circular hashing, and records every evidence file, changed Listing file, original listing audit, final media file, release-state snapshot, and the public ZIP. Manifest SHA-256: B23CA447CDDB5484DDFF7DE339EE8E2E3DC1ECA4C6EF3D7ABB1829F478F879A7. Entry count: 35.
