# Lab Report Control Engineering II (MCI)

Laborbericht „Modelling and Control of DC Motor Speed and Position“ mit der MCI-Klasse `mcidoc`.
Vorgaben und Formalkriterien: `CLAUDE.md`.

## Setup (einmal pro Rechner)
In PowerShell im Repo-Ordner ausführen:

    powershell -ExecutionPolicy Bypass -File .\setup.ps1

Das Skript installiert bei Bedarf MiKTeX, Strawberry Perl, Git und VS Code (winget), stellt MiKTeX
auf automatisches Nachladen fehlender Pakete und installiert die VS Code-Extensions aus
`.vscode/extensions.json` (LaTeX Workshop, LTeX+, Claude Code). VS Code schlägt diese Extensions
beim Öffnen des Ordners zusätzlich automatisch vor.

## Bauen
Ordner in VS Code öffnen, `main.tex` öffnen und speichern: LaTeX Workshop baut das PDF über
latexmk (pdfLaTeX + biber). Alternativ im Terminal: `latexmk -pdf main.tex`.

## Struktur
- `main.tex`: Metadaten, Kapitel-Includes, Verzeichnisse, List of Symbols
- `chapters/`: Kapitel und Anhang
- `data/`: Messdaten als CSV für die Diagramme, `img/`: Bilder
- `references.bib`: Quellen (IEEE)
- `Vorlagen.tex` / `Vorlagen.pdf`: Kopiervorlagen
