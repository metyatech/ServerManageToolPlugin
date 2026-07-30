const A = "../assets/";
const assets = {
  icon: A + "ServerManageTool-icon.png",
  tree: A + "ue-plugin-tree.png",
  settings: A + "ue-project-settings.png",
  blueprint: A + "ue-blueprint-graph.png",
  addressSearch: A + "ue-blueprint-search-address.png",
  exitSearch: A + "ue-blueprint-search-exit.png",
  local: A + "ue-local-launch-console.png",
  conflict: A + "ue-conflict-log.png",
  simulate: A + "ue-simulate-active.png",
  simulateMenu: A + "ue-simulate-menu.png",
  cleanup: A + "ue-cleanup-evidence.png"
};

const esc = value => value.replace(/[&<>"']/g, ch => ({"&":"&amp;","<":"&lt;",">":"&gt;","\"":"&quot;","'":"&#39;"}[ch]));
const shot = (src, cls = "") => `<div class="screenshot-frame ${cls}"><img src="${src}" alt="Actual Unreal Engine 5.8 screen evidence"></div>`;
const header = (eyebrow, title, version = true) => `<header class="topbar"><img src="${assets.icon}" alt="Server Manage Tool product icon"><div><div class="brand">Server Manage Tool</div><div class="version">${version ? "Version 1.1.2" : ""}</div></div><div class="badge">UE 5.8 · Win64</div></header><div class="eyebrow">${eyebrow}</div><h1>${title}</h1>`;
const footer = text => `<div class="footer">${esc(text)}</div>`;

function thumbnail() {
  return `<div class="thumb">${header("Local server workflows", "Reliable Local Server Workflows for Unreal Engine PIE")}
    <section class="grid two hero"><div class="hero-copy"><div class="rule"></div><p class="sub">Map-specific addresses, all-port preflight, and managed cleanup for Unreal Engine PIE.</p><p class="support">Map-specific addresses · all-port preflight · managed cleanup</p><div class="port-stack"><div class="port-card"><strong>7777</strong><span>Lobby · validated</span></div><div class="port-card"><strong>7778</strong><span>Match · validated</span></div></div></div><div>${shot(assets.settings, "hero-shot")}</div></section>${footer("Verified on UE 5.8 Win64 · actual Unreal Editor UI and measured run evidence")}</div>`;
}

function projectSettings() {
  return `<div class="gallery">${header("01 · Project Settings", "Configure Your Server List")}
    <section class="grid two content"><div class="left"><p class="headline">Map each Unreal level to the address your project should use.</p><div class="title-rule"></div>${shot(assets.settings, "wide-shot")}</div><div class="right side-stack"><div class="callout"><h3>Project Settings &gt; Project &gt; Servers</h3><p><code>/Game/Maps/Lobby</code><br>lobby.example.test:9001</p><p style="margin-top:14px"><code>/Game/Maps/Match</code><br>match.example.test:9002</p></div>${shot(assets.tree, "tree-inset")}<div class="callout"><p>Install as a project-local plugin: <code>YourProject / Plugins / ServerManageTool</code></p></div></div></section>${footer("Actual UE 5.8 Project Settings screen · example addresses are non-production placeholders")}</div>`;
}

function blueprintApi() {
  return `<div class="gallery">${header("02 · Blueprint API", "Resolve Server Addresses in Blueprint")}
    <section class="grid two content"><div class="left">${shot(assets.blueprint, "wide-shot")}<p class="mini-caption">Blueprint compile result: successful. Nodes are present without executing Request Server Exit.</p></div><div class="right side-stack"><div class="callout"><h3>Address lookup</h3><div class="check-list"><div class="check">Project Setting returns the configured address</div><div class="check">Local Launch returns loopback ports starting at 7777</div><div class="check">Null or missing maps return an empty string</div></div></div>${shot(assets.addressSearch, "search-inset")} ${shot(assets.exitSearch, "search-inset")}<div class="note">Request Server Exit should only be used in the server process.</div></div></section>${footer("Actual UE 5.8 Blueprint node discovery and compile evidence")}</div>`;
}

function localLaunch() {
  return `<div class="gallery">${header("03 · Local Launch", "Launch the Complete Local Server Group")}
    <section class="grid two content"><div class="left"><p class="headline">Every required UDP port is checked before any managed process starts.</p><div class="title-rule"></div>${shot(assets.local, "compact-shot")}<p class="mini-caption">Actual UE 5.8 Local Launch evidence.</p></div><div class="right side-stack"><div class="metric-row"><div class="metric"><b>7777</b><span>Lobby · requested = actual</span></div><div class="metric"><b>7778</b><span>Match · requested = actual</span></div></div><div class="port-stack"><div class="port-card"><strong>Validated</strong><span>SMT_PORT_VALIDATION_PASSED</span></div><div class="port-card"><strong>Ports Available</strong><span>SMT_PORT_PREFLIGHT_PASSED</span></div></div><div class="callout"><p>Ports Available = required UDP ports were available before launch.</p><p style="margin-top:10px">Validated = requested and actual bound ports matched.</p></div><div class="callout"><p>Two managed server processes were observed with the project-local host as parent.</p></div></div></section>${footer("Local Launch verification · 2 managed children · UDP 7777 / 7778")}</div>`;
}

function conflict() {
  return `<div class="gallery">${header("04 · Port Conflict", "Prevent Partial Launches")}
    <section class="grid two content"><div class="left">${shot(assets.conflict, "conflict-shot")}<p class="mini-caption">Actual UE 5.8 Output Log filtered to the preflight failure marker.</p><div class="diagram"><div class="diagram-row"><div class="node safe-node"><b>REQUIRED PORT</b>7777 free</div><div class="arrow">+</div><div class="node error-node"><b>REQUIRED PORT</b>7778 busy</div></div><div class="diagram-row"><div class="arrow">↓</div><div class="node error-node"><b>RESULT</b>Launch rejected before any managed child starts</div></div></div></div><div class="right side-stack"><p class="headline">If one required port is unavailable, no managed server from that launch attempt is started.</p><div class="title-rule"></div><div class="callout"><h3>Measured result</h3><div class="check-list"><div class="check">7778 unavailable</div><div class="check">SMT_PORT_PREFLIGHT_FAILED</div><div class="check">Managed children: 0</div><div class="check">The independent holder remained outside plugin cleanup</div></div></div><div class="scope"><p>No port shifting or partial launch is implied. The attempt is rejected before managed children start.</p></div></div></section>${footer("Preflight conflict evidence · holder cleanup was planned and verified separately")}</div>`;
}

function cleanup() {
  return `<div class="gallery">${header("05 · Cleanup and Scope", "Clean Editor Testing Workflows")}
    <section class="grid two content"><div class="left"><p class="headline">Managed server processes stop when PIE ends and are cleared during module shutdown.</p><div class="title-rule"></div>${shot(assets.cleanup, "wide-shot")}<p class="mini-caption">Actual post-End PIE cleanup evidence</p></div><div class="right side-stack"><div class="flow"><div class="node">Start PIE</div><div class="arrow">↓</div><div class="node safe-node">2 managed servers</div><div class="arrow">↓</div><div class="node">End PIE</div><div class="arrow">↓</div><div class="node safe-node">0 managed processes · 0 UDP owners</div></div><div class="scope"><h3>Editor / PIE only</h3><p>Does not build, deploy, or host production servers.</p><p style="margin-top:8px">A dedicated TargetType.Server executable is not included.</p></div></div></section>${footer("Process cleanup scope · actual editor screen plus measured lifecycle result")}</div>`;
}

const mode = new URLSearchParams(location.search).get("asset") || "thumbnail";
const pages = { thumbnail, settings: projectSettings, blueprint: blueprintApi, local: localLaunch, conflict, cleanup };
document.getElementById("canvas").innerHTML = (pages[mode] || thumbnail)();
