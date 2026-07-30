# Server Manage Tool 1.1.2 Fab listing media

This directory is the canonical, editable source and final media set for the Server Manage Tool 1.1.2 Fab listing.

## Canonical deliverables

- `final/ServerManageTool-Thumbnail.jpg`
- `final/ServerManageTool-01-Project-Settings.jpg`
- `final/ServerManageTool-02-Blueprint-API.jpg`
- `final/ServerManageTool-03-Local-Launch.jpg`
- `final/ServerManageTool-04-Port-Conflict.jpg`
- `final/ServerManageTool-05-Cleanup-Scope.jpg`

`review/ContactSheet.jpg` is a review artifact and is not part of the six-image submission set.

## Re-render

The editable source is `source/html/index.html`, with styles in `source/css/media.css`, rendering logic in `source/scripts/media.js`, and measured Unreal Editor crops in `source/assets/`.

The source is rendered at 2560x1440 with Chromium using the local HTML server, then converted to sRGB JPEG by the temporary verification automation. No network images, external fonts, image-generation tools, or third-party assets are required.

## Evidence and usage

`MediaManifest.json`, `Copy.md`, and `Rights.md` record the final files, copy review, and permitted source elements. The companion verification report is `Docs/Verification/FabListingMediaProduction-1.1.2.md`.

The media describes Editor/PIE workflows only. It does not claim production hosting, deployment, automatic port shifting, or a dedicated `TargetType.Server` executable.
