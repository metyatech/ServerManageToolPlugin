# Troubleshooting

**Start with the Output Log marker that matches the failure.** Then check the map configuration, Server List order, project server support, and the required local ports.

## Get Server Address returns empty

Check the following:

- `Map` is not null.
- The entry is under `Project Settings > Project > Servers`.
- `Map Name` is the full package name, such as `/Game/Maps/Lobby`.
- The configured name exactly matches the map asset's long package name.
- The map entry was not accidentally removed or reordered.

An empty result means the current map was null or no exact configured entry was found.

## Local Launch starts no servers

Check:

- **Server Mode** is set to **Local Launch**.
- The Server List contains the intended entries.
- The project supports running with `-server`.
- The Unreal Editor executable is available.
- The map package names are valid.
- The Output Log contains `SMT_PORT_PREFLIGHT_FAILED` or `SMT_SERVER_PROCESS_LAUNCH_FAILED`.

If preflight fails, no partial server group should remain from that attempt.

## UDP port conflict notification

When a required port is unavailable, the plugin reports the unavailable port in the notification and writes `SMT_PORT_PREFLIGHT_FAILED` to the Output Log.

1. Identify the unavailable port.
2. Stop or reconfigure the unrelated holder if appropriate.
3. Confirm that the project owns the intended port.
4. Start PIE again.

Do not assume that the plugin automatically shifts the whole managed group to new ports.

## Server starts on a different port

Search for `SMT_PORT_VALIDATION_FAILED`. The marker records the expected and actual port and requests clean exit from the server process.

Do not rely on a specific operating-system exit code. Use the marker and the actual socket evidence instead.

## Project does not support `-server`

This plugin launches the project's Unreal Editor executable with server arguments. It does not add dedicated-server gameplay support to the project. Add and verify the project's own `-server` support first.

## Client does not connect automatically

This is expected. `Get Server Address` only resolves an address. Pass the result to the project's own client-travel or connection flow.

## Local ports changed after reordering

Local Launch assigns ports by Server List position. Reordering entries changes their ports. Restore the previous order or update the project code that uses the assigned addresses.

## Local startup takes longer than expected

Local startup includes process creation, map loading, and socket binding. There is no automatic health check, retry, or restart. Keep the editor open, inspect the Output Log, and check whether the child process reached the validation marker.

## Collect Output Log evidence

Include:

- the selected Server Mode;
- the complete Server List entries and their order;
- the map package name;
- the exact markers around the failure;
- the Unreal Engine version;
- whether the project is Blueprint-only or source-built;
- whether a second process already owned `7777` or another assigned port.

Remove unrelated personal data before sharing logs.

## GitHub issue information

Open an issue at the [Server Manage Tool issue tracker](https://github.com/metyatech/ServerManageToolPlugin/issues). Include a short reproduction, expected and actual behavior, plugin version, engine version, selected mode, sanitized Output Log evidence, and the relevant configuration. Do not attach credentials, private project data, or production server secrets.
