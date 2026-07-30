# Rights and privacy audit

## Permitted elements used

- `METYATECH_PRODUCT_UI`: actual Server Manage Tool UI shown in the UE 5.8 project-local plugin.
- `METYATECH_PRODUCT_ICON`: the product `Resources/Icon128.png` copied into the editable source assets.
- `UNREAL_EDITOR_UI_AS_ACTUAL_SCREENSHOT`: actual UE 5.8 Editor screens captured from the Blueprint-only buyer project.
- `WINDOWS_CONSOLE_AS_ACTUAL_PRODUCT_EVIDENCE`: only in temporary evidence; final media uses a cropped, non-path-bearing editor frame and measured markers.
- `TEXT_AND_BASIC_SHAPES`: local HTML/CSS/SVG-free layout text, panels, lines, arrows, and measured port/process diagrams.

## Excluded elements

The final six images contain no third-party asset, third-party logo, external font, downloaded icon pack, stock image, Marketplace/Fab asset, decorative Unreal/Epic/Fab logo, personal avatar, browser tab, Windows notification, username, email, machine name, absolute local path, private repository path, private URL, production address, `Udon-Tobira` text, or unrelated product name.

The addresses shown in the evidence are the non-production examples `lobby.example.test:9001` and `match.example.test:9002`.

## Basis

All source images under `source/assets/` are cropped from the temporary UE 5.8 evidence captures or copied from the product repository icon. The Local Launch crop comes from `Evidence/RawScreenshots/R06-local-launch-active-verified.png` at `(110,535)-(1400,560)` and shows the actual `SMT_PORT_VALIDATION_PASSED` line. The cleanup crop comes from `Evidence/RawScreenshots/R08-simulate-after-stop-verified.png` at `(0,0)-(1500,760)` and is the actual post-End PIE UE 5.8 Editor frame; the adjacent zero-process/zero-UDP values are measured evidence from the same Buyer Project. Both captures are from the public Server Manage Tool 1.1.2 package in the Blueprint-only `ServerManageToolDemo` Buyer Project. Final composition source is local HTML/CSS/JavaScript. No third-party asset, external font, decorative Unreal/Epic/Fab logo, private information, or image-generation tool was used.
