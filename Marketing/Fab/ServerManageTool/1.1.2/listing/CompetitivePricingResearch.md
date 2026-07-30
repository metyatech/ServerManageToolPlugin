# Public Fab Competitive and Pricing Research

## Method

Reviewed public Fab listing pages on 2026-07-30 JST. The sample covers products displayed under Tools & Plugins > Network & Multiplayer and Tools & Plugins > Engine Tools. Ratings and price labels are copied only when visible in the fetched public page. A page showing a license selector without a numeric amount is recorded as “not displayed”, not assigned an inferred price.

The sample is directional. It is not a complete market census and does not establish a Fab-approved price for Server Manage Tool.

## Network & Multiplayer sample

| Product | Publisher | Fab category | Visible tags | Visible price | Reviews | Positioning and difference |
| --- | --- | --- | --- | --- | --- | --- |
| Ultimate PlayFab Kit | AsRock Studios | Network & Multiplayer | Plugin, Connection, Multiplayer, Lobby, Session, Online, Platform | Not displayed in fetched page | No rating shown | PlayFab backend integration with authentication, economy, server, and player-data features; materially broader scope than local PIE process management. [Public listing](https://www.fab.com/listings/e27eb7e2-016a-46c1-8187-13eec65f98c0) |
| ODIN Voice Chat - Unreal Engine | 4Players GmbH | Network & Multiplayer | Sound, Immersive, Effect, Multiplayer, Apple, Mobile, Voice, Walkietalkie, Android, Radio, Audio, Occlusion, Chat, Spatial, Blueprint | Free | 4.4/5 from 8 ratings | Voice and spatial-audio service integration; different problem from local server launch and port preflight. [Public listing](https://www.fab.com/listings/79d0a208-78e8-4bd7-9214-36f6cc190da2?lang=en) |
| Multiplayer Server Scaling System | Eagle 3D Streaming | Network & Multiplayer | Multiplayer | Free | 4.2/5 from 6 ratings | Dedicated-server sessions, replication, routing, and deployment-oriented scaling; Server Manage Tool explicitly does not provide production deployment or replication. [Public listing](https://www.fab.com/listings/a66b7bdb-6a36-4f19-be9f-e96c6b143aa9?lang=en) |
| Server Administration Plugin | Talos Interactive | Network & Multiplayer | Multiplayer, Dedicated, Server, Control, Administration | Not displayed in fetched page | 3.0/5 from 1 rating | Runtime controls for connected server administrators; Server Manage Tool focuses on editor-local process launch and cleanup. [Public listing](https://www.fab.com/listings/7fd37887-d241-4c0e-b965-a50478079f17) |
| Multiplayer Server Browser - Master Server - Server Listing | MeoPlay | Network & Multiplayer | Master, Multiplayer, Dedicated, Server, Blueprint | Not displayed in fetched page | 5.0/5 from 8 ratings | External master-server registration and browsing; Server Manage Tool returns project-owned addresses and does not provide a server browser. [Public listing](https://www.fab.com/listings/550c0531-c353-484b-a536-91b750dd6b17) |
| Easy Replication | DropFrame | Network & Multiplayer | Plugin, Replicated, CodePlugin, Multiplayer, Network, Online, Blueprint | Not displayed in fetched page | 4.0/5 from 1 rating | Replication and Blueprint synchronization; Server Manage Tool does not add replication. [Public listing](https://www.fab.com/listings/6a3afd68-ccc8-45c4-b9b4-67362b61a18b) |
| Advanced Party System | Spyzn's Store | Network & Multiplayer | Replicated, Friend, Lobby, Session, Online, Party, Beacon, Steam | Not displayed in fetched page | 2.3/5 from 3 ratings | Party and lobby flow through sessions and beacons; Server Manage Tool does not implement matchmaking, parties, or online sessions. [Public listing](https://www.fab.com/listings/5afeb0bc-ca07-4213-a63a-166d55cfbd7c) |
| Server HTTP Pro | JailsonCarlos | Network & Multiplayer | Online, Server, Response, Manager | Not displayed in fetched page | 1.0/5 from 1 rating | HTTP/JSON communication with external services; Server Manage Tool uses local UDP preflight and process lifecycle instead. [Public listing](https://www.fab.com/listings/9503a5c7-294f-4598-9b7c-ce89aa87b2cf) |

## Engine Tools sample

| Product | Publisher | Fab category | Visible tags | Visible price | Reviews | Positioning and difference |
| --- | --- | --- | --- | --- | --- | --- |
| Actions Extension | Piperift | Engine Tools | Plugin, Editor, Action, CodePlugin, Gameplay, Network, Script, AI, Sync | Free | 4.6/5 from 29 ratings | Blueprint asynchronous actions and editor/debugger workflow; Server Manage Tool is a focused PIE server lifecycle utility. [Public listing](https://www.fab.com/listings/1cf70f09-46b0-4637-8cca-7dea55e65c93) |
| Asset Tags Command | Fizzle Interactive | Engine Tools | Plugin, Editor, Package, Tool | Free | No rating shown | Asset context-menu utility; not a networking or local-server workflow. [Public listing](https://www.fab.com/listings/99dcf517-18cd-46b6-86d1-f827b8aa3954) |
| Editor Utility Extension | Vahab Ahmadvand | Engine Tools | Custom, Editor, Widget, Button, CodePlugin, Menu, Utility, Tool, Plugin, Blueprint, Editorutilities | Not displayed in fetched page | 4.7/5 from 3 ratings | Editor menus, widgets, and utility extensions; shares Editor and Blueprint positioning but not server-process management. [Public listing](https://www.fab.com/listings/d7fa27c7-56b7-49fe-997c-702c1b6fdc17?lang=en) |
| Asset Batch Edit Plugin for UE4 Editor | Rama | Engine Tools | Plugin, Code | Not displayed in fetched page | 5.0/5 from 2 ratings | Batch asset editing for the editor; a workflow utility with a different buyer outcome and engine target. [Public listing](https://www.fab.com/listings/ef7ebda2-68c5-4c2f-9acd-c9e03b0846c6) |

## Observed tag labels

The following labels were visibly used by one or more public pages in this sample and are candidates for the listing tag selector:

- Plugin
- CodePlugin
- Blueprint
- Multiplayer
- Network
- Server
- Dedicated
- Editor
- Tool
- Development

The Fab UI remains authoritative for the final selectable tag set. "Testing" was not included because it was not observed in the reviewed public pages.

## Positioning conclusion

Server Manage Tool should be positioned as a narrow, transparent Editor/PIE workflow plugin rather than as a replication, online-service, voice, matchmaking, hosting, deployment, or production-server product. The USD 9.99 Personal and USD 29.99 Professional recommendation is consistent with that focused scope and is documented separately in PricingDecision.md.
