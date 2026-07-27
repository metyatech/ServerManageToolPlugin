# Local Launch

**Local Launch starts all configured server entries during PIE after an all-port preflight.** It is an editor-only convenience workflow, not a health-check or production hosting system.

## Lifecycle

1. Select **Local Launch** in the editor's Server Mode menu.
2. Start PIE.
3. Read the Server List in order.
4. Assign `7777 + list index` to each entry.
5. Check every required UDP port before launching any server.
6. If every port is available, launch one local dedicated-server process per entry.
7. Pass the expected port to the server process.
8. Validate the port actually bound by each server.
9. Use the resulting loopback addresses through `Get Server Address`.
10. End PIE to clean up the managed processes.

The module also clears managed server ownership during module shutdown, including shutdown while a PIE session is active.

## All-or-nothing behavior

The plugin checks the complete port set first. If one configured port is unavailable, it reports the conflict and does not leave an earlier server from the same launch group running.

**OK example:** ports `7777` and `7778` are free, so both configured entries launch.

**NG example:** `7778` is held by another process, so neither configured entry is launched by this Local Launch attempt.

## Ports and runtime validation

The base port is fixed at `7777`. Server List order determines subsequent ports. A server can bind a different port because of external runtime conditions. The validator compares the expected port with the actual bound port, records the result, and requests clean exit on mismatch.

Do not rely on a specific operating-system exit code for a shifted-port mismatch. The Output Log marker and the requested cleanup action are the supported evidence.

## Timing and recovery

Typical startup includes editor process creation, map loading, and server socket binding. Allow the project enough time to reach its normal local startup state.

Local Launch provides **no health check, retry, or automatic restart**. If startup is slow or fails, inspect the Output Log and resolve the project, executable, map, or port condition before trying again.

## Output Log markers

Search the Output Log for these exact markers:

```text
SMT_PORT_PREFLIGHT_PASSED
SMT_PORT_PREFLIGHT_FAILED
SMT_SERVER_PROCESS_LAUNCH_FAILED
SMT_PORT_VALIDATION_PASSED
SMT_PORT_VALIDATION_FAILED
```

The markers identify preflight, process launch, and runtime validation outcomes. They do not guarantee a particular OS process exit status.

## Cleanup

- End PIE to stop managed Local Launch processes.
- If the editor module shuts down while PIE is active, module shutdown clears the managed server collection.
- Confirm that no project-owned child process or UDP endpoint remains before replacing plugin files.
