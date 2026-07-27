# Installation

**Install one plugin copy, enable it, and restart the editor before configuring servers.** A restart ensures all three plugin modules load together.

## Fab installation

1. Acquire **Server Manage Tool** from Fab.
2. Install it for the Unreal Engine version used by the project.
3. Open the project.
4. Open `Edit > Plugins`.
5. Enable **Server Manage Tool**.
6. Restart the editor when requested.

## Project plugin installation

For a source or locally copied package, place the plugin folder at:

```text
<Project>/Plugins/ServerManageTool
```

The folder must contain `ServerManageTool.uplugin` at its root. Do not place the `.uplugin` one directory deeper, because the editor will not discover the package there.

## Supported verification target

Version 1.1.0 was verified with a Blueprint-only host on **Unreal Engine 5.8 Win64**. A Blueprint-only project does not need a C++ `Modules` property to load the packaged plugin.

## Source project rebuild

If you are using a source project or changing the plugin's C++ source:

1. Close the Unreal Editor.
2. Keep the plugin under `<Project>/Plugins/ServerManageTool`.
3. Regenerate project files using the project's normal Unreal workflow.
4. Build the project and plugin modules for the required target.
5. Open the project and enable the plugin if it is not already enabled.
6. Restart the editor after a module rebuild.

Use the project's normal build configuration. This guide does not claim that a particular project has been integrated or packaged successfully.

## Uninstall

1. Close the Unreal Editor and any local server processes.
2. Disable **Server Manage Tool** in `Edit > Plugins` if the project is still open.
3. Remove the plugin folder from `<Project>/Plugins/ServerManageTool` or uninstall it through Fab.
4. Reopen the project and remove project settings or Blueprint references that belonged to the plugin.

**Why restart?** The plugin includes editor and runtime modules. Restarting avoids leaving an old module binary loaded while the package is being replaced.
