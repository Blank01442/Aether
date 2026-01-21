# Aether One-Click Installer Script
Write-Host "🌌 Connecting to Aether Cloud..." -ForegroundColor Cyan
$setup_url = "https://github.com/Blank01442/Aether/raw/main/setup.exe"
$dest = "$HOME\Desktop\Aether_Setup.exe"

Invoke-WebRequest -Uri $setup_url -OutFile $dest
Write-Host "✅ Setup Wizard Downloaded to Desktop." -ForegroundColor Green
Write-Host "🚀 Launching Aether Universal Setup v2.9.7..." -ForegroundColor Cyan

Start-Process $dest -Wait
Write-Host "🎉 Installation Script Complete." -ForegroundColor Green
