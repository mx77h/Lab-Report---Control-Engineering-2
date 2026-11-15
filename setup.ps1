# =====================================================================
#  Einmaliges Setup für dieses Repo (Windows), ähnlich wie requirements.txt
#
#  Ausführen in PowerShell im Repo-Ordner:
#      powershell -ExecutionPolicy Bypass -File .\setup.ps1
#
#  Installiert (falls noch nicht vorhanden) per winget:
#    - MiKTeX           LaTeX-Distribution inkl. latexmk, biber, pdfLaTeX/LuaLaTeX
#    - Strawberry Perl  wird von latexmk unter Windows benötigt
#    - Git              Versionsverwaltung inkl. Git Bash
#    - VS Code          Editor
#  Danach:
#    - MiKTeX lädt fehlende LaTeX-Pakete automatisch nach
#    - VS Code-Extensions aus .vscode/extensions.json werden installiert
# =====================================================================

$ErrorActionPreference = 'Continue'

function Update-SessionPath {
    $env:Path = [Environment]::GetEnvironmentVariable('Path', 'Machine') + ';' +
                [Environment]::GetEnvironmentVariable('Path', 'User')
}

if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
    Write-Host 'winget nicht gefunden. Bitte "App Installer" aus dem Microsoft Store installieren.' -ForegroundColor Red
    exit 1
}

# ---------- 1. Programme ----------
$programs = @(
    @{ Id = 'MiKTeX.MiKTeX';                Command = 'latexmk' },
    @{ Id = 'StrawberryPerl.StrawberryPerl'; Command = 'perl'    },
    @{ Id = 'Git.Git';                      Command = 'git'     },
    @{ Id = 'Microsoft.VisualStudioCode';   Command = 'code'    }
)

foreach ($p in $programs) {
    if (Get-Command $p.Command -ErrorAction SilentlyContinue) {
        Write-Host "OK      $($p.Id) ist bereits installiert." -ForegroundColor Green
    } else {
        Write-Host "INSTALL $($p.Id) ..." -ForegroundColor Yellow
        winget install --id $p.Id --exact --accept-package-agreements --accept-source-agreements
    }
}
Update-SessionPath

# ---------- 2. MiKTeX: fehlende Pakete automatisch installieren ----------
if (Get-Command initexmf -ErrorAction SilentlyContinue) {
    initexmf --set-config-value '[MPM]AutoInstall=1'
    Write-Host 'OK      MiKTeX installiert fehlende Pakete automatisch.' -ForegroundColor Green
} else {
    Write-Host 'HINWEIS MiKTeX-Befehle noch nicht im PATH: PowerShell neu öffnen und Skript erneut starten.' -ForegroundColor Yellow
}

# ---------- 3. VS Code-Extensions aus .vscode/extensions.json ----------
$extFile = Join-Path $PSScriptRoot '.vscode\extensions.json'
if ((Get-Command code -ErrorAction SilentlyContinue) -and (Test-Path $extFile)) {
    # Kommentare entfernen, dann JSON lesen
    $json = (Get-Content $extFile -Raw) -replace '(?m)\s*//.*$', ''
    $ids  = ($json | ConvertFrom-Json).recommendations
    foreach ($id in $ids) {
        code --install-extension $id --force | Out-Null
        Write-Host "OK      VS Code-Extension $id" -ForegroundColor Green
    }
} else {
    Write-Host 'HINWEIS VS Code noch nicht im PATH: PowerShell neu öffnen und Skript erneut starten.' -ForegroundColor Yellow
}

Write-Host ''
Write-Host 'Fertig. Ordner in VS Code öffnen, main.tex öffnen und speichern -> PDF wird gebaut.' -ForegroundColor Cyan
