# Frequently Asked Questions

## 1. Does this plugin build or host a production dedicated server?

No. Server Manage Tool is an Editor/PIE workflow for launching the project’s local server processes. Your project must provide its own server behavior. The plugin does not build, package, deploy, or host a production server and does not include a TargetType.Server executable.

## 2. Can I use it with an existing Unreal project?

Yes, when the project has a valid .uproject, uses full Unreal map package names, and already supports the project’s intended -server behavior. UE 5.8 Win64 is the verified version and platform for 1.1.2.

## 3. Is the plugin usable from a Blueprint-only host?

Yes. The packaged plugin was verified in a Blueprint-only UE 5.8 host without adding a C++ Modules property. The project still needs the project-side behavior required by its own server workflow.

## 4. How are Local Launch ports assigned?

Local Launch starts with fixed base port 7777 and increments by one for each Server List entry. Server List order determines the mapping, so reordering entries changes assigned ports.

## 5. What happens when one required UDP port is already in use?

The plugin checks all required ports before starting the group. If one port is unavailable, the complete Local Launch attempt is rejected and no partial managed server group is started. The plugin does not shift the group to another port range.

## 6. Does the plugin connect the client automatically?

No. Get Server Address returns an address string. Pass that result to the project’s own client connection or travel flow.

## 7. Does the plugin provide health checks, retries, or automatic restarts?

No. It validates the expected and actual port for a managed process, requests server exit on a mismatch, and cleans up managed processes at End PIE or module shutdown. Health checks, retries, and restarts are outside the product scope.

## 8. Is the source repository open source?

The source repository and public release files are accessible, but the repository does not grant an open-source license. Fab purchases are provided under the Fab Standard License.

## 9. Where can I find documentation and support?

Online documentation is available at https://metyatech.github.io/unreal-plugin-docs/server-manage-tool/. Report issues at https://github.com/metyatech/ServerManageToolPlugin/issues. Include sanitized logs, the plugin and engine versions, the selected mode, and the relevant Server List configuration.
